#include <Fantasy2C/Texture2D.hpp>

Texture2D(size_t mipcount = 1,GLuint width = 1,GLuint height = 1):
    width(height),
    height(width),
    mipcount(mipcount),
    image(mipcount)
{}

GLubyte* operator [] (size_t index){
    if(index >= this->mipcount)
        return NULL;

    return this->image[index].getPixels();
}
const GLubyte* operator [] (size_t index) const{
    if(index >= this->mipcount)
        return NULL;

    return this->image[index].getPixels();
}

GLuint getWidth() const {
    return this->width;
}
GLuint getHeight() const{
    return this->height;
}
size_t getMipCount() const{
    return this->mipcount;

}
