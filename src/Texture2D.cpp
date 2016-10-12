#include <Fantasy2C/Texture2D.hpp>

namespace F2C{

Texture2D::Texture2D(size_t maxmiplvl):
    width(0),
    height(0),
    mipcount(0),
    isTexImage2D(GL_FALSE),
    image(maxmiplvl,NULL)
{}

Texture2D::~Texture2D(){
    for(size_t i = 0;i < this->image.size();++i){
        if(this->image[i])
            delete[] this->image[i];
    }
}

void Texture2D::clampTextureSize(size_t level){
    if(level >= this->image.size())
        return;

    uint newW = Math::round2(this->width);
    uint newH = Math::round2(this->height);

    if (newW != this->width || newH != this->height){
        GLuint texW = this->width >> level;
        GLuint texH = this->height >> level;

        GLubyte* newimage = new GLubyte[newW*newH*4]();

        gluScaleImage(GL_RGBA,texW,texH,GL_UNSIGNED_BYTE,this->image[level],newW,newH,GL_UNSIGNED_BYTE,newimage);
        if(this->image[level])
            delete[] this->image[level];
        this->image[level] = newimage;

        this->width = newW;
        this->height = newH;
    }
}

GLboolean Texture2D::isCreateTexImage() const{
    return this->isTexImage2D;
}

void Texture2D::resize(size_t mipmaplvl){
    this->image.resize(mipmaplvl);

    if(this->mipcount >= mipmaplvl)
        this->mipcount = mipmaplvl-1;
}

GLubyte* Texture2D::operator [] (size_t level){
    if(level >= this->image.size())
        return NULL;

    return  this->image[level];
}
const GLubyte* Texture2D::operator [] (size_t level) const{
    if(level >= this->image.size())
        return NULL;

    return  this->image[level];
}

GLubyte* Texture2D::getImage(size_t level){
    if(level >= this->image.size())
        return NULL;

    return  this->image[level];
}
const GLubyte* Texture2D::getImage(size_t level) const{
    if(level >= this->image.size())
        return NULL;

    return  this->image[level];
}

GLuint Texture2D::getWidth() const {
    return this->width;
}
GLuint Texture2D::getHeight() const{
    return this->height;
}
size_t Texture2D::getMipCount() const{
    return this->mipcount;
}

void Texture2D::convertImageinRGBAFloat(GLubyte* texPixels,const GLvoid* pixels,GLenum format,GLuint texW,GLuint texH,size_t colors){
    const GLfloat* refPixels = static_cast<const GLfloat*>(pixels);

    size_t i = 0;
    size_t j = 0;
    for (size_t y = 0; y < texH; ++y){
        for (size_t x = 0; x < texW; ++x, i += 4, j += colors){
            switch (format){
                case GL_RED:
                    texPixels[i] = refPixels[j]*255;
                    texPixels[i+1] = 0;
                    texPixels[i+2] = 0;
                    texPixels[i+3] = 255;
                case GL_GREEN:
                    texPixels[i] = 0;
                    texPixels[i+1] = refPixels[j]*255;
                    texPixels[i+2] = 0;
                    texPixels[i+3] = 255;
                case GL_BLUE:
                    texPixels[i] = 0;
                    texPixels[i+1] = 0;
                    texPixels[i+2] = refPixels[j]*255;
                    texPixels[i+3] = 255;
                case GL_ALPHA:
                    texPixels[i] = 0;
                    texPixels[i+1] = 0;
                    texPixels[i+2] = 0;
                    texPixels[i+3] = refPixels[j]*255;
                case GL_LUMINANCE:
                    texPixels[i] = refPixels[j]*255;
                    texPixels[i+1] = refPixels[j]*255;
                    texPixels[i+2] = refPixels[j]*255;
                    texPixels[i+3] = 255;
                break;

                case GL_LUMINANCE_ALPHA:
                    texPixels[i] = refPixels[j]*255;
                    texPixels[i+1] = refPixels[j]*255;
                    texPixels[i+2] = refPixels[j]*255;
                    texPixels[i+3] = refPixels[j+1]*255;
                break;

                case GL_RGB:
                    texPixels[i] = refPixels[j]*255;
                    texPixels[i+1] = refPixels[j+1]*255;
                    texPixels[i+2] = refPixels[j+2]*255;
                    texPixels[i+3] = 255;
                break;

                case GL_RGBA:
                    texPixels[i] = refPixels[j]*255;
                    texPixels[i+1] = refPixels[j+1]*255;
                    texPixels[i+2] = refPixels[j+2]*255;
                    texPixels[i+3] = refPixels[j+3]*255;
                break;

                case GL_BGR:
                    texPixels[i] = refPixels[j+2]*255;
                    texPixels[i+1] = refPixels[j+1]*255;
                    texPixels[i+2] = refPixels[j]*255;
                    texPixels[i+3] = 255;
                break;

                case GL_BGRA:
                    texPixels[i] = refPixels[j+2]*255;
                    texPixels[i+1] = refPixels[j+1]*255;
                    texPixels[i+2] = refPixels[j]*255;
                    texPixels[i+3] = refPixels[j+3]*255;
                break;

                default:
                return;
            }
        }
    }
}


void Texture2D::convertRGBAinImageFloat(const GLubyte* texPixels,GLvoid* pixels,GLenum format,GLuint texW,GLuint texH,size_t colors){
    GLfloat* refPixels = static_cast<GLfloat*>(pixels);

    size_t i = 0;
    size_t j = 0;
    for (size_t y = 0; y < texH; ++y){
        for (size_t x = 0; x < texW; ++x, i += 4, j += colors){
            switch (format){
                case GL_RED:
                    refPixels[i] = texPixels[j]/255.0f;
                    refPixels[i+1] = 0;
                    refPixels[i+2] = 0;
                    refPixels[i+3] = 1.0f;
                case GL_GREEN:
                    refPixels[i] = 0;
                    refPixels[i+1] = texPixels[j]/255.0f;
                    refPixels[i+2] = 0;
                    refPixels[i+3] = 1.0f;
                case GL_BLUE:
                    refPixels[i] = 0;
                    refPixels[i+1] = 0;
                    refPixels[i+2] = texPixels[j]/255.0f;
                    refPixels[i+3] = 1.0f;
                case GL_ALPHA:
                    refPixels[i] = 0;
                    refPixels[i+1] = 0;
                    refPixels[i+2] = 0;
                    refPixels[i+3] = texPixels[j]/255.0f;
                case GL_LUMINANCE:
                    refPixels[i] = texPixels[j]/255.0f;
                    refPixels[i+1] = texPixels[j]/255.0f;
                    refPixels[i+2] = texPixels[j]/255.0f;
                    refPixels[i+3] = 1.0f;
                break;

                case GL_LUMINANCE_ALPHA:
                    refPixels[i] = texPixels[j]/255.0f;
                    refPixels[i+1] = texPixels[j]/255.0f;
                    refPixels[i+2] = texPixels[j]/255.0f;
                    refPixels[i+3] = texPixels[j+1]/255.0f;
                break;

                case GL_RGB:
                    refPixels[i] = texPixels[j]/255.0f;
                    refPixels[i+1] = texPixels[j+1]/255.0f;
                    refPixels[i+2] = texPixels[j+2]/255.0f;
                    refPixels[i+3] = 1.0f;
                break;

                case GL_RGBA:
                    refPixels[i] = texPixels[j]/255.0f;
                    refPixels[i+1] = texPixels[j+1]/255.0f;
                    refPixels[i+2] = texPixels[j+2]/255.0f;
                    refPixels[i+3] = texPixels[j+3]/255.0f;
                break;

                case GL_BGR:
                    refPixels[i] = texPixels[j+2]/255.0f;
                    refPixels[i+1] = texPixels[j+1]/255.0f;
                    refPixels[i+2] = texPixels[j]/255.0f;
                    refPixels[i+3] = 1.0f;
                break;

                case GL_BGRA:
                    refPixels[i] = texPixels[j+2]/255.0f;
                    refPixels[i+1] = texPixels[j+1]/255.0f;
                    refPixels[i+2] = texPixels[j]/255.0f;
                    refPixels[i+3] = texPixels[j+3]/255.0f;
                break;

                default:
                return;
            }
        }
    }
}

GLenum Texture2D::texSubImage2D(GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height,GLenum format, GLenum type, const GLvoid* pixels){
    if(this->isTexImage2D)
        return GL_INVALID_OPERATION;

    if(level >= this->image.size() || level < 0)
        return GL_INVALID_VALUE;

    GLuint texW = this->width >> level;
    GLuint texH = this->height >> level;

    // Clamp the image
    clamp<int>(xoffset, 0, this->width);
    clamp<int>(yoffset, 0, this->height);
    clamp<GLsizei>(width, 0, this->width);
    clamp<GLsizei>(height, 0, this->height);

    if (xoffset + width > this->width)
        width -= this->width - ( xoffset + width );
    if (yoffset + height > this->height)
        height -= this->height - ( yoffset + height );

    texW = std::min<GLuint>(texW,width);
    texH = std::min<GLuint>(texH,height);

    GLubyte* texPixels =  this->image[level];

    size_t colors = 0;
    switch (format){
        case 1:
        case GL_RED:
        case GL_GREEN:
        case GL_BLUE:
        case GL_ALPHA:
        case GL_LUMINANCE:
            colors = 1;
        break;
        case 2:
        case GL_LUMINANCE_ALPHA:
            colors = 2;
        break;
        case 3:
        case GL_RGB:
        case GL_BGR:
            colors = 3;
        break;
        case 4:
        case GL_RGBA:
        case GL_BGRA:
            colors = 4;
        break;

        default:
        return GL_INVALID_ENUM;
    }


    switch (type){
        case GL_UNSIGNED_BYTE:
            this->convertImageinRGBA<const GLubyte*>(texPixels,pixels,format,texW,texH,colors);
        break;
        case GL_BYTE:
            this->convertImageinRGBA<const GLbyte*>(texPixels,pixels,format,texW,texH,colors);
        break;
        case GL_UNSIGNED_SHORT:
            this->convertImageinRGBA<const GLushort*>(texPixels,pixels,format,texW,texH,colors);
        break;
        case GL_SHORT:
            this->convertImageinRGBA<const GLshort*>(texPixels,pixels,format,texW,texH,colors);
        break;
        case GL_INT:
            this->convertImageinRGBA<const GLint*>(texPixels,pixels,format,texW,texH,colors);
        break;
        case GL_UNSIGNED_INT:
            this->convertImageinRGBA<const GLuint*>(texPixels,pixels,format,texW,texH,colors);
        break;
        case GL_FLOAT:
            this->convertImageinRGBAFloat(texPixels,pixels,format,texW,texH,colors);
        break;

        default:
        return GL_INVALID_ENUM;
    }

    return GL_NO_ERROR;
}
GLenum Texture2D::copyTexSubImage2D(const GLubyte* pixelBuffer, GLsizei pixelBufferWidth, GLsizei pixelBufferHeight, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height){
    if(!pixelBuffer || pixelBufferWidth == 0 || pixelBufferHeight == 0)
        return GL_INVALID_VALUE;

    if(this->isTexImage2D)
        return GL_INVALID_OPERATION;

    if(level >= this->image.size() || level < 0)
        return GL_INVALID_VALUE;

    width = this->width >> level;
    height = this->height >> level;

    // Clamp the screen
    clamp(x, 0, pixelBufferWidth);
    clamp(y, 0,  pixelBufferHeight);
    clamp(width, 0, pixelBufferWidth);
    clamp(height, 0, pixelBufferHeight);

    if (x + width > pixelBufferWidth)
        width -= pixelBufferWidth - ( x + width );
    if (y + height > pixelBufferHeight)
        height -= pixelBufferHeight - ( y + height );

    // Clamp the image
    clamp<int>(xoffset, 0, this->width);
    clamp<int>(yoffset, 0, this->height);
    clamp<GLsizei>(width, 0, this->width);
    clamp<GLsizei>(height, 0, this->height);

    if (xoffset + width > this->width)
        width -= this->width - ( xoffset + width );
    if (yoffset + height > this->height)
        height -= this->height - ( yoffset + height );

    GLubyte* texPixels =  this->image[level];
    for (size_t iy = y; iy < y+height; ++iy){
        // Get the offsets
        size_t i = ( iy * pixelBufferWidth + x ) << 2;
        size_t j = ( ( iy - y + yoffset ) * this->width + xoffset ) << 2;

        // Loop for all texels
        for (size_t ix = x; ix < ( x + width ) << 2; ++ix, ++i, ++j)
            texPixels[j] = pixelBuffer[i];
    }

    return GL_NO_ERROR;
}

GLenum Texture2D::texImage2D(GLint level, GLsizei width ,GLsizei height, GLenum format, GLenum type, const GLvoid* pixels){
    if(level >= this->image.size() || level < 0)
        return GL_INVALID_VALUE;

    if (level == 0){
        this->width  = width;
        this->height = height;
    }

    if (this->mipcount <= level)
        this->mipcount = level+1;

    // Allocate new image data
    if(this->image[level])
        delete[] this->image[level];
    this->image[level] = new GLubyte [width*height*4]();
    this->isTexImage2D = GL_TRUE;

    // Fill the image data
    return this->texSubImage2D(level, 0, 0, width, height, format, type, pixels);
}
GLenum Texture2D::copyTexImage2D(const GLubyte* pixelBuffer, GLsizei pixelBufferWidth, GLsizei pixelBufferHeight, GLint level,GLint xoffset,GLint yoffset, GLint x, GLint y, GLsizei width ,GLsizei heigh){
    if(level >= this->image.size() || level < 0)
        return GL_INVALID_VALUE;

    width   >>= level;
    height  >>= level;

    if (level == 0){
        this->width  = width;
        this->height = height;
    }

    if (this->mipcount < level)
        this->mipcount = level;

    // Allocate new image data
    if(this->image[level])
        delete[] this->image[level];
    this->image[level] = new GLubyte [width*height*4]();
    this->isTexImage2D = GL_TRUE;

    return this->copyTexSubImage2D(pixelBuffer,pixelBufferWidth,pixelBufferHeight, level, xoffset, yoffset, x, y, width, height);
}

GLenum Texture2D::getImage2D(GLint level,GLenum format,GLenum type,GLvoid* pixels){
    if(!pixels || level >= this->image.size() || level < 0)
        return GL_INVALID_VALUE;

    const GLubyte* texPixels =  this->image[level];
    if(!texPixels)
        return GL_NO_ERROR;

    GLuint texW = this->width >> level;
    GLuint texH = this->height >> level;

    size_t colors = 0;
    switch (format){
        case 1:
        case GL_RED:
        case GL_GREEN:
        case GL_BLUE:
        case GL_ALPHA:
        case GL_LUMINANCE:
            colors = 1;
        break;
        case 2:
        case GL_LUMINANCE_ALPHA:
            colors = 2;
        break;
        case 3:
        case GL_RGB:
        case GL_BGR:
            colors = 3;
        break;
        case 4:
        case GL_RGBA:
        case GL_BGRA:
            colors = 4;
        break;

        default:
        return GL_INVALID_ENUM;
    }

    switch (type){
        case GL_UNSIGNED_BYTE:
            this->convertRGBAinImage<GLubyte*>(texPixels,pixels,format,texW,texH,colors);
        break;
        case GL_BYTE:
            this->convertRGBAinImage<GLbyte*>(texPixels,pixels,format,texW,texH,colors);
        break;
        case GL_UNSIGNED_SHORT:
            this->convertRGBAinImage<GLushort*>(texPixels,pixels,format,texW,texH,colors);
        break;
        case GL_SHORT:
            this->convertRGBAinImage<GLshort*>(texPixels,pixels,format,texW,texH,colors);
        break;
        case GL_INT:
            this->convertRGBAinImage<GLint*>(texPixels,pixels,format,texW,texH,colors);
        break;
        case GL_UNSIGNED_INT:
            this->convertRGBAinImage<GLuint*>(texPixels,pixels,format,texW,texH,colors);
        break;
        case GL_FLOAT:
            this->convertRGBAinImageFloat(texPixels,pixels,format,texW,texH,colors);
        break;

        default:
        return GL_INVALID_ENUM;
    }

    return GL_NO_ERROR;
}

}
