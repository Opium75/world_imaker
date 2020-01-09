//
// Created by piptouque on 09/01/2020.
//

#include "../include/wim/RadialFunctor.hpp"

namespace wim
{

    RadialMethod getNextMethod(const RadialMethod method)
    {
        return static_cast<RadialMethod >(
                (static_cast<SizeInt>(method)+1)%NB_RADIALMETHODS
                );
    }

    std::string toString(const RadialMethod method)
    {
        switch(method)
        {
            case RadialMethod::LINEAR :
                return std::string("LINEAR");
            case RadialMethod::MULTIQUADRIC:
                return std::string("MULTIQUADRIC");
            case RadialMethod::INVERT_MULTIQUADRIC:
                return std::string("INVERTED_MULTIQUADRIC");
            case RadialMethod::GAUSSIAN:
                return std::string("GAUSSIAN");
            default:
                return std::string("UNKNOWN");

        }
    }

    std::ostream& operator<<(std::ostream& out, const RadialMethod method)
    {
        out << toString(method);
        return out;
    }
}