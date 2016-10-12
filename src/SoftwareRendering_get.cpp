#include <Fantasy2C/SoftwareRendering.hpp>

namespace F2C{

GLboolean SoftwareRendering::isEnable(GLenum mode){
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
            return SoftwareRendering::enableSSC[mode];
        break;

        default:
            SoftwareRendering::lastError = GL_INVALID_ENUM;
            return false;
    }
}


std::string SoftwareRendering::getString(GLenum name){
    switch (name){
        case GL_VENDOR:
            return "Fantasy2C Engine";
        case GL_RENDERER:
            return "Fantasy2C Software Rendering";
        case GL_VERSION:
            return "1.2.5";
    }

    SoftwareRendering::lastError = GL_INVALID_ENUM;
    return "";
}
GLenum SoftwareRendering::getError(){
    return SoftwareRendering::lastError;
}

void SoftwareRendering::getFloat(GLenum pname,GLfloat* params){
    if(!params)
        return;

    switch (pname){
        case GL_SCISSOR_BOX:
            params[0] = SoftwareRendering::scissorRect.x;
            params[1] = SoftwareRendering::scissorRect.y;
            params[2] = SoftwareRendering::scissorRect.width;
            params[3] = SoftwareRendering::scissorRect.height;
        return;

        case GL_VIEWPORT:
            params[0] = SoftwareRendering::viewportRect.x;
            params[1] = SoftwareRendering::viewportRect.y;
            params[2] = SoftwareRendering::viewportRect.width;
            params[3] = SoftwareRendering::viewportRect.height;
        return;

        case GL_BLEND_COLOR:
            params[0] = SoftwareRendering::constBlendColor.r;
            params[1] = SoftwareRendering::constBlendColor.g;
            params[2] = SoftwareRendering::constBlendColor.b;
            params[3] = SoftwareRendering::constBlendColor.a;
        return;
        case GL_BLEND_SRC:
            *params = SoftwareRendering::blendSrcMode;
        return;
        case GL_BLEND_DST:
            *params = SoftwareRendering::blendDstMode;
        return;

        case GL_LINE_WIDTH:
            *params = SoftwareRendering::curLineWidth;
        return;
        case GL_RGBA_MODE:
            *params = GL_TRUE;
        return;

        case GL_MODELVIEW_MATRIX:
            SoftwareRendering::SoftwareRendering::renderMatrix[SoftwareRendering::MODELVIEW_MATRIX].get(params);
        return;
        case GL_PROJECTION_MATRIX:
            SoftwareRendering::SoftwareRendering::renderMatrix[SoftwareRendering::PROJECTION_MATRIX].get(params);
        return;
        case GL_TEXTURE_MATRIX:
            SoftwareRendering::SoftwareRendering::renderMatrix[SoftwareRendering::TEXTURE_MATRIX].get(params);
        return;


        case GL_CURRENT_COLOR:
            params[0] = SoftwareRendering::curVertex[SoftwareRendering::PLIndex]->clr.red;
            params[1] = SoftwareRendering::curVertex[SoftwareRendering::PLIndex]->clr.green;
            params[2] = SoftwareRendering::curVertex[SoftwareRendering::PLIndex]->clr.blue;
            params[3] = SoftwareRendering::curVertex[SoftwareRendering::PLIndex]->clr.alpha;
        return;
        case GL_CURRENT_NORMAL:
            params[0] = SoftwareRendering::curVertex[SoftwareRendering::PLIndex]->nml.x;
            params[1] = SoftwareRendering::curVertex[SoftwareRendering::PLIndex]->nml.y;
            params[2] = SoftwareRendering::curVertex[SoftwareRendering::PLIndex]->nml.z;
        return;
        case GL_CURRENT_TEXTURE_COORDS:
            params[0] = SoftwareRendering::curVertex[SoftwareRendering::PLIndex]->map[0].x;
            params[1] = SoftwareRendering::curVertex[SoftwareRendering::PLIndex]->map[0].y;
            params[2] = SoftwareRendering::curVertex[SoftwareRendering::PLIndex]->map[0].z;
            params[3] = SoftwareRendering::curVertex[SoftwareRendering::PLIndex]->map[0].w;
        return;
        case GL_SHADE_MODEL:
            params[0] = SoftwareRendering::curShadeModel;
        return;

        case GL_COLOR_CLEAR_VALUE:
            params[0] = SoftwareRendering::curClearColor.r;
            params[1] = SoftwareRendering::curClearColor.g;
            params[2] = SoftwareRendering::curClearColor.b;
            params[3] = SoftwareRendering::curClearColor.a;
        return;
        case GL_DEPTH_CLEAR_VALUE:
            params[0] = SoftwareRendering::curClearDepth;
        return;
        case GL_STENCIL_CLEAR_VALUE:
            params[0] = SoftwareRendering::curClearStencil;
        return;

        case GL_ALPHA_TEST_FUNC:
            params[0] = SoftwareRendering::curAlphaFunc;
        return;
        case GL_ALPHA_TEST_REF:
            params[0] = SoftwareRendering::curAlphaFuncRef;
        return;
        case GL_DEPTH_FUNC:
            params[0] = SoftwareRendering::curDepthFunc;
        return;
        case GL_STENCIL_FUNC:
            params[0] = SoftwareRendering::curStencilFunc;
        return;
        case GL_STENCIL_REF:
            params[0] = SoftwareRendering::curStencilFuncRef;
        return;
        case GL_STENCIL_VALUE_MASK:
            params[0] = SoftwareRendering::curStencilFuncMask;
        return;

        case GL_STENCIL_FAIL:
            params[0] = SoftwareRendering::curStencilFail;
        return;
        case GL_STENCIL_PASS_DEPTH_PASS:
            params[0] = SoftwareRendering::curStencilZPass;
        return;
        case GL_STENCIL_PASS_DEPTH_FAIL:
            params[0] = SoftwareRendering::curStencilZFail;
        return;

        case GL_ALPHA_TEST:
        case GL_BLEND:
        case GL_DEPTH_TEST:
        case GL_SCISSOR_TEST:
        case GL_NORMALIZE:
        case GL_STENCIL_TEST:
        case GL_TEXTURE_2D:
        case GL_TEXTURE_GEN_S:
        case GL_TEXTURE_GEN_T:
            *params = SoftwareRendering::enableSSC[pname];
        return;
    }

    SoftwareRendering::lastError = GL_INVALID_ENUM;
}

}
