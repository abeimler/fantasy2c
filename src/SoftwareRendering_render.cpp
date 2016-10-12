#include<Fantasy2C/SoftwareRendering.hpp>


namespace F2C{

bool SoftwareRendering::testDepth(size_t i,GLint z){
    bool isinBuffer = SoftwareRendering::enableSSC[GL_DEPTH_TEST] && z >= SoftwareRendering::rangeNear && z <= SoftwareRendering::rangeFar;
    if(!isinBuffer)
        return false;

    switch(SoftwareRendering::curDepthFunc){
        case GL_NEVER:
            return false;
        case GL_LESS:
            return z < SoftwareRendering::depthBuffer[i];
        case GL_EQUAL:
            return z == SoftwareRendering::depthBuffer[i];
        case GL_LEQUAL:
            return z <= SoftwareRendering::depthBuffer[i];
        case GL_GREATER:
            return z > SoftwareRendering::depthBuffer[i];
        case GL_NOTEQUAL:
            return z != SoftwareRendering::depthBuffer[i];
        case GL_GEQUAL:
            return z >= SoftwareRendering::depthBuffer[i];
        case GL_ALWAYS:
            return true;
        default:
            return false;
    }
}

void SoftwareRendering::renderPointColor(){
    // Plot the pixel
    if (SoftwareRendering::curPointSize == 1){
        SoftwareRendering::setFrame(
            SoftwareRendering::curVertex[0]->pos.x, SoftwareRendering::curVertex[0]->pos.y,
            SoftwareRendering::curVertex[0]->pos.z,
            SoftwareRendering::curVertex[0]->clr.red, SoftwareRendering::curVertex[0]->clr.green,
            SoftwareRendering::curVertex[0]->clr.blue, SoftwareRendering::curVertex[0]->clr.alpha
        );
    }else{
        int half = SoftwareRendering::curPointSize/2;
        int i;
        for (int y = half*-1; y < half; ++y){
            for (int x = half*-1; x < half; ++x){
                i = (SoftwareRendering::curVertex[0]->pos.y + y) * SoftwareRendering::screenSize.width +
                        SoftwareRendering::curVertex[0]->pos.x + x;

                if (i < 0 || i >= SoftwareRendering::depthBufferSize || !SoftwareRendering::testDepth(i, SoftwareRendering::curVertex[0]->pos.z))
                    continue;

                SoftwareRendering::setFrame(
                    SoftwareRendering::curVertex[0]->pos.x + x, SoftwareRendering::curVertex[0]->pos.y + y,
                    SoftwareRendering::curVertex[0]->pos.z,
                    SoftwareRendering::curVertex[0]->clr.red, SoftwareRendering::curVertex[0]->clr.green,
                    SoftwareRendering::curVertex[0]->clr.blue, SoftwareRendering::curVertex[0]->clr.alpha
                );
            }
        }
    }

}

}
