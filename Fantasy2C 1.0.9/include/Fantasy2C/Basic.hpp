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
*-Play sounds und music\n
*-Load images from memory or file\n
*-Load TTF files and create bitmapfont\n
*-Draw simple sprite with image\n
*-Draw scrolling background\n
*-Draw array of sprites (e.g. tilemap)\n
*-Draw texts with bitmapfonts\n
*-Window and input managment\n
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
*libFantasy2C.a \n
*\n
*Compiling Fantasy2C sourcecode,Settings Linker (Windows): \n
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
*@version 1.0.9
*@date 20.11.2008
*@author Alex Beimler (alias kiba) \n
*http://fantasy2c.fa.ohost.de/
*Copyright (C) 2009  Alex Beimler \n
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

#if defined(_MSC_VER) && _MSC_VER >= 1020
#pragma once
#endif

#if defined(NO_DLL) || defined(VCPPCLASSLIB)
	#define DLL
#else
	#if defined(WIN32) || defined(_Windows) || defined(__WIN32__)
		#if defined(FANTASY2C_EXPORTS) || defined(_WINDLL)
			#define DLL __declspec(dllexport)
		#else
			#define DLL __declspec(dllimport)
		#endif
	#else
		#define DLL
	#endif
#endif

#if defined(_MSC_VER) && _MSC_VER >= 1020
	#pragma comment(lib,"opengl32")
	#pragma comment(lib,"glu32")
	#pragma comment(lib,"DevIL.lib")
	#pragma comment(lib,"ILU.lib")
	#pragma comment(lib,"libglfw.a")
	#pragma comment(lib,"freetype.lib")
	#if defined(WIN32) || defined(_Windows) || defined(__WIN32__)
		#pragma comment(lib,"libglfwdll.a")
		#pragma comment(lib,"libfreetype.dll.a")
	#endif
	#pragma comment(lib,"audiere.lib")
#endif

//----- Includes -----//

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstdarg>
#include <cstring>
#include <ctime>

#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

#if defined(__APPLE__) && defined(__MACH__)
    //include OpenGL Header
    #include <OpenGL/gl.h>
    #include <OpenGL/glu.h>
#else
	//include Windows Header
	//#if defined(WIN32) || defined(_Windows) || defined(__WIN32__)
	//	#include <windows.h>
	//#endif

    //include OpenGL Header
    #include <GL/gl.h>
    #include <GL/glu.h>
#endif

#if defined(WIN32) || defined(_Windows) || defined(__WIN32__)
    class DLL std::_String_base;
    class DLL std::_Container_base_secure;
    class DLL std::ios_base;
#endif

/*
template class DLL std::allocator<int>;
template class DLL std::allocator<char>;
template class DLL std::basic_string<char, std::char_traits<char>, std::allocator<char> >;
template class DLL std::allocator< std::basic_string<char, std::char_traits<char>, std::allocator<char> > >;
template class DLL std::vector< std::basic_string<char, std::char_traits<char>, std::allocator<char> >, std::allocator<std::basic_string<char> > >;

template class DLL std::basic_ios<char, std::char_traits<char> >;
template class DLL std::basic_ostream<char, std::char_traits<char> >;
template class DLL std::basic_iostream<char, std::char_traits<char> >;
template class DLL std::basic_stringstream<char, std::char_traits<char>, std::allocator<char> >;
template class DLL std::basic_ostringstream<char, std::char_traits<char>, std::allocator<char> >;
*/

//inlude OpenIL(DevIL) Header
#include <IL/il.h>
#include <IL/ilu.h>

//inlude Audiere Header
#include <audiere.h>

//inlude Freetype2 Header
#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_GLYPH_H
#include FT_OUTLINE_H
#include FT_TRIGONOMETRY_H

#if defined(macintosh) || (defined(__APPLE__) && defined(__MACH__))
	#include FT_MAC_H
#endif

//inlude GLFW Header
#if defined(WIN32) || defined(_Windows) || defined(__WIN32__)
    #define GLFW_DLL
#endif
#include <GL/glfw.h>

//#if defined(__cplusplus)
//extern "C" {
//#endif
//
//bool DLL glExtensionSupported(const char *extName );
//
//#if defined(__cplusplus)
//}
//#endif

#if defined(WIN32) || defined(_Windows) || defined(__WIN32__)
    //#include <windows.h>
    //#include "wglext.h"
    //#define uglGetProcAddress(x) wglGetProcAddress(x)
    //#define uglExtensionSupported(x) glExtensionSupported(x)

    #define uglGetProcAddress(x) glfwGetProcAddress(x)
    #define uglExtensionSupported(x) (glfwExtensionSupported(x) != GL_FALSE)

    #define WIN32_OR_X11
#elif defined(__X11__) || defined(__linux)
    //#include <GL/glx.h>
    //#include "glxext.h"
    //#define uglGetProcAddress(x) (*glXGetProcAddressARB)((const GLubyte*)(x))
    //#define uglExtensionSupported(x) glExtensionSupported(x)

    #define uglGetProcAddress(x) glfwGetProcAddress(x)
    #define uglExtensionSupported(x) (glfwExtensionSupported(x) != GL_FALSE)

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

#if defined(__APPLE__)
  #include <OpenGL/glu.h>
  #include "glext.h"
#else
    #include "glext.h"
    #ifdef WIN32_OR_X11
        extern DLL PFNGLCREATEPROGRAMOBJECTARBPROC     glCreateProgramObjectARB;
        extern DLL PFNGLDELETEOBJECTARBPROC            glDeleteObjectARB;
        extern DLL PFNGLCREATESHADEROBJECTARBPROC      glCreateShaderObjectARB;
        extern DLL PFNGLSHADERSOURCEARBPROC            glShaderSourceARB;
        extern DLL PFNGLCOMPILESHADERARBPROC           glCompileShaderARB;
        extern DLL PFNGLGETOBJECTPARAMETERIVARBPROC    glGetObjectParameterivARB;
        extern DLL PFNGLATTACHOBJECTARBPROC            glAttachObjectARB;
        extern DLL PFNGLGETINFOLOGARBPROC              glGetInfoLogARB;
        extern DLL PFNGLLINKPROGRAMARBPROC             glLinkProgramARB;
        extern DLL PFNGLUSEPROGRAMOBJECTARBPROC        glUseProgramObjectARB;
        extern DLL PFNGLGETUNIFORMLOCATIONARBPROC      glGetUniformLocationARB;
        extern DLL PFNGLUNIFORM1FARBPROC               glUniform1fARB;
        extern DLL PFNGLUNIFORM1IARBPROC               glUniform1iARB;

        extern DLL PFNGLGENBUFFERSARBPROC glGenBuffersARB;
        extern DLL PFNGLBINDBUFFERARBPROC glBindBufferARB;
        extern DLL PFNGLBUFFERDATAARBPROC glBufferDataARB;
        extern DLL PFNGLDELETEBUFFERSARBPROC glDeleteBuffersARB;

        #if defined(WIN32) || defined(_Windows) || defined(__WIN32__)
            extern DLL PFNGLMULTITEXCOORD1FARBPROC glMultiTexCoord1fARB;
            extern DLL PFNGLMULTITEXCOORD2FARBPROC glMultiTexCoord2fARB;
            extern DLL PFNGLMULTITEXCOORD3FARBPROC glMultiTexCoord3fARB;
            extern DLL PFNGLMULTITEXCOORD4FARBPROC glMultiTexCoord4fARB;
            extern DLL PFNGLACTIVETEXTUREARBPROC glActiveTextureARB;
            extern DLL PFNGLCLIENTACTIVETEXTUREARBPROC glClientActiveTextureARB;
        #endif
    #endif
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


/**
*@param x Target reference variable
*@param min Minimum value
*@param max Maximum Value
*@brief Pushes x in the range of Min and Max.
*/
template <class T>
void clamp(T& x,T min,T max){
    if( x > max )
    { x = max;}
    else if( x < min )
    {x = min;}
}


/**
*@param v Value
*@return Power of 2
*@brief Round to the next highest power of 2.
*/
template <class T>
T nextPowerof2(T v){
    int tmpv = static_cast<int>(v);
    tmpv--;
    tmpv |= tmpv >> 1;
    tmpv |= tmpv >> 2;
    tmpv |= tmpv >> 4;
    tmpv |= tmpv >> 8;
    tmpv |= tmpv >> 16;
    tmpv++;
    return tmpv;
}

/**
*@brief Blending type
*/
namespace BlendType{
    enum Blend_Type{
      none = 0, ///< No particular type blending
      normal = 1, ///< Normal alpha Bleinding
      additives  = 2, ///< Additive blending
      multiplicative = 3, ///< Multiplicative blending
    };
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
    enum Tex_Param{
        None = 0, ///< No particular texture filter.
        Nearest = 1, ///< Texture with nearest filtering.
        Linear = 2 ///< Texture with linear filtering.
    };
}

/**
*@brief Keyboard Input
*/
namespace KeyboardEvent{
    enum Keyboard{
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
    };
}

/**
*@brief Mouse Input
*/
namespace MouseEvent{
    enum Mouse{
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
    };
}

/**
*@brief Joystick Input
*/
namespace JoystickEvent{
    enum Joystick{
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
    };
}

/**
*@brief Joystick Handle
*/
namespace JoystickEvent{
    enum ParamJoystick{
      Connected = GLFW_PRESENT, ///< Joystick is connected
      NumAxes = GLFW_AXES, ///< Number of axes supported by the joystick.
      NumButtons = GLFW_BUTTONS ///< Number of buttons supported by the joystick.
    };
}

/**
*@brief Window Handle
*/
namespace WindowProperty{
    enum ParamWindow{
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
    };
}

namespace Image{
    /**
    *@brief DataFormat: Pixel data format.
    */
    enum DataFormat{
          BRG = IL_BGR, ///< BRG
          BRGA = IL_BGRA, ///< BRGA
          ColourIndex = IL_COLOUR_INDEX, ///< Colour Index
          Luminance = IL_LUMINANCE, ///< Luminance
          LuminanceAlpha = IL_LUMINANCE_ALPHA, ///< Luminance Alpha
          RGB = IL_RGB, ///< RGB
          RGBA = IL_RGBA ///< RGBA
    };

    /**
    *@brief ImageType: File format.
    */
    enum ImageType{
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
    };
}

}

#endif
