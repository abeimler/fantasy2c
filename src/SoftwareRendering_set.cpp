#include <Fantasy2C/SoftwareRendering.hpp>

namespace F2C{

void SoftwareRendering::endisable(GLenum mode,GLboolean set){
    switch(mode){
        case GL_ALPHA_TEST:
        case GL_BLEND:
        case GL_DEPTH_TEST:
        case GL_SCISSOR_TEST:
        case GL_NORMALIZE:
        case GL_STENCIL_TEST:
        case GL_TEXTURE_2D:
        case GL_TEXTURE_GEN_S:
        case GL_TEXTURE_GEN_T:
            SoftwareRendering::enableSSC[mode] = set;
        break;

        default:
            SoftwareRendering::lastError = GL_INVALID_ENUM;
    }
}

void SoftwareRendering::enable(GLenum mode){
    SoftwareRendering::endisable(mode,true);
}

void SoftwareRendering::disable(GLenum mode){
    SoftwareRendering::endisable(mode,false);
}

void SoftwareRendering::clearColor(GLclampf red,GLclampf green,GLclampf blue,GLclampf alpha){
    SoftwareRendering::curClearColor = Color4f (red,green,blue,alpha);
}

void SoftwareRendering::clearDepth(GLclampd depth){
    SoftwareRendering::curClearDepth = depth;
}

void SoftwareRendering::clearStencil(GLint s){
    SoftwareRendering::curClearStencil = s;
}

void SoftwareRendering::lineWidth(GLuint width){
    if(width <= 0){
        SoftwareRendering::lastError = GL_INVALID_ENUM;
        return;
    }

    SoftwareRendering::curLineWidth = width;
}
void SoftwareRendering::pointSize(GLuint size){
    if(size <= 0){
        SoftwareRendering::lastError = GL_INVALID_ENUM;
        return;
    }

    SoftwareRendering::curPointSize = size;
}

void SoftwareRendering::setMaxTextureLayer(GLuint maxLayer){
    SoftwareRendering::maxTextureLayer = vclamp<GLuint>(maxLayer, 0, SoftwareRendering::TEXTURE_LAYER_SIZE);
}
void SoftwareRendering::useTextureLayer(GLuint layer){
    SoftwareRendering::textureLayer = layer;
}

void SoftwareRendering::shadeModel(GLenum mode){
    switch(mode){
        case GL_SMOOTH:
        case GL_FLAT:
            SoftwareRendering::curShadeModel = mode;
        break;

        default:
            SoftwareRendering::lastError = GL_INVALID_ENUM;
    }
}

void SoftwareRendering::depthFunc(GLenum func){
    switch(func){
        case GL_NEVER:
        case GL_LESS:
        case GL_EQUAL:
        case GL_LEQUAL:
        case GL_GREATER:
        case GL_NOTEQUAL:
        case GL_GEQUAL:
        case GL_ALWAYS:
            SoftwareRendering::curDepthFunc = func;
        break;

        default:
            SoftwareRendering::lastError = GL_INVALID_ENUM;
    }
}

void SoftwareRendering::alphaFunc(GLenum func,GLclampf mask){
    switch(func){
        case GL_NEVER:
        case GL_LESS:
        case GL_EQUAL:
        case GL_LEQUAL:
        case GL_GREATER:
        case GL_NOTEQUAL:
        case GL_GEQUAL:
        case GL_ALWAYS:
            SoftwareRendering::curAlphaFunc = func;
            SoftwareRendering::curAlphaFuncRef = vclamp(mask,0.0f,1.0f);
        break;

        default:
            SoftwareRendering::lastError = GL_INVALID_ENUM;
    }
}

void SoftwareRendering::stencilFunc(GLenum func, GLint ref,GLuint mask){
    switch(func){
        case GL_NEVER:
        case GL_LESS:
        case GL_EQUAL:
        case GL_LEQUAL:
        case GL_GREATER:
        case GL_NOTEQUAL:
        case GL_GEQUAL:
        case GL_ALWAYS:
            SoftwareRendering::curStencilFunc = func;
            SoftwareRendering::curStencilFuncRef = ref;
            SoftwareRendering::curStencilFuncMask = mask;
        break;

        default:
            SoftwareRendering::lastError = GL_INVALID_ENUM;
    }
}

void SoftwareRendering::stencilOp(GLenum fail,GLenum zfail,GLenum zpass){
    switch(fail){
        case GL_KEEP:
        case GL_ZERO:
        case GL_REPLACE:
        case GL_INCR:
        case GL_INCR_WRAP:
        case GL_DECR:
        case GL_DECR_WRAP:
        case GL_INVERT:
        break;

        default:
            SoftwareRendering::lastError = GL_INVALID_ENUM;
        return;
    }
    switch(zfail){
        case GL_KEEP:
        case GL_ZERO:
        case GL_REPLACE:
        case GL_INCR:
        case GL_INCR_WRAP:
        case GL_DECR:
        case GL_DECR_WRAP:
        case GL_INVERT:
        break;

        default:
            SoftwareRendering::lastError = GL_INVALID_ENUM;
        return;
    }
    switch(zpass){
        case GL_KEEP:
        case GL_ZERO:
        case GL_REPLACE:
        case GL_INCR:
        case GL_INCR_WRAP:
        case GL_DECR:
        case GL_DECR_WRAP:
        case GL_INVERT:
        break;

        default:
            SoftwareRendering::lastError = GL_INVALID_ENUM;
        return;
    }

    SoftwareRendering::curStencilFail = fail;
    SoftwareRendering::curStencilZFail = zfail;
    SoftwareRendering::curStencilZPass = zpass;

}

}
