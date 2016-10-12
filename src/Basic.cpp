#include <Fantasy2C/Basic.hpp>

#ifdef WIN32_OR_X11
#if defined(_ISWINDOWS)
// under Linux all multitexture is
// supported by OpenGL itself

PFNGLACTIVETEXTUREARBPROC        glActiveTextureARB        = NULL;
PFNGLCLIENTACTIVETEXTUREARBPROC  glClientActiveTextureARB  = NULL;
PFNGLMULTITEXCOORD1FARBPROC      glMultiTexCoord1f         = NULL;
PFNGLMULTITEXCOORD1FVARBPROC     glMultiTexCoord1fv        = NULL;
PFNGLMULTITEXCOORD2FARBPROC      glMultiTexCoord2f         = NULL;
PFNGLMULTITEXCOORD2FVARBPROC     glMultiTexCoord2fv        = NULL;
PFNGLMULTITEXCOORD3FARBPROC      glMultiTexCoord3f         = NULL;
PFNGLMULTITEXCOORD3FVARBPROC     glMultiTexCoord3fv        = NULL;
PFNGLMULTITEXCOORD4FARBPROC      glMultiTexCoord4f         = NULL;
PFNGLMULTITEXCOORD4FVARBPROC     glMultiTexCoord4fv        = NULL;
#endif

// fog coord function
PFNGLFOGCOORDFEXTPROC            glFogCoordf               = NULL;

// secondary color functions
PFNGLSECONDARYCOLOR3FPROC        glSecondaryColor3f        = NULL;
PFNGLSECONDARYCOLOR3FVPROC       glSecondaryColor3fv       = NULL;
PFNGLSECONDARYCOLORPOINTERPROC   glSecondaryColorPointer   = NULL;


// register combiners functions
PFNGLCOMBINERPARAMETERFVNVPROC   glCombinerParameterfvNV   = NULL;
PFNGLCOMBINERPARAMETERIVNVPROC   glCombinerParameterivNV   = NULL;
PFNGLCOMBINERPARAMETERFNVPROC    glCombinerParameterfNV    = NULL;
PFNGLCOMBINERPARAMETERINVPROC    glCombinerParameteriNV    = NULL;
PFNGLCOMBINERINPUTNVPROC         glCombinerInputNV         = NULL;
PFNGLCOMBINEROUTPUTNVPROC        glCombinerOutputNV        = NULL;
PFNGLFINALCOMBINERINPUTNVPROC    glFinalCombinerInputNV    = NULL;

// VBO functions
PFNGLBINDBUFFERARBPROC           glBindBufferARB           = NULL;
PFNGLDELETEBUFFERSARBPROC        glDeleteBuffersARB        = NULL;
PFNGLGENBUFFERSARBPROC           glGenBuffersARB           = NULL;
PFNGLISBUFFERARBPROC             glIsBufferARB             = NULL;
PFNGLBUFFERDATAARBPROC           glBufferDataARB           = NULL;
PFNGLBUFFERSUBDATAARBPROC        glBufferSubDataARB        = NULL;
PFNGLGETBUFFERSUBDATAARBPROC     glGetBufferSubDataARB     = NULL;
PFNGLMAPBUFFERARBPROC            glMapBufferARB            = NULL;
PFNGLUNMAPBUFFERARBPROC          glUnmapBufferARB          = NULL;
PFNGLGETBUFFERPARAMETERIVARBPROC glGetBufferParameterivARB = NULL;
PFNGLGETBUFFERPOINTERVARBPROC    glGetBufferPointervARB    = NULL;


#if defined(_ISWINDOWS)
    PFNWGLGETEXTENSIONSSTRINGARBPROC        wglGetExtensionsStringARB = NULL;

                                        // p-buffer functions
    PFNWGLCREATEPBUFFERARBPROC              wglCreatePbufferARB     = NULL;
    PFNWGLGETPBUFFERDCARBPROC               wglGetPbufferDCARB      = NULL;
    PFNWGLRELEASEPBUFFERDCARBPROC           wglReleasePbufferDCARB  = NULL;
    PFNWGLDESTROYPBUFFERARBPROC             wglDestroyPbufferARB    = NULL;
    PFNWGLQUERYPBUFFERARBPROC               wglQueryPbufferARB      = NULL;

                                        // WGL_ARB_pixel_format
    PFNWGLCHOOSEPIXELFORMATARBPROC          wglChoosePixelFormatARB = NULL;

                                        // WGL_ARB_render_texture
    PFNWGLBINDTEXIMAGEARBPROC               wglBindTexImageARB      = NULL;
    PFNWGLRELEASETEXIMAGEARBPROC            wglReleaseTexImageARB   = NULL;
    PFNWGLSETPBUFFERATTRIBARBPROC           wglSetPbufferAttribARB  = NULL;

                                        // WGL_EXT_swap_control
    PFNWGLSWAPINTERVALEXTPROC               wglSwapIntervalEXT      = NULL;
    PFNWGLGETSWAPINTERVALEXTPROC            wglGetSwapIntervalEXT   = NULL;
#elif defined(_ISLINUX)
                                        // GLX_SGIX_pbuffer
    PFNGLXCREATEGLXPBUFFERSGIXPROC          glXCreateGLXPbufferSGIX  = NULL;
    PFNGLXDESTROYGLXPBUFFERSGIXPROC         glXDestroyGLXPbufferSGIX = NULL;
    PFNGLXQUERYGLXPBUFFERSGIXPROC           glXQueryGLXPbufferSGIX   = NULL;

                                        // GLX_SGIX_fbconfig
    PFNGLXCHOOSEFBCONFIGSGIXPROC            glXChooseFBConfigSGIX          = NULL;
    PFNGLXCREATECONTEXTWITHCONFIGSGIXPROC   glXCreateContextWithConfigSGIX = NULL;
#endif

                                    // NV-occlusion query extension
PFNGLGENOCCLUSIONQUERIESNVPROC          glGenOcclusionQueriesNV = NULL;
PFNGLBEGINOCCLUSIONQUERYNVPROC          glBeginOcclusionQueryNV = NULL;
PFNGLENDOCCLUSIONQUERYNVPROC            glEndOcclusionQueryNV   = NULL;
PFNGLGETOCCLUSIONQUERYIVNVPROC          glGetOcclusionQueryivNV = NULL;

                                    // ARB_vertex_program extension
PFNGLGENPROGRAMSARBPROC                 glGenProgramsARB        = NULL;
PFNGLDELETEPROGRAMSARBPROC              glDeleteProgramsARB     = NULL;
PFNGLBINDPROGRAMARBPROC                 glBindProgramARB        = NULL;
PFNGLISPROGRAMARBPROC                   glIsProgramARB          = NULL;

PFNGLPROGRAMSTRINGARBPROC               glProgramStringARB      = NULL;
PFNGLGETPROGRAMIVARBPROC                glGetProgramivARB       = NULL;

PFNGLVERTEXATTRIB4FARBPROC              glVertexAttrib4fARB     = NULL;
PFNGLVERTEXATTRIB4FVARBPROC             glVertexAttrib4fvARB    = NULL;
PFNGLVERTEXATTRIB3FARBPROC              glVertexAttrib3fARB     = NULL;
PFNGLVERTEXATTRIB3FVARBPROC             glVertexAttrib3fvARB    = NULL;

PFNGLVERTEXATTRIBPOINTERARBPROC         glVertexAttribPointerARB        = NULL;
PFNGLENABLEVERTEXATTRIBARRAYARBPROC     glEnableVertexAttribArrayARB    = NULL;
PFNGLDISABLEVERTEXATTRIBARRAYARBPROC    glDisableVertexAttribArrayARB   = NULL;

PFNGLPROGRAMLOCALPARAMETER4FARBPROC     glProgramLocalParameter4fARB    = NULL;
PFNGLPROGRAMLOCALPARAMETER4FVARBPROC    glProgramLocalParameter4fvARB   = NULL;

PFNGLGETPROGRAMLOCALPARAMETERFVARBPROC  glGetProgramLocalParameterfvARB = NULL;

PFNGLPROGRAMENVPARAMETER4FARBPROC       glProgramEnvParameter4fARB      = NULL;
PFNGLPROGRAMENVPARAMETER4FVARBPROC      glProgramEnvParameter4fvARB     = NULL;

PFNGLGETPROGRAMENVPARAMETERFVARBPROC    glGetProgramEnvParameterfvARB   = NULL;

                                    // GL_EXT_texture3D
PFNGLTEXIMAGE3DEXTPROC                  glTexImage3DEXT                  = NULL;

                                    // ARB_texture_compression
PFNGLCOMPRESSEDTEXIMAGE3DARBPROC        glCompressedTexImage3DARB        = NULL;
PFNGLCOMPRESSEDTEXIMAGE2DARBPROC        glCompressedTexImage2DARB        = NULL;
PFNGLCOMPRESSEDTEXIMAGE1DARBPROC        glCompressedTexImage1DARB        = NULL;
PFNGLCOMPRESSEDTEXSUBIMAGE3DARBPROC     glCompressedTexSubImage3DARB     = NULL;
PFNGLCOMPRESSEDTEXSUBIMAGE2DARBPROC     glCompressedTexSubImage2DARB     = NULL;
PFNGLCOMPRESSEDTEXSUBIMAGE1DARBPROC     glCompressedTexSubImage1DARB     = NULL;
PFNGLGETCOMPRESSEDTEXIMAGEARBPROC       glGetCompressedTexImageARB       = NULL;

                                    // ARB_point_parameters
PFNGLPOINTPARAMETERFARBPROC             glPointParameterfARB             = NULL;
PFNGLPOINTPARAMETERFVARBPROC            glPointParameterfvARB            = NULL;

                                    // ARB_occlusion_query
PFNGLGENQUERIESARBPROC                  glGenQueriesARB        = NULL;
PFNGLDELETEQUERIESARBPROC               glDeleteQueriesARB     = NULL;
PFNGLISQUERYARBPROC                     glIsQueryARB           = NULL;
PFNGLBEGINQUERYARBPROC                  glBeginQueryARB        = NULL;
PFNGLENDQUERYARBPROC                    glEndQueryARB          = NULL;
PFNGLGETQUERYIVARBPROC                  glGetQueryivARB        = NULL;
PFNGLGETQUERYOBJECTIVARBPROC            glGetQueryObjectivARB  = NULL;
PFNGLGETQUERYOBJECTUIVARBPROC           glGetQueryObjectuivARB = NULL;

                                    // GLSL-specific extensions
                                    // GL_ARB_shader_object
PFNGLDELETEOBJECTARBPROC                glDeleteObjectARB         = NULL;
PFNGLGETHANDLEARBPROC                   glGetHandleARB            = NULL;
PFNGLDETACHOBJECTARBPROC                glDetachObjectARB         = NULL;
PFNGLCREATESHADEROBJECTARBPROC          glCreateShaderObjectARB   = NULL;
PFNGLSHADERSOURCEARBPROC                glShaderSourceARB         = NULL;
PFNGLCOMPILESHADERARBPROC               glCompileShaderARB        = NULL;
PFNGLCREATEPROGRAMOBJECTARBPROC         glCreateProgramObjectARB  = NULL;
PFNGLATTACHOBJECTARBPROC                glAttachObjectARB         = NULL;
PFNGLLINKPROGRAMARBPROC                 glLinkProgramARB          = NULL;
PFNGLUSEPROGRAMOBJECTARBPROC            glUseProgramObjectARB     = NULL;
PFNGLVALIDATEPROGRAMARBPROC             glValidateProgramARB      = NULL;
PFNGLUNIFORM1FARBPROC                   glUniform1fARB            = NULL;
PFNGLUNIFORM2FARBPROC                   glUniform2fARB            = NULL;
PFNGLUNIFORM3FARBPROC                   glUniform3fARB            = NULL;
PFNGLUNIFORM4FARBPROC                   glUniform4fARB            = NULL;
PFNGLUNIFORM1IARBPROC                   glUniform1iARB            = NULL;
PFNGLUNIFORM2IARBPROC                   glUniform2iARB            = NULL;
PFNGLUNIFORM3IARBPROC                   glUniform3iARB            = NULL;
PFNGLUNIFORM4IARBPROC                   glUniform4iARB            = NULL;
PFNGLUNIFORM1FVARBPROC                  glUniform1fvARB           = NULL;
PFNGLUNIFORM2FVARBPROC                  glUniform2fvARB           = NULL;
PFNGLUNIFORM3FVARBPROC                  glUniform3fvARB           = NULL;
PFNGLUNIFORM4FVARBPROC                  glUniform4fvARB           = NULL;
PFNGLUNIFORM1IVARBPROC                  glUniform1ivARB           = NULL;
PFNGLUNIFORM2IVARBPROC                  glUniform2ivARB           = NULL;
PFNGLUNIFORM3IVARBPROC                  glUniform3ivARB           = NULL;
PFNGLUNIFORM4IVARBPROC                  glUniform4ivARB           = NULL;
PFNGLUNIFORMMATRIX2FVARBPROC            glUniformMatrix2fvARB     = NULL;
PFNGLUNIFORMMATRIX3FVARBPROC            glUniformMatrix3fvARB     = NULL;
PFNGLUNIFORMMATRIX4FVARBPROC            glUniformMatrix4fvARB     = NULL;
PFNGLGETOBJECTPARAMETERFVARBPROC        glGetObjectParameterfvARB = NULL;
PFNGLGETOBJECTPARAMETERIVARBPROC        glGetObjectParameterivARB = NULL;
PFNGLGETINFOLOGARBPROC                  glGetInfoLogARB           = NULL;
PFNGLGETATTACHEDOBJECTSARBPROC          glGetAttachedObjectsARB   = NULL;
PFNGLGETUNIFORMLOCATIONARBPROC          glGetUniformLocationARB   = NULL;
PFNGLGETACTIVEUNIFORMARBPROC            glGetActiveUniformARB     = NULL;
PFNGLGETUNIFORMFVARBPROC                glGetUniformfvARB         = NULL;
PFNGLGETUNIFORMIVARBPROC                glGetUniformivARB         = NULL;
PFNGLGETSHADERSOURCEARBPROC             glGetShaderSourceARB      = NULL;

                                    // GL_ARB_vertex_shader
PFNGLBINDATTRIBLOCATIONARBPROC          glBindAttribLocationARB   = NULL;
PFNGLGETACTIVEATTRIBARBPROC             glGetActiveAttribARB      = NULL;
PFNGLGETATTRIBLOCATIONARBPROC           glGetAttribLocationARB    = NULL;
PFNGLGETVERTEXATTRIBFVARBPROC           glGetVertexAttribfvARB    = NULL;

                                    // EXT_stencil_two_side
PFNGLACTIVESTENCILFACEEXTPROC           glActiveStencilFaceEXT    = NULL;

				    				// EXT_depth_bounds_test
PFNGLDEPTHBOUNDSEXTPROC			glDepthBoundsEXT                  = NULL;

									// EXT_framebuffer_object
PFNGLISRENDERBUFFEREXTPROC						glIsRenderbufferEXT                      = NULL;
PFNGLBINDRENDERBUFFEREXTPROC					glBindRenderbufferEXT                    = NULL;
PFNGLDELETERENDERBUFFERSEXTPROC					glDeleteRenderbuffersEXT                 = NULL;
PFNGLGENRENDERBUFFERSEXTPROC					glGenRenderbuffersEXT                    = NULL;
PFNGLRENDERBUFFERSTORAGEEXTPROC					glRenderbufferStorageEXT                 = NULL;
PFNGLGETRENDERBUFFERPARAMETERIVEXTPROC			glGetRenderbufferParameterivEXT          = NULL;
PFNGLISFRAMEBUFFEREXTPROC						glIsFramebufferEXT                       = NULL;
PFNGLBINDFRAMEBUFFEREXTPROC						glBindFramebufferEXT                     = NULL;
PFNGLDELETEFRAMEBUFFERSEXTPROC					glDeleteFramebuffersEXT                  = NULL;
PFNGLGENFRAMEBUFFERSEXTPROC						glGenFramebuffersEXT                     = NULL;
PFNGLCHECKFRAMEBUFFERSTATUSEXTPROC				glCheckFramebufferStatusEXT              = NULL;
PFNGLFRAMEBUFFERTEXTURE1DEXTPROC				glFramebufferTexture1DEXT                = NULL;
PFNGLFRAMEBUFFERTEXTURE2DEXTPROC				glFramebufferTexture2DEXT                = NULL;
PFNGLFRAMEBUFFERTEXTURE3DEXTPROC				glFramebufferTexture3DEXT                = NULL;
PFNGLFRAMEBUFFERRENDERBUFFEREXTPROC				glFramebufferRenderbufferEXT             = NULL;
PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVEXTPROC	glGetFramebufferAttachmentParameterivEXT = NULL;
PFNGLGENERATEMIPMAPEXTPROC						glGenerateMipmapEXT                      = NULL;

#ifndef	GL_VERSION_1_3										// ARB_transpose matrix
    PFNGLLOADTRANSPOSEMATRIXFPROC					glLoadTransposeMatrixfARB                = NULL;
    PFNGLLOADTRANSPOSEMATRIXDPROC					glLoadTransposeMatrixdARB                = NULL;
    PFNGLMULTTRANSPOSEMATRIXFPROC					glMultTransposeMatrixfARB                = NULL;
    PFNGLMULTTRANSPOSEMATRIXDPROC					glMultTransposeMatrixdARB                = NULL;
#endif
															// ARB_color_buffer_float
PFNGLCLAMPCOLORARBPROC							glClampColorARB        = NULL;

#if defined(_ISWINDOWS)
// fresh Linux already has 2.0
// stencel ops from OpenGL 2.0
    PFNGLSTENCILFUNCSEPARATEPROC					glStencilFuncSeparate  = NULL;
    PFNGLSTENCILOPSEPARATEPROC						glStencilOpSeparate    = NULL;
    PFNGLSTENCILMASKSEPARATEPROC					glStencilMaskSeparate  = NULL;

    // blend ops from OPenGL 2.0
    PFNGLBLENDEQUATIONPROC							glBlendEquation         = NULL;
    PFNGLBLENDEQUATIONSEPARATEPROC		 			glBlendEquationSeparate = NULL;
    PFNGLBLENDFUNCSEPARATEPROC						glBlendFuncSeparate     = NULL;
    PFNGLBLENDCOLORPROC								glBlendColor            = NULL;
#endif

// draw buffers from OpenGL 2.0
PFNGLDRAWBUFFERSPROC							glDrawBuffers           = NULL;

// ATI_draw_buffers
PFNGLDRAWBUFFERSATIPROC							glDrawBuffersATI        = NULL;

// EXT_texture_integer
PFNGLTEXPARAMETERIIVEXTPROC				glTexParameterIivEXT      = NULL;
PFNGLTEXPARAMETERIUIVEXTPROC			glTexParameterIuivEXT     = NULL;
PFNGLGETTEXPARAMETERIIVEXTPROC			glGetTexParameterIivEXT   = NULL;
PFNGLGETTEXPARAMETERIUIVEXTPROC			glGetTexParameterIuivEXT  = NULL;
PFNGLCLEARCOLORIIEXTPROC				glClearColorIiEXT         = NULL;
PFNGLCLEARCOLORIUIEXTPROC				glClearColorIuiEXT        = NULL;

// EXT_draw_instanced
PFNGLDRAWARRAYSINSTANCEDEXTPROC			glDrawArraysInstancedEXT  = NULL;
PFNGLDRAWELEMENTSINSTANCEDEXTPROC		glDrawElementsInstancedEXT  = NULL;


// EXT_texture_buffer_object
PFNGLTEXBUFFEREXTPROC 					glTexBufferEXT  = NULL;

// EXT_gpu_shader4
PFNGLGETUNIFORMUIVEXTPROC				glGetUniformuivEXT        = NULL;
PFNGLBINDFRAGDATALOCATIONEXTPROC		glBindFragDataLocationEXT = NULL;
PFNGLGETFRAGDATALOCATIONEXTPROC			glGetFragDataLocationEXT  = NULL;
PFNGLUNIFORM1UIEXTPROC					glUniform1uiEXT           = NULL;
PFNGLUNIFORM2UIEXTPROC					glUniform2uiEXT           = NULL;
PFNGLUNIFORM3UIEXTPROC					glUniform3uiEXT           = NULL;
PFNGLUNIFORM4UIEXTPROC					glUniform4uiEXT           = NULL;
PFNGLUNIFORM1UIVEXTPROC					glUniform1uivEXT          = NULL;
PFNGLUNIFORM2UIVEXTPROC					glUniform2uivEXT          = NULL;
PFNGLUNIFORM3UIVEXTPROC					glUniform3uivEXT          = NULL;
PFNGLUNIFORM4UIVEXTPROC					glUniform4uivEXT          = NULL;
PFNGLVERTEXATTRIBI1IEXTPROC				glVertexAttribI1iEXT      = NULL;
PFNGLVERTEXATTRIBI2IEXTPROC				glVertexAttribI2iEXT      = NULL;
PFNGLVERTEXATTRIBI3IEXTPROC				glVertexAttribI3iEXT      = NULL;
PFNGLVERTEXATTRIBI4IEXTPROC				glVertexAttribI4iEXT      = NULL;
PFNGLVERTEXATTRIBI1UIEXTPROC			glVertexAttribI1uiEXT     = NULL;
PFNGLVERTEXATTRIBI2UIEXTPROC			glVertexAttribI2uiEXT     = NULL;
PFNGLVERTEXATTRIBI3UIEXTPROC			glVertexAttribI3uiEXT     = NULL;
PFNGLVERTEXATTRIBI4UIEXTPROC			glVertexAttribI4uiEXT     = NULL;
PFNGLVERTEXATTRIBI1IVEXTPROC			glVertexAttribI1ivEXT     = NULL;
PFNGLVERTEXATTRIBI2IVEXTPROC			glVertexAttribI2ivEXT     = NULL;
PFNGLVERTEXATTRIBI3IVEXTPROC			glVertexAttribI3ivEXT     = NULL;
PFNGLVERTEXATTRIBI4IVEXTPROC			glVertexAttribI4ivEXT     = NULL;
PFNGLVERTEXATTRIBI1UIVEXTPROC			glVertexAttribI1uivEXT    = NULL;
PFNGLVERTEXATTRIBI2UIVEXTPROC			glVertexAttribI2uivEXT    = NULL;
PFNGLVERTEXATTRIBI3UIVEXTPROC			glVertexAttribI3uivEXT    = NULL;
PFNGLVERTEXATTRIBI4UIVEXTPROC			glVertexAttribI4uivEXT    = NULL;
PFNGLVERTEXATTRIBI4BVEXTPROC			glVertexAttribI4bvEXT     = NULL;
PFNGLVERTEXATTRIBI4SVEXTPROC			glVertexAttribI4svEXT     = NULL;
PFNGLVERTEXATTRIBI4UBVEXTPROC			glVertexAttribI4ubvEXT    = NULL;
PFNGLVERTEXATTRIBI4USVEXTPROC			glVertexAttribI4usvEXT    = NULL;
PFNGLVERTEXATTRIBIPOINTEREXTPROC		glVertexAttribIPointerEXT = NULL;
PFNGLGETVERTEXATTRIBIIVEXTPROC			glGetVertexAttribIivEXT   = NULL;
PFNGLGETVERTEXATTRIBIUIVEXTPROC			glGetVertexAttribIuivEXT  = NULL;

// EXT_geometry_shader4
PFNGLPROGRAMPARAMETERIEXTPROC			glProgramParameteriEXT       = NULL;
PFNGLFRAMEBUFFERTEXTUREEXTPROC			glFramebufferTextureEXT      = NULL;
PFNGLFRAMEBUFFERTEXTURELAYEREXTPROC		glFramebufferTextureLayerEXT = NULL;
PFNGLFRAMEBUFFERTEXTUREFACEEXTPROC		glFramebufferTextureFaceEXT  = NULL;
#endif
