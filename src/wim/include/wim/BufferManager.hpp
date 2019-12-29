//
// Created by piptouque on 24/12/2019.
//

#ifndef WORLD_IMAKER_BUFFERMANAGER_HPP
#define WORLD_IMAKER_BUFFERMANAGER_HPP

#pragma once

#include <vector>
#include <memory>

#include "CommunDisplay.hpp"

#include "ShaderSender.hpp"
#include "TextureManager.hpp"

#include "Material.hpp"
#include "Light.hpp"
#include "Types.hpp"

namespace wim
{

    struct CameraMatricesData
    {
        UniformMatrix _MVP, _MV, _Normal;
        CameraMatricesData(const UniformMatrix& MV, const UniformMatrix& Proj) :
            _MVP(Proj*MV), _MV(MV), _Normal(glm::transpose(glm::inverse(MV)))
        {
        }
    };

    struct MaterialData
    {
        glm::vec3 _colour;
        GLfloat _isTextured; //used as boolean
        glm::vec4 _kD;
        glm::vec3 _kS;
        GLfloat _shininess;
        MaterialData(const Material& material, const bool isTextured) :
            _colour(material.colour().getCoord()), _isTextured(isTextured), _kD(material.kD().getCoord(),0), _kS(material.kS().getCoord()), _shininess(material.shininess())
        {
        }
    };

    struct AmbiantLightData
    {
        glm::vec3 _intensity;
        AmbiantLightData(const AmbiantLight& ambiant):
           _intensity(ambiant.intensity().getCoord())
        {
        }
    };

    /** NOTE: I can't get the shaders to recognise the sizes
       * of the two SSBO, apparently I(m not the only one with this issue:
       * https://gamedev.stackexchange.com/questions/96224/opengl-shader-storage-buffer-objects-array-length-problem
       * Anyway, sending the sizes as a different SSBO is a fine work-around.
       * **/
    struct LightNumberData
    {
        GLint _nbPoints;
        GLint _nbDirs;
        LightNumberData(const GLint nbPoints, const GLint nbDirs) :
            _nbPoints(nbPoints), _nbDirs(nbDirs) {}

    };

    struct PointLightData
    {
        glm::vec4 _intensity;
        glm::vec4 _origin_ms;

        PointLightData(const PointLight& pLight) :
                _intensity(pLight.intensity().getCoord(),0.f), _origin_ms(pLight.origin().getCoord(),1.f)
                {}

        inline  const glm::vec4& origin() const {return _origin_ms;}
        inline  glm::vec4& origin() {return _origin_ms;}
    };
    struct DirectionLightData
    {
        glm::vec4 _intensity;
        glm::vec4 _direction_ms;

        DirectionLightData(const DirectionLight &dLight) :
                _intensity(dLight.intensity().getCoord(), 0), _direction_ms(dLight.direction().getCoord(),0.f)
        {}
        inline  const glm::vec4& direction() const {return _direction_ms;}
        inline  glm::vec4& direction() {return _direction_ms;}
    };

    typedef std::vector<PointLightData> ListPLightData;
    typedef std::vector<DirectionLightData> ListDLightData;

    /*Names of uniform attributs as they are used in the shaders
     * For now, we will only support one light source. IN POINT LIGHT
     */
    //MATRICES
    static constexpr const char* UNI_BLOCK_MATRICES_NAME = "bMatrices";
    //MATERIAL
    static constexpr const char* UNI_BLOCK_MATERIAL_NAME = "bMaterial";
    //BASE TEXTURE
    static constexpr const char* UNI_LOC_BASETEXTURE_NAME = "uBaseTexture";
    /* LIGHTs
     * One ambiant, and multiple point and directional lights
     * (using shader storage buffers; see Light.hpp for storage details.)
     */
    static constexpr const char* UNI_BLOCK_AMBIANTLIGHT_NAME = "bAmbiantLight";

    static constexpr const char* STORAGE_BLOCK_POINTLIGHT_NAME = "sPointLight";
    static constexpr const char* STORAGE_BLOCK_DIRECTIONLIGHT_NAME = "sDirectionLight";
    static constexpr const char* STORAGE_BLOCK_LIGHTNUMBER_NAME = "sLightNumber";
    /* SEE STD140 FOR DETAILS ON OFFSETS AND SIZES
     * AS HANDLED BY GLSL
     */

    //UBOs
    static const GLuint BINDING_MATRICES_INDEX = 0;
    static const GLuint BINDING_MATERIAL_INDEX = 1;
    static const GLuint BINDING_AMBIANTLIGHT_INDEX = 2;

    //SSBOs
    static const GLuint BINDING_LIGHTNUMBER_INDEX = 0;
    static const GLuint BINDING_POINTLIGHT_INDEX = 1;
    static const GLuint BINDING_DIRECTIONLIGHT_INDEX = 2;


    static const GLsizeiptr DEFAULT_MATRICES_BUFFERSIZE = sizeof(CameraMatricesData);
    static const GLsizeiptr DEFAULT_MATERIAL_BUFFERSIZE = sizeof(MaterialData);
    static const GLsizeiptr DEFAULT_AMBIANTLIGHT_BUFFERSIZE = sizeof(AmbiantLightData);

    static const GLsizeiptr DEFAULT_LIGHTNUMBER_BUFFERSIZE = sizeof(LightNumberData);
    static const GLsizeiptr DEFAULT_ONE_POINTLIGHT_BUFFERSIZE = sizeof(PointLightData);
    static const GLsizeiptr DEFAULT_ONE_DIRECTIONALLIGHT_BUFFERSIZE = sizeof(DirectionLightData);


    struct Uniform
    {
    public:
        GLint _uId;
    public:
        Uniform()
        {
        }
        ~Uniform() = default;

        void localise(const GLuint programme, const char* uniAttrName);
        void update(const GLint texId ) const;

    };
    struct UBO
    {
    public:
        GLuint _ubo;
    public:
        UBO(const GLsizeiptr size) : _ubo()
        {
            glGenBuffers(1, &_ubo);
            this->alloc(size);

        }
        ~UBO() {glDeleteBuffers(1,&_ubo);}


        void bind(const GLuint programme, const char* uniBufferName, const GLuint binding) const;
        void alloc(const GLsizeiptr size) const;
        void update(const GLvoid* data,  const GLsizeiptr size) const;
    private:
        void bindBlock(const GLuint programme, const char* uniBufferName, const GLuint binding) const;
        void bindObject(const GLuint binding) const;
    };

    struct SSBO
    {
    public:
        GLuint _ssbo;
    public:
        SSBO(const GLsizeiptr size, const SizeInt max) : _ssbo()
        {
            glGenBuffers(1, &_ssbo);
            this->alloc(size, max);
        }
        ~SSBO() {glDeleteBuffers(1, &_ssbo);}

        void alloc(const GLsizeiptr size, const SizeInt max) const;
        void bind(const GLuint programme, const char* storageBufferName, const GLuint binding) const;
        void update(const GLvoid* data, const GLsizeiptr size, const SizeInt nbUpdate) const;

    private:
        void bindObject(const GLuint binding) const;
        void bindBlock(const GLuint programme, const char* storageBufferName, const GLuint binding) const;

    };

    ///BRIEF: A classof Texture objects using CUBEMAPS
    class ITO
    {
    public:
        GLuint _ito;
    public:
        ITO(){glGenTextures(1, &_ito);}
        ~ITO(){glDeleteTextures(1, &_ito);}

        void loadFace(const SizeInt indexFace, GLvoid *data, const GLsizei width, const GLsizei height) const;

        void setParameters() const;
    };

    typedef std::vector<ITO> ListITO;
    typedef std::shared_ptr<ListITO> ListITOPtr;

    class BufferManager
    {
    public:
    private:
        ListITOPtr _itos;
        UBO _matrices, _material, _ambiantLight;
        Uniform _baseTexture;
        SSBO _pointLights, _directionLights;
        SSBO _lightNumber;
    public:

        BufferManager(const TextureManagerPtr& textures) :
            _itos(std::make_shared<ListITO>(textures->getCubeMaps().size())),
            _matrices(DEFAULT_MATRICES_BUFFERSIZE),
            _material(DEFAULT_MATERIAL_BUFFERSIZE),
            _ambiantLight(DEFAULT_AMBIANTLIGHT_BUFFERSIZE),
            _baseTexture(),
            _pointLights(DEFAULT_ONE_POINTLIGHT_BUFFERSIZE, MAX_NB_EACH_LIGHT),
            _directionLights(DEFAULT_ONE_DIRECTIONALLIGHT_BUFFERSIZE, MAX_NB_EACH_LIGHT),
            _lightNumber(DEFAULT_LIGHTNUMBER_BUFFERSIZE,1)
        {
            this->loadCubeMaps(textures->getCubeMaps());
        }
        ~BufferManager() = default;


        ///brief; update MV, MVP, Normal and View matrices to shaders
        void updateMatrices(const UniformMatrix& MV, const UniformMatrix& Proj ) const;
        void updateMaterial(const Material& material, const bool isTextured) const;
        void updateLights(const LightManager& lights, const UniformMatrix& View ) const;
        void bindShaders(const ListSender& shaders) const;
        void localiseUniform(const ShaderSender& shader);

        void loadCubeMaps(const ListCubeMap& cubeMaps) const;

        inline ListITOPtr& getListITO() {return _itos;}

    private:
        void updateAmbiantLight(const AmbiantLight& ambiant) const;
        void updateLightNumber(const ListPLight& pLights, const ListDLight& dLights) const;
        void updatePointLights(const ListPLight& pLights, const UniformMatrix& View) const;
        void updateDirectionLights(const ListDLight& dLights, const UniformMatrix& View) const;

        void loadCubeMap(const SizeInt indexTexture, const CubeMap& cubeMap) const;
        void loadFace(const SizeInt indexFace, const SizeInt indexTexture, const CubeMap& cubeMap) const;

        void bindShader(const ShaderSender& shader) const;
    };

    typedef std::unique_ptr<BufferManager> BufferManagerPtr;
}

#endif //WORLD_IMAKER_BUFFERMANAGER_HPP
