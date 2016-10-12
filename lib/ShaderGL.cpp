#include <Fantasy2C/ShaderGL.hpp>

namespace F2C{

#if defined(WIN32_OR_X11)
void ShaderGL::setupExtensionsPlatform(){
    #if defined(_ISWINDOWS)
        ShaderGL::wgl_enabled = true;
        wglGetExtensionsStringARB = (PFNWGLGETEXTENSIONSSTRINGARBPROC) ShaderGL::getProcAddress ( "wglGetExtensionsStringARB" );

        if ( wglGetExtensionsStringARB == NULL )
            ShaderGL::wgl_enabled = false;

        const char* exts = wglGetExtensionsStringARB(wglGetCurrentDC());

        if ( exts == NULL )
            ShaderGL::wgl_enabled = false;

        if(ShaderGL::wgl_enabled){
            if ( strstr(exts,"WGL_ARB_pbuffer") != NULL ){
                wglCreatePbufferARB    = (PFNWGLCREATEPBUFFERARBPROC)     wglGetProcAddress ( "wglCreatePbufferARB"    );
                wglGetPbufferDCARB     = (PFNWGLGETPBUFFERDCARBPROC)      wglGetProcAddress ( "wglGetPbufferDCARB"     );
                wglReleasePbufferDCARB = (PFNWGLRELEASEPBUFFERDCARBPROC)  wglGetProcAddress ( "wglReleasePbufferDCARB" );
                wglDestroyPbufferARB   = (PFNWGLDESTROYPBUFFERARBPROC)    wglGetProcAddress ( "wglDestroyPbufferARB"   );
                wglQueryPbufferARB     = (PFNWGLQUERYPBUFFERARBPROC)      wglGetProcAddress ( "wglQueryPbufferARB"     );
            }

            if ( strstr ( exts, "WGL_ARB_pixel_format" ) != NULL )
                wglChoosePixelFormatARB = (PFNWGLCHOOSEPIXELFORMATARBPROC)wglGetProcAddress ( "wglChoosePixelFormatARB" );

            if ( strstr ( exts, "WGL_ARB_render_texture" ) != NULL ){
                wglBindTexImageARB      = (PFNWGLBINDTEXIMAGEARBPROC)     wglGetProcAddress ( "wglBindTexImageARB"     );
                wglReleaseTexImageARB   = (PFNWGLRELEASETEXIMAGEARBPROC)  wglGetProcAddress ( "wglReleaseTexImageARB"  );
                wglSetPbufferAttribARB  = (PFNWGLSETPBUFFERATTRIBARBPROC) wglGetProcAddress ( "wglSetPbufferAttribARB" );
            }

            if ( strstr ( exts, "WGL_EXT_swap_control" ) != NULL ){
                wglSwapIntervalEXT      = (PFNWGLSWAPINTERVALEXTPROC)       wglGetProcAddress ( "wglSwapIntervalEXT"    );
                wglGetSwapIntervalEXT   = (PFNWGLGETSWAPINTERVALEXTPROC)    wglGetProcAddress ( "wglGetSwapIntervalEXT" );
            }
        }
    #elif defined (_ISLINUX)
        glXCreateGLXPbufferSGIX = (PFNGLXCREATEGLXPBUFFERSGIXPROC) glXGetProcAddress("glXCreateGLXPbufferSGIX");
        glXDestroyGLXPbufferSGIX = (PFNGLXDESTROYGLXPBUFFERSGIXPROC) glXGetProcAddress("glXDestroyGLXPbufferSGIX");
        glXQueryGLXPbufferSGIX = (PFNGLXQUERYGLXPBUFFERSGIXPROC) glXGetProcAddress("glXQueryGLXPbufferSGIX");

        glXChooseFBConfigSGIX = (PFNGLXCHOOSEFBCONFIGSGIXPROC) glXGetProcAddress("glXChooseFBConfigSGIX");
        glXCreateContextWithConfigSGIX = (PFNGLXCREATECONTEXTWITHCONFIGSGIXPROC) glXGetProcAddress("glXCreateContextWithConfigSGIX");

        ShaderGL::glx_enabled = true;
    #endif

}

void ShaderGL::setupExtensionsShader(){

    if( ShaderGL::glExtensionSupported("GL_ARB_shader_objects") &&
      ShaderGL::glExtensionSupported("GL_ARB_shading_language_100") &&
      ShaderGL::glExtensionSupported("GL_ARB_vertex_shader") &&
      ShaderGL::glExtensionSupported("GL_ARB_fragment_shader") )
    {

        glFogCoordf              = (PFNGLFOGCOORDFEXTPROC)             ShaderGL::getProcAddress ( "glFogCoordfEXT"         );

        glSecondaryColor3f       = (PFNGLSECONDARYCOLOR3FPROC)         ShaderGL::getProcAddress ( "glSecondaryColor3fEXT"      );
        glSecondaryColor3fv      = (PFNGLSECONDARYCOLOR3FVPROC)        ShaderGL::getProcAddress ( "glSecondaryColor3fvEXT"     );
        glSecondaryColorPointer  = (PFNGLSECONDARYCOLORPOINTERPROC)    ShaderGL::getProcAddress ( "glSecondaryColorPointerEXT" );

        glCombinerParameterfvNV  = (PFNGLCOMBINERPARAMETERFVNVPROC)    ShaderGL::getProcAddress ( "glCombinerParameterfvNV"  );
        glCombinerParameterivNV  = (PFNGLCOMBINERPARAMETERIVNVPROC)    ShaderGL::getProcAddress ( "glCombinerParameterivNV"  );
        glCombinerParameterfNV   = (PFNGLCOMBINERPARAMETERFNVPROC)     ShaderGL::getProcAddress ( "glCombinerParameterfNV"   );
        glCombinerParameteriNV   = (PFNGLCOMBINERPARAMETERINVPROC)     ShaderGL::getProcAddress ( "glCombinerParameteriNV"   );
        glCombinerInputNV        = (PFNGLCOMBINERINPUTNVPROC)          ShaderGL::getProcAddress ( "glCombinerInputNV"        );
        glCombinerOutputNV       = (PFNGLCOMBINEROUTPUTNVPROC)         ShaderGL::getProcAddress ( "glCombinerOutputNV"       );
        glFinalCombinerInputNV   = (PFNGLFINALCOMBINERINPUTNVPROC)     ShaderGL::getProcAddress ( "glFinalCombinerInputNV"   );

        // NV-occlusion query extension
        glGenOcclusionQueriesNV = (PFNGLGENOCCLUSIONQUERIESNVPROC) ShaderGL::getProcAddress ( "glGenOcclusionQueriesNV" );
        glBeginOcclusionQueryNV = (PFNGLBEGINOCCLUSIONQUERYNVPROC) ShaderGL::getProcAddress ( "glBeginOcclusionQueryNV" );
        glEndOcclusionQueryNV   = (PFNGLENDOCCLUSIONQUERYNVPROC)   ShaderGL::getProcAddress ( "glEndOcclusionQueryNV"   );
        glGetOcclusionQueryivNV = (PFNGLGETOCCLUSIONQUERYIVNVPROC) ShaderGL::getProcAddress ( "glGetOcclusionQueryivNV" );

        // ARB_vertex_program extension
        glGenProgramsARB                = (PFNGLGENPROGRAMSARBPROC)               ShaderGL::getProcAddress ( "glGenProgramsARB" );
        glDeleteProgramsARB             = (PFNGLDELETEPROGRAMSARBPROC)            ShaderGL::getProcAddress ( "glDeleteProgramsARB" );
        glBindProgramARB                = (PFNGLBINDPROGRAMARBPROC)               ShaderGL::getProcAddress ( "glBindProgramARB" );
        glIsProgramARB                  = (PFNGLISPROGRAMARBPROC)                 ShaderGL::getProcAddress ( "glIsProgramARB" );
        glProgramStringARB              = (PFNGLPROGRAMSTRINGARBPROC)             ShaderGL::getProcAddress ( "glProgramStringARB" );
        glGetProgramivARB               = (PFNGLGETPROGRAMIVARBPROC)              ShaderGL::getProcAddress ( "glGetProgramivARB" );
        glVertexAttrib4fARB             = (PFNGLVERTEXATTRIB4FARBPROC)            ShaderGL::getProcAddress ( "glVertexAttrib4fARB" );
        glVertexAttrib4fvARB            = (PFNGLVERTEXATTRIB4FVARBPROC)           ShaderGL::getProcAddress ( "glVertexAttrib4fvARB" );
        glVertexAttrib3fARB             = (PFNGLVERTEXATTRIB3FARBPROC)            ShaderGL::getProcAddress ( "glVertexAttrib3fARB" );
        glVertexAttrib3fvARB            = (PFNGLVERTEXATTRIB3FVARBPROC)           ShaderGL::getProcAddress ( "glVertexAttrib3fvARB" );
        glVertexAttribPointerARB        = (PFNGLVERTEXATTRIBPOINTERARBPROC)       ShaderGL::getProcAddress ( "glVertexAttribPointerARB" );
        glEnableVertexAttribArrayARB    = (PFNGLENABLEVERTEXATTRIBARRAYARBPROC)   ShaderGL::getProcAddress ( "glEnableVertexAttribArrayARB" );
        glDisableVertexAttribArrayARB   = (PFNGLDISABLEVERTEXATTRIBARRAYARBPROC)  ShaderGL::getProcAddress ( "glDisableVertexAttribArrayARB" );
        glProgramLocalParameter4fARB    = (PFNGLPROGRAMLOCALPARAMETER4FARBPROC)   ShaderGL::getProcAddress ( "glProgramLocalParameter4fARB" );
        glProgramLocalParameter4fvARB   = (PFNGLPROGRAMLOCALPARAMETER4FVARBPROC)  ShaderGL::getProcAddress ( "glProgramLocalParameter4fvARB" );
        glGetProgramLocalParameterfvARB = (PFNGLGETPROGRAMLOCALPARAMETERFVARBPROC)ShaderGL::getProcAddress ( "glGetProgramLocalParameterfvARB" );
        glProgramEnvParameter4fARB      = (PFNGLPROGRAMENVPARAMETER4FARBPROC)     ShaderGL::getProcAddress ( "glProgramEnvParameter4fARB" );
        glProgramEnvParameter4fvARB     = (PFNGLPROGRAMENVPARAMETER4FVARBPROC)    ShaderGL::getProcAddress ( "glProgramEnvParameter4fvARB" );
        glGetProgramEnvParameterfvARB   = (PFNGLGETPROGRAMENVPARAMETERFVARBPROC)  ShaderGL::getProcAddress ( "glGetProgramEnvParameterfvARB" );

        // GL_EXT_texture3D
        glTexImage3DEXT                 =(PFNGLTEXIMAGE3DEXTPROC)                 ShaderGL::getProcAddress ( "glTexImage3DEXT" );

        // ARB_texture_compression
        glCompressedTexImage3DARB       = (PFNGLCOMPRESSEDTEXIMAGE3DARBPROC)      ShaderGL::getProcAddress ( "glCompressedTexImage3DARB"    );
        glCompressedTexImage2DARB       = (PFNGLCOMPRESSEDTEXIMAGE2DARBPROC)      ShaderGL::getProcAddress ( "glCompressedTexImage2DARB"    );
        glCompressedTexImage1DARB       = (PFNGLCOMPRESSEDTEXIMAGE1DARBPROC)      ShaderGL::getProcAddress ( "glCompressedTexImage1DARB"    );
        glCompressedTexSubImage3DARB    = (PFNGLCOMPRESSEDTEXSUBIMAGE3DARBPROC)   ShaderGL::getProcAddress ( "glCompressedTexSubImage3DARB" );
        glCompressedTexSubImage2DARB    = (PFNGLCOMPRESSEDTEXSUBIMAGE2DARBPROC)   ShaderGL::getProcAddress ( "glCompressedTexSubImage2DARB" );
        glCompressedTexSubImage1DARB    = (PFNGLCOMPRESSEDTEXSUBIMAGE1DARBPROC)   ShaderGL::getProcAddress ( "glCompressedTexSubImage1DARB" );
        glGetCompressedTexImageARB      = (PFNGLGETCOMPRESSEDTEXIMAGEARBPROC)     ShaderGL::getProcAddress ( "glGetCompressedTexImageARB"   );

        // ARB_point_parameters
        glPointParameterfARB             = (PFNGLPOINTPARAMETERFARBPROC)          ShaderGL::getProcAddress ( "glPointParameterfARB" );
        glPointParameterfvARB            = (PFNGLPOINTPARAMETERFVARBPROC)         ShaderGL::getProcAddress ( "glPointParameterfvARB" );

                                        // ARB_occlusion_query
        glGenQueriesARB        = (PFNGLGENQUERIESARBPROC)        ShaderGL::getProcAddress ( "glGenQueriesARB"        );
        glDeleteQueriesARB     = (PFNGLDELETEQUERIESARBPROC)     ShaderGL::getProcAddress ( "glDeleteQueriesARB"     );
        glIsQueryARB           = (PFNGLISQUERYARBPROC)           ShaderGL::getProcAddress ( "glIsQueryARB"           );
        glBeginQueryARB        = (PFNGLBEGINQUERYARBPROC)        ShaderGL::getProcAddress ( "glBeginQueryARB"        );
        glEndQueryARB          = (PFNGLENDQUERYARBPROC)          ShaderGL::getProcAddress ( "glEndQueryARB"          );
        glGetQueryivARB        = (PFNGLGETQUERYIVARBPROC)        ShaderGL::getProcAddress ( "glGetQueryivARB"        );
        glGetQueryObjectivARB  = (PFNGLGETQUERYOBJECTIVARBPROC)  ShaderGL::getProcAddress ( "glGetQueryObjectivARB"  );
        glGetQueryObjectuivARB = (PFNGLGETQUERYOBJECTUIVARBPROC) ShaderGL::getProcAddress ( "glGetQueryObjectuivARB" );

        // GLSL-specific extensions
        // GL_ARB_shader_object
        glDeleteObjectARB         = (PFNGLDELETEOBJECTARBPROC)         ShaderGL::getProcAddress ( "glDeleteObjectARB" );
        glGetHandleARB            = (PFNGLGETHANDLEARBPROC)            ShaderGL::getProcAddress ( "glGetHandleARB" );
        glDetachObjectARB         = (PFNGLDETACHOBJECTARBPROC)         ShaderGL::getProcAddress ( "glDetachObjectARB" );
        glCreateShaderObjectARB   = (PFNGLCREATESHADEROBJECTARBPROC)   ShaderGL::getProcAddress ( "glCreateShaderObjectARB" );
        glShaderSourceARB         = (PFNGLSHADERSOURCEARBPROC)         ShaderGL::getProcAddress ( "glShaderSourceARB" );
        glCompileShaderARB        = (PFNGLCOMPILESHADERARBPROC)        ShaderGL::getProcAddress ( "glCompileShaderARB" );
        glCreateProgramObjectARB  = (PFNGLCREATEPROGRAMOBJECTARBPROC)  ShaderGL::getProcAddress ( "glCreateProgramObjectARB" );
        glAttachObjectARB         = (PFNGLATTACHOBJECTARBPROC)         ShaderGL::getProcAddress ( "glAttachObjectARB" );
        glLinkProgramARB          = (PFNGLLINKPROGRAMARBPROC)          ShaderGL::getProcAddress ( "glLinkProgramARB" );
        glUseProgramObjectARB     = (PFNGLUSEPROGRAMOBJECTARBPROC)     ShaderGL::getProcAddress ( "glUseProgramObjectARB" );
        glValidateProgramARB      = (PFNGLVALIDATEPROGRAMARBPROC)      ShaderGL::getProcAddress ( "glValidateProgramARB" );
        glUniform1fARB            = (PFNGLUNIFORM1FARBPROC)            ShaderGL::getProcAddress ( "glUniform1fARB" );
        glUniform2fARB            = (PFNGLUNIFORM2FARBPROC)            ShaderGL::getProcAddress ( "glUniform2fARB" );
        glUniform3fARB            = (PFNGLUNIFORM3FARBPROC)            ShaderGL::getProcAddress ( "glUniform3fARB" );
        glUniform4fARB            = (PFNGLUNIFORM4FARBPROC)            ShaderGL::getProcAddress ( "glUniform4fARB" );
        glUniform1iARB            = (PFNGLUNIFORM1IARBPROC)            ShaderGL::getProcAddress ( "glUniform1iARB" );
        glUniform2iARB            = (PFNGLUNIFORM2IARBPROC)            ShaderGL::getProcAddress ( "glUniform2iARB" );
        glUniform3iARB            = (PFNGLUNIFORM3IARBPROC)            ShaderGL::getProcAddress ( "glUniform3iARB" );
        glUniform4iARB            = (PFNGLUNIFORM4IARBPROC)            ShaderGL::getProcAddress ( "glUniform4iARB" );
        glUniform1fvARB           = (PFNGLUNIFORM1FVARBPROC)           ShaderGL::getProcAddress ( "glUniform1fvARB" );
        glUniform2fvARB           = (PFNGLUNIFORM2FVARBPROC)           ShaderGL::getProcAddress ( "glUniform2fvARB" );
        glUniform3fvARB           = (PFNGLUNIFORM3FVARBPROC)           ShaderGL::getProcAddress ( "glUniform3fvARB" );
        glUniform4fvARB           = (PFNGLUNIFORM4FVARBPROC)           ShaderGL::getProcAddress ( "glUniform4fvARB" );
        glUniform1ivARB           = (PFNGLUNIFORM1IVARBPROC)           ShaderGL::getProcAddress ( "glUniform1ivARB" );
        glUniform2ivARB           = (PFNGLUNIFORM2IVARBPROC)           ShaderGL::getProcAddress ( "glUniform2ivARB" );
        glUniform3ivARB           = (PFNGLUNIFORM3IVARBPROC)           ShaderGL::getProcAddress ( "glUniform3ivARB" );
        glUniform4ivARB           = (PFNGLUNIFORM4IVARBPROC)           ShaderGL::getProcAddress ( "glUniform4ivARB" );
        glUniformMatrix2fvARB     = (PFNGLUNIFORMMATRIX2FVARBPROC)     ShaderGL::getProcAddress ( "glUniformMatrix2fvARB" );
        glUniformMatrix3fvARB     = (PFNGLUNIFORMMATRIX3FVARBPROC)     ShaderGL::getProcAddress ( "glUniformMatrix3fvARB" );
        glUniformMatrix4fvARB     = (PFNGLUNIFORMMATRIX4FVARBPROC)     ShaderGL::getProcAddress ( "glUniformMatrix4fvARB" );
        glGetObjectParameterfvARB = (PFNGLGETOBJECTPARAMETERFVARBPROC) ShaderGL::getProcAddress ( "glGetObjectParameterfvARB" );
        glGetObjectParameterivARB = (PFNGLGETOBJECTPARAMETERIVARBPROC) ShaderGL::getProcAddress ( "glGetObjectParameterivARB" );
        glGetInfoLogARB           = (PFNGLGETINFOLOGARBPROC)           ShaderGL::getProcAddress ( "glGetInfoLogARB" );
        glGetAttachedObjectsARB   = (PFNGLGETATTACHEDOBJECTSARBPROC)   ShaderGL::getProcAddress ( "glGetAttachedObjectsARB" );
        glGetUniformLocationARB   = (PFNGLGETUNIFORMLOCATIONARBPROC)   ShaderGL::getProcAddress ( "glGetUniformLocationARB" );
        glGetActiveUniformARB     = (PFNGLGETACTIVEUNIFORMARBPROC)     ShaderGL::getProcAddress ( "glGetActiveUniformARB" );
        glGetUniformfvARB         = (PFNGLGETUNIFORMFVARBPROC)         ShaderGL::getProcAddress ( "glGetUniformfvARB" );
        glGetUniformivARB         = (PFNGLGETUNIFORMIVARBPROC)         ShaderGL::getProcAddress ( "glGetUniformivARB" );
        glGetShaderSourceARB      = (PFNGLGETSHADERSOURCEARBPROC)      ShaderGL::getProcAddress ( "glGetShaderSourceARB" );

        // GL_ARB_vertex_shader
        glBindAttribLocationARB   = (PFNGLBINDATTRIBLOCATIONARBPROC)   ShaderGL::getProcAddress ( "glBindAttribLocationARB" );
        glGetActiveAttribARB      = (PFNGLGETACTIVEATTRIBARBPROC)      ShaderGL::getProcAddress ( "glGetActiveAttribARB"    );
        glGetAttribLocationARB    = (PFNGLGETATTRIBLOCATIONARBPROC)    ShaderGL::getProcAddress ( "glGetAttribLocationARB"  );
        glGetVertexAttribfvARB    = (PFNGLGETVERTEXATTRIBFVARBPROC)    ShaderGL::getProcAddress ( "glGetVertexAttribfvARB"  );

        // EXT_stencil_two_side
        glActiveStencilFaceEXT    = (PFNGLACTIVESTENCILFACEEXTPROC)    ShaderGL::getProcAddress ( "glActiveStencilFaceEXT" );

        // EXT_depth_bounds_test
        glDepthBoundsEXT      = (PFNGLDEPTHBOUNDSEXTPROC)          ShaderGL::getProcAddress ( "glDepthBoundsEXT" );

        // EXT_framebuffer_object
        glIsRenderbufferEXT                      = (PFNGLISRENDERBUFFEREXTPROC                     ) ShaderGL::getProcAddress ( "glIsRenderbufferEXT" );
        glBindRenderbufferEXT                    = (PFNGLBINDRENDERBUFFEREXTPROC                   ) ShaderGL::getProcAddress ( "glBindRenderbufferEXT" );
        glDeleteRenderbuffersEXT                 = (PFNGLDELETERENDERBUFFERSEXTPROC                ) ShaderGL::getProcAddress ( "glDeleteRenderbuffersEXT" );
        glGenRenderbuffersEXT                    = (PFNGLGENRENDERBUFFERSEXTPROC                   ) ShaderGL::getProcAddress ( "glGenRenderbuffersEXT" );
        glRenderbufferStorageEXT                 = (PFNGLRENDERBUFFERSTORAGEEXTPROC                ) ShaderGL::getProcAddress ( "glRenderbufferStorageEXT" );
        glGetRenderbufferParameterivEXT          = (PFNGLGETRENDERBUFFERPARAMETERIVEXTPROC         ) ShaderGL::getProcAddress ( "glGetRenderbufferParameterivEXT" );
        glIsFramebufferEXT                       = (PFNGLISFRAMEBUFFEREXTPROC                      ) ShaderGL::getProcAddress ( "glIsFramebufferEXT" );
        glBindFramebufferEXT                     = (PFNGLBINDFRAMEBUFFEREXTPROC                    ) ShaderGL::getProcAddress ( "glBindFramebufferEXT" );
        glDeleteFramebuffersEXT                  = (PFNGLDELETEFRAMEBUFFERSEXTPROC                 ) ShaderGL::getProcAddress ( "glDeleteFramebuffersEXT" );
        glGenFramebuffersEXT                     = (PFNGLGENFRAMEBUFFERSEXTPROC                    ) ShaderGL::getProcAddress ( "glGenFramebuffersEXT" );
        glCheckFramebufferStatusEXT              = (PFNGLCHECKFRAMEBUFFERSTATUSEXTPROC             ) ShaderGL::getProcAddress ( "glCheckFramebufferStatusEXT" );
        glFramebufferTexture1DEXT                = (PFNGLFRAMEBUFFERTEXTURE1DEXTPROC               ) ShaderGL::getProcAddress ( "glFramebufferTexture1DEXT" );
        glFramebufferTexture2DEXT                = (PFNGLFRAMEBUFFERTEXTURE2DEXTPROC               ) ShaderGL::getProcAddress ( "glFramebufferTexture2DEXT" );
        glFramebufferTexture3DEXT                = (PFNGLFRAMEBUFFERTEXTURE3DEXTPROC               ) ShaderGL::getProcAddress ( "glFramebufferTexture3DEXT" );
        glFramebufferRenderbufferEXT             = (PFNGLFRAMEBUFFERRENDERBUFFEREXTPROC			   ) ShaderGL::getProcAddress ( "glFramebufferRenderbufferEXT" );
        glGetFramebufferAttachmentParameterivEXT = (PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVEXTPROC) ShaderGL::getProcAddress ( "glGetFramebufferAttachmentParameterivEXT" );
        glGenerateMipmapEXT                      = (PFNGLGENERATEMIPMAPEXTPROC					   ) ShaderGL::getProcAddress ( "glGenerateMipmapEXT" );

        #ifndef	GL_VERSION_1_3
            // ARB_transpose matrix
            glLoadTransposeMatrixfARB	              = (PFNGLLOADTRANSPOSEMATRIXFPROC                 ) ShaderGL::getProcAddress ( "glLoadTransposeMatrixfARB" );
            glLoadTransposeMatrixdARB	              = (PFNGLLOADTRANSPOSEMATRIXDPROC                 ) ShaderGL::getProcAddress ( "glLoadTransposeMatrixdARB" );
            glMultTransposeMatrixfARB	              = (PFNGLMULTTRANSPOSEMATRIXFPROC                 ) ShaderGL::getProcAddress ( "glMultTransposeMatrixfARB" );
            glMultTransposeMatrixdARB	              = (PFNGLMULTTRANSPOSEMATRIXDPROC                 ) ShaderGL::getProcAddress ( "glMultTransposeMatrixdARB" );
        #endif

                                                                // ARB_color_buffer_float
        glClampColorARB         = (PFNGLCLAMPCOLORARBPROC)      ShaderGL::getProcAddress ( "glClampColorARB" );

        #if defined(_ISWINDOWS)
            // fresh Linux already has 2.0
            // stencil ops from OpenGL 2.0
            glStencilFuncSeparate  = (PFNGLSTENCILFUNCSEPARATEPROC) ShaderGL::getProcAddress ( "glStencilFuncSeparate" );
            glStencilOpSeparate    = (PFNGLSTENCILOPSEPARATEPROC)   ShaderGL::getProcAddress ( "glStencilOpSeparate" );
            glStencilMaskSeparate  = (PFNGLSTENCILMASKSEPARATEPROC) ShaderGL::getProcAddress ( "glStencilMaskSeparate" );

                                                                    // blend ops from OPenGL 2.0
            glBlendEquation         = (PFNGLBLENDEQUATIONPROC)         ShaderGL::getProcAddress ( "glBlendEquation" );
            glBlendEquationSeparate = (PFNGLBLENDEQUATIONSEPARATEPROC) ShaderGL::getProcAddress ( "glBlendEquationSeparate" );
            glBlendFuncSeparate     = (PFNGLBLENDFUNCSEPARATEPROC)     ShaderGL::getProcAddress ( "glBlendFuncSeparate" );
            glBlendColor            = (PFNGLBLENDCOLORPROC)            ShaderGL::getProcAddress ( "glBlendColor" );
        #endif

                                                                // draw buffers from OpenGL 2.0
        glDrawBuffers           = (PFNGLDRAWBUFFERSPROC)           ShaderGL::getProcAddress ( "glDrawBuffers" );
                                                                // ATI_draw_buffers
        glDrawBuffersATI        = (PFNGLDRAWBUFFERSATIPROC)        ShaderGL::getProcAddress ( "glDrawBuffersATI" );

                                                                // EXT_texture_integer
        glTexParameterIivEXT      = (PFNGLTEXPARAMETERIIVEXTPROC)     ShaderGL::getProcAddress ( "glTexParameterIivEXT" );
        glTexParameterIuivEXT     = (PFNGLTEXPARAMETERIUIVEXTPROC)    ShaderGL::getProcAddress ( "glTexParameterIuivEXT" );
        glGetTexParameterIivEXT   = (PFNGLGETTEXPARAMETERIIVEXTPROC)  ShaderGL::getProcAddress ( "glGetTexParameterIivEXT" );
        glGetTexParameterIuivEXT  = (PFNGLGETTEXPARAMETERIUIVEXTPROC) ShaderGL::getProcAddress ( "glGetTexParameterIuivEXT" );
        glClearColorIiEXT         = (PFNGLCLEARCOLORIIEXTPROC)        ShaderGL::getProcAddress ( "glClearColorIiEXT" );
        glClearColorIuiEXT        = (PFNGLCLEARCOLORIUIEXTPROC)       ShaderGL::getProcAddress ( "glClearColorIuiEXT" );

                                                                // EXT_draw_instanced
        glDrawArraysInstancedEXT    = (PFNGLDRAWARRAYSINSTANCEDEXTPROC)    ShaderGL::getProcAddress ( "glDrawArraysInstancedEXT" );
        glDrawElementsInstancedEXT  = (PFNGLDRAWELEMENTSINSTANCEDEXTPROC)  ShaderGL::getProcAddress ( "glDrawElementsInstancedEXT" );

                                                                // EXT_texture_buffer_object
        glTexBufferEXT  = (PFNGLTEXBUFFEREXTPROC)  ShaderGL::getProcAddress ( "glTexBufferEXT" );

                                                                // EXT_gpu_shader4
        glGetUniformuivEXT         = (PFNGLGETUNIFORMUIVEXTPROC)        ShaderGL::getProcAddress ( "" );
        glBindFragDataLocationEXT  = (PFNGLBINDFRAGDATALOCATIONEXTPROC) ShaderGL::getProcAddress ( "glBindFragDataLocationEXT" );
        glGetFragDataLocationEXT   = (PFNGLGETFRAGDATALOCATIONEXTPROC)  ShaderGL::getProcAddress ( "glGetFragDataLocationEXT" );
        glUniform1uiEXT            = (PFNGLUNIFORM1UIEXTPROC)           ShaderGL::getProcAddress ( "glUniform1uiEXT" );
        glUniform2uiEXT            = (PFNGLUNIFORM2UIEXTPROC)           ShaderGL::getProcAddress ( "glUniform2uiEXT" );
        glUniform3uiEXT            = (PFNGLUNIFORM3UIEXTPROC)           ShaderGL::getProcAddress ( "glUniform3uiEXT" );
        glUniform4uiEXT            = (PFNGLUNIFORM4UIEXTPROC)           ShaderGL::getProcAddress ( "glUniform4uiEXT" );
        glUniform1uivEXT           = (PFNGLUNIFORM1UIVEXTPROC)          ShaderGL::getProcAddress ( "glUniform1uivEXT" );
        glUniform2uivEXT           = (PFNGLUNIFORM2UIVEXTPROC)          ShaderGL::getProcAddress ( "glUniform2uivEXT" );
        glUniform3uivEXT           = (PFNGLUNIFORM2UIVEXTPROC)          ShaderGL::getProcAddress ( "glUniform3uivEXT" );
        glUniform4uivEXT           = (PFNGLUNIFORM2UIVEXTPROC)          ShaderGL::getProcAddress ( "glUniform4uivEXT" );
        glVertexAttribI1iEXT       = (PFNGLVERTEXATTRIBI1IEXTPROC)      ShaderGL::getProcAddress ( "glVertexAttribI1iEXT" );
        glVertexAttribI2iEXT       = (PFNGLVERTEXATTRIBI2IEXTPROC)      ShaderGL::getProcAddress ( "glVertexAttribI2iEXT" );
        glVertexAttribI3iEXT       = (PFNGLVERTEXATTRIBI3IEXTPROC)      ShaderGL::getProcAddress ( "glVertexAttribI3iEXT" );
        glVertexAttribI4iEXT       = (PFNGLVERTEXATTRIBI4IEXTPROC)      ShaderGL::getProcAddress ( "glVertexAttribI4iEXT" );
        glVertexAttribI1uiEXT      = (PFNGLVERTEXATTRIBI1UIEXTPROC)     ShaderGL::getProcAddress ( "glVertexAttribI1uiEXT" );
        glVertexAttribI2uiEXT      = (PFNGLVERTEXATTRIBI2UIEXTPROC)     ShaderGL::getProcAddress ( "glVertexAttribI2uiEXT" );
        glVertexAttribI3uiEXT      = (PFNGLVERTEXATTRIBI3UIEXTPROC)     ShaderGL::getProcAddress ( "glVertexAttribI3uiEXT" );
        glVertexAttribI4uiEXT      = (PFNGLVERTEXATTRIBI4UIEXTPROC)     ShaderGL::getProcAddress ( "glVertexAttribI4uiEXT" );
        glVertexAttribI1ivEXT      = (PFNGLVERTEXATTRIBI1IVEXTPROC)     ShaderGL::getProcAddress ( "glVertexAttribI1ivEXT" );
        glVertexAttribI2ivEXT      = (PFNGLVERTEXATTRIBI2IVEXTPROC)     ShaderGL::getProcAddress ( "glVertexAttribI2ivEXT" );
        glVertexAttribI3ivEXT      = (PFNGLVERTEXATTRIBI3IVEXTPROC)     ShaderGL::getProcAddress ( "glVertexAttribI3ivEXT" );
        glVertexAttribI4ivEXT      = (PFNGLVERTEXATTRIBI4IVEXTPROC)     ShaderGL::getProcAddress ( "glVertexAttribI4ivEXT" );
        glVertexAttribI1uivEXT     = (PFNGLVERTEXATTRIBI1UIVEXTPROC)    ShaderGL::getProcAddress ( "glVertexAttribI1uivEXT" );
        glVertexAttribI2uivEXT     = (PFNGLVERTEXATTRIBI2UIVEXTPROC)    ShaderGL::getProcAddress ( "glVertexAttribI2uivEXT" );
        glVertexAttribI3uivEXT     = (PFNGLVERTEXATTRIBI3UIVEXTPROC)    ShaderGL::getProcAddress ( "glVertexAttribI3uivEXT" );
        glVertexAttribI4uivEXT     = (PFNGLVERTEXATTRIBI4UIVEXTPROC)    ShaderGL::getProcAddress ( "glVertexAttribI4uivEXT" );
        glVertexAttribI4bvEXT      = (PFNGLVERTEXATTRIBI4BVEXTPROC)     ShaderGL::getProcAddress ( "glVertexAttribI4bvEXT" );
        glVertexAttribI4svEXT      = (PFNGLVERTEXATTRIBI4SVEXTPROC)     ShaderGL::getProcAddress ( "glVertexAttribI4svEXT" );
        glVertexAttribI4ubvEXT     = (PFNGLVERTEXATTRIBI4UBVEXTPROC)    ShaderGL::getProcAddress ( "glVertexAttribI4ubvEXT" );
        glVertexAttribI4usvEXT     = (PFNGLVERTEXATTRIBI4USVEXTPROC)    ShaderGL::getProcAddress ( "glVertexAttribI4usvEXT" );
        glVertexAttribIPointerEXT  = (PFNGLVERTEXATTRIBIPOINTEREXTPROC) ShaderGL::getProcAddress ( "glVertexAttribIPointerEXT" );
        glGetVertexAttribIivEXT    = (PFNGLGETVERTEXATTRIBIIVEXTPROC)   ShaderGL::getProcAddress ( "glGetVertexAttribIivEXT" );
        glGetVertexAttribIuivEXT   = (PFNGLGETVERTEXATTRIBIUIVEXTPROC)  ShaderGL::getProcAddress ( "glGetVertexAttribIuivEXT" );

                                                            // EXT_geometry_shader4
        glProgramParameteriEXT       = (PFNGLPROGRAMPARAMETERIEXTPROC)       ShaderGL::getProcAddress ( "glProgramParameteriEXT" );
        glFramebufferTextureEXT      = (PFNGLFRAMEBUFFERTEXTUREEXTPROC)      ShaderGL::getProcAddress ( "glFramebufferTextureEXT" );
        glFramebufferTextureLayerEXT = (PFNGLFRAMEBUFFERTEXTURELAYEREXTPROC) ShaderGL::getProcAddress ( "glFramebufferTextureLayerEXT" );
        glFramebufferTextureFaceEXT  = (PFNGLFRAMEBUFFERTEXTUREFACEEXTPROC)  ShaderGL::getProcAddress ( "glFramebufferTextureFaceEXT" );

          ShaderGL::shading_enabled = true;
    } else
          ShaderGL::shading_enabled = false;

    ShaderGL::setupExtensionsPlatform();

}

void ShaderGL::setupExtensionsVBO(){

    if( ShaderGL::glExtensionSupported("GL_ARB_vertex_buffer_object")){
        glBindBufferARB           = (PFNGLBINDBUFFERARBPROC)           ShaderGL::getProcAddress ( "glBindBufferARB"           );
        glDeleteBuffersARB        = (PFNGLDELETEBUFFERSARBPROC)        ShaderGL::getProcAddress ( "glDeleteBuffersARB"        );
        glGenBuffersARB           = (PFNGLGENBUFFERSARBPROC)           ShaderGL::getProcAddress ( "glGenBuffersARB"           );
        glIsBufferARB             = (PFNGLISBUFFERARBPROC)             ShaderGL::getProcAddress ( "glIsBufferARB"             );
        glBufferDataARB           = (PFNGLBUFFERDATAARBPROC)           ShaderGL::getProcAddress ( "glBufferDataARB"           );
        glBufferSubDataARB        = (PFNGLBUFFERSUBDATAARBPROC)        ShaderGL::getProcAddress ( "glBufferSubDataARB"        );
        glGetBufferSubDataARB     = (PFNGLGETBUFFERSUBDATAARBPROC)     ShaderGL::getProcAddress ( "glGetBufferSubDataARB"     );
        glMapBufferARB            = (PFNGLMAPBUFFERARBPROC)            ShaderGL::getProcAddress ( "glMapBufferARB"            );
        glUnmapBufferARB          = (PFNGLUNMAPBUFFERARBPROC)          ShaderGL::getProcAddress ( "glUnmapBufferARB"          );
        glGetBufferParameterivARB = (PFNGLGETBUFFERPARAMETERIVARBPROC) ShaderGL::getProcAddress ( "glGetBufferParameterivARB" );
        glGetBufferPointervARB    = (PFNGLGETBUFFERPOINTERVARBPROC)    ShaderGL::getProcAddress ( "glGetBufferPointervARB"    );

        ShaderGL::vbo_enabled = true;
    }else
        ShaderGL::vbo_enabled = false;

}

void ShaderGL::setupExtensionsMultiTexel(){

  if( ShaderGL::glExtensionSupported("GL_ARB_multitexture") &&
      ShaderGL::glExtensionSupported("GL_EXT_texture_env_combine") )
  {
    #if defined(_ISWINDOWS)
        glActiveTextureARB       = (PFNGLACTIVETEXTUREARBPROC)         ShaderGL::getProcAddress ( "glActiveTextureARB"       );
        glClientActiveTextureARB = (PFNGLCLIENTACTIVETEXTUREARBPROC)   ShaderGL::getProcAddress ( "glClientActiveTextureARB" );
        glMultiTexCoord1f        = (PFNGLMULTITEXCOORD1FARBPROC)       ShaderGL::getProcAddress ( "glMultiTexCoord1fARB"     );
        glMultiTexCoord1fv       = (PFNGLMULTITEXCOORD1FVARBPROC)      ShaderGL::getProcAddress ( "glMultiTexCoord1fvARB"    );
        glMultiTexCoord2f        = (PFNGLMULTITEXCOORD2FARBPROC)       ShaderGL::getProcAddress ( "glMultiTexCoord2fARB"     );
        glMultiTexCoord2fv       = (PFNGLMULTITEXCOORD2FVARBPROC)      ShaderGL::getProcAddress ( "glMultiTexCoord2fvARB"    );
        glMultiTexCoord3f        = (PFNGLMULTITEXCOORD3FARBPROC)       ShaderGL::getProcAddress ( "glMultiTexCoord3fARB"     );
        glMultiTexCoord3fv       = (PFNGLMULTITEXCOORD3FVARBPROC)      ShaderGL::getProcAddress ( "glMultiTexCoord3fvARB"    );
        glMultiTexCoord4f        = (PFNGLMULTITEXCOORD4FARBPROC)       ShaderGL::getProcAddress ( "glMultiTexCoord4fARB"     );
        glMultiTexCoord4fv       = (PFNGLMULTITEXCOORD4FVARBPROC)      ShaderGL::getProcAddress ( "glMultiTexCoord4fvARB"    );

        ShaderGL::multitexel_enabled = true;
    #else
            ShaderGL::multitexel_enabled = true;
    #endif
  } else
      ShaderGL::multitexel_enabled = false;

  glGetIntegerv(GL_MAX_TEXTURE_UNITS_ARB,&ShaderGL::maxTexelUnits);
}

#else
      void ShaderGL::setupExtensionsShader(){
          if( ShaderGL::glExtensionSupported("GL_ARB_shader_objects") &&
                ShaderGL::glExtensionSupported("GL_ARB_shading_language_100") &&
                ShaderGL::glExtensionSupported("GL_ARB_vertex_shader") &&
                ShaderGL::glExtensionSupported("GL_ARB_fragment_shader"))
                    ShaderGL::shading_enabled = true;
            else
                ShaderGL::shading_enabled = false;

            ShaderGL::wgl_enabled = false;
            ShaderGL::glx_enabled = false;
        }
        void ShaderGL::setupExtensionsVBO(){
          if(this->glExtensionSupported("GL_ARB_vertex_buffer_object"))
                ShaderGL::vbo_enabled = true;
            else
                ShaderGL::vbo_enabled = false;
        }
        void ShaderGL::setupExtensionsMultiTexel(){
          if( uglExtensionSupported("GL_ARB_multitexture") &&
                uglExtensionSupported("GL_EXT_texture_env_combine")){
                    ShaderGL::multitexel_enabled = true;
                    glGetIntegerv(GL_MAX_TEXTURE_UNITS_ARB,&ShaderGL::maxTexelUnits);
            }else
                ShaderGL::multitexel_enabled = false;
        }
#endif

bool ShaderGL::wgl_enabled = false;
bool ShaderGL::glx_enabled = false;
bool ShaderGL::shading_enabled = false;
bool ShaderGL::vbo_enabled = false;
bool ShaderGL::multitexel_enabled = false;
bool ShaderGL::GL_NV_occlusion_query_enabled = false;
bool ShaderGL::GL_SGIS_generate_mipmap_enabled = false;
bool ShaderGL::GL_NV_register_combiners_enabled = false;
int ShaderGL::GL_NV_maxCombiners = 0;
std::string ShaderGL::vendor_info;
std::string ShaderGL::renderer_info;
std::string ShaderGL::version_info;
int ShaderGL::maxTexelUnits = 1;
bool ShaderGL::initSetupExtensions = false;

ShaderGL::ShaderGL():
	programObj(0),
    fragmentShader(0),
    vertexShader(0)
{
    if(!ShaderGL::initSetupExtensions){
        ShaderGL::InitGLShader();
        ShaderGL::initSetupExtensions = true;
    }
}

ShaderGL::ShaderGL(const ShaderGL& copy):
	programObj(0),
    fragmentShader(0),
    vertexShader(0)
{
    if(!ShaderGL::initSetupExtensions){
        ShaderGL::InitGLShader();
        ShaderGL::initSetupExtensions = true;
    }
    *this = copy;
}

ShaderGL::~ShaderGL(){
    if (this->fragmentShader)
		glDeleteObjectARB( this->fragmentShader );
	if (this->vertexShader)
		glDeleteObjectARB( this->vertexShader );
	if (this->programObj)
		glDeleteObjectARB( this->programObj );
}

void ShaderGL::loadFromCode(){
    if(!this->fsCode.empty())
        this->LoadGLFragmentShader(this->fsCode,NULL);
    if(!this->vsCode.empty())
        this->LoadGLVertexShader(this->vsCode,NULL);

    if(this->fsCode.empty() && this->vsCode.empty()){
        if (this->fragmentShader)
            glDeleteObjectARB( this->fragmentShader );
        if (this->vertexShader)
            glDeleteObjectARB( this->vertexShader );
        if (this->programObj)
            glDeleteObjectARB( this->programObj );
        this->fragmentShader = 0;
        this->vertexShader = 0;
        this->programObj = 0;
    }else
        this->CreateShaderProgram(NULL);
}

ShaderGL& ShaderGL::operator= (const ShaderGL& copy){
    if(this != &copy){
        this->fsCode = copy.fsCode;
        this->vsCode = copy.vsCode;

        this->loadFromCode();
    }
    return *this;
}

std::ostream& operator<<(std::ostream &out,const ShaderGL& obj){
    out << obj.fsCode;
    out << obj.vsCode;

    return out;
}
std::istream& operator>>(std::istream &in, ShaderGL& copy){
    in >> copy.fsCode;
    in >> copy.vsCode;

    copy.loadFromCode();

    return in;
}

int ShaderGL::loadshader(std::string filename, std::string& ShaderSource){
   std::ifstream file;
   file.open(filename.c_str(), std::ios::in); // opens as ASCII!
   if(!file)
    return -1;

   uint32 len;
   if(!file.good())
      len = 0;
   else{
      file.seekg (0, std::ios::end);
      len = file.tellg();
      file.seekg(0,std::ios::beg);
   }

   if (len == 0)
      return -2;   // Error: Empty File

   while (!file.eof()){
     ShaderSource.push_back(file.get());
   }

   file.close();

   return 1; // No Error
}

int16 ShaderGL::InitGLShader(){
    ShaderGL::setupExtensionsShader();
    ShaderGL::setupExtensionsVBO();
    ShaderGL::setupExtensionsMultiTexel();
    ShaderGL::initInfo();

    if(! ShaderGL::glExtensionSupported("GL_ARB_shading_language_100") )
        return -1;

    if(! ShaderGL::glExtensionSupported("GL_ARB_shader_objects"))
        return -2;

    if(!ShaderGL::shading_enabled)
      return -3;

    return 1;
}

void ShaderGL::printLog(uint obj,std::string* error){
    if(!error)
        return;
    int infologLength = 0;
    char infoLog[1024];

    glGetInfoLogARB(obj, 1024, &infologLength, infoLog);

    if (infologLength > 0){
		std::string tmp (infoLog,infologLength);
		*error += tmp;
		*error += '\n';
    }
}

int16 ShaderGL::LoadGLVertexShader(std::string shaderfilename,std::string* error){
    /* The vertex shader */
	std::string vsSource;
	int status = this->loadshader(shaderfilename.c_str(),vsSource);
	if(status < 0)
	    return status;

	/* Compile and load the program */
	if (this->vertexShader)
		glDeleteObjectARB( this->vertexShader );
    this->vertexShader = 0;

    std::stringstream getfilename;
    getfilename << "Shader Filename: " << shaderfilename << std::endl;
    if(error)
        *error += getfilename.str();

    const GLcharARB* vsSrc = vsSource.c_str();
	this->vertexShader = glCreateShaderObjectARB(GL_VERTEX_SHADER);
	glShaderSourceARB(this->vertexShader, 1,&vsSrc,NULL);
	glCompileShaderARB(this->vertexShader);
	this->printLog(this->vertexShader,error);
	this->vsCode = vsSource;

	return 1;
}

int16 ShaderGL::LoadGLFragmentShader(std::string shaderfilename,std::string* error){
	/* The fragment shader */
	std::string fsSource;
	int status = this->loadshader(shaderfilename,fsSource);
	if(status < 0)
	    return status;

	/* Compile and load the program */
    if (this->fragmentShader)
        glDeleteObjectARB( this->fragmentShader );
    this->fragmentShader = 0;

    std::stringstream getfilename;
    getfilename << "Shader Filename: " << shaderfilename << std::endl;
    if(error)
        *error += getfilename.str();

    const GLcharARB* fsSrc = fsSource.c_str();
	this->fragmentShader = glCreateShaderObjectARB(GL_FRAGMENT_SHADER);
	glShaderSourceARB(this->fragmentShader, 1,&fsSrc, NULL);
	glCompileShaderARB(this->fragmentShader);
	this->printLog(this->fragmentShader,error);
	this->fsCode = fsSource;

	return 1;
}

void ShaderGL::CreateShaderProgram(std::string* error){
    if (this->programObj)
		glDeleteObjectARB( this->programObj );
    this->programObj = 0;

	this->programObj = glCreateProgramObjectARB();
    glAttachObjectARB(this->programObj, this->fragmentShader);
    glAttachObjectARB(this->programObj, this->vertexShader);
    glLinkProgramARB(this->programObj);
	this->printLog(this->programObj,error);
}

int ShaderGL::getUniformi(std::string name) const {
    if(!this->programObj)
        return 0;

    int result = 0;
    GLint unilocal = glGetUniformLocationARB(this->programObj,name.c_str());
    glGetUniformivARB(this->programObj,unilocal,&result);
    return result;
}
float ShaderGL::getUniformf(std::string name) const {
    if(!this->programObj)
        return 0.0f;

    float result = 0.0f;
    GLint unilocal = glGetUniformLocationARB(this->programObj,name.c_str());
    glGetUniformfvARB(this->programObj,unilocal,&result);
    return result;
}

void ShaderGL::setUniformi(std::string name,int value){
    if(!this->programObj)
        return;

    GLhandleARB curHandle = glGetHandleARB(GL_PROGRAM_OBJECT_ARB);
    glUseProgramObjectARB(this->programObj);
    GLint unilocal = glGetUniformLocationARB(this->programObj,name.c_str());
    glUniform1iARB(unilocal,value);
    glUseProgramObjectARB(curHandle);
}
void ShaderGL::setUniformf(std::string name,float value){
    if(!this->programObj)
        return;

    GLhandleARB curHandle = glGetHandleARB(GL_PROGRAM_OBJECT_ARB);
    glUseProgramObjectARB(this->programObj);
    GLint unilocal = glGetUniformLocationARB(this->programObj,name.c_str());
    glUniform1fARB(unilocal,value);
    glUseProgramObjectARB(curHandle);
}

bool ShaderGL::getSupportedShader(){return ShaderGL::shading_enabled;}
bool ShaderGL::getSupportedVBO(){return ShaderGL::vbo_enabled;}
bool ShaderGL::getSupportedMultiTexel(){return ShaderGL::multitexel_enabled;}
int ShaderGL::getMaxTexelUnits(){return ShaderGL::maxTexelUnits;}

bool ShaderGL::getSupportedWGL(){return ShaderGL::wgl_enabled;}
bool ShaderGL::getSupportedGLX(){return ShaderGL::glx_enabled;}
bool ShaderGL::getSupportedNVOcclusionQuery(){return ShaderGL::GL_NV_occlusion_query_enabled;}
bool ShaderGL::getSupportedSGISGenerateMipmap(){return ShaderGL::GL_SGIS_generate_mipmap_enabled;}
bool ShaderGL::getSupportedNVRegisterCombiners(){return ShaderGL::GL_NV_register_combiners_enabled;}
int ShaderGL::getMaxNVCombiners(){return ShaderGL::GL_NV_maxCombiners;}

std::string ShaderGL::getGLVendor(){return ShaderGL::vendor_info;}
std::string ShaderGL::getGLRenderer(){return ShaderGL::renderer_info;}
std::string ShaderGL::getGLVersion(){return ShaderGL::version_info;}

GLhandleARB ShaderGL::getProgramObj() const {return this->programObj;}
GLhandleARB ShaderGL::getFragmentShader() const {return this->vertexShader;}
GLhandleARB ShaderGL::getVertexShader() const {return this->programObj;}

std::string ShaderGL::getFragmentCode() const {return this->fsCode;}
std::string ShaderGL::getVertexCode() const {return this->vsCode;}

void* ShaderGL::getProcAddress(std::string proc){
    if(proc.empty())
        return NULL;

    #ifdef WIN32_OR_X11
        #if defined(_ISWINDOWS)
            return (void*)wglGetProcAddress(proc.c_str());
        #elif defined(_ISLINUX)
            return (void*)glXGetProcAddress((const GLubyte*)(proc.c_str()));
        #endif
    #endif
    return glfwGetProcAddress(proc.c_str());
}

bool ShaderGL::glExtensionSupported(std::string ext){
    if(ext.empty())
        return false;

    char* extl = (char*)glGetString(GL_EXTENSIONS);

    if (ShaderGL::findString(ext,extl)){
	    return true;
    }

    #ifdef WIN32_OR_X11
        #if defined(_ISWINDOWS)
            if ( wglGetExtensionsStringARB == NULL ){
                return false;
            }

            extl = (char*)wglGetExtensionsStringARB(wglGetCurrentDC());
            bool result = ShaderGL::findString(ext,extl);
            return result;
        #elif defined(_ISLINUX)
            Display* display = glXGetCurrentDisplay();
            int screen = 0;
            if(display)
                screen  = DefaultScreen(display);
            else{
                return false;
            }

            extl = (char*)glXQueryExtensionsString(display,screen);
            bool result = ShaderGL::findString(ext,extl);
            return result;
        #endif
    #endif

    return false;
}

bool ShaderGL::findString(std::string in, std::string list){
  if(in.length() < 1 || list.length() < 1)
    return false;

  return list.find(in) != std::string::npos;
}

std::string ShaderGL::getGLExtensions(){
	return std::string((char*)glGetString(GL_EXTENSIONS));
}

std::string ShaderGL::getPlatformExtensions(){
    if(!ShaderGL::initSetupExtensions){
        ShaderGL::InitGLShader();
        ShaderGL::initSetupExtensions = true;
    }

    #ifdef WIN32_OR_X11
        #if defined(_ISWINDOWS)
            if ( wglGetExtensionsStringARB == NULL )
                return "";
            return wglGetExtensionsStringARB ( wglGetCurrentDC () );
        #elif defined(_ISLINUX)
            Display* display = glXGetCurrentDisplay();
            int screen = 0;
            if(display)
                screen = DefaultScreen(display);
            else
                return "";

            return glXQueryExtensionsString ( display, screen );
        #endif
    #endif
    return "";
}

void ShaderGL::initInfo(){
    const char* vendor = (const char*)glGetString(GL_VENDOR);
    ShaderGL::vendor_info = (vendor)? std::string(vendor) : "";

    const char* renderer = (const char*)glGetString(GL_RENDERER);
    ShaderGL::renderer_info = (renderer)? std::string(renderer) : "";

    const char* version = (const char*)glGetString(GL_VERSION);
    ShaderGL::version_info = (version)? std::string(version) : "";

    if( ShaderGL::glExtensionSupported("GL_NV_register_combiners" ) ){
        ShaderGL::GL_NV_register_combiners_enabled = true;
        glGetIntegerv(GL_MAX_GENERAL_COMBINERS_NV, &ShaderGL::GL_NV_maxCombiners);
    }else
        ShaderGL::GL_NV_register_combiners_enabled = false;

    ShaderGL::GL_NV_occlusion_query_enabled = ShaderGL::glExtensionSupported( "GL_NV_occlusion_query" );
    ShaderGL::GL_SGIS_generate_mipmap_enabled = ShaderGL::glExtensionSupported( "GL_SGIS_generate_mipmap" );
}


}
