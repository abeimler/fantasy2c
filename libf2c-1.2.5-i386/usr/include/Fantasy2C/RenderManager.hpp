#ifndef RENDERMANAGER_HPP_INCLUDED
#define RENDERMANAGER_HPP_INCLUDED

#include <Fantasy2C/Basic.hpp>
#include <Fantasy2C/Color.hpp>
#include <Fantasy2C/Rect.hpp>
#include <Fantasy2C/Bitmap.hpp>

namespace F2C{

/**
*@class RenderManager
*@brief Some usefull Rendering functions. (OpenGL Functions)
*/
class DLL RenderManager{
    public:

    /**
    *@param enable Enable/Disable
    *@brief Enable/Disable GL_TEXTURE_2D (glEn/Disable(GL_TEXTURE_2D))
    */
    static void enable2DTexture(bool enable);

    /**
    *@param enable Enable/Disable
    *@brief Enable/Disable GL_SCISSOR_TEST (glEn/Disable(GL_SCISSOR_TEST))
    */
    static void enableScissor(bool enable);

    /**
    *@param enable Enable/Disable
    *@brief Enable/Disable GL_STENCIL_TEST (glEn/Disable(GL_STENCIL_TEST))
    */
    static void enableStencil(bool enable);

    /**
    *@brief clear stencil-buffer and set stencil option
    */
    static void startStencil();

    /**
    *@brief clear stencil-buffer
    */
    static void clearStencil();

    /**
    *@brief prevents writing to the stencil-buffer
    */
    static void endStencil();

    /**
    *@param texture Texture Name
    *@brief Bind a named texture
    */
    static void bindTexture(GLuint texture);

    /**
    *@param param Texture parameter
    *@brief Set texture parameter (glTexParameter)
    */
    static void setTexParam(TexParam::Tex_Param param);

    /**
    *@param type Blending Function Type
    *@brief set Blend Function (glBlendFunc)
    */
    static void setBlendFunc(BlendType::Blend_Type type);

    /**
    *@param x x-Coordinate
    *@param y y-Coordinate
    *@param z z-Coordinate
    *@param width Width of texture (in pixels)
    *@param height Height of texture (in pixels)
    *@param angle_x x-axes rotation, angle in degrees
    *@param angle_y y-axes rotation, angle in degrees
    *@param angle_z z-axes rotation, angle in degrees
    *@param zoom_x scale factors along the x-axes
    *@param zoom_y scale factors along the y-axes
    *@brief Set coordinate,rotation and scaling the matrix. (glTranslate,glRotate,glScale)
    */
    static void setCoord(GLdouble x,GLdouble y,GLdouble z,
                            GLuint width,GLuint height,
                            GLdouble angle_x,GLdouble angle_y,GLdouble angle_z,
                            GLdouble zoom_x,GLdouble zoom_y);

    /**
    *@param texcoords Array of texcoords (Size: 8) {x1,y1,  x2,y2,  x3,y3,  x4,y4}
    *@param tcx texture coordinate: x
    *@param tcy texture coordinate: y
    *@param tcwidth texture coordinate: width
    *@param tcheight texture coordinate: height
    *@param texturewidth Width of texture (in pixels)
    *@param textureheight Height of texture (in pixels)
    *@brief Set texture coordinate of array
    */
    static void getTexCoordArray8(GLdouble* texcoords,GLdouble tcx,
                                    GLdouble tcy,GLdouble tcwidth,GLdouble tcheight,
                                    GLdouble texturewidth,GLdouble textureheight);
    /**
    *@param texcoords Array of texcoords (Size: 8) {x1,y1,  x2,y2,  x3,y3,  x4,y4}
    *@param coord texture coordinate
    *@param texturewidth Width of texture (in pixels)
    *@param textureheight Height of texture (in pixels)
    *@brief Set texture coordinate of array
    */
    static void getTexCoordArray8(GLdouble* texcoords,Rect coord,
                                    GLdouble texturewidth,GLdouble textureheight);

    /**
    *@param vertices Array of vertices (Size: 12) {x1,y1,  x2,y2,  x3,y3,  x4,y4}
    *@param x vertex coordinate: x
    *@param y vertex coordinate: y
    *@param width vertex width
    *@param height vertex height
    *@brief Set vertices of array
    */
    static void getVerticesArray8(GLdouble* vertices,GLdouble x,GLdouble y,GLdouble width,GLdouble height);

    /**
    *@param vertices Array of vertices (Size: 12) {x1,y1,  x2,y2,  x3,y3,  x4,y4}
    *@param vertex vertex coordinate
    *@brief Set vertices of array
    */
    static void getVerticesArray8(GLdouble* vertices,Rect vertex);

    /**
    *@param vertices Array of vertices (Size: 12) {x1,y1,z1,  x2,y2,z2,  x3,y3,z3,  x4,y4,z4}
    *@param x vertex coordinate: x
    *@param y vertex coordinate: y
    *@param z vertex coordinate: z
    *@param width vertex width
    *@param height vertex height
    *@brief Set vertices of array
    */
    static void getVerticesArray12(GLdouble* vertices,GLdouble x,GLdouble y,GLdouble z,GLdouble width,GLdouble height);

    /**
    *@param texcoords Array of texcoords (Size: 8) {x1,y1,  x2,y2,  x3,y3,  x4,y4}
    *@brief flipped Flipped texture horizontal
    */
    static void flippedHTexCoord8(GLdouble* texcoords);

    /**
    *@param texcoords Array of texcoords (Size: 8) {x1,y1,  x2,y2,  x3,y3,  x4,y4}
    *@brief flipped Flipped texture vertical
    */
    static void flippedVTexCoord8(GLdouble* texcoords);

    /**
    *@param colors Array of colors(RGB) (Size: 3*srccolorsize) {r,g,b,  r,g,b,  r,g,b,  ...}
    *@param srccolors Source Color
    *@param colorsize Numbers of Colors in colors Array
    *@param srccolorsize Numbers of Source Colors
    *@brief Set color of array (copy from Source Colors)
    */
    static void getColorArray3(GLubyte* colors,const Color* srccolors,size_t colorsize,size_t srccolorsize);

    /**
    *@param colors Array of colors(RGBA) (Size: 4*colorsize) {r,g,b,a,  r,g,b,a,  r,g,b,a,  ...}
    *@param srccolors Source Color
    *@param colorsize Numbers of Colors in colors Array
    *@param srccolorsize Numbers of Source Colors
    *@brief Set color of array (copy from Source Colors)
    */
    static void getColorArray4(GLubyte* colors,const Color* srccolors,size_t colorsize,size_t srccolorsize);

    /**
    *@param colors 4 Array of colors(RGBA) (Size: 4*4*quadnumbers) { {r,g,b,a,  r,g,b,a,  r,g,b,a,  r,g,b,a},  {r,g,b,a,  r,g,b,a,  r,g,b,a,  r,g,b,a}, ...}
    *@param srccolors Source Color
    *@param srccolorsize Numbers of Source Colors
    *@param quadnumbers Numbers of Quads
    *@brief Set color of array (copy from Source Colors)
    */
    static void getColorArrayQuad4(GLubyte* colors,const Color* srccolors,size_t quadnumbers,size_t srccolorsize);

    /**
    *@param colors 4 Array of colors(RGB) (Size: 4*3*quadnumbers) { {r,g,b,  r,g,b,  r,g,b,  r,g,b},  {r,g,b,  r,g,b,  r,g,b,  r,g,b}, ...}
    *@param srccolors Source Color
    *@param srccolorsize Numbers of Source Colors
    *@param quadnumbers Numbers of Quads
    *@brief Set color of array (copy from Source Colors)
    */
    static void getColorArrayQuad3(GLubyte* colors,const Color* srccolors,size_t quadnumbers,size_t srccolorsize);

    /**
    *@param texcoords Array of texture coordinates
    *@param vertices Array of vertices
    *@param colors Array of colors
    *@param tcsize Number of texture coordinates per vertex (1,2,3,4)
    *@param vexsize Number of vertices per vertex (2,3,4)
    *@param colsize Number of color per vertex (2,3)
    *@param numbersofquads Numbers of Quads
    *@param usedrawarray Use glDrawArrays Function, else use glVertexv,glTexCoordv,glColorv Functions
    */
    static void renderingQuad(GLdouble* texcoords,GLdouble* vertices,GLubyte* colors,
                                GLint tcsize,GLint vexsize,GLint colsize,
                                GLuint numbersofquads,bool usedrawarray = false);

    /**
    *@param x x-Coordinate of rect
    *@param y y-Coordinate of rect
    *@param width Width of rect
    *@param height Height of rect
    *@brief Is rect in viewport range (glGetIntegerv(GL_VIEWPORT, ...))
    */
    static bool isInViewportRange(GLint x,GLint y,GLuint width,GLuint height);

    /**
    *@param rect Rect
    *@brief Is rect in viewport range (glGetIntegerv(GL_VIEWPORT, ...))
    */
    static bool isInViewportRange(Rect rect);

    /**
    *@param x x-Coordinate of scissor
    *@param y y-Coordinate of scissor
    *@param width Width of scissor
    *@param height Height of scissor
    *@brief Set scissor in top left coordinate system (glScissor)
    */
    static void setScissorInTopLeftMode(GLint x,GLint y,GLuint width,GLuint height);

    /**
    *@param rect Rect of scissor
    *@brief Set scissor in top left coordinate system (glScissor)
    */
    static void setScissorInTopLeftMode(Rect rect);

    /**
    *@param rect1 1st Rect
    *@param rect2 2nd Rect
    *@brief Is true if both rectangles collide
    */
    static bool iscollisionRect(Rect rect1,Rect rect2);

    /**
    *@param x1 x-Coordinate of 1st Rect
    *@param y1 y-Coordinate of 1st Rect
    *@param width1 Width of 1st Rect
    *@param height1 Height of 1st Rect
    *@param x2 x-Coordinate of 2nd Rect
    *@param y2 y-Coordinate of 2nd Rect
    *@param width2 Width of 2nd Rect
    *@param height2 Height of 2nd Rect
    *@brief Is true if both rectangles collide
    */
    static bool iscollisionRect(GLint x1,GLint y1,GLuint width1,GLuint height1,GLint x2,GLint y2,GLuint width2,GLuint height2);
};

}

#endif // RENDERMANAGER_HPP_INCLUDED
