#ifndef COLOR4_HPP_INCLUDED
#define COLOR4_HPP_INCLUDED

#include <Fantasy2C/Color.hpp>
#include <Fantasy2C/Color3.hpp>

namespace F2C{

    /**
    *@class Color4i
    *@brief Color (RGBA) as Integer \n
    *Red  \n
    *Green  \n
    *Blue  \n
    *Alpha  \n
    */
    class Color4i{
        public:
        int r,g,b,a;

        Color4i();
        Color4i(int r,int g,int b);
        Color4i(int r,int g,int b,int a);
        Color4i(const Color3i& col);
        Color4i(const Color4ub& col);

        DEF_ASS_OPERATOR(Color4i)
        DEF_ASS_OPERATOR_T(Color4i,int)
    };

    DEFDLL_G_OPERATOR(Color4i)
    DEFDLL_G_OPERATOR_T(Color4i,int)

    /**
    *@class Color4f
    *@brief Color (RGBA) as float \n
    *Red 0.0-1.0 \n
    *Green 0.0-1.0 \n
    *Blue 0.0-1.0 \n
    *Alpha 0.0-1.0 \n
    */
    class Color4f{
        public:
        float r,g,b,a;

        Color4f();
        Color4f(float r,float g,float b);
        Color4f(float r,float g,float b,float a);
        Color4f(const Color3f& col);
        Color4f(const Color4ub& col);

        DEF_ASS_OPERATOR(Color4f)
        DEF_ASS_OPERATOR_T(Color4f,float)
    };

    DEFDLL_G_OPERATOR(Color4f)
    DEFDLL_G_OPERATOR_T(Color4f,float)

    /**
    *@class Color4d
    *@brief Color (RGBA) as double \n
    *Red 0.0-1.0 \n
    *Green 0.0-1.0 \n
    *Blue 0.0-1.0 \n
    *Alpha 0.0-1.0 \n
    */
    class Color4d{
        public:
        double r,g,b,a;

        Color4d();
        Color4d(double r,double g,double b);
        Color4d(double r,double g,double b,double a);
        Color4d(const Color3d& col);
        Color4d(const Color4f& col);
        Color4d(const Color4ub& col);

        DEF_ASS_OPERATOR(Color4d)
        DEF_ASS_OPERATOR_T(Color4d,double)
    };

    DEFDLL_G_OPERATOR(Color4d)
    DEFDLL_G_OPERATOR_T(Color4d,double)

}

#endif // COLOR4_HPP_INCLUDED
