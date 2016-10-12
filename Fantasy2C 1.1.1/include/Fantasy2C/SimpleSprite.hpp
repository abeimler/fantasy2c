#ifndef __F2C_SIMPLESPRITE_HPP_INCLUDED
#define __F2C_SIMPLESPRITE_HPP_INCLUDED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <Fantasy2C/Basic.hpp>
#include <Fantasy2C/SpriteBase.hpp>

namespace F2C{

/**
*@class SimpleSprite
*@brief Renders an image (Bitmap class) on the screen.
*This class offers less than the normal Sprite class is but a little faster at rendering.
*
*Please note the following OpenGL capability are enabled when rendering and at the end disable: \n
*GL_TEXTURE_2D \n
*GL_DEPTH_TEST \n
*GL_ALPHA_TEST \n
*GL_BLEND \n
*and use glShadeModel(GL_SMOOTH) \n
*\n
*Dont forget to set the depth and alpha test function, e.g.: \n
*glAlphaFunc(GL_GREATER, 0.0f) \n
*glDepthFunc(GL_LEQUAL) \n
*\n
*Used OpenGL Buffers \n
*-GL_COLOR_BUFFER_BIT \n
*-GL_DEPTH_BUFFER_BIT \n
*/
class DLL SimpleSprite : public SpriteBase{
    private:
		static bool VertexArray;
		static bool checkVertexArray;

	public:
        /**
        *@brief Handle by the ARB program object for the ArraySprite. (Default: NULL) \n
        *The Tranzperenz(Alpha Color) of the generated shader image (with the ARB program object) can be determined by the grayscale. \n
        *Optimal : Post-Processing-Shader Program
        */
        static GLhandleARB ShaderProgramObj;
		static TexParam::Tex_Param filter; ///< Set the texture filtering of the Sprite. (Default: Linear)

		uint8 grayscale; ///< Grayscale value (or the tranzperenz the shader generated image).

		SimpleSprite(); ///< Default constructor
		SimpleSprite(const Bitmap* bitmap); ///< @param bitmap Pointer of Bitmap @brief Load the pixels from the bitmap into the texture. If NULL, is equivalent to the behavior as a disabled texturing.
		SimpleSprite(const SimpleSprite& copy); ///< Copy constructor
		SimpleSprite& operator= (const SimpleSprite& copy); ///< Assignment operator with deep copy.

		/**
		*@param copy Source copy
		*@brief Copies all properties(x,y,z-Coord.,vColor,...), except the texture(Bitmap,bitmapWidth,Height,...)
		*/
		void copyProperties(const SimpleSprite& copy);

		/**
        *@return -1, show is false.
        *@return -2, The width or height of the bitmap or the src_rect are 0.
        *@return -3, The sprite is outside the display (glViewport).
        *@return -4, The alpha color of all 4 Vertices are less than 1.
        *@return -5, zoom_x or zoom_y is exactly 0.
        *@return 1, Sprite has been successfully rendered.
        *@brief Render the bitmap on screen.
        */
		int render() const;
};

}

#endif // SIMPLESPRITE_HPP_INCLUDED
