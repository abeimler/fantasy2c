#include <Fantasy2C/SoftwareRendering.hpp>

namespace F2C{

GLenum SoftwareRendering::blendSrcMode = GL_ONE;
GLenum SoftwareRendering::blendDstMode = GL_ZERO;

const size_t SoftwareRendering::RENDER_PIPELINE_SIZE = 4;
const size_t SoftwareRendering::TEXTURE_LAYER_SIZE = 2;
const size_t SoftwareRendering::MAX_MIPMAPLEVELS = sizeof(int)*8;

std::vector<Vertex*> SoftwareRendering::curVertex;
std::vector<Vertex*> SoftwareRendering::curMemVertex;
std::vector<Texture2D*> SoftwareRendering::curTexture;

Color4f SoftwareRendering::constBlendColor (0.0f,0.0f,0.0f,0.0f);
Color4f SoftwareRendering::setClearColor (0.0f,0.0f,0.0f,0.0f);
double SoftwareRendering::setClearDepth = 0.0f;

std::map<GLenum,bool> SoftwareRendering::enableSSC; //enable or disable server-side capabilities (glEnable status)

GLint* SoftwareRendering::stencilBuffer = NULL;
GLint* SoftwareRendering::depthBuffer = NULL;
GLint* SoftwareRendering::pixelBuffer = NULL;

size_t SoftwareRendering::depthBufferSize = 8;
size_t SoftwareRendering::colorBufferSize = 8;
size_t SoftwareRendering::stencilBufferSize = 8;

Rect SoftwareRendering::bufferSize;

size_t SoftwareRendering::PLIndex = 0;

GLenum SoftwareRendering::matrixMode = GL_MODELVIEW;
size_t SoftwareRendering::textureLayer = 0;
size_t SoftwareRendering::maxTextureLayer = 1;
size_t SoftwareRendering::textureMipMapLevel = 0;
bool SoftwareRendering::updateVerticesMatrix = true;
size_t SoftwareRendering::lineWidth = 1;
size_t SoftwareRendering::pointSize = 1;

Rect SoftwareRendering::pixelRect;
Rect SoftwareRendering::viewportRect;
Rect SoftwareRendering::scissorRect;
Rect SoftwareRendering::screenSize;

GLfloat SoftwareRendering::planeNear = 1.0f;
GLfloat SoftwareRendering::planeFar = 100.0f;

GLfloat SoftwareRendering::rangeNear = 1.0f;
GLfloat SoftwareRendering::rangeFar = 1.0f / 100.0f;

GLfloat SoftwareRendering::fieldOfView = 320.0f;

std::vector< Matrix4<float> > SoftwareRendering::renderMatrix (static_cast<size_t>(SoftwareRendering::ProjectionsMatrix::MAX_MATRICES));

size_t SoftwareRendering::texID = 0;

void SoftwareRendering::getCurTexelColor(Color4ub& outcol,size_t pixelIndex){
    outcol.r = SoftwareRendering::curTexture[SoftwareRendering::textureLayer]->[SoftwareRendering::textureMipMapLevel][pixelIndex];
    outcol.g = SoftwareRendering::curTexture[SoftwareRendering::textureLayer]->[SoftwareRendering::textureMipMapLevel][pixelIndex+1];
    outcol.b = SoftwareRendering::curTexture[SoftwareRendering::textureLayer]->[SoftwareRendering::textureMipMapLevel][pixelIndex+2];
    outcol.a = SoftwareRendering::curTexture[SoftwareRendering::textureLayer]->[SoftwareRendering::textureMipMapLevel][pixelIndex+3];
}

Color4d SoftwareRendering::InterpolateColor(const Color4d& col1, const Color4d& col2,double t){
    return Color4d(col1.r + (col2.r - col1.r) * t,
                    col1.g + (col2.g - col1.g) * t,
                    col1.b + (col2.b - col1.b) * t,
                    col1.a + (col2.a - col1.a) * t );
}

bool SoftwareRendering::isInsidePixelBuffer(int x ,int y){
    return x >= SoftwareRendering::pixelRect.x && y >= SoftwareRendering::pixelRect.y &&
            x < SoftwareRendering::pixelRect.width && y < SoftwareRendering::pixelRect.height;
}

bool SoftwareRendering::isInsidePixelBuffer(int x ,int y,int z,size_t depthBufferIndex){
    return( x >= SoftwareRendering::pixelRect.x && y >= SoftwareRendering::pixelRect.y &&
            x < SoftwareRendering::pixelRect.width && y < SoftwareRendering::pixelRect.height ) &&
            ( (SoftwareRendering::enableSSC[GL_DEPTH_TEST])? z >= SoftwareRendering::rangeNear && z <= SoftwareRendering::rangeFar && z < SoftwareRendering::depthBuffer[depthBufferIndex] : true );
}

void SoftwareRendering::setPixelRGB(size_t bufferIndex,GLubyte r,GLubyte g,GLubyte b){
    bufferIndex <<= 2;
    SoftwareRendering::pixelBuffer[bufferIndex+0] = r;
    SoftwareRendering::pixelBuffer[bufferIndex+1] = g;
    SoftwareRendering::pixelBuffer[bufferIndex+2] = b;
}

void SoftwareRendering::setPixelRGBA(size_t bufferIndex,GLubyte r,GLubyte g,GLubyte b,GLubyte a){
    bufferIndex <<= 2;
    SoftwareRendering::pixelBuffer[bufferIndex+0] = (((r+1) * a) + ((SoftwareRendering::pixelBuffer[bufferIndex+0]+1) * (256-a))) >> 8;
    SoftwareRendering::pixelBuffer[bufferIndex+1] = (((g+1) * a) + ((SoftwareRendering::pixelBuffer[bufferIndex+1]+1) * (256-a))) >> 8;
    SoftwareRendering::pixelBuffer[bufferIndex+2] = (((b+1) * a) + ((SoftwareRendering::pixelBuffer[bufferIndex+2]+1) * (256-a))) >> 8;
    SoftwareRendering::pixelBuffer[bufferIndex+3] = (((a+1) * a) + ((SoftwareRendering::pixelBuffer[bufferIndex+3]+1) * (256-a))) >> 8;
}

void SoftwareRendering::setFrame(size_t index,GLclampf z,GLubyte r,GLubyte g,GLubyte b,GLubyte a){
    // Check if the pixel is able to render
    if (a < 0)
        return;

    // set depth
    if (SoftwareRendering::enableSSC[GL_DEPTH_TEST])
        SoftwareRendering::depthBuffer[index] = z;

    // Get the pixel buffer index
    index <<= 2;

    // Check if blending is used
    if (a == 255 || !SoftwareRendering::enableSSC[GL_BLEND]){
        // Plot the pixel
        SoftwareRendering::pixelBuffer[index] = r;
        SoftwareRendering::pixelBuffer[index+1] = g;
        SoftwareRendering::pixelBuffer[index+2] = b;
    }else{
        GLint srcColor[4] = {r,g,b,a};
        GLint* dstColor = &SoftwareRendering::pixelBuffer[index];

        // blending
        SoftwareRendering::blendFuncPixel(SoftwareRendering::blendSrcMode, //Blend Mode (GL_ONE,GL_ZERO,GL_SRC_COLOR,GL_DST_COLOR,...)
                                                srcColor, //out Pixels (must RGBA format)
                                                srcColor, //pixels of Src (must RGBA format)
                                                dstColor, //pixels of Dst (must RGBA format)
                                                SoftwareRendering::constBlendColor);
        SoftwareRendering::blendFuncPixel(SoftwareRendering::blendDstMode, //Blend Mode (GL_ONE,GL_ZERO,GL_SRC_COLOR,GL_DST_COLOR,...)
                                                dstColor, //out Pixels (must RGBA format)
                                                srcColor, //pixels of Src (must RGBA format)
                                                dstColor, //pixels of Dst (must RGBA format)
                                                SoftwareRendering::constBlendColor);

        // plot the pixel
        SoftwareRendering::pixelBuffer[index] += srcColor[0];
        SoftwareRendering::pixelBuffer[index+1] += srcColor[1];
        SoftwareRendering::pixelBuffer[index+2] += srcColor[2];
        SoftwareRendering::pixelBuffer[index+3] += srcColor[3];
    }
}

void SoftwareRendering::setFrameAlpha(size_t index,GLclampf z,GLubyte r,GLubyte g,GLubyte b,GLubyte a){
    // Plot the depth
    if (z >= SoftwareRendering::depthBuffer[index]){
        SoftwareRendering::depthBuffer[index] = z;

        index <<= 2;
        SoftwareRendering::pixelBuffer[index] = (((r+1) * a) + ((SoftwareRendering::pixelBuffer[index]+1) * (256-a))) >> 8;
        SoftwareRendering::pixelBuffer[index+1] = (((g+1) * a) + ((SoftwareRendering::pixelBuffer[index+1]+1) * (256-a))) >> 8;
        SoftwareRendering::pixelBuffer[index+2] = (((b+1) * a) + ((SoftwareRendering::pixelBuffer[index+2]+1) * (256-a))) >> 8;
        SoftwareRendering::pixelBuffer[index+3] = a;
    }else{
        GLint olda;

        i <<= 2;

        r = (((r+1) * a) + ((SoftwareRendering::pixelBuffer[index]+1) * (256-a))) >> 8;
        g = (((g+1) * a) + ((SoftwareRendering::pixelBuffer[index+1]+1) * (256-a))) >> 8;
        b = (((b+1) * a) + ((SoftwareRendering::pixelBuffer[index+2]+1) * (256-a))) >> 8;

        olda = SoftwareRendering::pixelBuffer[index+3];
        SoftwareRendering::pixelBuffer[index] = (((r+1) * olda) + ((SoftwareRendering::pixelBuffer[index]+1) * (256-olda))) >> 8;
        SoftwareRendering::pixelBuffer[index+1] = (((g+1) * olda) + ((SoftwareRendering::pixelBuffer[index+1]+1) * (256-olda))) >> 8;
        SoftwareRendering::pixelBuffer[index+2] = (((b+1) * olda) + ((SoftwareRendering::pixelBuffer[index+2]+1) * (256-olda))) >> 8;
        SoftwareRendering::pixelBuffer[index+3] = a;
    }
}

void SoftwareRendering::setFrame(int x, int y,GLclampf z,GLubyte r,GLubyte g,GLubyte b,GLubyte a){
    if (x < SoftwareRendering::pixelRect.x || y < SoftwareRendering::pixelRect.y ||
        x >= SoftwareRendering::pixelRect.height || y >= SoftwareRendering::pixelRect.height)
            return;

    SoftwareRendering::setFrame(x+y*SoftwareRendering::bufferSize.width, z, r, g, b, a);
}

void SoftwareRendering::getFreeVisibleVertexIndexA(int index,const Vector<int>& veci){
	switch (index){
        case 0:
            veci.x = 1, veci.y = 2; 
		break;
        case 1:
            veci.x = 2, veci.y = 0; 
		break;
        case 2:
            veci.x = 0, veci.y = 1; 
		break;
    }
}
int SoftwareRendering::getFreeVisibleVertexIndexB(int index1,int index2){
	switch (index1){
        case 0:
            switch (index2){
                case 1: return 2;
                case 2: return 1;
            }
            break;
        case 1:
            switch (index2){
                case 0: return 2;
                case 2: return 0;
            }
            break;
        case 2:
            switch (index2){
                case 0: return 1;
                case 1: return 0;
            }
            break;
    }
    
    return -1;
}
void SoftwareRendering::enable(GLenum mode){
    SoftwareRendering::enableSSC[mode] = true;
}
void SoftwareRendering::disable(GLenum mode){
    SoftwareRendering::enableSSC[mode] = false;
}

void SoftwareRendering::blendFunc(GLenum sfactor,GLenum dfactor){
    SoftwareRendering::blendSrcMode = sfactor;
    SoftwareRendering::blendDstMode = dfactor;
}

void SoftwareRendering::clearColor(GLclampf red,GLclampf green,GLclampf blue,GLclampf alpha){
    SoftwareRendering::setClearColor = Color4f (red,green,blue,alpha);
}

void SoftwareRendering::clearDepth(GLclampd depth){
    SoftwareRendering::setClearDepth = depth;
}

}
