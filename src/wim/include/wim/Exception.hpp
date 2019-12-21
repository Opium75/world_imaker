//
// Created by piptouque on 02/12/2019.
//

#ifndef WORLD_IMAKER_EXCEPTION_HPP
#define WORLD_IMAKER_EXCEPTION_HPP

#pragma once

#include <cstring>
#include <string>
#include <exception>

namespace wim
{
    enum class ExceptCode
    {
        INIT_ERROR,
        OUT_OF_RANGE,
        DOMAIN_ERROR,
        NULL_POINTER,
        END_OF_FILE,
        CATASTROPHIC_FAILURE
    };


    class Exception : public std::exception
    {
    public:
        typedef int ExceptLvl;
    private:
        const ExceptCode _code;
        const ExceptLvl  _lvl;
        const std::string _msg;

    public:
        Exception(const ExceptCode& code, const ExceptLvl lvl, const std::string& msg) noexcept
            : _code(code), _lvl(lvl), _msg(msg)
        {}
        Exception(const Exception& except) noexcept
            : _code(except._code), _lvl(except._lvl), _msg(except._msg)
        {}

        virtual ~Exception() noexcept {}

        inline ExceptLvl getLevel() const noexcept {return _lvl;}
        inline const ExceptCode& getCode() const noexcept {return _code;}
        inline const std::string& getMsg() const noexcept {return _msg;}

        const char* what() const noexcept override
        {
            return _msg.c_str();
        }
    };

}

#endif //WORLD_IMAKER_EXCEPTION_HPP
