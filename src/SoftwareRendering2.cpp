#include <Fantasy2C/SoftwareRendering.hpp>

namespace F2C{

void SoftwareRendering::texGen(GLenum coord, GLenum param){
    if(param == GL_SPHERE_MAP && (coord == GL_R || coord == GL_Q))
        SoftwareRendering::lastError = GL_INVALID_ENUM;

    switch(param){
        case GL_OBJECT_LINEAR:
        case GL_EYE_LINEAR:
        case GL_SPHERE_MAP:
        break;

        default:
            SoftwareRendering::lastError = GL_INVALID_ENUM;
        return;
    }
     switch (coord){
        case GL_S:
            SoftwareRendering::mappingGenType[SoftwareRendering::textureLayer].genu = param;
        break;
        case GL_T:
            SoftwareRendering::mappingGenType[SoftwareRendering::textureLayer].genv = param;
        break;
        default:
            SoftwareRendering::lastError = GL_INVALID_ENUM;
        return;
    }
}

void SoftwareRendering::vertex2i(GLint x, GLint y){
    SoftwareRendering::curVertex[SoftwareRendering::PLIndex]->pos.x = x;
    SoftwareRendering::curVertex[SoftwareRendering::PLIndex]->pos.y = y;
    SoftwareRendering::curVertex[SoftwareRendering::PLIndex]->pos.z = 0;
    SoftwareRendering::curVertex[SoftwareRendering::PLIndex]->pos.w = 1;

    ++SoftwareRendering::PLIndex;
}
void SoftwareRendering::vertex3i(GLint x, GLint y, GLint z){
    SoftwareRendering::curVertex[SoftwareRendering::PLIndex]->pos.x = x;
    SoftwareRendering::curVertex[SoftwareRendering::PLIndex]->pos.y = y;
    SoftwareRendering::curVertex[SoftwareRendering::PLIndex]->pos.z = z;
    SoftwareRendering::curVertex[SoftwareRendering::PLIndex]->pos.w = 1;

    ++SoftwareRendering::PLIndex;
}
void SoftwareRendering::vertex4i(GLint x, GLint y, GLint z, GLint w){
    SoftwareRendering::curVertex[SoftwareRendering::PLIndex]->pos.x = x;
    SoftwareRendering::curVertex[SoftwareRendering::PLIndex]->pos.y = y;
    SoftwareRendering::curVertex[SoftwareRendering::PLIndex]->pos.z = z;
    SoftwareRendering::curVertex[SoftwareRendering::PLIndex]->pos.w = w;

    ++SoftwareRendering::PLIndex;
}

void SoftwareRendering::vertex2f(GLfloat x, GLfloat y){
    SoftwareRendering::curVertex[SoftwareRendering::PLIndex]->pos.x = x;
    SoftwareRendering::curVertex[SoftwareRendering::PLIndex]->pos.y = y;
    SoftwareRendering::curVertex[SoftwareRendering::PLIndex]->pos.z = 0;
    SoftwareRendering::curVertex[SoftwareRendering::PLIndex]->pos.w = 1;

    ++SoftwareRendering::PLIndex;
}
void SoftwareRendering::vertex3f(GLfloat x, GLfloat y, GLfloat z){
    SoftwareRendering::curVertex[SoftwareRendering::PLIndex]->pos.x = x;
    SoftwareRendering::curVertex[SoftwareRendering::PLIndex]->pos.y = y;
    SoftwareRendering::curVertex[SoftwareRendering::PLIndex]->pos.z = z;
    SoftwareRendering::curVertex[SoftwareRendering::PLIndex]->pos.w = 1;

    ++SoftwareRendering::PLIndex;
}
void SoftwareRendering::vertex4f(GLfloat x, GLfloat y, GLfloat z, GLfloat w){
    SoftwareRendering::curVertex[SoftwareRendering::PLIndex]->pos.x = x;
    SoftwareRendering::curVertex[SoftwareRendering::PLIndex]->pos.y = y;
    SoftwareRendering::curVertex[SoftwareRendering::PLIndex]->pos.z = z;
    SoftwareRendering::curVertex[SoftwareRendering::PLIndex]->pos.w = w;

    ++SoftwareRendering::PLIndex;
}

void SoftwareRendering::normal3i(GLint x, GLint y, GLint z){
    SoftwareRendering::curVertex[SoftwareRendering::PLIndex]->nml.x = x;
    SoftwareRendering::curVertex[SoftwareRendering::PLIndex]->nml.y = y;
    SoftwareRendering::curVertex[SoftwareRendering::PLIndex]->nml.z = z;
}
void SoftwareRendering::normal3f(GLfloat x, GLfloat y, GLfloat z){
    SoftwareRendering::curVertex[SoftwareRendering::PLIndex]->nml.x = x;
    SoftwareRendering::curVertex[SoftwareRendering::PLIndex]->nml.y = y;
    SoftwareRendering::curVertex[SoftwareRendering::PLIndex]->nml.z = z;
}

void SoftwareRendering::texCoord2i(GLint x, GLint y){
    SoftwareRendering::curVertex[SoftwareRendering::PLIndex]->map[0].x = x;
    SoftwareRendering::curVertex[SoftwareRendering::PLIndex]->map[0].y = y;
    SoftwareRendering::curVertex[SoftwareRendering::PLIndex]->map[0].z = 0;
    SoftwareRendering::curVertex[SoftwareRendering::PLIndex]->map[0].w = 1;
}
void SoftwareRendering::texCoord2f(GLfloat x, GLfloat y){
    const Matrix4<float>& m = SoftwareRendering::renderMatrix[SoftwareRendering::TEXTURE_MATRIX];

    SoftwareRendering::curVertex[SoftwareRendering::PLIndex]->map[0].x = x*m.m11 + y*m.m21 + m.m41;
    SoftwareRendering::curVertex[SoftwareRendering::PLIndex]->map[0].y = x*m.m12 + y*m.m22 + m.m42;
    SoftwareRendering::curVertex[SoftwareRendering::PLIndex]->map[0].z = x*m.m13 + y*m.m23 + m.m43;
    SoftwareRendering::curVertex[SoftwareRendering::PLIndex]->map[0].w = x*m.m14 + y*m.m24 + m.m44;
}

void SoftwareRendering::color3i(GLubyte red, GLubyte green, GLubyte blue){
    SoftwareRendering::curVertex[SoftwareRendering::PLIndex]->clr.red = red;
    SoftwareRendering::curVertex[SoftwareRendering::PLIndex]->clr.green = green;
    SoftwareRendering::curVertex[SoftwareRendering::PLIndex]->clr.blue = blue;
    SoftwareRendering::curVertex[SoftwareRendering::PLIndex]->clr.alpha = 255;
}
void SoftwareRendering::color4i(GLubyte red, GLubyte green, GLubyte blue,GLubyte alpha){
    SoftwareRendering::curVertex[SoftwareRendering::PLIndex]->clr.red = red;
    SoftwareRendering::curVertex[SoftwareRendering::PLIndex]->clr.green = green;
    SoftwareRendering::curVertex[SoftwareRendering::PLIndex]->clr.blue = blue;
    SoftwareRendering::curVertex[SoftwareRendering::PLIndex]->clr.alpha = alpha;
}

void SoftwareRendering::color3f(GLfloat red, GLfloat green, GLfloat blue){
    SoftwareRendering::curVertex[SoftwareRendering::PLIndex]->clr.red = red*255;
    SoftwareRendering::curVertex[SoftwareRendering::PLIndex]->clr.green = green*255;
    SoftwareRendering::curVertex[SoftwareRendering::PLIndex]->clr.blue = blue*255;
    SoftwareRendering::curVertex[SoftwareRendering::PLIndex]->clr.alpha = 255;
}
void SoftwareRendering::color4f(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha){
    SoftwareRendering::curVertex[SoftwareRendering::PLIndex]->clr.red = red*255;
    SoftwareRendering::curVertex[SoftwareRendering::PLIndex]->clr.green = green*255;
    SoftwareRendering::curVertex[SoftwareRendering::PLIndex]->clr.blue = blue*255;
    SoftwareRendering::curVertex[SoftwareRendering::PLIndex]->clr.alpha = alpha*255;
}

void SoftwareRendering::createDevice(GLuint screenWidth,GLuint screenHeight){
    // General settings
    SoftwareRendering::screenSize.set(0,0,screenWidth,screenHeight);

    SoftwareRendering::depthBufferSize = screenWidth * screenHeight;
    SoftwareRendering::stencilBufferSize = SoftwareRendering::depthBufferSize;
    SoftwareRendering::colorBufferSize = SoftwareRendering::depthBufferSize << 2;

    // Allocate the screen buffers
    if(SoftwareRendering::colorBuffer)
        delete[] SoftwareRendering::colorBuffer;
    SoftwareRendering::colorBuffer = new GLint[SoftwareRendering::colorBufferSize]();

    if(SoftwareRendering::stencilBuffer)
        delete[] SoftwareRendering::stencilBuffer;
    SoftwareRendering::stencilBuffer = new GLint[SoftwareRendering::stencilBufferSize]();

    if(SoftwareRendering::depthBuffer)
        delete[] SoftwareRendering::depthBuffer;
    SoftwareRendering::depthBuffer = new GLint[SoftwareRendering::depthBufferSize]();

    // Allocate all arrays
    SoftwareRendering::curVertex.resize(SoftwareRendering::RENDER_PIPELINE_SIZE);
    SoftwareRendering::curMemVertex.resize(SoftwareRendering::RENDER_PIPELINE_SIZE);
    SoftwareRendering::curTexture.resize(SoftwareRendering::TEXTURE_LAYER_SIZE);
    SoftwareRendering::renderMatrix.resize(SoftwareRendering::MAX_MATRICES);
    SoftwareRendering::mappingGenType.resize(SoftwareRendering::TEXTURE_LAYER_SIZE);

    SoftwareRendering::curMatrixMode = GL_MODELVIEW_MATRIX;
    SoftwareRendering::enableSSC[GL_ALPHA_TEST] = false;
    SoftwareRendering::enableSSC[GL_BLEND] = false;
    SoftwareRendering::enableSSC[GL_DEPTH_TEST] = false;
    SoftwareRendering::enableSSC[GL_SCISSOR_TEST] = false;
    SoftwareRendering::enableSSC[GL_NORMALIZE] = false;
    SoftwareRendering::enableSSC[GL_STENCIL_TEST] = false;
    SoftwareRendering::enableSSC[GL_TEXTURE_2D] = false;
    SoftwareRendering::enableSSC[GL_TEXTURE_GEN_S] = false;
    SoftwareRendering::enableSSC[GL_TEXTURE_GEN_T] = false;

    // Create the device context
    glGenTextures(1, &SoftwareRendering::texDeviceID);
    glBindTexture(GL_TEXTURE_2D, SoftwareRendering::texDeviceID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, 4, screenWidth, screenHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, SoftwareRendering::colorBuffer);
    glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, SoftwareRendering::texDeviceID);
}

void SoftwareRendering::deleteDevice(){
    if(SoftwareRendering::colorBuffer)
        delete[] SoftwareRendering::colorBuffer;

    if(SoftwareRendering::stencilBuffer)
        delete[] SoftwareRendering::stencilBuffer;

    if(SoftwareRendering::depthBuffer)
        delete[] SoftwareRendering::depthBuffer;

    glDeleteTextures(1,&SoftwareRendering::texDeviceID);
}

void SoftwareRendering::clear(GLbitfield mask){
    if(mask & GL_COLOR_BUFFER_BIT){
        for(size_t i = 0;i < SoftwareRendering::colorBufferSize;i+=4){
            SoftwareRendering::colorBuffer[i] = SoftwareRendering::curClearColor.r;
            SoftwareRendering::colorBuffer[i+1] = SoftwareRendering::curClearColor.g;
            SoftwareRendering::colorBuffer[i+2] = SoftwareRendering::curClearColor.b;
            SoftwareRendering::colorBuffer[i+3] = SoftwareRendering::curClearColor.a;
        }
    }

    if(mask & GL_DEPTH_BUFFER_BIT){
        for(size_t i = 0;i < SoftwareRendering::depthBufferSize;i++)
            SoftwareRendering::depthBuffer[i] = SoftwareRendering::curClearDepth;
    }

    if(mask & GL_STENCIL_BUFFER_BIT){
        for(size_t i = 0;i < SoftwareRendering::stencilBufferSize;i++)
            SoftwareRendering::stencilBuffer[i] = SoftwareRendering::curClearStencil;
    }
}


void SoftwareRendering::swapBuffers(){
    Vector2<GLfloat> pos1 (0.0f, 0.0f);
    Vector2<GLfloat> pos2 (SoftwareRendering::screenSize.width,SoftwareRendering::screenSize.height);

    // Put onto the screen
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0,
                        SoftwareRendering::screenSize.width,
                        SoftwareRendering::screenSize.height,
                        GL_RGBA, GL_UNSIGNED_BYTE,
                        SoftwareRendering::colorBuffer);

    SoftwareRendering::Project2Dto3D(pos1);
    SoftwareRendering::Project2Dto3D(pos2);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Draw the result
    glBegin(GL_TRIANGLE_STRIP);
        glTexCoord2f(0.0f, 0.0f);
        glVertex2f(pos1.x, pos1.y);

        glTexCoord2f(0.0f, 1.0f);
        glVertex2f(pos1.x, pos2.y);

        glTexCoord2f(1.0f, 0.0f);
        glVertex2f(pos2.x, pos1.y);

        glTexCoord2f(1.0f, 1.0f);
        glVertex2f(pos2.x, pos2.y);
    glEnd();
}

}
