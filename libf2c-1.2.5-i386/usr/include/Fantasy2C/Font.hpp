#ifndef __F2C_FONT_HPP_INCLUDED
#define __F2C_FONT_HPP_INCLUDED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <Fantasy2C/Basic.hpp>
#include <Fantasy2C/Color.hpp>
#include <Fantasy2C/Bitmap.hpp>

template class DLL std::allocator<F2C::uint>;
template class DLL std::vector<F2C::uint, std::allocator<F2C::uint> >;

namespace F2C{

/**
*@class TTFFont
*@brief Loading TTF(True Type Font) file and Creates a BitmapFont.
*/
class DLL TTFFont{
    private:
        void open(Bitmap& bitmap,std::string filename, uint size,Color color,uint charsperwidth,uint charsperheight);

        class DLL_LOCAL TTFLibrary{
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
		Rect char_rect[256];
		uint charsperwidth;
        uint charsperheight;

		void BuildFont(Rect* outarray,size_t outarraysize,
                       const Bitmap& bitmapfont,
                       uint charpw,uint charph,uint8 alphatolerance);

	public:
        /**
        *@brief default value of Transparency (alpha) tolerance, to determine the spacing between the Character
        *(Is tolerance equal to 0: the whole rectangle of the Character.
        *If the alpha value greater than or equal to the tolerance is measured as the distance from)
        *(default: 5)
        */
        static uint8 defaultAlphaTolerance;

        static uint defaultCharsperW; ///< Standard characters per column (default: 16)
        static uint defaultCharsperH; ///< Standard characters per line (default: 16)
		static std::string defaultName; ///< Default filename (default: Arial)
		static uint defaultSize; ///< Default font size (default: 16)
		static Color defaultColor; ///< Standatd font color (Default: (255,255,255,255))
		/**
		*@brief Default System Font directory \n
		*Windows: C:/WINDOWS/Fonts/ \n
		*Linux:   /usr/share/fonts/truetype/ \n
		*MacOS:   /Library/Fonts/ \n
		*/
		static std::string defaultdir;

        /**
        *@brief Transparency (alpha) tolerance, to determine the spacing between the Character
        *(Is tolerance equal to 0: the whole rectangle of the Character.
        *If the alpha value greater than or equal to the tolerance is measured as the distance from)
        */
        uint8 alphaTolerance;

        TTFFont(); ///< Default constructor

        /**
        *@param filename TTF filename
        *@param size Font size
        *@param color Font color
        *@param charsperwidth Characters per column
        *@param charsperheight Characters per line
        *@param usesystemdir Searches the file in the system font directory (TTFFont::defaultdir)
        *@exception LogError, If the file can not be loaded.
        *@brief Load a true type font file and creates a BitmapFont.
        */
		TTFFont(std::string filename,
                uint size = TTFFont::defaultSize,
                const Color& color  = TTFFont::defaultColor,
                uint charsperwidth = TTFFont::defaultCharsperW,
                uint charsperheight = TTFFont::defaultCharsperH,
                bool usesystemdir = false);
        /**
        *@param filename TTF filename
        *@param size Font size
        *@param color Font color
        *@param charsperwidth Characters per column
        *@param charsperheight Characters per line
        *@param usesystemdir Searches the file in the system font directory (TTFFont::defaultdir)
        *@exception LogError, If the file can not be loaded.
        *@brief Load a true type font file and creates a BitmapFont.
        */
		void loadFile(std::string filename,
                        uint size = TTFFont::defaultSize,
                        const Color& color  = TTFFont::defaultColor,
                        uint charsperwidth = TTFFont::defaultCharsperW,
                        uint charsperheight = TTFFont::defaultCharsperH,
                        bool usesystemdir = false);

        /**
        *@param filename TTF filename
        *@param size Font size
        *@param usesystemdir Searches the file in the system font directory (TTFFont::defaultdir)
        *@exception LogError, If the file can not be loaded.
        *@brief Load a true type font file and creates a BitmapFont.
        */
		void loadFile(std::string filename,
                        uint size,
                        bool usesystemdir);

        /**
        *@param bitmap Bitmap
        *@param charsperwidth Characters per column
        *@param charsperheight Characters per line
        *@brief Creates a BitmapFont.
        */
		void loadBitmap(const Bitmap& bitmap,
                        uint charsperwidth = TTFFont::defaultCharsperW,
                        uint charsperheight = TTFFont::defaultCharsperH);


        /**
        *@param cbitmap Destination bitmap
        *@brief Copy BitmapFont into destination bitmap.
        */
        void copyBitmap(Bitmap& cbitmap) const;
        std::string getFilename() const; ///< getMethode: TTF Filename
		uint getSize() const; ///< getMethode: Font Size
		Color getColor() const; ///< getMethode: Font Color
		const Bitmap& getBitmap() const; ///< getMethode: BitmapFont
		/**
		*@param c Character (ASCII: 0-255)
		*@brief getMethode: The size (in pixel) of a Character.
		*/
		Rect getCharSize(uint8 c) const;
		const Rect* getCharsSize() const; ///< getMethode: get all size of Character(in pixel) as array (size: 256)
		uint getCharsperWidth() const; ///< getMethode: Chars per width
		uint getCharsperHeight() const; ///< getMethode: Chars per height

		friend std::ostream& operator<<(std::ostream &out,const TTFFont& obj);
        friend std::istream& operator>>(std::istream &in, TTFFont& obj);
};

/**
*@param out Output stream
*@param obj Object
*@brief Write the Object into output stream.
*/
std::ostream& DLL operator<<(std::ostream &out,const TTFFont& obj);

/**
*@param in Input stream
*@param obj Object
*@brief Read the Object from input stream.
*/
std::istream& DLL operator>>(std::istream &in, TTFFont& obj);

}

#endif

