#ifndef COLOR3_HPP_INCLUDED
#define COLOR3_HPP_INCLUDED

#include <Fantasy2C/operatorMacros.hpp>
#include <Fantasy2C/Color.hpp>

namespace F2C{
    typedef Color Color4ub;

    /**
    *@class Color3i
    *@brief Color (RGB) as Integer \n
    *Red  \n
    *Green  \n
    *Blue  \n
    */
    class DLL Color3i{
        public:
        int r,g,b;

        Color3i();
        Color3i(int r,int g,int b);
        Color3i(const Color4ub& col);

        DEF_ASS_OPERATOR(Color3i)
        DEF_ASS_OPERATOR_T(Color3i,int)
    };

    DEFDLL_G_OPERATOR(Color3i)
    DEFDLL_G_OPERATOR_T(Color3i,int)

    /**
    *@class Color3f
    *@brief Color (RGB) as float \n
    *Red 0.0-1.0 \n
    *Green 0.0-1.0 \n
    *Blue 0.0-1.0 \n
    *Alpha 0.0-1.0 \n
    */
    class DLL Color3f{
        public:
        float r,g,b;

        Color3f();
        Color3f(float r,float g,float b);
        Color3f(const Color4ub& col);

        DEF_ASS_OPERATOR(Color3f)
        DEF_ASS_OPERATOR_T(Color3f,float)
    };

    DEFDLL_G_OPERATOR(Color3f)
    DEFDLL_G_OPERATOR_T(Color3f,float)

    /**
    *@class Color3d
    *@brief Color (RGB) as double \n
    *Red 0.0-1.0 \n
    *Green 0.0-1.0 \n
    *Blue 0.0-1.0 \n
    */
    class DLL Color3d{
        public:
        double r,g,b;

        Color3d();
        Color3d(double r,double g,double b);
        Color3d(const Color3f& col);
        Color3d(const Color4ub& col);

        DEF_ASS_OPERATOR(Color3d)
        DEF_ASS_OPERATOR_T(Color3d,double)
    };

    DEFDLL_G_OPERATOR(Color3d)
    DEFDLL_G_OPERATOR_T(Color3d,double)
}

#endif // COLOR3_HPP_INCLUDED
