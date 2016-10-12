#ifndef __F2C_ARRAYSPRITE_HPP_INCLUDED
#define __F2C_ARRAYSPRITE_HPP_INCLUDED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <Fantasy2C/Basic.hpp>
#include <Fantasy2C/Bitmap.hpp>
#include <Fantasy2C/Rect.hpp>
#include <Fantasy2C/Color.hpp>
#include <Fantasy2C/ColorTone.hpp>
#include <Fantasy2C/Viewport.hpp>
#include <Fantasy2C/RenderManager.hpp>

namespace F2C{

/**
*@class SpriteElement
*@brief Element Type of ArraySprite
*/
class DLL SpriteElement{
	public:
		Rect src_rect; ///< Show rect of spriters
		bool show; ///< Show spriters On/Off
		int x; ///< X-coordinate
		int y; ///< Y-coordinate
		int z; ///< Z-coordinate
		double zoom_x; ///< Zoom factor of the X-axis
        double zoom_y; ///< Zoom factor of the Y-axis
        int angle_x; ///< Rotation angle (in degrees) of the X-axis
        int angle_y; ///< Rotation angle (in degrees) of the Y-axis
        int angle_z; ///< Rotation angle (in degrees) of the Z-axis
		Color vColor[4]; ///< Colors of the 4 Vertices @image html vcolor.jpg
		bool flippedH; ///< flipped horizontally (Y-axis 180 degree turn)
		bool flippedV; ///< flipped vertically (X-axis 180 degree turn)

		SpriteElement(); ///< Default constructor

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

		/**
		*@param out Output stream
		*@param obj Object
		*@brief Write the Object into output stream.
		*/
		friend std::ostream& operator<<(std::ostream &out, SpriteElement& obj);

		/**
		*@param in Input stream
		*@param obj Object
		*@brief Read the Object from input stream.
		*/
        friend std::istream& operator>>(std::istream &in, SpriteElement& obj);
};

/**
*@param out Output stream
*@param obj Object
*@brief Write the Object into output stream.
*/
std::ostream& DLL operator<<(std::ostream &out, SpriteElement& obj);

/**
*@param in Input stream
*@param obj Object
*@brief Read the Object from input stream.
*/
std::istream& DLL operator>>(std::istream &in, SpriteElement& obj);

}

template class DLL std::allocator< F2C::SpriteElement >;
template class DLL std::vector< F2C::SpriteElement, std::allocator<F2C::SpriteElement> >;

namespace F2C{
/**
*@class ArraySprite
*@brief Renders a picture(Bitmap), as an array of different values.
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
class DLL ArraySprite{
	private:
		uint texture;
		uint bitmapWidth;
		uint bitmapHeight;
		uint pixelsWidth;
		ubyte* pixels;
		Image::DataFormat bitmapFormat;
		uint bitmapBits;
		static bool VertexArray;
		static bool checkVertexArray;

	public:
        /**
        *@brief Handle by the ARB program object for the ArraySprite. (Default: NULL) \n
        *The Tranzperenz(Alpha Color) of the generated shader image (with the ARB program object) can be determined by the grayscale. \n
        *Optimal: Post-Processing-Shader Program
        */
        static GLhandleARB ShaderProgramObj;
		static TexParam::Tex_Param filter; ///< Set the texture filtering of the Sprite. (Default: Linear)

		/**
		*@param enable Enable/Disable
		*@brief if enable then use glDrawArrays,glEnableClientState,... , if disable then use glBegin(),glVertex(),...,glEnd(). \n
		*Is automatically enable when VBO is supported.
		*/
		static void enableGLDrawArray(bool enable);
		static bool isEnableGLDrawArray(); ///< getMethode: Is glDrawArrays,glEnableClientState,... used when rendering.

		ArraySprite(); ///< Default constructor
		virtual ~ArraySprite(); ///< Delete the texture from memory.
		ArraySprite(Viewport* viewport); ///< @param viewport Pointer of Viewport @brief Set the pointer of the viewport and the clip_rect.
		ArraySprite(const Bitmap* bitmap); ///< @param bitmap Pointer of Bitmap @brief Load the pixels from the bitmap into the texture. If NULL, is equivalent to the behavior as a disabled texturing.
		ArraySprite(const ArraySprite& copy); ///< Copy constructor
		ArraySprite& operator= (const ArraySprite& copy); ///< Assignment operator with deep copy.

		/**
        *@return -1, show from viewport is false.
        *@return -2, The width or height of the bitmap is 0.
        *@return -3, zoom_x or zoom_y is exactly 0.
        *@return -4, Empty array.
        *@return 1, Elements has been successfully rendered.
        *@brief Renders all elements on the screen.
        */
		int16 render() const;

		/**
		*@param starteid Start index of the sprite elements.
        *@return -1, show is false (or from viewport).
        *@return -2, The width or height of the bitmap is 0.
        *@return -3, zoom_x or zoom_y is exactly 0
        *@return -4, Empty array.
		*@return -5, starteid is outside the array elements.
        *@return 1, Elements has been rendered.
        *@brief Renders a particular area (from the starteid until the end of the array elements) of the elements on the screen.
        */
		int16 render(size_t starteid) const;
		/**
		*@param starteid Start index of the array elements.
		*@param endeid End index of the array elements
        *@return -1, show from viewport is false.
        *@return -2, The width or height of the bitmap is 0.
        *@return -3, zoom_x or zoom_y is exactly 0
        *@return -4, Empty array.
		*@return -5, starteid is outside the array elements.
        *@return 1, Elements has been rendered.
        *@brief Renders a particular area (from the starteid to endeid) the elements on the screen.
        */
		int16 render(size_t starteid,size_t endeid) const;

        Viewport* viewport; ///< Additional Z-coordinate and ColorTone
		Rect* clip_rect; ///< Clipping Rect, Cutting the sprites on the screen the desired section or window.
		int x; ///< X-coordinate
		int y; ///< Y-coordinate
		int z; ///< Z-coordinate
		double zoom_x; ///< Zoom factor of the X-axis
        double zoom_y; ///< Zoom factor of the Y-axis
		ColorTone tone; ///< Color tone
		BlendType::Blend_Type blend_type; ///< Blending type
		std::vector<SpriteElement> elements; ///< Array with the SpriteElemets.

		uint getTexture() const; ///< getMethode: OpenGL Texture Name(ID)
		uint getTexWidth() const; ///< getMethode: Width of the bitmap.
		uint getTexHeight() const; ///< getMethode: Height of the bitmap.
		uint getTexBits() const; ///< getMethode: Color depth (in bits) of the texture.
		Image::DataFormat getTexDataFormat() const; ///< getMethode: Pixel format of the texture.

		void setBitmap(const Bitmap* bitmap); ///< @param bitmap Pointer of Bitmap @brief Load the pixels from the bitmap into the texture. If NULL, is equivalent to the behavior as a disabled texturing.
		void setViewport(Viewport* viewport); ///< @param viewport Pointer of Viewport @brief setMethode: Set the pointer of the viewport and the clip_rect.

		friend std::ostream& operator<<(std::ostream &out,const ArraySprite& obj);
        friend std::istream& operator>>(std::istream &in, ArraySprite& obj);
};

/**
*@param out Output stream
*@param obj Object
*@brief Write the Object into output stream. (dont write the Texture Name)
*/
std::ostream& DLL operator<<(std::ostream &out,const ArraySprite& obj);

/**
*@param in Input stream
*@param obj Object
*@brief Read the Object from input stream. (use old(or create new) Texture Name)
*/
std::istream& DLL operator>>(std::istream &in, ArraySprite& obj);

}


#endif
