#ifndef __F2C_COLOR_HPP_INCLUDED
#define __F2C_COLOR_HPP_INCLUDED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include "Basic.hpp"

namespace F2C{

/**
*@class Color
*@brief Color (RGBA) \n
*Red 0-255 \n
*Green 0-255 \n
*Blue 0-255 \n
*Alpha 0-255 \n
*/
class DLL Color{
	public:
		uint8 red; ///< Color red
		uint8 green; ///< Color green
		uint8 blue; ///< Color blue
		uint8 alpha; ///< Color alpha

		Color(); ///< Default constructor

		/**
		*@param red Red
		*@param green Green
		*@param blue Blue
		*@param alpha Alpha
		*@brief Set Colors RGBA.
		*/
		Color(uint8 red,uint8 green,uint8 blue,uint8 alpha);
		/**
		*@param red Red
		*@param green Green
		*@param blue Blue
		*@brief Set Colors RGB.
		*/
		Color(uint8 red,uint8 green,uint8 blue);

		/**
		*@param red Red
		*@param green Green
		*@param blue Blue
		*@param alpha Alpha
		*@brief setMethode: Set Colors RGBA.
		*/
		void set(uint8 red,uint8 green,uint8 blue,uint8 alpha);
		/**
		*@param red Red
		*@param green Green
		*@param blue Blue
		*@brief setMethode: Set Colors RGB.
		*/
		void set(uint8 red,uint8 green,uint8 blue);

		bool operator == (const Color& color) const; ///< Comparison Operator: ==
		bool operator != (const Color& color) const; ///< Comparison Operator: !=
		const Color& operator += (const Color& color); ///< Combined assignment operator: +=
		const Color& operator -= (const Color& color); ///< Combined assignment operator: -=

        /**
        *@param h Hue (0-360)
        *@param s Saturation (0-255)
        *@param v Value (0-255)
        *@param outRGB target referece Varaible
        *@brief Convert HSV in RGB.
        */
        static void HSVtoRGB(int h,uint8 s, uint8 v,ubyte (&outRGB)[3]);
        /**
        *@param r Red (0-255)
		*@param g Green (0-255)
		*@param b Blue (0-255)
        *@param outHSV target referece Varaible
        *@brief Convert RGB in HSV.
        */
		static void RGBtoHSV(uint8 r,uint8 g,uint8 b,int (&outHSV)[3]);
		/**
        *@param c Cyan (-255-0)
		*@param m Magenta (-255-0)
		*@param y Yellow (-255-0)
        *@param outRGB target referece Varaible
        *@brief Convert CMY in RGB.
        */
		static void CMYtoRGB(int c,int m,int y,ubyte (&outRGB)[3]);
};

}

#endif

