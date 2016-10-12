#include <Fantasy2C/SoftwareRendering.hpp>

/**
*Blend Func:
*Rs, Gs, Bs, As = Src Color(RGBA)
*Rd, Gd, Bd, Ad = Dst Color(RGBA)
*Rc, Gc, Bc, Ac = blend color (RGBA) (glBlendColor)
*(1,1,1,1) = maximal RGBA Value
*(0,0,0,0) = minimal RGBA Value
*
*sB = sizeof(type) * 8 = Size of Type in Bits
*kR, kG, kB, kA = 2^sB - 1  = Maximum Value of Color(RGBA)
*e.g.
*uByte:
*kX = 2^8 - 1 = 255
*
*i = min(As, kA - dA) /kA
*Result = RGBA * ...
*GL_ZERO 	                    RGBA * (0,0,0,0)
*GL_ONE 	                    RGBA * (1,1,1,1)
*GL_SRC_COLOR 	                RGBA * (Rs/kR, Gs/kG, Bs/kB, As/kA)
*GL_ONE_MINUS_SRC_COLOR 	    RGBA * ((1,1,1,1) - (Rs/kR, Gs/kG, Bs/kB, As/kA))
*GL_DST_COLOR 	                RGBA * (Rd/kR, Gd/kG, Bd/kB, Ad/kA)
*GL_ONE_MINUS_DST_COLOR 	    RGBA * ((1,1,1,1) - (Rd/kR, Gd/kG, Bd/kB, Ad/kA))
*GL_SRC_ALPHA 	                RGBA * (As/kA, As/kA, As/kA, As/kA)
*GL_ONE_MINUS_SRC_ALPHA 	    RGBA * ((1,1,1,1) - (As/kA, As/kA, As/kA, As/kA))
*GL_DST_ALPHA 	                RGBA * (Ad/kA, Ad/kA, Ad/kA, Ad/kA)
*GL_ONE_MINUS_DST_ALPHA 	    RGBA * ((1,1,1,1) - (Ad/kA, Ad/kA, Ad/kA, Ad/kA))
*GL_CONSTANT_COLOR 	            RGBA * (Rc, Gc, Bc, Ac)
*GL_ONE_MINUS_CONSTANT_COLOR 	RGBA * ((1,1,1,1) - (Rc, Gc, Bc, Ac))
*GL_CONSTANT_ALPHA 	            RGBA * (Ac, Ac, Ac, Ac)
*GL_ONE_MINUS_CONSTANT_ALPHA 	RGBA * (1,1,1,1) - (Ac, Ac, Ac, Ac)
*GL_SRC_ALPHA_SATURATE 	        RGBA * (i,i,i,1)
*
*
*http://wiki.delphigl.com/index.php/glBlendFunc
*/

namespace F2C{

void SoftwareRendering::blendFunc(GLenum sfactor,GLenum dfactor){
    switch(sfactor){
        case GL_ZERO:
        case GL_ONE:
        case GL_SRC_COLOR:
        case GL_ONE_MINUS_SRC_COLOR:
        case GL_DST_COLOR:
        case GL_ONE_MINUS_DST_COLOR:
        case GL_SRC_ALPHA:
        case GL_ONE_MINUS_SRC_ALPHA:
        case GL_DST_ALPHA:
        case GL_ONE_MINUS_DST_ALPHA:
        case GL_CONSTANT_COLOR:
        case GL_ONE_MINUS_CONSTANT_COLOR:
        case GL_CONSTANT_ALPHA:
        case GL_ONE_MINUS_CONSTANT_ALPHA:
        case GL_SRC_ALPHA_SATURATE:
            SoftwareRendering::blendSrcMode = sfactor;
        break;

        default:
            SoftwareRendering::lastError = GL_INVALID_ENUM;
        return;
    }

    switch(dfactor){
        case GL_ZERO:
        case GL_ONE:
        case GL_SRC_COLOR:
        case GL_ONE_MINUS_SRC_COLOR:
        case GL_DST_COLOR:
        case GL_ONE_MINUS_DST_COLOR:
        case GL_SRC_ALPHA:
        case GL_ONE_MINUS_SRC_ALPHA:
        case GL_DST_ALPHA:
        case GL_ONE_MINUS_DST_ALPHA:
        case GL_CONSTANT_COLOR:
        case GL_ONE_MINUS_CONSTANT_COLOR:
        case GL_CONSTANT_ALPHA:
        case GL_ONE_MINUS_CONSTANT_ALPHA:
        case GL_SRC_ALPHA_SATURATE:
            SoftwareRendering::blendDstMode = dfactor;
        break;

        default:
            SoftwareRendering::lastError = GL_INVALID_ENUM;
        return;
    }
}

void SoftwareRendering::blendFuncPixel(GLenum mode, //Blend Mode (GL_ONE,GL_ZERO,GL_SRC_COLOR,GL_DST_COLOR,...)
                                    GLubyte* rgbaPixels, //out Pixels (must RGBA format)
                                    const GLubyte* srcPixels, //pixels of Src (must RGBA format)
                                    const GLubyte* dstPixels, //pixels of Dst (must RGBA format)
                                    const Color4f& cBlendColor)
{
    if(mode == GL_ONE)
        return;
    if(mode == GL_ZERO){
        rgbaPixels[0] =
        rgbaPixels[1] =
        rgbaPixels[2] =
        rgbaPixels[3] = 0;
        return;
    }

    GLubyte constBlendColor[4] = { cBlendColor.r,cBlendColor.g,cBlendColor.b,cBlendColor.a };
    GLubyte ca = cBlendColor.a;

    //alpha Values
    GLubyte sa = srcPixels[3];
    GLubyte da = dstPixels[3];

    switch(mode){
        break;
        case GL_SRC_COLOR:
            rgbaPixels[0] = rgbaPixels[0] * srcPixels[0] / 255.0f;
            rgbaPixels[1] = rgbaPixels[1] * srcPixels[0] / 255.0f;
            rgbaPixels[2] = rgbaPixels[2] * srcPixels[0] / 255.0f;
            rgbaPixels[3] = rgbaPixels[3] * srcPixels[0] / 255.0f;
        break;
        case GL_ONE_MINUS_SRC_COLOR:
            rgbaPixels[0] = rgbaPixels[0] * (255 - srcPixels[0]) / 255.0f;
            rgbaPixels[1] = rgbaPixels[1] * (255 - srcPixels[1]) / 255.0f;
            rgbaPixels[2] = rgbaPixels[2] * (255 - srcPixels[2]) / 255.0f;
            rgbaPixels[3] = rgbaPixels[3] * (255 - srcPixels[3]) / 255.0f;
        break;
        case GL_DST_COLOR:
            rgbaPixels[0] = rgbaPixels[0] * dstPixels[0] / 255.0f;
            rgbaPixels[1] = rgbaPixels[1] * dstPixels[1] / 255.0f;
            rgbaPixels[2] = rgbaPixels[2] * dstPixels[2] / 255.0f;
            rgbaPixels[3] = rgbaPixels[3] * dstPixels[3] / 255.0f;
        break;
        case GL_ONE_MINUS_DST_COLOR:
            rgbaPixels[0] = rgbaPixels[0] * (255 - dstPixels[0]) / 255.0f;
            rgbaPixels[1] = rgbaPixels[1] * (255 - dstPixels[1]) / 255.0f;
            rgbaPixels[2] = rgbaPixels[2] * (255 - dstPixels[2]) / 255.0f;
            rgbaPixels[3] = rgbaPixels[3] * (255 - dstPixels[3]) / 255.0f;
        break;
        case GL_DST_ALPHA:
            rgbaPixels[0] = rgbaPixels[0] * da / 255.0f;
            rgbaPixels[1] = rgbaPixels[1] * da / 255.0f;
            rgbaPixels[2] = rgbaPixels[2] * da / 255.0f;
            rgbaPixels[3] = rgbaPixels[3] * da / 255.0f;
        break;
        case GL_ONE_MINUS_DST_ALPHA:
            rgbaPixels[0] = rgbaPixels[0] * (255 - da) / 255.0f;
            rgbaPixels[1] = rgbaPixels[1] * (255 - da) / 255.0f;
            rgbaPixels[2] = rgbaPixels[2] * (255 - da) / 255.0f;
            rgbaPixels[3] = rgbaPixels[3] * (255 - da) / 255.0f;
        break;
        case GL_CONSTANT_COLOR:
            rgbaPixels[0] = rgbaPixels[0] * constBlendColor[0] / 255.0f;
            rgbaPixels[1] = rgbaPixels[1] * constBlendColor[1] / 255.0f;
            rgbaPixels[2] = rgbaPixels[2] * constBlendColor[2] / 255.0f;
            rgbaPixels[3] = rgbaPixels[3] * constBlendColor[3] / 255.0f;
        break;
        case GL_ONE_MINUS_CONSTANT_COLOR:
            rgbaPixels[0] = rgbaPixels[0] * (255 - constBlendColor[0]) / 255.0f;
            rgbaPixels[1] = rgbaPixels[1] * (255 - constBlendColor[1]) / 255.0f;
            rgbaPixels[2] = rgbaPixels[2] * (255 - constBlendColor[2]) / 255.0f;
            rgbaPixels[3] = rgbaPixels[3] * (255 - constBlendColor[3]) / 255.0f;
        break;
        case GL_CONSTANT_ALPHA:
            rgbaPixels[0] = rgbaPixels[0] * ca / 255.0f;
            rgbaPixels[1] = rgbaPixels[1] * ca / 255.0f;
            rgbaPixels[2] = rgbaPixels[2] * ca / 255.0f;
            rgbaPixels[3] = rgbaPixels[3] * ca / 255.0f;
        break;
        case GL_ONE_MINUS_CONSTANT_ALPHA:
            rgbaPixels[0] = rgbaPixels[0] * (255 - ca) / 255.0f;
            rgbaPixels[1] = rgbaPixels[1] * (255 - ca) / 255.0f;
            rgbaPixels[2] = rgbaPixels[2] * (255 - ca) / 255.0f;
            rgbaPixels[3] = rgbaPixels[3] * (255 - ca) / 255.0f;
        break;
        case GL_SRC_ALPHA_SATURATE:
            float sas_f = std::min<float>(sa, 255 - da) / 255.0f;
            rgbaPixels[0] = rgbaPixels[0] * sas_f;
            rgbaPixels[1] = rgbaPixels[1] * sas_f;
            rgbaPixels[2] = rgbaPixels[2] * sas_f;
        break;
    }
}

void SoftwareRendering::blendFuncPixel(GLenum mode, //Blend Mode (GL_ONE,GL_ZERO,GL_SRC_COLOR,GL_DST_COLOR,...)
                                    GLint* rgbaPixels, //out Pixels (must RGBA format)
                                    const GLint* srcPixels, //pixels of Src (must RGBA format)
                                    const GLint* dstPixels, //pixels of Dst (must RGBA format)
                                    const Color4f& cBlendColor)
{
    if(mode == GL_ONE)
        return;
    if(mode == GL_ZERO){
        rgbaPixels[0] =
        rgbaPixels[1] =
        rgbaPixels[2] =
        rgbaPixels[3] = 0;
        return;
    }

    GLint constBlendColor[4] = { cBlendColor.r,cBlendColor.g,cBlendColor.b,cBlendColor.a };
    GLint ca = cBlendColor.a;

    //alpha Values
    GLint sa = srcPixels[3];
    GLint da = dstPixels[3];

    switch(mode){
        break;
        case GL_SRC_COLOR:
            rgbaPixels[0] = rgbaPixels[0] * srcPixels[0] / 255.0f;
            rgbaPixels[1] = rgbaPixels[1] * srcPixels[0] / 255.0f;
            rgbaPixels[2] = rgbaPixels[2] * srcPixels[0] / 255.0f;
            rgbaPixels[3] = rgbaPixels[3] * srcPixels[0] / 255.0f;
        break;
        case GL_ONE_MINUS_SRC_COLOR:
            rgbaPixels[0] = rgbaPixels[0] * (255 - srcPixels[0]) / 255.0f;
            rgbaPixels[1] = rgbaPixels[1] * (255 - srcPixels[1]) / 255.0f;
            rgbaPixels[2] = rgbaPixels[2] * (255 - srcPixels[2]) / 255.0f;
            rgbaPixels[3] = rgbaPixels[3] * (255 - srcPixels[3]) / 255.0f;
        break;
        case GL_DST_COLOR:
            rgbaPixels[0] = rgbaPixels[0] * dstPixels[0] / 255.0f;
            rgbaPixels[1] = rgbaPixels[1] * dstPixels[1] / 255.0f;
            rgbaPixels[2] = rgbaPixels[2] * dstPixels[2] / 255.0f;
            rgbaPixels[3] = rgbaPixels[3] * dstPixels[3] / 255.0f;
        break;
        case GL_ONE_MINUS_DST_COLOR:
            rgbaPixels[0] = rgbaPixels[0] * (255 - dstPixels[0]) / 255.0f;
            rgbaPixels[1] = rgbaPixels[1] * (255 - dstPixels[1]) / 255.0f;
            rgbaPixels[2] = rgbaPixels[2] * (255 - dstPixels[2]) / 255.0f;
            rgbaPixels[3] = rgbaPixels[3] * (255 - dstPixels[3]) / 255.0f;
        break;
        case GL_DST_ALPHA:
            rgbaPixels[0] = rgbaPixels[0] * da / 255.0f;
            rgbaPixels[1] = rgbaPixels[1] * da / 255.0f;
            rgbaPixels[2] = rgbaPixels[2] * da / 255.0f;
            rgbaPixels[3] = rgbaPixels[3] * da / 255.0f;
        break;
        case GL_ONE_MINUS_DST_ALPHA:
            rgbaPixels[0] = rgbaPixels[0] * (255 - da) / 255.0f;
            rgbaPixels[1] = rgbaPixels[1] * (255 - da) / 255.0f;
            rgbaPixels[2] = rgbaPixels[2] * (255 - da) / 255.0f;
            rgbaPixels[3] = rgbaPixels[3] * (255 - da) / 255.0f;
        break;
        case GL_CONSTANT_COLOR:
            rgbaPixels[0] = rgbaPixels[0] * constBlendColor[0] / 255.0f;
            rgbaPixels[1] = rgbaPixels[1] * constBlendColor[1] / 255.0f;
            rgbaPixels[2] = rgbaPixels[2] * constBlendColor[2] / 255.0f;
            rgbaPixels[3] = rgbaPixels[3] * constBlendColor[3] / 255.0f;
        break;
        case GL_ONE_MINUS_CONSTANT_COLOR:
            rgbaPixels[0] = rgbaPixels[0] * (255 - constBlendColor[0]) / 255.0f;
            rgbaPixels[1] = rgbaPixels[1] * (255 - constBlendColor[1]) / 255.0f;
            rgbaPixels[2] = rgbaPixels[2] * (255 - constBlendColor[2]) / 255.0f;
            rgbaPixels[3] = rgbaPixels[3] * (255 - constBlendColor[3]) / 255.0f;
        break;
        case GL_CONSTANT_ALPHA:
            rgbaPixels[0] = rgbaPixels[0] * ca / 255.0f;
            rgbaPixels[1] = rgbaPixels[1] * ca / 255.0f;
            rgbaPixels[2] = rgbaPixels[2] * ca / 255.0f;
            rgbaPixels[3] = rgbaPixels[3] * ca / 255.0f;
        break;
        case GL_ONE_MINUS_CONSTANT_ALPHA:
            rgbaPixels[0] = rgbaPixels[0] * (255 - ca) / 255.0f;
            rgbaPixels[1] = rgbaPixels[1] * (255 - ca) / 255.0f;
            rgbaPixels[2] = rgbaPixels[2] * (255 - ca) / 255.0f;
            rgbaPixels[3] = rgbaPixels[3] * (255 - ca) / 255.0f;
        break;
        case GL_SRC_ALPHA_SATURATE:
            float sas_f = std::min<float>(sa, 255 - da) / 255.0f;
            rgbaPixels[0] = rgbaPixels[0] * sas_f;
            rgbaPixels[1] = rgbaPixels[1] * sas_f;
            rgbaPixels[2] = rgbaPixels[2] * sas_f;
        break;
    }
}

void SoftwareRendering::blendFuncPixels(GLenum mode, //Blend Mode (GL_ONE,GL_ZERO,GL_SRC_COLOR,GL_DST_COLOR,...)
                                    GLubyte* rgbaPixels, //out Pixels (must RGBA format)
                                    const GLubyte* srcPixels, //pixels of Src (must RGBA format)
                                    const GLubyte* dstPixels, //pixels of Dst (must RGBA format)
                                    size_t rgbaPixelsSize, //Sizes of Pixels
                                    size_t srcSize,
                                    size_t dstSize,
                                    const Color4f& cBlendColor)
{
    if(mode == GL_ONE)
        return;
    if(mode == GL_ZERO){
        memset(rgbaPixels,0,rgbaPixelsSize);
        return;
    }

    GLubyte constBlendColor[4] = { cBlendColor.r,cBlendColor.g,cBlendColor.b,cBlendColor.a };
    GLubyte ca = constBlendColor[3];
    size_t ip = 0;
    uint8 j = 0;

    for(size_t i = 0;i < rgbaPixelsSize || i < srcSize || i < dstSize;i+=4){ //pixels

        //alpha Values
        GLubyte sa = srcPixels[i+3];
        GLubyte da = dstPixels[i+3];

        for(j = 0;j < 4;j++){ //color
            ip = i+j;
            switch(mode){
                break;
                case GL_SRC_COLOR:
                    rgbaPixels[ip] = rgbaPixels[ip] * srcPixels[ip] / 255.0f;
                break;
                case GL_ONE_MINUS_SRC_COLOR:
                    rgbaPixels[ip] = rgbaPixels[ip] * (255 - srcPixels[ip]) / 255.0f;
                break;
                case GL_DST_COLOR:
                    rgbaPixels[ip] = rgbaPixels[ip] * dstPixels[ip] / 255.0f;
                break;
                case GL_ONE_MINUS_DST_COLOR:
                    rgbaPixels[ip] = rgbaPixels[ip] * (255 - dstPixels[ip]) / 255.0f;
                break;
                case GL_DST_ALPHA:
                    rgbaPixels[ip] = rgbaPixels[ip] * da / 255.0f;
                break;
                case GL_ONE_MINUS_DST_ALPHA:
                    rgbaPixels[ip] = rgbaPixels[ip] * (255 - da) / 255.0f;
                break;
                case GL_CONSTANT_COLOR:
                    rgbaPixels[ip] = rgbaPixels[ip] * constBlendColor[j] / 255.0f;
                break;
                case GL_ONE_MINUS_CONSTANT_COLOR:
                    rgbaPixels[ip] = rgbaPixels[ip] * (255 - constBlendColor[j]) / 255.0f;
                break;
                case GL_CONSTANT_ALPHA:
                    rgbaPixels[ip] = rgbaPixels[ip] * ca / 255.0f;
                break;
                case GL_ONE_MINUS_CONSTANT_ALPHA:
                    rgbaPixels[ip] = rgbaPixels[ip] * (255 - ca) / 255.0f;
                break;
                case GL_SRC_ALPHA_SATURATE:
                    if(j < 3){//only RGB
                        float f = std::min<float>(sa, 255 - da) / 255.0f;
                        rgbaPixels[ip] = rgbaPixels[ip] * f;
                    }
                break;
            }
        }
    }
}

void SoftwareRendering::blendFuncPixels(GLenum mode, //Blend Mode (GL_ONE,GL_ZERO,GL_SRC_COLOR,GL_DST_COLOR,...)
                                    GLint* rgbaPixels, //out Pixels (must RGBA format)
                                    const GLint* srcPixels, //pixels of Src (must RGBA format)
                                    const GLint* dstPixels, //pixels of Dst (must RGBA format)
                                    size_t rgbaPixelsSize, //Sizes of Pixels
                                    size_t srcSize,
                                    size_t dstSize,
                                    const Color4f& cBlendColor)
{
    if(mode == GL_ONE)
        return;
    if(mode == GL_ZERO){
        memset(rgbaPixels,0,rgbaPixelsSize*sizeof(int));
        return;
    }

    GLubyte constBlendColor[4] = { cBlendColor.r,cBlendColor.g,cBlendColor.b,cBlendColor.a };
    GLint ca = constBlendColor[3];
    size_t ip = 0;
    uint8 j = 0;
    //SRC_ALPHA_SATURATE factor

    for(size_t i = 0;i < rgbaPixelsSize || i < srcSize || i < dstSize;i+=4){ //pixels

        //alpha Values
        GLint sa = srcPixels[i+3];
        GLint da = dstPixels[i+3];

        for(j = 0;j < 4;j++){ //color
            ip = i+j;
            switch(mode){
                break;
                case GL_SRC_COLOR:
                    rgbaPixels[ip] = rgbaPixels[ip] * srcPixels[ip] / 255.0f;
                break;
                case GL_ONE_MINUS_SRC_COLOR:
                    rgbaPixels[ip] = rgbaPixels[ip] * (255 - srcPixels[ip]) / 255.0f;
                break;
                case GL_DST_COLOR:
                    rgbaPixels[ip] = rgbaPixels[ip] * dstPixels[ip] / 255.0f;
                break;
                case GL_ONE_MINUS_DST_COLOR:
                    rgbaPixels[ip] = rgbaPixels[ip] * (255 - dstPixels[ip]) / 255.0f;
                break;
                case GL_DST_ALPHA:
                    rgbaPixels[ip] = rgbaPixels[ip] * da / 255.0f;
                break;
                case GL_ONE_MINUS_DST_ALPHA:
                    rgbaPixels[ip] = rgbaPixels[ip] * (255 - da) / 255.0f;
                break;
                case GL_CONSTANT_COLOR:
                    rgbaPixels[ip] = rgbaPixels[ip] * constBlendColor[j] / 255.0f;
                break;
                case GL_ONE_MINUS_CONSTANT_COLOR:
                    rgbaPixels[ip] = rgbaPixels[ip] * (255 - constBlendColor[j]) / 255.0f;
                break;
                case GL_CONSTANT_ALPHA:
                    rgbaPixels[ip] = rgbaPixels[ip] * ca / 255.0f;
                break;
                case GL_ONE_MINUS_CONSTANT_ALPHA:
                    rgbaPixels[ip] = rgbaPixels[ip] * (255 - ca) / 255.0f;
                break;
                case GL_SRC_ALPHA_SATURATE:
                    if(j < 3){//only RGB
                        float sas_f = std::min<float>(sa, 255 - da) / 255.0f;
                        rgbaPixels[ip] = rgbaPixels[ip] * sas_f;
                    }
                break;
            }
        }
    }
}

}

