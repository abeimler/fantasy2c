#ifndef TEXTURE2D_HPP_INCLUDED
#define TEXTURE2D_HPP_INCLUDED

#include <Fantasy2C/Basic.hpp>
#include <Fantasy2C/Bitmap.hpp>


template class DLL std::allocator<GLubyte*>;
template class DLL std::vector<GLubyte*, std::allocator<GLubyte*> >;

namespace F2C{

class DLL Texture2D{
    private:
        GLuint width;
        GLuint height;
        size_t mipcount;
        GLboolean isTexImage2D;
        std::vector<GLubyte*> image;

        template<typename T>
        void convertRGBAinImage(const GLubyte* texPixels,GLvoid* pixels,GLenum format,GLuint texW,GLuint texH,size_t colors){
            T refPixels = static_cast<T>(pixels);

            size_t i = 0;
            size_t j = 0;
            for (size_t y = 0; y < texH; ++y){
                for (size_t x = 0; x < texW; ++x, i += 4, j += colors){
                    switch (format){
                        case GL_RED:
                            refPixels[i] = texPixels[j];
                            refPixels[i+1] = 0;
                            refPixels[i+2] = 0;
                            refPixels[i+3] = 255;
                        case GL_GREEN:
                            refPixels[i] = 0;
                            refPixels[i+1] = texPixels[j];
                            refPixels[i+2] = 0;
                            refPixels[i+3] = 255;
                        case GL_BLUE:
                            refPixels[i] = 0;
                            refPixels[i+1] = 0;
                            refPixels[i+2] = texPixels[j];
                            refPixels[i+3] = 255;
                        case GL_ALPHA:
                            refPixels[i] = 0;
                            refPixels[i+1] = 0;
                            refPixels[i+2] = 0;
                            refPixels[i+3] = texPixels[j];
                        case GL_LUMINANCE:
                            refPixels[i] = texPixels[j];
                            refPixels[i+1] = texPixels[j];
                            refPixels[i+2] = texPixels[j];
                            refPixels[i+3] = 255;
                        break;

                        case GL_LUMINANCE_ALPHA:
                            refPixels[i] = texPixels[j];
                            refPixels[i+1] = texPixels[j];
                            refPixels[i+2] = texPixels[j];
                            refPixels[i+3] = texPixels[j+1];
                        break;

                        case GL_RGB:
                            refPixels[i] = texPixels[j];
                            refPixels[i+1] = texPixels[j+1];
                            refPixels[i+2] = texPixels[j+2];
                            refPixels[i+3] = 255;
                        break;

                        case GL_RGBA:
                            refPixels[i] = texPixels[j];
                            refPixels[i+1] = texPixels[j+1];
                            refPixels[i+2] = texPixels[j+2];
                            refPixels[i+3] = texPixels[j+3];
                        break;

                        case GL_BGR:
                            refPixels[i] = texPixels[j+2];
                            refPixels[i+1] = texPixels[j+1];
                            refPixels[i+2] = texPixels[j];
                            refPixels[i+3] = 255;
                        break;

                        case GL_BGRA:
                            refPixels[i] = texPixels[j+2];
                            refPixels[i+1] = texPixels[j+1];
                            refPixels[i+2] = texPixels[j];
                            refPixels[i+3] = texPixels[j+3];
                        break;

                        default:
                        return;
                    }
                }
            }
        }


        template<typename T>
        void convertImageinRGBA(GLubyte* texPixels,const GLvoid* pixels,GLenum format,GLuint texW,GLuint texH,size_t colors){
            T refPixels = static_cast<T>(pixels);

            size_t i = 0;
            size_t j = 0;
            for (size_t y = 0; y < texH; ++y){
                for (size_t x = 0; x < texW; ++x, i += 4, j += colors){
                    switch (format){
                        case GL_RED:
                            texPixels[i] = refPixels[j];
                            texPixels[i+1] = 0;
                            texPixels[i+2] = 0;
                            texPixels[i+3] = 255;
                        case GL_GREEN:
                            texPixels[i] = 0;
                            texPixels[i+1] = refPixels[j];
                            texPixels[i+2] = 0;
                            texPixels[i+3] = 255;
                        case GL_BLUE:
                            texPixels[i] = 0;
                            texPixels[i+1] = 0;
                            texPixels[i+2] = refPixels[j];
                            texPixels[i+3] = 255;
                        case GL_ALPHA:
                            texPixels[i] = 0;
                            texPixels[i+1] = 0;
                            texPixels[i+2] = 0;
                            texPixels[i+3] = refPixels[j];
                        case GL_LUMINANCE:
                            texPixels[i] = refPixels[j];
                            texPixels[i+1] = refPixels[j];
                            texPixels[i+2] = refPixels[j];
                            texPixels[i+3] = 255;
                        break;

                        case GL_LUMINANCE_ALPHA:
                            texPixels[i] = refPixels[j];
                            texPixels[i+1] = refPixels[j];
                            texPixels[i+2] = refPixels[j];
                            texPixels[i+3] = refPixels[j+1];
                        break;

                        case GL_RGB:
                            texPixels[i] = refPixels[j];
                            texPixels[i+1] = refPixels[j+1];
                            texPixels[i+2] = refPixels[j+2];
                            texPixels[i+3] = 255;
                        break;

                        case GL_RGBA:
                            texPixels[i] = refPixels[j];
                            texPixels[i+1] = refPixels[j+1];
                            texPixels[i+2] = refPixels[j+2];
                            texPixels[i+3] = refPixels[j+3];
                        break;

                        case GL_BGR:
                            texPixels[i] = refPixels[j+2];
                            texPixels[i+1] = refPixels[j+1];
                            texPixels[i+2] = refPixels[j];
                            texPixels[i+3] = 255;
                        break;

                        case GL_BGRA:
                            texPixels[i] = refPixels[j+2];
                            texPixels[i+1] = refPixels[j+1];
                            texPixels[i+2] = refPixels[j];
                            texPixels[i+3] = refPixels[j+3];
                        break;

                        default:
                        return;
                    }
                }
            }
        }

        void convertImageinRGBAFloat(GLubyte* texPixels,const GLvoid* pixels,GLenum format,GLuint texW,GLuint texH,size_t colors);
        void convertRGBAinImageFloat(const GLubyte* texPixels,GLvoid* pixels,GLenum format,GLuint texW,GLuint texH,size_t colors);
    public:
        Texture2D(size_t mipcount = 1);
        ~Texture2D();

        GLubyte* operator [] (size_t level);
        const GLubyte* operator [] (size_t level) const;

        GLubyte* getImage(size_t level);
        const GLubyte* getImage(size_t level) const;

        void clampTextureSize(size_t lvl);
        void resize(size_t mipmaplvl);

        GLuint getWidth() const;
        GLuint getHeight() const;
        size_t getMipCount() const;

        GLboolean isCreateTexImage() const;

        GLenum texSubImage2D(GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height,GLenum format, GLenum type, const GLvoid* pixels);
        GLenum copyTexSubImage2D(const GLubyte* pixelBuffer, GLsizei pixelBufferWidth, GLsizei pixelBufferHeight, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height);

        GLenum texImage2D(GLint level, GLsizei width ,GLsizei height, GLenum format, GLenum type, const GLvoid* pixels);
        GLenum copyTexImage2D(const GLubyte* pixelBuffer, GLsizei pixelBufferWidth, GLsizei pixelBufferHeight, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width ,GLsizei height);

        GLenum getImage2D(GLint level,GLenum format,GLenum type,GLvoid* pixels);
};

}

#endif // TEXTURE2D_HPP_INCLUDED
