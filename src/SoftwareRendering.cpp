#include <Fantasy2C/SoftwareRendering.hpp>

namespace F2C{

GLenum SoftwareRendering::blendSrcMode = GL_ONE;
GLenum SoftwareRendering::blendDstMode = GL_ZERO;

GLenum SoftwareRendering::curDepthFunc = GL_LESS;
GLenum SoftwareRendering::curAlphaFunc = GL_ALWAYS;

GLenum SoftwareRendering::curShadeModel = GL_SMOOTH;

GLenum SoftwareRendering::curStencilFunc = GL_ALWAYS;
GLint SoftwareRendering::curStencilFuncRef = 0;
GLuint SoftwareRendering::curStencilFuncMask = std::numeric_limits<GLuint>::max();
GLenum SoftwareRendering::curStencilFail = GL_KEEP;
GLenum SoftwareRendering::curStencilZFail = GL_KEEP;
GLenum SoftwareRendering::curStencilZPass = GL_KEEP;

const size_t SoftwareRendering::RENDER_PIPELINE_SIZE = 4;
const size_t SoftwareRendering::TEXTURE_LAYER_SIZE = 2;
const size_t SoftwareRendering::MAX_MIPMAPLEVELS = 32;

GLenum SoftwareRendering::lastError = GL_NO_ERROR;

std::vector<Vertex*> SoftwareRendering::curVertex;
std::vector<Vertex*> SoftwareRendering::curMemVertex;
std::vector<Texture2D*> SoftwareRendering::curTexture;

std::vector<GenMappingTex> SoftwareRendering::mappingGenType;

Color4f SoftwareRendering::constBlendColor (0.0f,0.0f,0.0f,0.0f);
Color4f SoftwareRendering::curClearColor (0.0f,0.0f,0.0f,0.0f);
GLclampd SoftwareRendering::curClearDepth = 0.0f;
GLint SoftwareRendering::curClearStencil = 0;
GLclampf SoftwareRendering::curAlphaFuncRef = 0;

std::map<GLenum,bool> SoftwareRendering::enableSSC; //enable or disable server-side capabilities (glEnable status)

GLint* SoftwareRendering::stencilBuffer = NULL;
GLint* SoftwareRendering::depthBuffer = NULL;
GLint* SoftwareRendering::colorBuffer = NULL;

size_t SoftwareRendering::depthBufferSize = 8;
size_t SoftwareRendering::colorBufferSize = 8;
size_t SoftwareRendering::stencilBufferSize = 8;

size_t SoftwareRendering::PLIndex = 0;

GLenum SoftwareRendering::curMatrixMode = GL_MODELVIEW;
size_t SoftwareRendering::textureLayer = 0;
size_t SoftwareRendering::maxTextureLayer = 32;
size_t SoftwareRendering::textureMipMapLevel = 0;
bool SoftwareRendering::updateVerticesMatrix = true;
size_t SoftwareRendering::curLineWidth = 1;
size_t SoftwareRendering::curPointSize = 1;

Rect SoftwareRendering::pixelRect;
Rect SoftwareRendering::viewportRect;
Rect SoftwareRendering::scissorRect;
Rect SoftwareRendering::screenSize;

GLfloat SoftwareRendering::planeNear = 1.0f;
GLfloat SoftwareRendering::planeFar = 100.0f;

GLfloat SoftwareRendering::rangeNear = 1.0f;
GLfloat SoftwareRendering::rangeFar = 1.0f / 100.0f;

GLfloat SoftwareRendering::fieldOfView = 320.0f;

std::vector< Matrix4<float> > SoftwareRendering::renderMatrix (static_cast<size_t>(SoftwareRendering::MAX_MATRICES));

size_t SoftwareRendering::texID = 0;
GLuint SoftwareRendering::texDeviceID = 0;

void SoftwareRendering::getCurTexelColor(Color4ub& outcol,size_t pixelIndex){
    outcol.red = SoftwareRendering::curTexture[SoftwareRendering::textureLayer]->getImage(SoftwareRendering::textureMipMapLevel)[pixelIndex];
    outcol.green = SoftwareRendering::curTexture[SoftwareRendering::textureLayer]->getImage(SoftwareRendering::textureMipMapLevel)[pixelIndex+1];
    outcol.blue = SoftwareRendering::curTexture[SoftwareRendering::textureLayer]->getImage(SoftwareRendering::textureMipMapLevel)[pixelIndex+2];
    outcol.alpha = SoftwareRendering::curTexture[SoftwareRendering::textureLayer]->getImage(SoftwareRendering::textureMipMapLevel)[pixelIndex+3];
}

void SoftwareRendering::getCurTexelColor(Color4i& outcol,size_t pixelIndex){
    outcol.r = SoftwareRendering::curTexture[SoftwareRendering::textureLayer]->getImage(SoftwareRendering::textureMipMapLevel)[pixelIndex];
    outcol.g = SoftwareRendering::curTexture[SoftwareRendering::textureLayer]->getImage(SoftwareRendering::textureMipMapLevel)[pixelIndex+1];
    outcol.b = SoftwareRendering::curTexture[SoftwareRendering::textureLayer]->getImage(SoftwareRendering::textureMipMapLevel)[pixelIndex+2];
    outcol.a = SoftwareRendering::curTexture[SoftwareRendering::textureLayer]->getImage(SoftwareRendering::textureMipMapLevel)[pixelIndex+3];
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
    SoftwareRendering::colorBuffer[bufferIndex+0] = r;
    SoftwareRendering::colorBuffer[bufferIndex+1] = g;
    SoftwareRendering::colorBuffer[bufferIndex+2] = b;
}

void SoftwareRendering::setPixelRGBA(size_t bufferIndex,GLubyte r,GLubyte g,GLubyte b,GLubyte a){
    bufferIndex <<= 2;
    SoftwareRendering::colorBuffer[bufferIndex+0] = (((r+1) * a) + ((SoftwareRendering::colorBuffer[bufferIndex+0]+1) * (256-a))) >> 8;
    SoftwareRendering::colorBuffer[bufferIndex+1] = (((g+1) * a) + ((SoftwareRendering::colorBuffer[bufferIndex+1]+1) * (256-a))) >> 8;
    SoftwareRendering::colorBuffer[bufferIndex+2] = (((b+1) * a) + ((SoftwareRendering::colorBuffer[bufferIndex+2]+1) * (256-a))) >> 8;
    SoftwareRendering::colorBuffer[bufferIndex+3] = (((a+1) * a) + ((SoftwareRendering::colorBuffer[bufferIndex+3]+1) * (256-a))) >> 8;
}

void SoftwareRendering::setFrame(size_t index,GLclampf z,GLubyte r,GLubyte g,GLubyte b,GLubyte a){
    // Check if the pixel is able to render
    if (a <= 0)
        return;

    // set depth
    if (SoftwareRendering::enableSSC[GL_DEPTH_TEST])
        SoftwareRendering::depthBuffer[index] = z;

    // Get the pixel buffer index
    index <<= 2;

    // Check if blending is used
    if (a == 255 || !SoftwareRendering::enableSSC[GL_BLEND]){
        // Plot the pixel
        SoftwareRendering::colorBuffer[index] = r;
        SoftwareRendering::colorBuffer[index+1] = g;
        SoftwareRendering::colorBuffer[index+2] = b;
    }else{
        GLint srcColor[4] = {r,g,b,a};
        GLint* dstColor = &SoftwareRendering::colorBuffer[index];

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
        SoftwareRendering::colorBuffer[index] += srcColor[0];
        SoftwareRendering::colorBuffer[index+1] += srcColor[1];
        SoftwareRendering::colorBuffer[index+2] += srcColor[2];
        SoftwareRendering::colorBuffer[index+3] += srcColor[3];
    }
}

void SoftwareRendering::setFrameAlpha(size_t index,GLclampf z,GLubyte r,GLubyte g,GLubyte b,GLubyte a){
    // Plot the depth
    if (z >= SoftwareRendering::depthBuffer[index]){
        SoftwareRendering::depthBuffer[index] = z;

        index <<= 2;
        SoftwareRendering::colorBuffer[index] = (((r+1) * a) + ((SoftwareRendering::colorBuffer[index]+1) * (256-a))) >> 8;
        SoftwareRendering::colorBuffer[index+1] = (((g+1) * a) + ((SoftwareRendering::colorBuffer[index+1]+1) * (256-a))) >> 8;
        SoftwareRendering::colorBuffer[index+2] = (((b+1) * a) + ((SoftwareRendering::colorBuffer[index+2]+1) * (256-a))) >> 8;
        SoftwareRendering::colorBuffer[index+3] = a;
    }else{
        GLint olda;

        index <<= 2;

        r = (((r+1) * a) + ((SoftwareRendering::colorBuffer[index]+1) * (256-a))) >> 8;
        g = (((g+1) * a) + ((SoftwareRendering::colorBuffer[index+1]+1) * (256-a))) >> 8;
        b = (((b+1) * a) + ((SoftwareRendering::colorBuffer[index+2]+1) * (256-a))) >> 8;

        olda = SoftwareRendering::colorBuffer[index+3];
        SoftwareRendering::colorBuffer[index] = (((r+1) * olda) + ((SoftwareRendering::colorBuffer[index]+1) * (256-olda))) >> 8;
        SoftwareRendering::colorBuffer[index+1] = (((g+1) * olda) + ((SoftwareRendering::colorBuffer[index+1]+1) * (256-olda))) >> 8;
        SoftwareRendering::colorBuffer[index+2] = (((b+1) * olda) + ((SoftwareRendering::colorBuffer[index+2]+1) * (256-olda))) >> 8;
        SoftwareRendering::colorBuffer[index+3] = a;
    }
}

void SoftwareRendering::setFrame(int x, int y,GLclampf z,GLubyte r,GLubyte g,GLubyte b,GLubyte a){
    if (x < SoftwareRendering::pixelRect.x || y < SoftwareRendering::pixelRect.y ||
        x >= SoftwareRendering::pixelRect.height || y >= SoftwareRendering::pixelRect.height)
            return;

    SoftwareRendering::setFrame(x+y*SoftwareRendering::screenSize.width, z, r, g, b, a);
}

void SoftwareRendering::getFreeVisibleVertexIndexA(int index,Vector2<int>& veci){
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

void SoftwareRendering::updateMappingGen(float& map,GLenum genType,float pos,float nml){
    switch (genType){
        case GL_EYE_LINEAR:
            map = pos;
        break;
        case GL_SPHERE_MAP:
            map = nml / 2.0f + 0.5f;
        break;
    }
}

void SoftwareRendering::getVertexClippingPlane(Vertex& outver,const Vertex& vertexA, const Vertex& vertexB){
    float distA = vertexB.pos.z - vertexA.pos.z; // Distance between vertex A and B
    float distB = vertexB.pos.z - SoftwareRendering::planeNear;   // Distance between vertex B and near plane
    float distFactor = distB / distA;
    Vector2<float> dir;
    outver = vertexA;

    dir.x = vertexA.pos.x - vertexB.pos.x;
    dir.y = vertexA.pos.y - vertexB.pos.y;

    outver.pos.x = vertexB.pos.x + dir.x * distFactor;
    outver.pos.y = vertexB.pos.y + dir.y * distFactor;
    outver.pos.z = SoftwareRendering::planeNear;

    dir.x = vertexA.map[0].x - vertexB.map[0].x;
    dir.y = vertexA.map[0].y - vertexB.map[0].y;

    outver.map[0].x = vertexB.map[0].x + dir.x * distFactor;
    outver.map[0].y = vertexB.map[0].y + dir.y * distFactor;
}

void SoftwareRendering::genMipMapLevel(){
    // Pixel face size
    float psize = abs(SoftwareRendering::getTriangleFaceSize(
                                                SoftwareRendering::curVertex[0]->pos,
                                                SoftwareRendering::curVertex[1]->pos,
                                                SoftwareRendering::curVertex[2]->pos));

    Vector2<float> mapa, mapb, mapc;
    GLuint texW = SoftwareRendering::curTexture[SoftwareRendering::textureLayer]->getWidth();
    GLuint texH = SoftwareRendering::curTexture[SoftwareRendering::textureLayer]->getHeight();

    mapa.x = SoftwareRendering::curVertex[0]->map[SoftwareRendering::textureLayer].x * texW;
    mapa.y = SoftwareRendering::curVertex[0]->map[SoftwareRendering::textureLayer].y * texH;

    mapb.x = SoftwareRendering::curVertex[1]->map[SoftwareRendering::textureLayer].x * texW;
    mapb.y = SoftwareRendering::curVertex[1]->map[SoftwareRendering::textureLayer].y * texH;

    mapc.x = SoftwareRendering::curVertex[2]->map[SoftwareRendering::textureLayer].x * texW;
    mapc.y = SoftwareRendering::curVertex[2]->map[SoftwareRendering::textureLayer].y * texH;

    // Texel face size
    float tsize = abs(SoftwareRendering::getTriangleFaceSize(mapa, mapb, mapc));

    // MIP-map level
    SoftwareRendering::textureMipMapLevel = vclamp<size_t>(tsize / psize, 0, 1024);

    size_t c = 0;
    while ((SoftwareRendering::textureMipMapLevel >> 2) > 0){
        SoftwareRendering::textureMipMapLevel >>= 2;
        ++c;
    }

    SoftwareRendering::textureMipMapLevel = vclamp<size_t>(c, 0, SoftwareRendering::curTexture[SoftwareRendering::textureLayer]->getMipCount() - 1);
}

void SoftwareRendering::updatePixelRect(){
    if (SoftwareRendering::enableSSC[GL_SCISSOR_TEST]){
        SoftwareRendering::pixelRect.x = ( (SoftwareRendering::viewportRect.x < SoftwareRendering::scissorRect.x)? SoftwareRendering::viewportRect.x : SoftwareRendering::scissorRect.x );
        SoftwareRendering::pixelRect.y = ( (SoftwareRendering::viewportRect.y < SoftwareRendering::scissorRect.y)? SoftwareRendering::viewportRect.y : SoftwareRendering::scissorRect.y );
        SoftwareRendering::pixelRect.width = ( (SoftwareRendering::viewportRect.width < SoftwareRendering::scissorRect.width)? SoftwareRendering::viewportRect.width : SoftwareRendering::scissorRect.width );
        SoftwareRendering::pixelRect.height = ( (SoftwareRendering::viewportRect.height < SoftwareRendering::scissorRect.height)? SoftwareRendering::viewportRect.height : SoftwareRendering::scissorRect.height );
    }else{
        SoftwareRendering::pixelRect = SoftwareRendering::viewportRect;
    }

    clamp<int>(SoftwareRendering::pixelRect.x, 0, SoftwareRendering::screenSize.width);
    clamp<int>(SoftwareRendering::pixelRect.y, 0, SoftwareRendering::screenSize.height);
    clamp<uint>(SoftwareRendering::pixelRect.width, 0, SoftwareRendering::screenSize.width);
    clamp<uint>(SoftwareRendering::pixelRect.height, 0, SoftwareRendering::screenSize.height);

    if (SoftwareRendering::pixelRect.x > SoftwareRendering::pixelRect.width){
        int tmp = SoftwareRendering::pixelRect.x;
        SoftwareRendering::pixelRect.x = SoftwareRendering::pixelRect.width;
        SoftwareRendering::pixelRect.width = tmp;
    }
    if (SoftwareRendering::pixelRect.y > SoftwareRendering::pixelRect.height){
        int tmp = SoftwareRendering::pixelRect.y;
        SoftwareRendering::pixelRect.y = SoftwareRendering::pixelRect.height;
        SoftwareRendering::pixelRect.height = tmp;
    }
}

}
