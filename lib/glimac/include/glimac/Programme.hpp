#pragma once

#include <GL/glew.h>
#include "Shader.hpp"
#include "FilePath.hpp"

namespace glimac {

class Programme {
public:
	Programme(): m_nGLId(glCreateProgram()) {
	}

	~Programme() {
		glDeleteProgram(m_nGLId);
	}

    Programme(Programme&& rvalue): m_nGLId(rvalue.m_nGLId) {
        rvalue.m_nGLId = 0;
	}

	Programme& operator =(Programme&& rvalue) {
		m_nGLId = rvalue.m_nGLId;
		rvalue.m_nGLId = 0;
		return *this;
	}

	GLuint getGLId() const {
		return m_nGLId;
	}

	void attachShader(const Shader& shader) {
		glAttachShader(m_nGLId, shader.getGLId());
	}

	bool link();

	const std::string getInfoLog() const;

	void use() const {
		glUseProgram(m_nGLId);
	}

private:
	Programme(const Programme&);
	Programme& operator =(const Programme&);

	GLuint m_nGLId;
};

// Build a GLSL program from source code
Programme buildProgramme(const GLchar* vsSrc, const GLchar* fsSrc);

// Load source code from files and build a GLSL program
Programme loadProgramme(const FilePath& vsFile, const FilePath& fsFile);


}
