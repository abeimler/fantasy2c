#ifndef SOFTWARERENDERING_HPP_INCLUDED
#define SOFTWARERENDERING_HPP_INCLUDED

#include <Fantasy2C/SoftwareRenderingBasic.hpp>

namespace F2C{
    class DLL SoftwareRendering{
        private:
        typedef enum ProjectionsMatrix{
            MODELVIEW_MATRIX = 0,
            PROJECTION_MATRIX = 1,
            NORMAL_MATRIX = 2,
            TEXTURE_MATRIX = 3,
            VIEWPORT_MATRIX = 4,
            MAX_MATRICES = 5
        } ProjectionsMatrix;

        //const settings
        static const size_t RENDER_PIPELINE_SIZE;
        static const size_t TEXTURE_LAYER_SIZE;
        static const size_t MAX_MIPMAPLEVELS;

        //current settings of pipeline
        static GLenum lastError;
        static std::vector<Vertex*> curVertex;
        static std::vector<Vertex*> curMemVertex;
        static std::vector<Texture2D*> curTexture;

        static size_t PLIndex; // render pipe line index

        static GLenum curMatrixMode;
        static size_t textureLayer;
        static size_t maxTextureLayer;
        static size_t textureMipMapLevel;
        static bool updateVerticesMatrix;
        static size_t curLineWidth;
        static size_t curPointSize;

        //current settings
        static GLenum curDepthFunc; //Depth test func
        static GLenum curAlphaFunc; //Alpha test func
        static GLclampf curAlphaFuncRef; //Alpha test ref

        static GLenum curStencilFunc; //Stencil test func
        static GLint curStencilFuncRef; //Stencil test ref
        static GLuint curStencilFuncMask; //Stencil test mask
        static GLenum curStencilFail; //is Sencil Test Fail
        static GLenum curStencilZFail; //is Stencil Test is successful, but Depth Test Fail
        static GLenum curStencilZPass; //is Sencil Test Fail

        static GLenum blendSrcMode; //Blendmode src
        static GLenum blendDstMode; //blendmode dst
        static GLenum curShadeModel; //shade model modus
        static Color4f constBlendColor; //(const) blend color
        static Color4f curClearColor; //clear color
        static GLclampd curClearDepth; //clear depth
        static GLint curClearStencil; //clear Stencil
        static std::map<GLenum,bool> enableSSC; //enable or disable server-side capabilities (glEnable status)
        static std::vector<GenMappingTex> mappingGenType; //control the generation of texture coordinates

        //Matrix member
        static Rect pixelRect; //Pixel Buffer Rect
        static Rect viewportRect; //Viewport Rect
        static Rect scissorRect; //Scissor Rect
        static Rect screenSize; //Screen Size

        static GLfloat planeFar, planeNear;
        static GLfloat rangeFar, rangeNear;
        static GLfloat fieldOfView;

        static std::vector< Matrix4<GLfloat> > renderMatrix;

        //Buffer
        static GLint* depthBuffer;
        static GLint* stencilBuffer;
        static GLint* colorBuffer;

        static size_t depthBufferSize;
        static size_t stencilBufferSize;
        static size_t colorBufferSize;

        //texture
        static size_t texID;
        static GLuint texDeviceID;

        template<typename T>
        static Vector2<T> Project3Dto2D(const Vector3<T>& vec){
            Vector2<T> re;
            Vector3<T> v = SoftwareRendering::renderMatrix[SoftwareRendering::PROJECTION_MATRIX] * vec;
            T invw = 1.0f / v.w;

            const Matrix4<float>& viewportM = SoftwareRendering::renderMatrix[SoftwareRendering::VIEWPORT_MATRIX];
            re.x = invw * ( v.x * viewportM.m11 + v.w * viewportM.m41 );
            re.y = invw * ( v.y * viewportM.m22 + v.w * viewportM.m42 );
            return re;
        }

        template<typename T>
        inline static Vector3<T> Project2Dto3D(const Vector2<T>& vec){
            return Vector2<T>( ( vec.x - screenSize.width /2) / (screenSize.width /2),
                                ((vec.y*-1) + screenSize.height/2) / (screenSize.height/2));

        }

        template<typename T>
        static Vector2<T> clampTexCoords(GLuint w,GLuint h,GLuint u,GLuint v){
            Vector2<T> uv(u -(u / w) * w,v - (v / h) * h);

            if (uv.x < 0)
                uv.x = w + uv.x;
            if (uv.y < 0)
                uv.y = h + uv.y;

            return uv;
        }

        template<typename T>
        inline static float getTriangleFaceSize(const Vector2<T>& a,const Vector2<T>& b,const Vector2<T>& c){
            return ( 0.5f*( a.x*(b.y - c.y) + b.x*(c.y - a.y) + c.x*(a.y - b.y) ) );
        }

        template<typename T>
        inline static float getTriangleFaceSize(const Vector3<T>& a,const Vector3<T>& b,const Vector3<T>& c){
            return ( 0.5f*( a.x*(b.y - c.y) + b.x*(c.y - a.y) + c.x*(a.y - b.y) ) );
        }

        template<typename T>
        inline static float getTriangleFaceSize(const Vector4<T>& a,const Vector4<T>& b,const Vector4<T>& c){
            return ( 0.5f*( a.x*(b.y - c.y) + b.x*(c.y - a.y) + c.x*(a.y - b.y) ) );
        }

        template<typename T>
        static void getTexturePixelLinear(Color4i& col,const Vector2<T>& map){
            GLuint texW = SoftwareRendering::curTexture[SoftwareRendering::textureLayer]->getWidth();
            GLuint texH = SoftwareRendering::curTexture[SoftwareRendering::textureLayer]->getHeight();

            Vector2<T> uv = SoftwareRendering::clampTexCoords(
                texW,
                texH,
                map.x, map.y
            );

            size_t i = ( ( static_cast<int>(uv.y) >> SoftwareRendering::textureMipMapLevel ) *
                         ( texW >> SoftwareRendering::textureMipMapLevel ) +
                         ( static_cast<int>(uv.x) >> SoftwareRendering::textureMipMapLevel )
                        ) << 2;

            SoftwareRendering::getCurTexelColor(col, i);
        }

        template<typename T>
        static void getTexturePixelSmooth(Color4ub& outcol,const Vector2<T>& vec){
            Vector2<T> vec2;
            int offset1, offset2;
            Color4i col[4];
            int ratiox, ratioy, invratiox, invratioy;
            GLuint texW = SoftwareRendering::curTexture[SoftwareRendering::textureLayer]->getWidth();
            GLuint texH = SoftwareRendering::curTexture[SoftwareRendering::textureLayer]->getHeight();

            // Clamp the texture coordinates
            SoftwareRendering::clampTexCoords(
                texW,
                texH,
                vec.x, vec.y
            );

            // Get the next texture coordinates
            vec2.x = vec.x + (1 << SoftwareRendering::textureMipMapLevel);
            vec2.y = vec.y + (1 << SoftwareRendering::textureMipMapLevel);

            if (vec2.x > texW)
                vec2.x = 0;
            if (vec2.y > texH)
                vec2.y = 0;

            offset1 = ( static_cast<int>(vec.y) >> SoftwareRendering::textureMipMapLevel ) * ( texW >> SoftwareRendering::textureMipMapLevel );
            offset2 = ( static_cast<int>(vec2.y) >> SoftwareRendering::textureMipMapLevel ) * ( texH >> SoftwareRendering::textureMipMapLevel );

            // Get the texels color
            size_t i = 0;
            #define GET_TEXEL_COLOR(c, o, p)\
                i = ( o + ( static_cast<int>(p) >> SoftwareRendering::textureMipMapLevel ) ) << 2;\
                SoftwareRendering::getCurTexelColor(c, i);

            GET_TEXEL_COLOR(col[0], offset1, vec.x);
            GET_TEXEL_COLOR(col[1], offset1, vec2.x);
            GET_TEXEL_COLOR(col[2], offset2, vec2.x);
            GET_TEXEL_COLOR(col[3], offset2, vec.x);

            #undef GET_TEXEL_COLOR

            // Compute the mix value
            vec.x /= 1 << SoftwareRendering::textureMipMapLevel;
            vec.y /= 1 << SoftwareRendering::textureMipMapLevel;

            ratiox = (vec.x - static_cast<int>(vec.x))*255;
            ratioy = (vec.y - static_cast<int>(vec.y))*255;

            invratiox = 255 - ratiox;
            invratioy = 255 - ratioy;

            outcol.set(( col[0].r * invratiox / 255 + col[1].r * ratiox / 255 ) * invratioy / 255 +
                        ( col[3].r * invratiox / 255 + col[2].r * ratiox / 255 ) * ratioy / 255,

                        ( col[0].g * invratiox / 255 + col[1].g * ratiox / 255 ) * invratioy / 255 +
                        ( col[3].g * invratiox / 255 + col[2].g * ratiox / 255 ) * ratioy / 255,

                        ( col[0].b * invratiox / 255 + col[1].b * ratiox / 255 ) * invratioy / 255 +
                        ( col[3].b * invratiox / 255 + col[2].b * ratiox / 255 ) * ratioy / 255,

                        ( col[0].a * invratiox / 255 + col[1].a * ratiox / 255 ) * invratioy / 255 +
                        ( col[3].a * invratiox / 255 + col[2].a * ratiox / 255 ) * ratioy / 255);
        }
        template<typename T>
        inline static bool isPointInside(Vector2<T> p){
            return p.x < 0 || p.x >= SoftwareRendering::screenSize.width || p.y < 0 || p.y > SoftwareRendering::screenSize.height;
        }

        static bool isInsidePixelBuffer(int x ,int y);
        static bool isInsidePixelBuffer(int x ,int y,int z,size_t depthBufferIndex);

        static void setPixelRGB(size_t bufferIndex,GLubyte r,GLubyte g,GLubyte b);
        static void setPixelRGBA(size_t bufferIndex,GLubyte r,GLubyte g,GLubyte b,GLubyte a);

        static void setFrame(size_t index,GLclampf z,GLubyte r,GLubyte g,GLubyte b,GLubyte a);
        static void setFrameAlpha(size_t index,GLclampf z,GLubyte r,GLubyte g,GLubyte b,GLubyte a);
        static void setFrame(int x, int y,GLclampf z,GLubyte r,GLubyte g,GLubyte b,GLubyte a);

        static Color4d InterpolateColor(const Color4d& col1, const Color4d& col2,double t);
        static void getCurTexelColor(Color4ub& outcol,size_t pixelIndex);
        static void getCurTexelColor(Color4i& outcol,size_t pixelIndex);
		static void getFreeVisibleVertexIndexA(int index,Vector2<int>& veci);
		static int getFreeVisibleVertexIndexB(int index1,int index2);
		static void getVertexClippingPlane(Vertex& outver,const Vertex& vertexA, const Vertex& vertexB);

		static void genMipMapLevel();
		static void updateMappingGen(float& map,GLenum genType,float pos,float nml);
		static void updatePixelRect();

		static void endisable(GLenum mode,GLboolean enable);
		static void updateNormalMatrix();

        static void blendFuncPixel(GLenum mode, //Blend Mode (GL_ONE,GL_ZERO,GL_SRC_COLOR,GL_DST_COLOR,...)
                                        GLint* rgbaPixel, //target Pixels (must RGBA format)
                                        const GLint* srcPixel, //pixels of Src (must RGBA format)
                                        const GLint* dstPixel, //pixels of Dst (must RGBA format)
                                        const Color4f& constBlendColor); // const blend color (glBlendColor)

        static void blendFuncPixel(GLenum mode, //Blend Mode (GL_ONE,GL_ZERO,GL_SRC_COLOR,GL_DST_COLOR,...)
                                        GLubyte* rgbaPixel, //target Pixels (must RGBA format)
                                        const GLubyte* srcPixel, //pixels of Src (must RGBA format)
                                        const GLubyte* dstPixel, //pixels of Dst (must RGBA format)
                                        const Color4f& constBlendColor); // const blend color (glBlendColor)

        static void blendFuncPixels(GLenum mode, //Blend Mode (GL_ONE,GL_ZERO,GL_SRC_COLOR,GL_DST_COLOR,...)
                                        GLint* rgbaPixels, //target Pixels (must RGBA format)
                                        const GLint* srcPixels, //pixels of Src (must RGBA format)
                                        const GLint* dstPixels, //pixels of Dst (must RGBA format)
                                        size_t rgbaSize, //Sizes
                                        size_t srcSize,
                                        size_t dstSize,
                                        const Color4f& constBlendColor); // const blend color (glBlendColor)

        static void blendFuncPixels(GLenum mode, //Blend Mode (GL_ONE,GL_ZERO,GL_SRC_COLOR,GL_DST_COLOR,...)
                                        GLubyte* rgbaPixels, //target Pixels (must RGBA format)
                                        const GLubyte* srcPixels, //pixels of Src (must RGBA format)
                                        const GLubyte* dstPixels, //pixels of Dst (must RGBA format)
                                        size_t rgbaSize, //Sizes
                                        size_t srcSize,
                                        size_t dstSize,
                                        const Color4f& constBlendColor); // const blend color (glBlendColor)

        bool testDepth(size_t i, GLint z);
        void renderPointColor();
        public:

        static void enable(GLenum mode);
        static void disable(GLenum mode);
        static GLboolean isEnable(GLenum mode);

        static void blendFunc(GLenum sfactor,GLenum dfactor);
        static void depthFunc(GLenum func);
        static void alphaFunc(GLenum func,GLclampf mask);
        static void stencilFunc(GLenum func, GLint ref,GLuint mask);
        static void stencilOp(GLenum fail,GLenum zfail,GLenum zpass);
        static void clearColor(GLclampf red,GLclampf green,GLclampf blue,GLclampf alpha);
        static void clearDepth(GLclampd depth);
        static void clearStencil(GLint s);

        static std::string getString(GLenum name);
        static GLenum getError();

        static void getFloat(GLenum pname,GLfloat* params);

        static void scissor(GLint x, GLint y, GLuint width, GLuint height);
        static void viewport(GLint x, GLint y, GLuint width, GLuint height);
        static void perspective(GLfloat glnear, GLfloat glfar, GLfloat fieldOfView);

        static void lineWidth(GLuint width);
        static void pointSize(GLuint size);
        static void shadeModel(GLenum mode);

        static void setMaxTextureLayer(GLuint maxLayer);
        static void useTextureLayer(GLuint layer);

        static void genTextures(GLuint* ID);
        static void deleteTextures(GLuint* ID);

        static void bindTexture(GLuint ID);
        static void unbindTexture();
        static GLuint getCurTexture();

        static void texGen(GLenum coord, GLenum param);

        static void texSubImage2D(GLuint ID,GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height,GLenum format, GLenum type, const GLvoid* pixels);
        static void copyTexSubImage2D(GLuint ID, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width,GLsizei height);

        static void texImage2D(GLuint ID, GLint level, GLsizei width ,GLsizei height, GLenum format, GLenum type, const GLvoid* pixels);
        static void copyTexImage2D(GLuint ID, GLint level,GLint xoffset,GLint yoffset, GLint x, GLint y, GLsizei width ,GLsizei heigh);

        static void getImage2D(GLuint ID,GLint level,GLenum format,GLenum type,GLvoid* pixels);

        static void vertex2i(GLint x, GLint y);
        static void vertex3i(GLint x, GLint y, GLint z);
        static void vertex4i(GLint x, GLint y, GLint z, GLint w);

        static void vertex2f(GLfloat x, GLfloat y);
        static void vertex3f(GLfloat x, GLfloat y, GLfloat z);
        static void vertex4f(GLfloat x, GLfloat y, GLfloat z, GLfloat w);

        static void normal3i(GLint x, GLint y, GLint z);
        static void normal3f(GLfloat x, GLfloat y, GLfloat z);

        static void texCoord2i(GLint x, GLint y);
        static void texCoord2f(GLfloat x, GLfloat y);

        static void color3ub(GLubyte red, GLubyte green, GLubyte blue);
        static void color4ub(GLubyte red, GLubyte green, GLubyte blue,GLubyte alpha);

        static void color3i(GLubyte red, GLubyte green, GLubyte blue);
        static void color4i(GLubyte red, GLubyte green, GLubyte blue,GLubyte alpha);

        static void color3f(GLfloat red, GLfloat green, GLfloat blue);
        static void color4f(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);

        static void matrixMode(GLenum mode);

        static void loadIdentity();
        static void loadMatrix(const float* m);
        static void loadMatrix(const Matrix4<float>& m);

        static void getMatrix(float* m);
        static void getMatrix(const Matrix4<float> m);

        static void createDevice(GLuint screenWidth, GLuint screenHeight);
        static void deleteDevice();

        static void clear(GLbitfield mask);
        static void swapBuffers();

        static void write2DPixel(GLint x, GLint y,const Color4i& color);
        static void write3DPixel(GLint x, GLint y, GLfloat z,const Color4i& color);

        static void write2DPixelFast(GLint x, GLint y, const Color4i& color);
        static void write3DPixelFast(GLint x, GLint y, const Color4i& color);

        static void read2DPixel(GLint x, GLint y, Color4i& color);
        static void read3DPixel(GLint x, GLint y, GLfloat* z,Color4i& color);

    };
}

#endif // SOFTWARERENDERING_HPP_INCLUDED
