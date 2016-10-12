#ifndef SOFTWARERENDERINGBASIC_HPP_INCLUDED
#define SOFTWARERENDERINGBASIC_HPP_INCLUDED

#include <Fantasy2C/Basic.hpp>
#include <Fantasy2C/Color4.hpp>
#include <Fantasy2C/Rect.hpp>
#include <Fantasy2C/Vector4.hpp>
#include <Fantasy2C/Matrix3.hpp>
#include <Fantasy2C/Matrix4.hpp>
#include <Fantasy2C/Texture2D.hpp>

namespace F2C{
    class GenMappingTex{
        public:
        GLenum genu;
        GLenum genv;

        GenMappingTex():
            genu(GL_OBJECT_LINEAR),
            genv(GL_OBJECT_LINEAR)
        {}
    };

    class Vertex{
        public:
        Vector4<float> pos;    // Coordinate
        Vector3<float> nml;    // Normal
        Color4ub clr;     // Color
        std::vector< Vector4<float> > map;   // Texture map coordinate

        Vertex(size_t mapsize = 1):
            map(mapsize,Vector4<float> (0,0,0,1))
        {}
    };

}

#endif // SOFTWARERENDERINGBASIC_HPP_INCLUDED
