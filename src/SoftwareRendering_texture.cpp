#include <Fantasy2C/SoftwareRendering.hpp>

namespace F2C {

void SoftwareRendering::genTextures(GLuint* ID){
    Texture2D* tex = new Texture2D(SoftwareRendering::MAX_MIPMAPLEVELS);

    *ID = reinterpret_cast<GLuint>(tex);
}
void SoftwareRendering::deleteTextures(GLuint* ID){
    if(!ID)
        return;
    if(*ID == 0)
        return;

    Texture2D* tex = reinterpret_cast<Texture2D*>(*ID);

    delete tex;

    *ID = 0;
}

void SoftwareRendering::bindTexture(GLuint ID){
    if(ID)
        SoftwareRendering::curTexture[SoftwareRendering::textureLayer] = reinterpret_cast<Texture2D*>(ID);
}
void SoftwareRendering::unbindTexture(){
    SoftwareRendering::curTexture[SoftwareRendering::textureLayer] = NULL;
}
GLuint SoftwareRendering::getCurTexture(){
    return reinterpret_cast<GLuint>(SoftwareRendering::curTexture[SoftwareRendering::textureLayer]);
}

void SoftwareRendering::texSubImage2D(GLuint ID,GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height,GLenum format, GLenum type, const GLvoid* pixels){
    // Check if the parameter values are valid

    Texture2D* tex =  reinterpret_cast<Texture2D*>(ID);
    GLenum glerror = tex->texSubImage2D(level,xoffset,yoffset,width,height,format,type,pixels);

    if(glerror != GL_NO_ERROR)
        SoftwareRendering::lastError = glerror;
}
void SoftwareRendering::copyTexSubImage2D(GLuint ID, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height){
    // Check if the parameter values are valid

    Texture2D* tex =  reinterpret_cast<Texture2D*>(ID);
    GLenum glerror = tex->copyTexSubImage2D((GLubyte*)SoftwareRendering::colorBuffer,SoftwareRendering::screenSize.width,SoftwareRendering::screenSize.height,
                           level,xoffset,yoffset,x,y,width,height);

    if(glerror != GL_NO_ERROR)
        SoftwareRendering::lastError = glerror;
}

void SoftwareRendering::texImage2D(GLuint ID, GLint level, GLsizei width ,GLsizei height, GLenum format, GLenum type, const GLvoid* pixels){
    // Check if the parameter values are valid

    Texture2D* tex =  reinterpret_cast<Texture2D*>(ID);
    GLenum glerror = tex->texImage2D(level,width,height,format,type,pixels);

    if(glerror != GL_NO_ERROR)
        SoftwareRendering::lastError = glerror;
}
void SoftwareRendering::copyTexImage2D(GLuint ID, GLint level,GLint xoffset,GLint yoffset, GLint x, GLint y, GLsizei width ,GLsizei height){
    // Check if the parameter values are valid

    Texture2D* tex =  reinterpret_cast<Texture2D*>(ID);
    GLenum glerror = tex->copyTexImage2D((GLubyte*)SoftwareRendering::colorBuffer,SoftwareRendering::screenSize.width,SoftwareRendering::screenSize.height,
                                            level,xoffset,yoffset,x,y,width,height);
    if(glerror != GL_NO_ERROR)
        SoftwareRendering::lastError = glerror;
}

void SoftwareRendering::getImage2D(GLuint ID,GLint level,GLenum format,GLenum type,GLvoid* pixels){
    // Check if the parameter values are valid

    Texture2D* tex =  reinterpret_cast<Texture2D*>(ID);
    GLenum glerror = tex->getImage2D(level,format,type,pixels);

    if(glerror != GL_NO_ERROR)
        SoftwareRendering::lastError = glerror;
}

}
