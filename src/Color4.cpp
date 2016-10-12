#include <Fantasy2C/Color.hpp>
#include <Fantasy2C/Color4.hpp>

namespace F2C{

    Color4i::Color4i():
        r(0),
        g(0),
        b(0),
        a(0)
    {}

    Color4i::Color4i(int r,int g,int b):
        r(r),
        g(g),
        b(b),
        a(1)
    {}

    Color4i::Color4i(int r,int g,int b,int a):
        r(r),
        g(g),
        b(b),
        a(a)
    {}

    Color4i::Color4i(const Color3i& col):
        r(col.r),
        g(col.g),
        b(col.b),
        a(1)
    {}

    Color4i::Color4i(const Color4ub& col):
        r(col.red),
        g(col.green),
        b(col.blue),
        a(col.alpha)
    {}

    ASS_OPERATOR(Color4i)
    ASS_OPERATOR_T(Color4i,int)

    G_OPERATOR4(Color4i,r,g,b,a)
    G_OPERATOR_T4(Color4i,int,r,g,b,a)

    Color4f::Color4f():
        r(0.0f),
        g(0.0f),
        b(0.0f),
        a(0.0f)
    {}

    Color4f::Color4f(float r,float g,float b):
        r(r),
        g(g),
        b(b),
        a(1.0f)
    {}

    Color4f::Color4f(float r,float g,float b,float a):
        r(r),
        g(g),
        b(b),
        a(a)
    {}

    Color4f::Color4f(const Color3f& col):
        r(col.r),
        g(col.g),
        b(col.b),
        a(1.0f)
    {}

    Color4f::Color4f(const Color4ub& col):
        r(col.red/255.0f),
        g(col.green/255.0f),
        b(col.blue/255.0f),
        a(col.alpha/255.0f)
    {}

    ASS_OPERATOR(Color4f)
    ASS_OPERATOR_T(Color4f,float)

    G_OPERATOR4(Color4f,r,g,b,a)
    G_OPERATOR_T4(Color4f,float,r,g,b,a)

    Color4d::Color4d():
        r(0.0f),
        g(0.0f),
        b(0.0f),
        a(0.0f)
    {}

    Color4d::Color4d(double r,double g,double b):
        r(r),
        g(g),
        b(b),
        a(1.0f)
    {}

    Color4d::Color4d(double r,double g,double b,double a):
        r(r),
        g(g),
        b(b),
        a(a)
    {}

    Color4d::Color4d(const Color3d& col):
        r(col.r),
        g(col.g),
        b(col.b),
        a(1.0f)
    {}

    Color4d::Color4d(const Color4f& col):
        r(col.r),
        g(col.g),
        b(col.b),
        a(col.a)
    {}

    Color4d::Color4d(const Color4ub& col):
        r(col.red/255.0f),
        g(col.green/255.0f),
        b(col.blue/255.0f),
        a(col.alpha/255.0f)
    {}

    ASS_OPERATOR(Color4d)
    ASS_OPERATOR_T(Color4d,double)

    G_OPERATOR4(Color4d,r,g,b,a)
    G_OPERATOR_T4(Color4d,double,r,g,b,a)

}
