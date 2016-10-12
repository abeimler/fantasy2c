#include <Fantasy2C/SoftwareRendering.hpp>

namespace F2C{

void SoftwareRendering::scissor(GLint x, GLint y, GLuint width, GLuint height){
    if(x + static_cast<GLint>(width) < 0 || y + static_cast<GLint>(height) < 0){
        SoftwareRendering::lastError = GL_INVALID_ENUM;
        return;
    }

    SoftwareRendering::scissorRect.x = x;
    SoftwareRendering::scissorRect.y = y;
    SoftwareRendering::scissorRect.width = x + width;
    SoftwareRendering::scissorRect.height = y + height;
    SoftwareRendering::updatePixelRect();
}
void SoftwareRendering::viewport(GLint x, GLint y, GLuint width, GLuint height){
    if(x + static_cast<GLint>(width) < 0 || y + static_cast<GLint>(height) < 0){
        SoftwareRendering::lastError = GL_INVALID_ENUM;
        return;
    }

    SoftwareRendering::viewportRect.x = x;
    SoftwareRendering::viewportRect.y = y;
    SoftwareRendering::viewportRect.width = x + width;
    SoftwareRendering::viewportRect.height = y + height;
    SoftwareRendering::updatePixelRect();
}
void SoftwareRendering::perspective(GLfloat glnear, GLfloat glfar, GLfloat fieldOfView){
    if(glnear == 0.0f)
        glnear = 1.0f;

    SoftwareRendering::planeNear = glnear;
    SoftwareRendering::planeFar = glfar;

    SoftwareRendering::rangeNear = 1.0f / glnear;
    SoftwareRendering::rangeFar = 1.0f / glfar;

    SoftwareRendering::fieldOfView = fieldOfView;
}


void SoftwareRendering::loadIdentity(){
    SoftwareRendering::SoftwareRendering::renderMatrix
            [SoftwareRendering::curMatrixMode].set(
                1,0,0,0,
                0,1,0,0,
                0,0,1,0,
                0,0,0,1
            );
}

void SoftwareRendering::loadMatrix(const float* m){
    SoftwareRendering::SoftwareRendering::renderMatrix[SoftwareRendering::curMatrixMode].set(m);
}

void SoftwareRendering::loadMatrix(const Matrix4<float>& m){
    SoftwareRendering::SoftwareRendering::renderMatrix[SoftwareRendering::curMatrixMode] = m;
}

void SoftwareRendering::updateNormalMatrix(){
    SoftwareRendering::renderMatrix[SoftwareRendering::NORMAL_MATRIX] =
        SoftwareRendering::renderMatrix[SoftwareRendering::MODELVIEW_MATRIX];

    SoftwareRendering::renderMatrix[SoftwareRendering::NORMAL_MATRIX].m41 =
        SoftwareRendering::renderMatrix[SoftwareRendering::NORMAL_MATRIX].m42 =
        SoftwareRendering::renderMatrix[SoftwareRendering::NORMAL_MATRIX].m43 = 0.0f;
}

}
