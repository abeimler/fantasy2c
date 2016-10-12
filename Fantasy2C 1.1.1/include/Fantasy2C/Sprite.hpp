#ifndef __F2C_SPRITE_HPP_INCLUDED
#define __F2C_SPRITE_HPP_INCLUDED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <Fantasy2C/Basic.hpp>
#include <Fantasy2C/SpriteBase.hpp>

namespace F2C{

/**
*@class Sprite
*@brief Renders an image (Bitmap class) on the screen.
*
*Please note the following OpenGL capability are enabled when rendering and at the end disable: \n
*GL_SCISSOR_TEST (if necessary) \n
*GL_STENCIL_TEST \n
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
*-GL_STENCIL_BUFFER_BIT \n
*/
class DLL Sprite : public SpriteBase{
	private:
		static bool VertexArray;
		static bool checkVertexArray;

	public:
        /**
        *@brief Handle by the ARB program object for the ArraySprite. (Default: NULL) \n
        *The Tranzperenz(Alpha Color) of the generated shader image (with the ARB program object) can be determined by the grayscale.
        */
        static GLhandleARB ShaderProgramObj;
		static TexParam::Tex_Param filter; ///< Set the texture filtering of the Sprite. (Default: Linear)

		Sprite(); ///< Default constructor
		Sprite(Viewport* viewport); ///< @param viewport Pointer of Viewport @brief Set the pointer of the viewport and the clip_rect.
		Sprite(const Bitmap* bitmap); ///< @param bitmap Pointer of Bitmap @brief Load the pixels from the bitmap into the texture. If NULL, is equivalent to the behavior as a disabled texturing.
		Sprite(const Sprite& copy); ///< Copy constructor
		Sprite& operator= (const Sprite& copy); ///< Assignment operator with deep copy.

		/**
		*@param copy Source copy
		*@brief Copies all properties(x,y,z-Coord.,vColor,...), except the texture(Bitmap,bitmapWidth,Height,...)
		*/
		void copyProperties(const Sprite& copy);

		/**
        *@return -1, show is false (or from viewport).
        *@return -2, The width or height of the bitmap or the src_rect are 0.
        *@return -3, The sprite is outside the display (glViewport).
        *@return -4, The alpha color of all 4 Vertices are less than 1.
        *@return -5, zoom_x or zoom_y is exactly 0.
        *@return 1, Sprite has been successfully rendered.
        *@brief Render the bitmap on screen.
        */
		int render() const;

        Rect* clip_rect; ///< Clipping Rect, Cutting the sprites on the screen the desired section or window.
        Viewport* viewport; ///< Additional Z-coordinate and ColorTone
		ColorTone tone; ///< Color tone

		void setViewport(Viewport* viewport); ///< @param viewport Pointer of Viewport @brief setMethode: Set the pointer of the viewport and the clip_rect.

};

}

#endif

