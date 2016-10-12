#include <Fantasy2C/Color3.hpp>

namespace F2C{

    Color3i::Color3i():
        r(0),
        g(0),
        b(0)
    {}

    Color3i::Color3i(int r,int g,int b):
        r(r),
        g(g),
        b(b)
    {}

    Color3i::Color3i(const Color4ub& col):
        r(col.red),
        g(col.green),
        b(col.blue)
    {}

    ASS_OPERATOR(Color3i,col)
    ASS_OPERATOR_T(Color3i,int,col)

    G_OPERATOR(Color3i,col1,col2,r,g,b)
    G_OPERATOR_T(Color3i,col1,int,col2,r,g,b)

    Color3f::Color3f():
        r(0.0f),
        g(0.0f),
        b(0.0f)
    {}

    Color3f::Color3f(float r,float g,float b):
        r(r),
        g(g),
        b(b)
    {}

    Color3f::Color3f(const Color4ub& col):
        r(col.red/255.0f),
        g(col.green/255.0f),
        b(col.blue/255.0f)
    {}

    ASS_OPERATOR(Color3f,col)
    ASS_OPERATOR_T(Color3f,float,col)

    G_OPERATOR(Color3f,col1,col2,r,g,b)
    G_OPERATOR_T(Color3f,col1,float,col2,r,g,b)

    Color3d::Color3d():
        r(0.0f),
        g(0.0f),
        b(0.0f)
    {}

    Color3d::Color3d(double r,double g,double b):
        r(r),
        g(g),
        b(b)
    {}

    Color3d::Color3d(const Color3f& col):
        r(col.r),
        g(col.g),
        b(col.b)
    {}

    Color3d::Color3d(const Color4ub& col):
        r(col.red/255.0f),
        g(col.green/255.0f),
        b(col.blue/255.0f)
    {}

    ASS_OPERATOR(Color3d,col)
    ASS_OPERATOR_T(Color3d,double,col)

    G_OPERATOR(Color3d,col1,col2,r,g,b)
    G_OPERATOR_T(Color3d,col1,double,col2,r,g,b)
}
