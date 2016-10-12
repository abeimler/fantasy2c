/**
*@mainpage Fantasy2C
*@brief @image html logo.jpg
* Fantasy2C is an object oriented multimedia library, supported with OpenGL, \n
* uses hardware acceleration. \n
* With additional libraries like DevIL,GLFW or Audiere. \n
* Quickly and easily load Images, create window or play sound and music. \n
* Fantasy2C is what you need for a 2D-Game \n
*\n
*Features: \n
*-Play sounds und music \n
*-Load images from memory or file \n
*-Load TTF files and create bitmapfont \n
*-Draw simple sprite with image \n
*-Draw scrolling background \n
*-Draw array of sprites (e.g. tilemap) \n
*-Draw texts with bitmapfonts \n
*-Window and input managment \n
*-GLSL Shader Managment (Load Files) \n
*\n
*GNU Lesser General Public License. \n
*\n
*Use Librarys: \n
*OpenGL \n
*DevIL \n
*GLFW \n
*Audiere \n
*FreeType2 \n
*\n
*Settings Linker (Windows): \n
*libFantasy2C.a \n
*\n
*Settings Linker (Linux): \n
*Fantasy2C \n
*\n
*Compiling Fantasy2C sourcecode, Settings Include Directory (Linux): \n
* /usr/include/freetype2 \n
*\n
*Compiling Fantasy2C sourcecode, Settings Linker (Windows): \n
*opengl32 \n
*glu32 \n
*DevIL \n
*IL \n
*ILU \n
*glfw \n
*glfwdll \n
*audiere \n
*freetype.dll \n
*freetype \n
*\n
*Compiling Fantasy2C sourcecode,Settings Linker (Linux): \n
*GL \n
*GLU \n
*X11 \n
*pthread \n
*Xxf86vm \n
*Xrandr \n
*m \n
*IL \n
*ILU \n
*glfw \n
*audiere \n
*freetype \n
*\n
*@version 1.2.5
*@date 21.11.2010
*@author Alex Beimler (alias kiba) \n
*http://fantasy2c.bplaced.net/ \n
*\n
*Copyright (C) 2008-2010  Alex Beimler \n
*\n
*This library is free software  \n
*you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License \n
*as published by the Free Software Foundation; either version 2.1 of the License, or (at your option) any later version. \n
*This library is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; \n
*without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. \n
*See the GNU Lesser General Public License for more details. \n
*\n
*You should have received a copy of the GNU Lesser General Public License along with this library; \n
*if not, write to the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110, USA \n
*/

#ifndef __F2C_BASIC_HPP_INCLUDED
#define __F2C_BASIC_HPP_INCLUDED

#ifndef __cplusplus
#error A C++ compiler is required!
#endif

#if defined(_MSC_VER) && _MSC_VER >= 1020
#pragma once
#endif

#if defined(_WIN32) || defined(_Windows) || defined(__WIN32__) || defined(_WIN64) || defined(__WIN64__)
    #define _ISWINDOWS
#endif

#if defined(__X11__) || defined(__linux) || defined(linux) || defined(__unix__)
    #define _ISLINUX
#endif

// Generic helper definitions for shared library support
#if defined(_ISWINDOWS)
//    #if defined(__GNUC__)
//        #define HELPER_DLL_IMPORT __attribute__(dllimport)
//        #define HELPER_DLL_EXPORT __attribute__(dllexport)
//        #define HELPER_DLL_LOCAL
//    #else
        #define HELPER_DLL_IMPORT __declspec(dllimport)
        #define HELPER_DLL_EXPORT __declspec(dllexport)
        #define HELPER_DLL_LOCAL
//    #endif
#else
  #if __GNUC__ >= 4
    #define HELPER_DLL_IMPORT __attribute__ ((visibility("default")))
    #define HELPER_DLL_EXPORT __attribute__ ((visibility("default")))
    #define HELPER_DLL_LOCAL __attribute__ ((visibility("hidden")))
  #else
    #define HELPER_DLL_IMPORT
    #define HELPER_DLL_EXPORT
    #define HELPER_DLL_LOCAL
  #endif
#endif

// Now we use the generic helper definitions above to define DLL
// DLL is used for the public API symbols. It either DLL imports or DLL exports (or does nothing for static build)

#if !defined(NO_DLL)// defined if is compiled as a DLL
  #if defined(FANTASY2C_EXPORTS) || defined(_WINDLL) // defined if we are building the DLL (instead of using it)
    #define DLL HELPER_DLL_EXPORT
  #else
    #define DLL HELPER_DLL_IMPORT //Used DLL, import DLL
  #endif
  #define DLL_LOCAL HELPER_DLL_LOCAL
#else // DLL is not defined: is a static lib.
  #define DLL
  #define DLL_LOCAL
#endif

#if defined(_MSC_VER) && _MSC_VER >= 1020
	#pragma comment(lib,"opengl32.lib")
	#pragma comment(lib,"glu32.lib")
	#pragma comment(lib,"DevIL.lib")
	#pragma comment(lib,"ILU.lib")
	#pragma comment(lib,"libglfw.a")
	#if defined(_WIN32) || defined(_Windows) || defined(__WIN32__) || defined(_WIN64) || defined(__WIN64__)
		#pragma comment(lib,"libglfwdll.a")
		#pragma comment(lib,"libfreetype.dll.a")
	#endif
	#pragma comment(lib,"audiere.lib")
#endif

//----- Includes -----//

#include <cmath>
#include <cstdio>
#include <cstddef>
#include <cstdlib>
#include <cstdarg>
#include <cstring>
#include <ctime>

#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <locale>
#include <sstream>
#include <limits>

#if defined(_ISWINDOWS)
	#define WIN32_LEAN_AND_MEAN
	#undef NOMINMAX
    #define NOMINMAX
	#include <windows.h>
#endif

#if defined(__APPLE__) && defined(__MACH__)
    //include OpenGL Header
    #include <OpenGL/gl.h>
    #include <OpenGL/glu.h>
#else
    //include OpenGL Header
    #include <GL/gl.h>
    #include <GL/glu.h>
#endif


//#if defined(_ISWINDOWS)
//    class DLL std::_String_base;
//    class DLL std::_Container_base_secure;
//    class DLL std::ios_base;
//#endif

//#if defined(_ISWINDOWS)
//    template class DLL std::allocator<char>;
//    template class DLL std::char_traits<char>;
//    template class DLL std::basic_string<char, std::char_traits<char>, std::allocator<char> >;
//
//    template class DLL std::basic_ios<char, std::char_traits<char> >;
//    template class DLL std::basic_ostream<char, std::char_traits<char> >;
//    template class DLL std::basic_iostream<char, std::char_traits<char> >;
//    template class DLL std::basic_stringstream<char, std::char_traits<char>, std::allocator<char> >;
//    template class DLL std::basic_ostringstream<char, std::char_traits<char>, std::allocator<char> >;
//#endif

template class DLL std::allocator<int>;
template class DLL std::allocator< std::basic_string<char, std::char_traits<char>, std::allocator<char> > >;
template class DLL std::vector< std::basic_string<char, std::char_traits<char>, std::allocator<char> >, std::allocator<std::basic_string<char> > >;

//inlude OpenIL(DevIL) Header
#include <IL/il.h>
#include <IL/ilu.h>

//inlude Audiere Header
#include <audiere.h>

//inlude Freetype2 Header
#include <ft2build.h>
#include <freetype/freetype.h>
#include <freetype/ftglyph.h>
#include <freetype/ftoutln.h>
#include <freetype/fttrigon.h>

#if defined(macintosh) || (defined(__APPLE__) && defined(__MACH__))
	#include FT_MAC_H
#endif
#include FT_FREETYPE_H
#include FT_OUTLINE_H
#include FT_TRUETYPE_IDS_H

//inlude GLFW Header
#if defined(_ISWINDOWS)
    #define GLFW_DLL
#endif
#include <GL/glfw.h>

#if defined(_ISWINDOWS)
    #include "glext.h"
    #include "wglext.h"
    //#define uglShaderGL::getProcAddress(x) wglShaderGL::getProcAddress(x)

    //#define uglShaderGL::getProcAddress(x) glfwShaderGL::getProcAddress(x)
    //#define uglExtensionSupported(x) (glfwExtensionSupported(x) == GL_TRUE)

    #define WIN32_OR_X11
#elif defined(_ISLINUX)
    #include "glext.h"
    #include <GL/glx.h>
    #include <GL/glxext.h>

    #define glXGetProcAddress(x) (*glXGetProcAddressARB)((const GLubyte*)x)

    //#define uglgetProcAddress(x) (*glXGetProcAddressARB)((const GLubyte*)(x))

    //#define uglgetProcAddress(x) glfwgetProcAddress(x)
    //#define uglExtensionSupported(x) (glfwExtensionSupported(x) == GL_TRUE)

    #define WIN32_OR_X11
    #undef None
    #undef Button1
    #undef Button2
    #undef Button3
    #undef Button4
    #undef Button5
    #undef Button6
    #undef Button7
    #undef Button8
    #undef Button9
#endif

#ifdef WIN32_OR_X11
    // fog coord function
    extern DLL PFNGLFOGCOORDFEXTPROC            glFogCoordf;

    // secondary color functions
    extern DLL PFNGLSECONDARYCOLOR3FPROC        glSecondaryColor3f;
    extern DLL PFNGLSECONDARYCOLOR3FVPROC       glSecondaryColor3fv;
    extern DLL PFNGLSECONDARYCOLORPOINTERPROC   glSecondaryColorPointer;


    // register combiners functions
    extern DLL PFNGLCOMBINERPARAMETERFVNVPROC   glCombinerParameterfvNV;
    extern DLL PFNGLCOMBINERPARAMETERIVNVPROC   glCombinerParameterivNV;
    extern DLL PFNGLCOMBINERPARAMETERFNVPROC    glCombinerParameterfNV;
    extern DLL PFNGLCOMBINERPARAMETERINVPROC    glCombinerParameteriNV;
    extern DLL PFNGLCOMBINERINPUTNVPROC         glCombinerInputNV;
    extern DLL PFNGLCOMBINEROUTPUTNVPROC        glCombinerOutputNV;
    extern DLL PFNGLFINALCOMBINERINPUTNVPROC    glFinalCombinerInputNV;

    // VBO functions
    extern DLL PFNGLBINDBUFFERARBPROC           glBindBufferARB;
    extern DLL PFNGLDELETEBUFFERSARBPROC        glDeleteBuffersARB;
    extern DLL PFNGLGENBUFFERSARBPROC           glGenBuffersARB;
    extern DLL PFNGLISBUFFERARBPROC             glIsBufferARB;
    extern DLL PFNGLBUFFERDATAARBPROC           glBufferDataARB;
    extern DLL PFNGLBUFFERSUBDATAARBPROC        glBufferSubDataARB;
    extern DLL PFNGLGETBUFFERSUBDATAARBPROC     glGetBufferSubDataARB;
    extern DLL PFNGLMAPBUFFERARBPROC            glMapBufferARB;
    extern DLL PFNGLUNMAPBUFFERARBPROC          glUnmapBufferARB;
    extern DLL PFNGLGETBUFFERPARAMETERIVARBPROC glGetBufferParameterivARB;
    extern DLL PFNGLGETBUFFERPOINTERVARBPROC    glGetBufferPointervARB;


    #if defined(_ISWINDOWS)
        extern DLL PFNWGLGETEXTENSIONSSTRINGARBPROC        wglGetExtensionsStringARB;

        // p-buffer functions
        extern DLL PFNWGLCREATEPBUFFERARBPROC              wglCreatePbufferARB;
        extern DLL PFNWGLGETPBUFFERDCARBPROC               wglGetPbufferDCARB;
        extern DLL PFNWGLRELEASEPBUFFERDCARBPROC           wglReleasePbufferDCARB;
        extern DLL PFNWGLDESTROYPBUFFERARBPROC             wglDestroyPbufferARB;
        extern DLL PFNWGLQUERYPBUFFERARBPROC               wglQueryPbufferARB;

        // WGL_ARB_pixel_format
        extern DLL PFNWGLCHOOSEPIXELFORMATARBPROC          wglChoosePixelFormatARB;

        // WGL_ARB_render_texture
        extern DLL PFNWGLBINDTEXIMAGEARBPROC               wglBindTexImageARB;
        extern DLL PFNWGLRELEASETEXIMAGEARBPROC            wglReleaseTexImageARB;
        extern DLL PFNWGLSETPBUFFERATTRIBARBPROC           wglSetPbufferAttribARB;

        // WGL_EXT_swap_control
        extern DLL PFNWGLSWAPINTERVALEXTPROC               wglSwapIntervalEXT;
        extern DLL PFNWGLGETSWAPINTERVALEXTPROC            wglGetSwapIntervalEXT;
    #else
        // GLX_SGIX_pbuffer
        extern DLL PFNGLXCREATEGLXPBUFFERSGIXPROC          glXCreateGLXPbufferSGIX;
        extern DLL PFNGLXDESTROYGLXPBUFFERSGIXPROC         glXDestroyGLXPbufferSGIX;
        extern DLL PFNGLXQUERYGLXPBUFFERSGIXPROC           glXQueryGLXPbufferSGIX;

        // GLX_SGIX_fbconfig
        extern DLL PFNGLXCHOOSEFBCONFIGSGIXPROC            glXChooseFBConfigSGIX;
        extern DLL PFNGLXCREATECONTEXTWITHCONFIGSGIXPROC   glXCreateContextWithConfigSGIX;
    #endif

    // NV-occlusion query extension
    extern DLL PFNGLGENOCCLUSIONQUERIESNVPROC          glGenOcclusionQueriesNV;
    extern DLL PFNGLBEGINOCCLUSIONQUERYNVPROC          glBeginOcclusionQueryNV;
    extern DLL PFNGLENDOCCLUSIONQUERYNVPROC            glEndOcclusionQueryNV;
    extern DLL PFNGLGETOCCLUSIONQUERYIVNVPROC          glGetOcclusionQueryivNV;

    // ARB_vertex_program extension
    extern DLL PFNGLGENPROGRAMSARBPROC                 glGenProgramsARB;
    extern DLL PFNGLDELETEPROGRAMSARBPROC              glDeleteProgramsARB;
    extern DLL PFNGLBINDPROGRAMARBPROC                 glBindProgramARB;
    extern DLL PFNGLISPROGRAMARBPROC                   glIsProgramARB;

    extern DLL PFNGLPROGRAMSTRINGARBPROC               glProgramStringARB;
    extern DLL PFNGLGETPROGRAMIVARBPROC                glGetProgramivARB;

    extern DLL PFNGLVERTEXATTRIB4FARBPROC              glVertexAttrib4fARB;
    extern DLL PFNGLVERTEXATTRIB4FVARBPROC             glVertexAttrib4fvARB;
    extern DLL PFNGLVERTEXATTRIB3FARBPROC              glVertexAttrib3fARB;
    extern DLL PFNGLVERTEXATTRIB3FVARBPROC             glVertexAttrib3fvARB;

    extern DLL PFNGLVERTEXATTRIBPOINTERARBPROC         glVertexAttribPointerARB;
    extern DLL PFNGLENABLEVERTEXATTRIBARRAYARBPROC     glEnableVertexAttribArrayARB;
    extern DLL PFNGLDISABLEVERTEXATTRIBARRAYARBPROC    glDisableVertexAttribArrayARB;

    extern DLL PFNGLPROGRAMLOCALPARAMETER4FARBPROC     glProgramLocalParameter4fARB;
    extern DLL PFNGLPROGRAMLOCALPARAMETER4FVARBPROC    glProgramLocalParameter4fvARB;

    extern DLL PFNGLGETPROGRAMLOCALPARAMETERFVARBPROC  glGetProgramLocalParameterfvARB;

    extern DLL PFNGLPROGRAMENVPARAMETER4FARBPROC       glProgramEnvParameter4fARB;
    extern DLL PFNGLPROGRAMENVPARAMETER4FVARBPROC      glProgramEnvParameter4fvARB;

    extern DLL PFNGLGETPROGRAMENVPARAMETERFVARBPROC    glGetProgramEnvParameterfvARB;

    // GL_EXT_texture3D
    extern DLL PFNGLTEXIMAGE3DEXTPROC                  glTexImage3DEXT;

    // ARB_texture_compression
    extern DLL PFNGLCOMPRESSEDTEXIMAGE3DARBPROC        glCompressedTexImage3DARB;
    extern DLL PFNGLCOMPRESSEDTEXIMAGE2DARBPROC        glCompressedTexImage2DARB;
    extern DLL PFNGLCOMPRESSEDTEXIMAGE1DARBPROC        glCompressedTexImage1DARB;
    extern DLL PFNGLCOMPRESSEDTEXSUBIMAGE3DARBPROC     glCompressedTexSubImage3DARB;
    extern DLL PFNGLCOMPRESSEDTEXSUBIMAGE2DARBPROC     glCompressedTexSubImage2DARB;
    extern DLL PFNGLCOMPRESSEDTEXSUBIMAGE1DARBPROC     glCompressedTexSubImage1DARB;
    extern DLL PFNGLGETCOMPRESSEDTEXIMAGEARBPROC       glGetCompressedTexImageARB;

    // ARB_point_parameters
    extern DLL PFNGLPOINTPARAMETERFARBPROC             glPointParameterfARB;
    extern DLL PFNGLPOINTPARAMETERFVARBPROC            glPointParameterfvARB;

    // ARB_occlusion_query
    extern DLL PFNGLGENQUERIESARBPROC                  glGenQueriesARB;
    extern DLL PFNGLDELETEQUERIESARBPROC               glDeleteQueriesARB;
    extern DLL PFNGLISQUERYARBPROC                     glIsQueryARB;
    extern DLL PFNGLBEGINQUERYARBPROC                  glBeginQueryARB;
    extern DLL PFNGLENDQUERYARBPROC                    glEndQueryARB;
    extern DLL PFNGLGETQUERYIVARBPROC                  glGetQueryivARB;
    extern DLL PFNGLGETQUERYOBJECTIVARBPROC            glGetQueryObjectivARB;
    extern DLL PFNGLGETQUERYOBJECTUIVARBPROC           glGetQueryObjectuivARB;

    // GLSL-specific extensions
    // GL_ARB_shader_object
    extern DLL PFNGLDELETEOBJECTARBPROC                glDeleteObjectARB;
    extern DLL PFNGLGETHANDLEARBPROC                   glGetHandleARB;
    extern DLL PFNGLDETACHOBJECTARBPROC                glDetachObjectARB;
    extern DLL PFNGLCREATESHADEROBJECTARBPROC          glCreateShaderObjectARB;
    extern DLL PFNGLSHADERSOURCEARBPROC                glShaderSourceARB;
    extern DLL PFNGLCOMPILESHADERARBPROC               glCompileShaderARB;
    extern DLL PFNGLCREATEPROGRAMOBJECTARBPROC         glCreateProgramObjectARB;
    extern DLL PFNGLATTACHOBJECTARBPROC                glAttachObjectARB;
    extern DLL PFNGLLINKPROGRAMARBPROC                 glLinkProgramARB;
    extern DLL PFNGLUSEPROGRAMOBJECTARBPROC            glUseProgramObjectARB;
    extern DLL PFNGLVALIDATEPROGRAMARBPROC             glValidateProgramARB;
    extern DLL PFNGLUNIFORM1FARBPROC                   glUniform1fARB;
    extern DLL PFNGLUNIFORM2FARBPROC                   glUniform2fARB;
    extern DLL PFNGLUNIFORM3FARBPROC                   glUniform3fARB;
    extern DLL PFNGLUNIFORM4FARBPROC                   glUniform4fARB;
    extern DLL PFNGLUNIFORM1IARBPROC                   glUniform1iARB;
    extern DLL PFNGLUNIFORM2IARBPROC                   glUniform2iARB;
    extern DLL PFNGLUNIFORM3IARBPROC                   glUniform3iARB;
    extern DLL PFNGLUNIFORM4IARBPROC                   glUniform4iARB;
    extern DLL PFNGLUNIFORM1FVARBPROC                  glUniform1fvARB;
    extern DLL PFNGLUNIFORM2FVARBPROC                  glUniform2fvARB;
    extern DLL PFNGLUNIFORM3FVARBPROC                  glUniform3fvARB;
    extern DLL PFNGLUNIFORM4FVARBPROC                  glUniform4fvARB;
    extern DLL PFNGLUNIFORM1IVARBPROC                  glUniform1ivARB;
    extern DLL PFNGLUNIFORM2IVARBPROC                  glUniform2ivARB;
    extern DLL PFNGLUNIFORM3IVARBPROC                  glUniform3ivARB;
    extern DLL PFNGLUNIFORM4IVARBPROC                  glUniform4ivARB;
    extern DLL PFNGLUNIFORMMATRIX2FVARBPROC            glUniformMatrix2fvARB;
    extern DLL PFNGLUNIFORMMATRIX3FVARBPROC            glUniformMatrix3fvARB;
    extern DLL PFNGLUNIFORMMATRIX4FVARBPROC            glUniformMatrix4fvARB;
    extern DLL PFNGLGETOBJECTPARAMETERFVARBPROC        glGetObjectParameterfvARB;
    extern DLL PFNGLGETOBJECTPARAMETERIVARBPROC        glGetObjectParameterivARB;
    extern DLL PFNGLGETINFOLOGARBPROC                  glGetInfoLogARB;
    extern DLL PFNGLGETATTACHEDOBJECTSARBPROC          glGetAttachedObjectsARB;
    extern DLL PFNGLGETUNIFORMLOCATIONARBPROC          glGetUniformLocationARB;
    extern DLL PFNGLGETACTIVEUNIFORMARBPROC            glGetActiveUniformARB;
    extern DLL PFNGLGETUNIFORMFVARBPROC                glGetUniformfvARB;
    extern DLL PFNGLGETUNIFORMIVARBPROC                glGetUniformivARB;
    extern DLL PFNGLGETSHADERSOURCEARBPROC             glGetShaderSourceARB;

    // GL_ARB_vertex_shader
    extern DLL PFNGLBINDATTRIBLOCATIONARBPROC          glBindAttribLocationARB;
    extern DLL PFNGLGETACTIVEATTRIBARBPROC             glGetActiveAttribARB;
    extern DLL PFNGLGETATTRIBLOCATIONARBPROC           glGetAttribLocationARB;
    extern DLL PFNGLGETVERTEXATTRIBFVARBPROC           glGetVertexAttribfvARB;

    // EXT_stencil_two_side
    extern DLL PFNGLACTIVESTENCILFACEEXTPROC           glActiveStencilFaceEXT;

    // EXT_depth_bounds_test
    extern DLL PFNGLDEPTHBOUNDSEXTPROC			glDepthBoundsEXT;

    // EXT_framebuffer_object
    extern DLL PFNGLISRENDERBUFFEREXTPROC						glIsRenderbufferEXT;
    extern DLL PFNGLBINDRENDERBUFFEREXTPROC					glBindRenderbufferEXT;
    extern DLL PFNGLDELETERENDERBUFFERSEXTPROC					glDeleteRenderbuffersEXT;
    extern DLL PFNGLGENRENDERBUFFERSEXTPROC					glGenRenderbuffersEXT;
    extern DLL PFNGLRENDERBUFFERSTORAGEEXTPROC					glRenderbufferStorageEXT;
    extern DLL PFNGLGETRENDERBUFFERPARAMETERIVEXTPROC			glGetRenderbufferParameterivEXT;
    extern DLL PFNGLISFRAMEBUFFEREXTPROC						glIsFramebufferEXT;
    extern DLL PFNGLBINDFRAMEBUFFEREXTPROC						glBindFramebufferEXT;
    extern DLL PFNGLDELETEFRAMEBUFFERSEXTPROC					glDeleteFramebuffersEXT;
    extern DLL PFNGLGENFRAMEBUFFERSEXTPROC						glGenFramebuffersEXT;
    extern DLL PFNGLCHECKFRAMEBUFFERSTATUSEXTPROC				glCheckFramebufferStatusEXT;
    extern DLL PFNGLFRAMEBUFFERTEXTURE1DEXTPROC				glFramebufferTexture1DEXT;
    extern DLL PFNGLFRAMEBUFFERTEXTURE2DEXTPROC				glFramebufferTexture2DEXT;
    extern DLL PFNGLFRAMEBUFFERTEXTURE3DEXTPROC				glFramebufferTexture3DEXT;
    extern DLL PFNGLFRAMEBUFFERRENDERBUFFEREXTPROC				glFramebufferRenderbufferEXT;
    extern DLL PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVEXTPROC	glGetFramebufferAttachmentParameterivEXT;
    extern DLL PFNGLGENERATEMIPMAPEXTPROC						glGenerateMipmapEXT;

    // ARB_transpose matrix
    #ifndef	GL_VERSION_1_3
        extern DLL PFNGLLOADTRANSPOSEMATRIXFPROC					glLoadTransposeMatrixfARB;
        extern DLL PFNGLLOADTRANSPOSEMATRIXDPROC					glLoadTransposeMatrixdARB;
        extern DLL PFNGLMULTTRANSPOSEMATRIXFPROC					glMultTransposeMatrixfARB;
        extern DLL PFNGLMULTTRANSPOSEMATRIXDPROC					glMultTransposeMatrixdARB;
    #endif
                                                                // ARB_color_buffer_float
    extern DLL PFNGLCLAMPCOLORARBPROC							glClampColorARB;

    // fresh Linux already has 2.0
    #if defined(_ISWINDOWS)
        // stencel ops from OpenGL 2.0
        extern DLL PFNGLSTENCILFUNCSEPARATEPROC					glStencilFuncSeparate;
        extern DLL PFNGLSTENCILOPSEPARATEPROC						glStencilOpSeparate;
        extern DLL PFNGLSTENCILMASKSEPARATEPROC					glStencilMaskSeparate;

        // blend ops from OPenGL 2.0
        extern DLL PFNGLBLENDEQUATIONPROC							glBlendEquation;
        extern DLL PFNGLBLENDEQUATIONSEPARATEPROC		 			glBlendEquationSeparate;
        extern DLL PFNGLBLENDFUNCSEPARATEPROC						glBlendFuncSeparate;
        extern DLL PFNGLBLENDCOLORPROC								glBlendColor;
    #endif

    // draw buffers from OpenGL 2.0
    extern DLL PFNGLDRAWBUFFERSPROC							glDrawBuffers;

    // ATI_draw_buffers
    extern DLL PFNGLDRAWBUFFERSATIPROC							glDrawBuffersATI;

    // EXT_texture_integer
    extern DLL PFNGLTEXPARAMETERIIVEXTPROC				glTexParameterIivEXT;
    extern DLL PFNGLTEXPARAMETERIUIVEXTPROC			glTexParameterIuivEXT;
    extern DLL PFNGLGETTEXPARAMETERIIVEXTPROC			glGetTexParameterIivEXT;
    extern DLL PFNGLGETTEXPARAMETERIUIVEXTPROC			glGetTexParameterIuivEXT;
    extern DLL PFNGLCLEARCOLORIIEXTPROC				glClearColorIiEXT;
    extern DLL PFNGLCLEARCOLORIUIEXTPROC				glClearColorIuiEXT;

    // EXT_draw_instanced
    extern DLL PFNGLDRAWARRAYSINSTANCEDEXTPROC			glDrawArraysInstancedEXT;
    extern DLL PFNGLDRAWELEMENTSINSTANCEDEXTPROC		glDrawElementsInstancedEXT;

    // EXT_texture_buffer_object
    extern DLL PFNGLTEXBUFFEREXTPROC 					glTexBufferEXT;

    // EXT_gpu_shader4
    extern DLL PFNGLGETUNIFORMUIVEXTPROC				glGetUniformuivEXT;
    extern DLL PFNGLBINDFRAGDATALOCATIONEXTPROC		glBindFragDataLocationEXT;
    extern DLL PFNGLGETFRAGDATALOCATIONEXTPROC			glGetFragDataLocationEXT;
    extern DLL PFNGLUNIFORM1UIEXTPROC					glUniform1uiEXT;
    extern DLL PFNGLUNIFORM2UIEXTPROC					glUniform2uiEXT;
    extern DLL PFNGLUNIFORM3UIEXTPROC					glUniform3uiEXT;
    extern DLL PFNGLUNIFORM4UIEXTPROC					glUniform4uiEXT;
    extern DLL PFNGLUNIFORM1UIVEXTPROC					glUniform1uivEXT;
    extern DLL PFNGLUNIFORM2UIVEXTPROC					glUniform2uivEXT;
    extern DLL PFNGLUNIFORM3UIVEXTPROC					glUniform3uivEXT;
    extern DLL PFNGLUNIFORM4UIVEXTPROC					glUniform4uivEXT;
    extern DLL PFNGLVERTEXATTRIBI1IEXTPROC				glVertexAttribI1iEXT;
    extern DLL PFNGLVERTEXATTRIBI2IEXTPROC				glVertexAttribI2iEXT;
    extern DLL PFNGLVERTEXATTRIBI3IEXTPROC				glVertexAttribI3iEXT;
    extern DLL PFNGLVERTEXATTRIBI4IEXTPROC				glVertexAttribI4iEXT;
    extern DLL PFNGLVERTEXATTRIBI1UIEXTPROC			glVertexAttribI1uiEXT;
    extern DLL PFNGLVERTEXATTRIBI2UIEXTPROC			glVertexAttribI2uiEXT;
    extern DLL PFNGLVERTEXATTRIBI3UIEXTPROC			glVertexAttribI3uiEXT;
    extern DLL PFNGLVERTEXATTRIBI4UIEXTPROC			glVertexAttribI4uiEXT;
    extern DLL PFNGLVERTEXATTRIBI1IVEXTPROC			glVertexAttribI1ivEXT;
    extern DLL PFNGLVERTEXATTRIBI2IVEXTPROC			glVertexAttribI2ivEXT;
    extern DLL PFNGLVERTEXATTRIBI3IVEXTPROC			glVertexAttribI3ivEXT;
    extern DLL PFNGLVERTEXATTRIBI4IVEXTPROC			glVertexAttribI4ivEXT;
    extern DLL PFNGLVERTEXATTRIBI1UIVEXTPROC			glVertexAttribI1uivEXT;
    extern DLL PFNGLVERTEXATTRIBI2UIVEXTPROC			glVertexAttribI2uivEXT;
    extern DLL PFNGLVERTEXATTRIBI3UIVEXTPROC			glVertexAttribI3uivEXT;
    extern DLL PFNGLVERTEXATTRIBI4UIVEXTPROC			glVertexAttribI4uivEXT;
    extern DLL PFNGLVERTEXATTRIBI4BVEXTPROC			glVertexAttribI4bvEXT;
    extern DLL PFNGLVERTEXATTRIBI4SVEXTPROC			glVertexAttribI4svEXT;
    extern DLL PFNGLVERTEXATTRIBI4UBVEXTPROC			glVertexAttribI4ubvEXT;
    extern DLL PFNGLVERTEXATTRIBI4USVEXTPROC			glVertexAttribI4usvEXT;
    extern DLL PFNGLVERTEXATTRIBIPOINTEREXTPROC		glVertexAttribIPointerEXT;
    extern DLL PFNGLGETVERTEXATTRIBIIVEXTPROC			glGetVertexAttribIivEXT;
    extern DLL PFNGLGETVERTEXATTRIBIUIVEXTPROC			glGetVertexAttribIuivEXT;

    // EXT_geometry_shader4
    extern DLL PFNGLPROGRAMPARAMETERIEXTPROC			glProgramParameteriEXT;
    extern DLL PFNGLFRAMEBUFFERTEXTUREEXTPROC			glFramebufferTextureEXT;
    extern DLL PFNGLFRAMEBUFFERTEXTURELAYEREXTPROC		glFramebufferTextureLayerEXT;
    extern DLL PFNGLFRAMEBUFFERTEXTUREFACEEXTPROC		glFramebufferTextureFaceEXT;


    #if defined(_ISWINDOWS)
        extern DLL PFNGLACTIVETEXTUREARBPROC        glActiveTextureARB;
        extern DLL PFNGLCLIENTACTIVETEXTUREARBPROC  glClientActiveTextureARB;
        extern DLL PFNGLMULTITEXCOORD1FARBPROC      glMultiTexCoord1f;
        extern DLL PFNGLMULTITEXCOORD1FVARBPROC     glMultiTexCoord1fv;
        extern DLL PFNGLMULTITEXCOORD2FARBPROC      glMultiTexCoord2f;
        extern DLL PFNGLMULTITEXCOORD2FVARBPROC     glMultiTexCoord2fv;
        extern DLL PFNGLMULTITEXCOORD3FARBPROC      glMultiTexCoord3f;
        extern DLL PFNGLMULTITEXCOORD3FVARBPROC     glMultiTexCoord3fv;
        extern DLL PFNGLMULTITEXCOORD4FARBPROC      glMultiTexCoord4f;
        extern DLL PFNGLMULTITEXCOORD4FVARBPROC     glMultiTexCoord4fv;
    #endif
#endif

/* Define NULL pointer value */
#undef NULL
#ifdef __cplusplus
    #define NULL 0
#else
    #define NULL ((void *)0)
#endif

/**
*@namespace F2C
*@brief Fantasy2C Namespace
*/
namespace F2C{

typedef signed char int8; ///< Interger 8 Bit
typedef unsigned char uint8; ///< Unsigned Interger 8 Bit
typedef unsigned char ubyte; ///< Unsigned Interger 8 Bit

typedef short int int16; ///< Interger 16 Bit
typedef unsigned short int uint16; ///< Unsigned Interger 16 Bit

typedef unsigned int uint; ///< Unsigned Interger

typedef long int int32; ///< Interger 32 Bit
typedef unsigned long int uint32; ///< Unsigned Interger 32 Bit

typedef long long int int64; ///< Interger 64 Bit
typedef unsigned long long int uint64; ///< Unsigned Interger 64 Bit


/**
*@param value Reference of Value
*@param min Minimum value
*@param max Maximum Value
*@brief Pushes value in the range of min and max.
*/
template <typename T>
inline void clamp(T& value,T min,T max){
    if( value > max )
    { value = max;}
    else if( value < min )
    { value = min;}
}

/**
*@param value Value
*@param min Minimum value
*@param max Maximum Value
*@brief Pushes value in the range of min and max.
*/
template <typename T>
inline T vclamp(T value,T min,T max){
    if( value > max )
    { value = max;}
    else if( value < min )
    { value = min;}

    return value;
}

/**
*@param v Value
*@return Power of 2
*@brief Round to the next highest power of 2.
*/
template <typename T>
inline T nextPowerof2(T v){
    int tmpv = static_cast<int>(v);
    tmpv--;
    tmpv |= tmpv >> 1;
    tmpv |= tmpv >> 2;
    tmpv |= tmpv >> 4;
    tmpv |= tmpv >> 8;
    tmpv |= tmpv >> 16;
    tmpv++;
    return static_cast<T>(tmpv);
}


namespace Math{

const double PI = 3.14159265358979323846;

template<typename T>
inline T round2(T value){
    T i = 1;
    for (; i < value; i <<= 1);

    if (i - value <= value - i/2)
        return i;

    return i/2;
}

template<typename T>
inline T delta(T x,T y){
    return abs(x-y);
}

template<typename T>
inline T distance(T x,T y){
    return static_cast<T>(sqrt(x*x+y*y));
}

template<typename T>
inline T sigma(const std::vector<T>& arr){
    T re = 0;
    for(size_t i = 0;i < arr.size();++i)
        re += arr[i];
    return re;
}

template<typename T>
inline T sigma(const T* arr,size_t size){
    T re = 0;
    for(size_t i = 0;i < size;++i)
        re += arr[i];
    return re;
}

template<typename T>
inline T gradtoRad(T angle){
    return angle / 180.0f * F2C::Math::PI;
}

template<typename T>
inline T radtoGrad(T rad){
    return rad * 180.0f / F2C::Math::PI;
}

}

template<class T>
static std::ostream& operator<< (std::ostream& out,const std::vector<T>& vec){
    out << vec.size();
    for(size_t i = 0;i < vec.size();++i)
        out << vec[i];
    return out;
}

template<class T>
static std::istream& operator>> (std::istream& in,std::vector<T>& vec){
    size_t size = 0;
    in >> size;
    vec.resize(size);
    for(size_t i = 0;i < vec.size();++i){
        in >> vec[i];
    }
    return in;
}

/**
*@brief Blending type
*/
namespace BlendType{
    typedef enum Blend_Type{
      none = 0, ///< No particular type blending
      normal = 1, ///< Normal alpha Bleinding
      additives  = 2, ///< Additive blending
      multiplicative = 3, ///< Multiplicative blending
      light = 4, ///< LightMap blending
      mask = 5 ///< Masking blending
    } Blend_Type;
}

/**
*@brief Texture filtering \n
*Nearest: \n
*glTexParameter: \n
*MAG_FILTER : GL_NEAREST \n
*MIN_FILTER : GL_NEAREST \n
*\n
*Linear: \n
*glTexParameter: \n
*MAG_FILTER : GL_LINEAR \n
*MIN_FILTER : GL_LINEAR \n
*\n
*@image html filter.jpg
*Original Size: 500x200 Pixel \n
*/
namespace TexParam{
    typedef enum Tex_Param{
        None = 0, ///< No particular texture filter.
        Nearest = 1, ///< Texture with nearest filtering.
        Linear = 2 ///< Texture with linear filtering.
    } Tex_Param;
}

/**
*@brief Keyboard Input
*/
namespace KeyboardEvent{
    typedef enum Keyboard{
       Space = GLFW_KEY_SPACE, ///< Space
       Esc = GLFW_KEY_ESC, ///< Escape
       F1 = GLFW_KEY_F1, ///< Function key * (* can be in the range 1..25)
       F2 = GLFW_KEY_F2,
       F3 = GLFW_KEY_F3,
       F4 = GLFW_KEY_F4,
       F5 = GLFW_KEY_F5,
       F6 = GLFW_KEY_F6,
       F7 = GLFW_KEY_F7,
       F8 = GLFW_KEY_F8,
       F9 = GLFW_KEY_F9,
       F10 = GLFW_KEY_F10,
       F11 = GLFW_KEY_F11,
       F12 = GLFW_KEY_F12,
       F13 = GLFW_KEY_F13,
       F14 = GLFW_KEY_F14,
       F15 = GLFW_KEY_F15,
       F16 = GLFW_KEY_F16,
       F17 = GLFW_KEY_F17,
       F18 = GLFW_KEY_F18,
       F19 = GLFW_KEY_F19,
       F20 = GLFW_KEY_F20,
       F21 = GLFW_KEY_F21,
       F22 = GLFW_KEY_F22,
       F23 = GLFW_KEY_F23,
       F24 = GLFW_KEY_F24,
       F25 = GLFW_KEY_F25,
       Up = GLFW_KEY_UP, ///< Cursor up
       Down = GLFW_KEY_DOWN, ///< Cursor down
       Left = GLFW_KEY_LEFT, ///< Cursor left
       Right = GLFW_KEY_RIGHT, ///< Cursor right
       LShift = GLFW_KEY_LSHIFT, ///< Left shift key
       RShift = GLFW_KEY_RSHIFT, ///< Right shift key
       LCtrl = GLFW_KEY_LCTRL, ///< Left control key
       RCtrl = GLFW_KEY_RCTRL, ///< Right control key
       LAlt = GLFW_KEY_LALT, ///< Left alternate function key
       RAlt = GLFW_KEY_RALT, ///< Right alternate function key
       Tab = GLFW_KEY_TAB, ///< Tabulator
       Enter = GLFW_KEY_ENTER, ///< Enter
       Backspace = GLFW_KEY_BACKSPACE, ///< Backspace
       Insert = GLFW_KEY_INSERT, ///< Insert
       Del = GLFW_KEY_DEL, ///< Delete
       PageUp = GLFW_KEY_PAGEUP, ///< Page up
       PageDown = GLFW_KEY_PAGEDOWN, ///< Page down
       Home = GLFW_KEY_HOME, ///< Home
       End = GLFW_KEY_END, ///< End
       KPNum0 = GLFW_KEY_KP_0,///< Keypad Number * (* can be in the range 0..9)
       KPNum1 = GLFW_KEY_KP_1,
       KPNum2 = GLFW_KEY_KP_2,
       KPNum3 = GLFW_KEY_KP_3,
       KPNum4 = GLFW_KEY_KP_4,
       KPNum5 = GLFW_KEY_KP_5,
       KPNum6 = GLFW_KEY_KP_6,
       KPNum7 = GLFW_KEY_KP_7,
       KPNum8 = GLFW_KEY_KP_8,
       KPNum9 = GLFW_KEY_KP_9,
       KPDiv = GLFW_KEY_KP_DIVIDE, ///< Keypad divide (/)
       KPMul = GLFW_KEY_KP_MULTIPLY, ///< Keypad multiply (*)
       KPSub = GLFW_KEY_KP_SUBTRACT, ///< Keypad subtract (-)
       KPAdd = GLFW_KEY_KP_ADD, ///< Keypad add (+)
       KPDec = GLFW_KEY_KP_DECIMAL, ///< Keypad decimal (. or ,)
       KPEqu = GLFW_KEY_KP_EQUAL, ///< Keypad equal (=)
       KPEnt = GLFW_KEY_KP_ENTER ///< Keypad enter
    } Keyboard;
}

/**
*@brief Mouse Input
*/
namespace MouseEvent{
    typedef enum Mouse{
       Left = GLFW_MOUSE_BUTTON_LEFT, ///< Left mouse button (button 1)
       Right = GLFW_MOUSE_BUTTON_RIGHT, ///< Right mouse button (button 2)
       Middle = GLFW_MOUSE_BUTTON_MIDDLE, ///< Middle mouse button (button 3)
       Button1 = GLFW_MOUSE_BUTTON_1, ///< Mouse Button * (* can be in the range 1..8)
       Button2 = GLFW_MOUSE_BUTTON_2,
       Button3 = GLFW_MOUSE_BUTTON_3,
       Button4 = GLFW_MOUSE_BUTTON_4,
       Button5 = GLFW_MOUSE_BUTTON_5,
       Button6 = GLFW_MOUSE_BUTTON_6,
       Button7 = GLFW_MOUSE_BUTTON_7,
       Button8 = GLFW_MOUSE_BUTTON_8
    } Mouse;
}

/**
*@brief Joystick Input
*/
namespace JoystickEvent{
    typedef enum Joystick{
      Joystick1 = GLFW_JOYSTICK_1,///< Joystick * (* can be in the range 1..16)
      Joystick2 = GLFW_JOYSTICK_2,
      Joystick3 = GLFW_JOYSTICK_3,
      Joystick4 = GLFW_JOYSTICK_4,
      Joystick5 = GLFW_JOYSTICK_5,
      Joystick6 = GLFW_JOYSTICK_6,
      Joystick7 = GLFW_JOYSTICK_7,
      Joystick8 = GLFW_JOYSTICK_8,
      Joystick9 = GLFW_JOYSTICK_9,
      Joystick10 = GLFW_JOYSTICK_10,
      Joystick11 = GLFW_JOYSTICK_11,
      Joystick12 = GLFW_JOYSTICK_12,
      Joystick13 = GLFW_JOYSTICK_13,
      Joystick14 = GLFW_JOYSTICK_14,
      Joystick15 = GLFW_JOYSTICK_15,
      Joystick16 = GLFW_JOYSTICK_16
    } Joystick;
}

/**
*@brief Joystick Handle
*/
namespace JoystickEvent{
    typedef enum ParamJoystick{
      Connected = GLFW_PRESENT, ///< Joystick is connected
      NumAxes = GLFW_AXES, ///< Number of axes supported by the joystick.
      NumButtons = GLFW_BUTTONS ///< Number of buttons supported by the joystick.
    } ParamJoystick;
}

/**
*@brief Window Handle
*/
namespace WindowProperty{
    typedef enum ParamWindow{
       Open = GLFW_OPENED, ///< true if window is opened, else false.
       Active = GLFW_ACTIVE, ///< true if window has focus, else false.
       Iconiffied = GLFW_ICONIFIED, ///< true if window is iconified, else false.
       Accelrtated = GLFW_ACCELERATED, ///< true if window is hardware accelerated, else false.
       RedBits = GLFW_RED_BITS, ///< Number of bits for the red color component.
       GreenBits = GLFW_GREEN_BITS, ///< Number of bits for the green color component.
       BlueBits = GLFW_BLUE_BITS, ///< Number of bits for the blue color component.
       AlphaBits = GLFW_ALPHA_BITS, ///< Number of bits for the alpha buffer.
       DepthBits = GLFW_DEPTH_BITS, ///< Number of bits for the depth buffer.
       StencilBits = GLFW_STENCIL_BITS, ///< Number of bits for the stencil buffer.
       RefreshRate = GLFW_REFRESH_RATE, ///< Vertical monitor refresh rate in Hz. Zero indicates an unknown or a default refresh rate.
       AccumRedBits = GLFW_ACCUM_RED_BITS, ///< Number of bits for the red channel of the accumulator buffer.
       AccumGreenBits = GLFW_ACCUM_GREEN_BITS, ///< Number of bits for the green channel of the accumulator buffer.
       AccumBlueBits = GLFW_ACCUM_BLUE_BITS, ///< Number of bits for the blue channel of the accumulator buffer.
       AccumAlphaBits = GLFW_ACCUM_ALPHA_BITS, ///< Number of bits for the alpha channel of the accumulator buffer.
       AuxBuffer = GLFW_AUX_BUFFERS, ///< Number of auxiliary buffers.
       StereoRendering = GLFW_STEREO, ///< true if stereo rendering is supported, else false.
       MultisamplingBufferSamples = GLFW_FSAA_SAMPLES, ///< Number of multisampling buffer samples. Zero indicated multisampling is disabled.
       NoResize = GLFW_WINDOW_NO_RESIZE ///< true if the window cannot be resized, else false.
    } ParamWindow;
}

namespace Image{
    /**
    *@brief DataFormat: Pixel data format.
    */
    typedef enum DataFormat{
          BRG = IL_BGR, ///< BRG
          BRGA = IL_BGRA, ///< BRGA
          ColourIndex = IL_COLOUR_INDEX, ///< Colour Index
          Luminance = IL_LUMINANCE, ///< Luminance
          LuminanceAlpha = IL_LUMINANCE_ALPHA, ///< Luminance Alpha
          RGB = IL_RGB, ///< RGB
          RGBA = IL_RGBA ///< RGBA
    } DataFormat;

    /**
    *@brief ImageType: File format.
    */
    typedef enum ImageType{
       bmp = IL_BMP, ///< Microsoft bitmap.
       CHeader = IL_CHEAD, ///< C Header.
       cut = IL_CUT, ///< Dr. Halo .cut image.
       dcx = IL_DCX, ///< .dcx image.
       dds =  IL_DDS, ///< DirectDraw Surface image.
       wad = IL_DOOM, ///< Doom texture.
       wadFlat = IL_DOOM_FLAT, ///< Doom flat (floor).
       gif = IL_GIF, ///< Graphics Interchange Format(.gif) file.
       hdr = IL_HDR, ///< RADIANCE High Dynamic Range Image.
       ico = IL_ICO, ///< Microsoft icon (.ico).
       jasc = IL_JASC_PAL, ///< Load the file into the current image's palette as a Paint Shop Pro (Jasc) palette.
       jpg = IL_JPG, ///< Jpeg.
       lif = IL_LIF, ///< Homeworld image.
       mdl = IL_MDL, ///< Half-Life model file (.mdl).
       mng = IL_MNG, ///< Load a Multiple Network Graphics (.mng).
       pcd = IL_PCD, ///< Kodak PhotoCD image.
       pcx = IL_PCX, ///< .pcx Image.
       pic = IL_PIC, ///< Softimage Pic image.
       pix = IL_PIX, ///< Alias | Wavefront .pix file.
       png = IL_PNG, ///< Portable Network Graphics (.png) image.
       pnm = IL_PNM, ///< Portable AnyMap (.pbm, .pgm or .ppm).
       psd = IL_PSD, ///< PhotoShop (.psd) file.
       psp = IL_PSP, ///< Paint Shop Pro file.
       pxr = IL_PXR, ///< Pxrar (.pxr) file.
       raw = IL_RAW, ///< Raw data with a 13-byte header.
       sgi = IL_SGI, ///< SGI (.bw, .rgb, .rgba or .sgi).
       tga = IL_TGA, ///< TrueVision Targa (.tga).
       tif = IL_TIF, ///< TIFF (.tif or .tiff) image.
       unknown = IL_TYPE_UNKNOWN, ///< unknow file.
       wal = IL_WAL, ///< Quake .wal texture.
       xpm = IL_XPM, ///< .xpm file.
    } ImageType;
}

}

#endif
