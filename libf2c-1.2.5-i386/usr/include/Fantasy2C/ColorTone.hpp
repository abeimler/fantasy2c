#ifndef __F2C_COLORTONE_HPP_INCLUDED
#define __F2C_COLORTONE_HPP_INCLUDED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <Fantasy2C/Basic.hpp>
#include <Fantasy2C/Color.hpp>

namespace F2C{

/**
*@class ColorTone
*@brief Colortone (CMY-RGB) \n
*Cyan -255-0,0-255 Red \n
*Magenta -255-0,0-255 Green \n
*Yellow -255-0,0-255 Blue \n
*Grayscale 0-255
*/
class DLL ColorTone{
	private:
		int16 red;
		int16 green;
		int16 blue;

	public:
		uint8 grayscale; ///< Grayscale value (or the tranzperenz the shader generated image).

		ColorTone(); ///< Default constructor

		/**
		*@param red Cyan(-255 - 0)/Red(0 - 255).
		*@param green Magenta(-255 - 0)/Green(0 - 255).
		*@param blue Yellow(-255 - 0)/Blue(0 - 255).
		*@param grayscale Grayscale
		*@brief Sets the color RGB (CMY) and the grayscale value.
		*/
		ColorTone(int16 red,int16 green,int16 blue,uint8 grayscale);
		/**
		*@param red Cyan(-255 - 0)/Red(0 - 255).
		*@param green Magenta(-255 - 0)/Green(0 - 255).
		*@param blue Yellow(-255 - 0)/Blue(0 - 255).
		*@brief Sets the color RGB (CMY).
		*/
		ColorTone(int16 red,int16 green,int16 blue);
		/**
		*@param red Cyan(-255 - 0)/Red(0 - 255).
		*@param green Magenta(-255 - 0)/Green(0 - 255).
		*@param blue Yellow(-255 - 0)/Blue(0 - 255).
		*@param grayscale Grayscale
		*@brief setMedthode: Sets the color RGB (CMY) and the grayscale value.
		*/
		void set(int16 red,int16 green,int16 blue,uint8 grayscale);
		/**
		*@param red Cyan(-255 - 0)/Red(0 - 255).
		*@param green Magenta(-255 - 0)/Green(0 - 255).
		*@param blue Yellow(-255 - 0)/Blue(0 - 255).
		*@brief setMethode: Sets the color RGB (CMY).
		*/
		void set(int16 red,int16 green,int16 blue);

		/**
		*@param color RGB Color
		*@brief setMethode: Set the color RGB (not CMY)
		*/
		void set(const Color& color);

        /**
        *@param red Cyan/Rot @brief setMethode: Set Cyan(-255 - 0)/Red(0 - 255).
        */
		void setRed(int16 red);
		/**
        *@param green Magenta/Gruen @brief setMethode: Set Magenta(-255 - 0)/Green(0 - 255).
        */
		void setGreen(int16 green);
		/**
        *@param blue Yellow/Blau @brief setMethode: Set Yellow(-255 - 0)/Blue(0 - 255).
        */
		void setBlue(int16 blue);

        bool operator == (const ColorTone& color) const; ///< Comparison Operator: ==
		bool operator != (const ColorTone& color) const; ///< Comparison Operator: !=
		const ColorTone& operator += (const ColorTone& color); ///< Combined assignment operator: +=
		const ColorTone& operator -= (const ColorTone& color); ///< Combined assignment operator: -=

		int16 getRed() const; ///< getMethode: Cyan/Red
		int16 getGreen() const; ///< getMethode: Magenta/Green
		int16 getBlue() const; ///< getMethode: Yellow/Blue

		/**
        *@param tone ColorTone
        *@param outHSV target referece Varaible
        *@brief Convert ColorTone-Klasse in HSV.
        */
		static void ColorTonetoHSV(const ColorTone& tone,int (&outHSV)[3]);
		/**
        *@param tone ColorTone
        *@param outRGB target referece Varaible
        *@brief Convert ColorTone-Klasse in RGB.
        */
		static void ColorTonetoRGB(const ColorTone& tone,ubyte (&outRGB)[3]);

		friend std::ostream& operator<<(std::ostream &out,const ColorTone& obj);
        friend std::istream& operator>>(std::istream &in, ColorTone& obj);

        friend ColorTone operator+(const ColorTone& obj1,const ColorTone& obj2);
        friend ColorTone operator-(const ColorTone& obj1,const ColorTone& obj2);
};

ColorTone DLL operator+(const ColorTone& obj1,const ColorTone& obj2); ///< operator: +
ColorTone DLL operator-(const ColorTone& obj1,const ColorTone& obj2); ///< operator: -

/**
*@param out Output stream
*@param obj Object
*@brief Write the Object into output stream.
*/
std::ostream& DLL operator<<(std::ostream &out,const ColorTone& obj);

/**
*@param in Input stream
*@param obj Object
*@brief Read the Object from input stream.
*/
std::istream& DLL operator>>(std::istream &in, ColorTone& obj);

}

#endif

