#ifndef __F2C_FONT_HPP_INCLUDED
#define __F2C_FONT_HPP_INCLUDED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include "Basic.hpp"
#include "Color.hpp"
#include "Bitmap.hpp"

namespace F2C{

#if defined(WIN32) || defined(_Windows) || defined(__WIN32__)
template class DLL std::allocator<uint>;
template class DLL std::vector<uint, std::allocator<uint> >;
#endif

/**
*@class TTFFont
*@brief Loading TTF(True Type Font) file and Creates a BitmapFont.
*/
class DLL TTFFont{
    private:
        void open(Bitmap& bitmap,std::string filename, uint size,Color color,uint charsperwidth,uint charsperheight);

        class DLL TTFLibrary{
            private:
                static FT_Library library_;
            public:
                TTFLibrary();
                virtual ~TTFLibrary();

                FT_Library& getLibrary();
        };
        static TTFLibrary library;
        std::string filename;
		uint size;
		Color color;
		Bitmap bitmap;
		std::vector<uint> heights;
		std::vector<uint> widths;

	public:
        TTFFont(); ///< Default constructor

        /**
        *@param filename TTF filename
        *@param size Font size
        *@param color Font color
        *@param charsperwidth Characters per column
        *@param charsperheight Characters per line
        *@exception LogError, If the file can not be loaded.
        *@brief Load a true type font file and creates a BitmapFont.
        */
		TTFFont(std::string filename,
                uint size = TTFFont::defaultSize,
                const Color& color  = TTFFont::defaultColor,
                uint charsperwidth = TTFFont::defaultCharsperW,
                uint charsperheight = TTFFont::defaultCharsperH);
        /**
        *@param filename TTF filename
        *@param size Font size
        *@param color Font color
        *@param charsperwidth Characters per column
        *@param charsperheight Characters per line
        *@exception LogError, If the file can not be loaded.
        *@brief Load a true type font file and creates a BitmapFont.
        */
		void loadFile(std::string filename,
                        uint size = TTFFont::defaultSize,
                        const Color& color  = TTFFont::defaultColor,
                        uint charsperwidth = TTFFont::defaultCharsperW,
                        uint charsperheight = TTFFont::defaultCharsperH);

        /**
        *@param cbitmap Destination bitmap
        *@brief Copy BitmapFont into destination bitmap.
        */
        void copyBitmap(Bitmap& cbitmap) const;
        std::string getFilename() const; ///< getMethode: TTF Filename
		uint getSize() const; ///< getMethode: Fint Size
		Color getColor() const; ///< getMethode: Font Color
		const Bitmap& getBitmap() const; ///< getMethode: BitmapFont
		/**
		*@param c Character (ASCII: 0-255)
		*@brief getMethode: The size (in pixel) of a Character.
		*/
		Rect getCharSize(uint8 c) const;

        static uint defaultCharsperW; ///< Standard characters per column (default: 16)
        static uint defaultCharsperH; ///< Standard characters per line (default: 16)
		static std::string defaultName; ///< Default filename (default: "Arial.ttf")
		static uint defaultSize; ///< Default font size (default: 16)
		static Color defaultColor; ///< Standatd font color (Default: (255,255,255,255))
};

}

#endif

