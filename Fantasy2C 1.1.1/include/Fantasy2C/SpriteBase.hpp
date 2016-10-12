#ifndef __F2C_BASESPRITE_HPP_INCLUDED
#define __F2C_BASESPRITE_HPP_INCLUDED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <Fantasy2C/Basic.hpp>
#include <Fantasy2C/Bitmap.hpp>
#include <Fantasy2C/Rect.hpp>
#include <Fantasy2C/Color.hpp>
#include <Fantasy2C/ColorTone.hpp>
#include <Fantasy2C/Viewport.hpp>

namespace F2C{

/**
*@class SpriteBase
*@brief Basis Class of Sprite
*/
class DLL SpriteBase{
    protected:
		GLuint texture; ///< OpenGL Texture Name(ID)
		uint bitmapWidth; ///< Bitmap width
		uint bitmapHeight; ///< Bitmap height
		uint pixelsWidth; ///< Width (or height) of the pixel array.
		ubyte* pixels; ///< Copy of pixels.
		Image::DataFormat bitmapFormat; ///< Pixel data format
		uint bitmapBits; ///< Bits per pixel (color depth (in bits))

	public:
		Rect src_rect; ///< Show rect of Sprite
		bool show; ///< Show Sprite On/Off
		int x; ///< X-coordinate
		int y; ///< Y-coordinate
		int z; ///< Z-coordinate
		double zoom_x; ///< Zoom factor of the X-axis
        double zoom_y; ///< Zoom factor of the Y-axis
        int angle_x; ///< Rotation angle (in degrees) of the X-axis
        int angle_y; ///< Rotation angle (in degrees) of the Y-axis
        int angle_z; ///< Rotation angle (in degrees) of the Z-axis
		BlendType::Blend_Type blend_type; ///< Blending type
		Color vColor[4]; ///< Colors of the 4 Vertices @image html vcolor.jpg
		bool flippedH; ///< flipped horizontally (Y-axis 180 degree turn)
		bool flippedV; ///< flipped vertically (X-axis 180 degree turn)

		SpriteBase(); ///< Default constructor
		virtual ~SpriteBase(); ///< Default destructor
		SpriteBase(const Bitmap* bitmap); ///< @param bitmap Pointer of Bitmap @brief Load the pixels from the bitmap into the texture. If NULL, is equivalent to the behavior as a disabled texturing.
		SpriteBase(const SpriteBase& copy); ///< Copy constructor
		SpriteBase& operator= (const SpriteBase& copy); ///< Assignment operator with deep copy.

		/**
		*@param copy Source copy
		*@brief Copies all properties(x,y,z-Coord.,vColor,...), except the texture(Bitmap,bitmapWidth,Height,...)
		*/
		void copyProperties(const SpriteBase& copy);

		/**
		*@brief Render the bitmap on screen.
        */
		virtual int render() const = 0;

		void setRed(uint8 red); ///< @param red Red @brief setMethode: Sets the color red of all 4 Vertices.
		void setGreen(uint8 green); ///< @param green Green @brief setMethode: Sets the color green of all 4 Vertices.
		void setBlue(uint8 blue); ///< @param blue Blue @brief setMethode: Sets the color blue of all 4 Vertices.
		void setAlpha(uint8 alpha); ///< @param alpha Alpha @brief setMethode: Sets the color alpha of all 4 Vertices.
		void setColor(const Color& color); ///< @param color Color @brief setMethode: Sets all colors of the 4 Vertices.
		/**
		*@param red Red
		*@param green Green
		*@param blue Blue
		*@param alpha Alpha
		*@brief setMethode: Sets all colors of the 4 Vertices.
		*/
		void setColor(uint8 red,uint8 green,uint8 blue,uint8 alpha);
		/**
		*@param red Red
		*@param green Green
		*@param blue Blue
		*@brief setMethode: Sets all colors of the 4 Vertices.
		*/
		void setColor(uint8 red,uint8 green,uint8 blue);

		GLuint getTexture() const; ///< getMethode: OpenGL Texture Name(ID)
		uint getTexWidth() const; ///< getMethode: Width of the bitmap.
		uint getTexHeight() const; ///< getMethode: Height of the bitmap.
		uint getTexBits() const; ///< getMethode: Color depth (in bits) of the texture.
		Image::DataFormat getTexDataFormat() const; ///< getMethode: Pixel format of the texture.

		void setBitmap(const Bitmap* bitmap); ///< @param bitmap Pointer of Bitmap @brief Load the pixels from the bitmap into the texture. If NULL, is equivalent to the behavior as a disabled texturing.
};

}

#endif // BASESPRITE_HPP_INCLUDED
