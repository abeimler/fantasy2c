#ifndef SHADERGL_HPP_INCLUDED
#define SHADERGL_HPP_INCLUDED

#include <Fantasy2C/Basic.hpp>

namespace F2C{


/**
*@class ShaderGL
*@brief Loading Fragment and Vertex Shader Files into GLhandleARB Program Object. \n
*\n
*Thanks at Alex V. Boreskoff.
*/
class DLL ShaderGL{
    private:
    static bool wgl_enabled;
    static bool glx_enabled;
    static bool shading_enabled;
    static bool vbo_enabled;
    static bool multitexel_enabled;
    static bool GL_NV_occlusion_query_enabled;
    static bool GL_SGIS_generate_mipmap_enabled;
    static bool GL_NV_register_combiners_enabled;
    static int GL_NV_maxCombiners;
    static std::string vendor_info;
    static std::string renderer_info;
    static std::string version_info;
    static int maxTexelUnits;
    static bool initSetupExtensions;

    GLhandleARB programObj;
    GLhandleARB fragmentShader;
    GLhandleARB vertexShader;
    std::string fsCode;
    std::string vsCode;

    static void setupExtensionsPlatform();
    static void setupExtensionsShader();
    static void setupExtensionsVBO();
    static void setupExtensionsMultiTexel();
    static void initInfo();
    static bool findString(std::string in,std::string list);
    void printLog(uint obj,std::string* error);
    int loadshader(std::string filename,std::string& ShaderSource);
    void loadFromCode();

    public:
    ShaderGL();  ///< Default constructor
    ~ShaderGL(); ///< Delete program,fragment and vertex object.

    ShaderGL(const ShaderGL& copy); ///< Copy constructor
    ShaderGL& operator= (const ShaderGL& copy); ///< Assignment operator with deep copy.

    /**
    *@return -1, This extension string indicates that the OpenGL Shading Language,version 1.00,not is supported.
    *@return -2, GL_ARB_shader_objects extension was not found.
    *@return -3, not support shader.
    *@return 1, Success
    *@brief Initializes the ARB shader functions.
    */
    static int16 InitGLShader();

    /**
    *@return -1, Can't open the Shaderfile.
    *@return -2, The Shaderfile is empty.
    *@return 1, Success
    *@param shaderfilename Filename
    *@param error Target-Varaible: Log Text
    *@brief Load the fragment shader file and creates the ARB fragment object.
    *The build log of the ARB fragment object is writing in the "error" variable.
    */
    int16 LoadGLFragmentShader(std::string shaderfilename,std::string* error = NULL);
    /**
    *@return -1, Can't open the Shaderfile.
    *@return -2, The Shaderfile is empty.
    *@return 1, Success
    *@param shaderfilename Filename
    *@param error Target-Varaible: Log Text
    *@brief Load the fragment shader file and creates the ARB vertex object.
    *The build log of the ARB vertexc object is writing in the "error" variable.
    */
    int16 LoadGLVertexShader(std::string shaderfilename,std::string* error = NULL);

    /**
    *@param error Target reference varaible: Log text
    *@brief Creates the ARB shader program object loaded by the ARB and ARB fragment object Vertex object.
    */
    void CreateShaderProgram(std::string* error = NULL);

    GLhandleARB getProgramObj() const; ///< getMethode: Handle of ARB program object.
    GLhandleARB getFragmentShader() const; ///< getMethode: Handle of ARB fragment object.
    GLhandleARB getVertexShader() const; ///< getMethode: Handle of ARB vertex object.

    /**
    *@param name Uniform Variable Name (in Shader Program)
    *@brief getMethode: Value of Uniform Variable
    */
    int getUniformi(std::string name) const;
    /**
    *@param name Uniform Variable Name (in Shader Program)
    *@brief getMethode: Value of Uniform Variable
    */
    float getUniformf(std::string name) const;

    /**
    *@param name Uniform Variable Name (in Shader Program)
    *@param value new Value of Uniform Variable
    *@brief setMethode: Value of Uniform Variable
    */
    void setUniformi(std::string name,int value);
    /**
    *@param name Uniform Variable Name (in Shader Program)
    *@param value new Value of Uniform Variable
    *@brief setMethode: Value of Uniform Variable
    */
    void setUniformf(std::string name,float value);

    std::string getFragmentCode() const; ///< getMethode: Fragment shader sourcecode
    std::string getVertexCode() const; ///< getMethode: Vertex shader sourcecode

    static bool getSupportedShader(); ///< getMethode: Shader supported Yes / No.
    static bool getSupportedVBO(); ///< getMethode: VBO(Vertex Buffer Object) supported Yes / No.
    static bool getSupportedMultiTexel(); ///< getMethode: MultiTexturing supported Yes / No.

    static bool getSupportedWGL(); ///< getMethode: Windows and WGL supported Yes / No.
    static bool getSupportedGLX(); ///< getMethode: Linux and GLX System supported Yes / No.
    static bool getSupportedNVOcclusionQuery(); ///< getMethode: GL_NV_occlusion_query extension supported Yes / No.
    static bool getSupportedSGISGenerateMipmap(); ///< getMethode: GL_SGIS_generate_mipmap extension supported Yes / No.
    static bool getSupportedNVRegisterCombiners(); ///< getMethode: GL_NV_register_combiners extension supported Yes / No.
    static int getMaxNVCombiners(); ///< getMethode: Maximum general NV combiners.
    static int getMaxTexelUnits(); ///< getMethode: Maximum number of texel pipelines.

    static std::string getGLVendor(); ///< getMethode: Company responsible for this GL implementation.
    static std::string getGLRenderer(); ///< getMethode: Particular configuration of a hardware platform.
    static std::string getGLVersion(); ///< getMethode:OpenGL version or release number.

    static bool glExtensionSupported(std::string extName); ///< getMethode: OpenGL(or WGL or GLX) Extensions Supported Yes / No.
    /**
    *@param proc Name of an OpenGL extension function
    *@brief Returns the pointer to the specified OpenGL function, if it is not supported
    *returned NULL.
    */
    static void* getProcAddress(std::string proc); ///< getMethode: Pointer to the specified OpenGL function.
    static std::string getGLExtensions(); ///< getMethode: OpenGL Extensions
    static std::string getPlatformExtensions(); ///< getMethode: WGL or GLX Extensions, else return empty string

    friend std::ostream& operator<<(std::ostream &out,const ShaderGL& obj);
    friend std::istream& operator>>(std::istream &in, ShaderGL& obj);

};

/**
*@param out Output stream
*@param obj Object
*@brief Write the Object into output stream. (dont write the Shader Obj.,only shadercode)
*/
std::ostream& DLL operator<<(std::ostream &out,const ShaderGL& obj);

/**
*@param in Input stream
*@param obj Object
*@brief Read the Object from input stream. (use old(or create new) Shader Obj.,compile shadercode)
*/
std::istream& DLL operator>>(std::istream &in, ShaderGL& obj);

}

#endif // SHADERGL_HPP_INCLUDED
