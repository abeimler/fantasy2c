#ifndef __F2C_FONTSPRITE_HPP_INCLUDED
#define __F2C_FONTSPRITE_HPP_INCLUDED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <Fantasy2C/Basic.hpp>
#include <Fantasy2C/SpriteBase.hpp>
#include <Fantasy2C/Font.hpp>
#include <Fantasy2C/GameError.hpp>
#include <string>
#include <vector>

template class DLL std::allocator<F2C::Rect>;
template class DLL std::vector<F2C::Rect, std::allocator<F2C::Rect> >;

namespace F2C{

/**
*@class FontSprite
*@brief Displaying messages on the screen via BitmapFont (bitmap).
*
*Please note the following OpenGL capability are enabled when rendering and at the end disable: \n
*GL_SCISSOR_TEST \n
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
class DLL FontSprite : public SpriteBase{
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

        Rect* clip_rect; ///< Clipping Rect, Cutting the sprites on the screen the desired section or window.
        Viewport* viewport; ///< Additional Z-coordinate and ColorTone
        ColorTone tone; ///< Color tone

        void setViewport(Viewport* viewport); ///< @param viewport Pointer of Viewport @brief setMethode: Set the pointer of the viewport and the clip_rect.

	private:
        uint charsperwidth;
        uint charsperheight;
        uint biggestCharWidth;
        uint biggestCharHeight;
        TTFFont bitmapfont;
        Rect char_rect[256];
        std::vector<std::string> strings;
        std::vector<Rect> rect_strings;

	public:
        /**
        *@brief Transparency (alpha) tolerance, to determine the spacing between the Character
        *(Is tolerance equal to 0: the whole rectangle of the Character.
        *If the alpha value greater than or equal to the tolerance is measured as the distance from)
        *(default: 1)
        */
        static uint8 AlphaTolerance;
        static uint defaultCharsperW; ///< Standard characters per column (default: 16)
        static uint defaultCharsperH; ///< Standard characters per line (default: 16)
        bool italic; ///< Sets the text to italics On/Off

        /**
		*@param enable Enable/Disable
		*@brief if enable then use glDrawArrays,glEnableClientState,... , if disable then use glBegin(),glVertex(),...,glEnd(). \n
		*Is automatically enable when VBO is supported.
		*/
		static void enableGLDrawArray(bool enable);
		static bool isEnableGLDrawArray(); ///< getMethode: Is glDrawArrays,glEnableClientState,... used when rendering.

        FontSprite(); ///< Default constructor
        FontSprite(const FontSprite& copy); ///< Copy constructor
        FontSprite(Viewport* viewport); ///< @param viewport Pointer of Viewport @brief Set the pointer of the viewport and the clip_rect.
		FontSprite& operator= (const FontSprite& copy); ///< Assignment operator with deep copy.

        /**
        *@param bitmapfont Pointer of Bitmap
        *@param charsperwidth Characters per column
        *@param charsperheight Characters per line
        *@brief Load the pixels from the bitmap into the texture. If NULL, is equivalent to the behavior as a disabled texturing.
        *@image html Font.jpg
        */
        FontSprite(const Bitmap* bitmapfont,uint charsperwidth = FontSprite::defaultCharsperW,uint charsperheight = FontSprite::defaultCharsperH);

        /**
		*@param copy Source copy
		*@brief Copies all properties(x,y,z-Coord.,vColor,Texts,...), except the texture(Bitmap,bitmapWidth,Height,...)
		*/
		void copyProperties(const FontSprite& copy);

        /**
        *@return -1, show is false (or from viewport).
        *@return -2, The width or height of the bitmap is 0.
        *@return -3, There are no texts to display.
        *@return -4, The alpha color of all 4 Vertices are less than 1.
        *@return -5, zoom_x or zoom_y is exactly 0.
        *@return 1, Texts has been successfully rendered.
        *@brief Render the text on the screen.
        */
        int16 render() const;

        /**
        *@param font Pointer of TTF Font
        *@brief Load the pixels from the TTF Font(or Bitmapfont) into the texture. If NULL, is equivalent to the behavior as a disabled texturing.
        *@image html Font.jpg
        */
        void setBitmap(const TTFFont* font);

        /**
        *@param bitmap Pointer of Bitmap
        *@param charsperwidth Characters per column
        *@param charsperheight Characters per line
        *@brief Load the pixels from the bitmap into the texture. If NULL, is equivalent to the behavior as a disabled texturing.
        *@image html Font.jpg
        */
        void setBitmap(const Bitmap* bitmap,uint charsperwidth = FontSprite::defaultCharsperW,uint charsperheight = FontSprite::defaultCharsperH);

        /**
        *@param x X coordinate
        *@param y Y coordinate
        *@param width Width of the display area
        *@param height Height of the display area
        *@param text Text
        *@brief Adds a text to a specific position. \n
        *You can use "\n" for newline
        */
        void addText(int x,int y,uint width,uint height,std::string text);
        /**
        *@param rect Display area
        *@param text Text
        *@brief Adds a text to a specific position. \n
        *You can use "\n" for newline
        */
        void addText(const Rect& rect,std::string text);

        /**
        *@param x X coordinate
        *@param y Y coordinate
        *@param text Text
        *@brief Adds a text to a specific position.(size is automatically) \n
        *You can use "\n" for newline
        */
        void addText(int x,int y,std::string text);
        void clearTexts(); ///< Clear all Texts.

        uint getCharsperWidth() const; ///< getMethode: Characters per column
        uint getCharsperHeight() const; ///< getMethode: Characters per line
        const std::vector<std::string>& getTexts() const; ///< getMethode: Inserted texts
        const std::vector<Rect>& getTextsRect() const; ///< getMethode: Size(in pixels) of inserted texts.
		const Rect* getCharsRect() const; ///< getMethode: Return the coordinates and the size of all characters (ASCII :0-255, Size: 256).
		Rect getStringSize(std::string str) const; ///< @param str Text @brief getMethode: Get Size of Text (in Pixels)

		friend std::ostream& operator<<(std::ostream &out,const FontSprite& obj);
        friend std::istream& operator>>(std::istream &in,FontSprite& obj);
};

/**
*@param out Output stream
*@param obj Object
*@brief Write the Object into output stream. (dont write pointer (Viewport,clip_rect))
*/
std::ostream& DLL operator<<(std::ostream &out,const FontSprite& obj);

/**
*@param in Input stream
*@param obj Object
*@brief Read the Object from input stream. (dont read pointer (Viewport,clip_rect))
*/
std::istream& DLL operator>>(std::istream &in,FontSprite& obj);

}

#endif

