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
        OUT_OF_RANGE
    };


    class Exception : public std::exception
    {
    public:
        typedef int ExceptLvl;
    private:
        const ExceptLvl  _lvl;
        const ExceptCode _code;
        const std::string _msg;

    public:
        Exception(const ExceptLvl lvl, const ExceptCode& code, const std::string& msg) noexcept
            : _lvl(lvl), _code(code), _msg(msg)
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
