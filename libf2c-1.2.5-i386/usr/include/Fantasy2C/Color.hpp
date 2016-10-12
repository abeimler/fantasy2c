#ifndef __F2C_COLOR_HPP_INCLUDED
#define __F2C_COLOR_HPP_INCLUDED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <Fantasy2C/operatorMacros.hpp>
#include <Fantasy2C/Basic.hpp>

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
		*@param rgba 32-Bit color in hex. (0xRRGGBBAA)
		*@brief Set Colors RGBA.
		*/
		Color(uint32 rgba);

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

		uint32 getUint32() const; ///< getMethode: get Color in uint32 Format (in hex: 0xRRGGBBAA)
		operator uint32 () const; ///< cast operator to uint32 (Color::getUint32())

		bool operator == (const Color& color) const; ///< Comparison Operator: ==
		bool operator != (const Color& color) const; ///< Comparison Operator: !=
		bool operator < (const Color& color) const; ///< Comparison Operator: <
		const Color& operator += (const Color& color); ///< Combined assignment operator: +=
		const Color& operator -= (const Color& color); ///< Combined assignment operator: -=
		const Color& operator *= (const Color& color); ///< Combined assignment operator: *=
		const Color& operator /= (const Color& color); ///< Combined assignment operator: /=

		const Color& operator += (uint8 col); ///< Combined assignment operator: += (col applies to all colors (RGBA))
		const Color& operator -= (uint8 col); ///< Combined assignment operator: -= (col applies to all colors (RGBA))
		const Color& operator *= (uint8 col); ///< Combined assignment operator: *= (col applies to all colors (RGBA))
		const Color& operator /= (uint8 col); ///< Combined assignment operator: /= (col applies to all colors (RGBA))

		const Color& operator *= (float col); ///< Combined assignment operator: *= (col applies to all colors (RGBA))
		const Color& operator /= (float col); ///< Combined assignment operator: /= (col applies to all colors (RGBA))

		const Color& operator *= (double col); ///< Combined assignment operator: *= (col applies to all colors (RGBA))
		const Color& operator /= (double col); ///< Combined assignment operator: /= (col applies to all colors (RGBA))

        /**
        *@param h Hue (0-360)
        *@param s Saturation (0-255)
        *@param v Value (0-255)
        *@param outRGB target referece Varaible
        *@brief Convert HSV in RGB.
        */
        static void HSVtoRGB(int h,uint8 s, uint8 v,ubyte* outRGB);
        /**
        *@param r Red (0-255)
		*@param g Green (0-255)
		*@param b Blue (0-255)
        *@param outHSV target referece Varaible
        *@brief Convert RGB in HSV.
        */
		static void RGBtoHSV(uint8 r,uint8 g,uint8 b,int* outHSV);
		/**
        *@param c Cyan (-255-0)
		*@param m Magenta (-255-0)
		*@param y Yellow (-255-0)
        *@param outRGB target referece Varaible
        *@brief Convert CMY in RGB.
        */
		static void CMYtoRGB(int c,int m,int y,ubyte* outRGB);

		friend std::ostream& operator<<(std::ostream &out,const Color& obj);
        friend std::istream& operator>>(std::istream &in, Color& obj);

        friend Color operator+(const Color& obj1,const Color& obj2);
        friend Color operator-(const Color& obj1,const Color& obj2);
        friend Color operator*(const Color& obj1,const Color& obj2);
        friend Color operator/(const Color& obj1,const Color& obj2);

        friend Color operator+(const Color& obj1,uint8 col);
        friend Color operator-(const Color& obj1,uint8 col);
        friend Color operator*(const Color& obj1,uint8 col);
        friend Color operator/(const Color& obj1,uint8 col);

        friend Color operator*(const Color& obj1,float col);
        friend Color operator/(const Color& obj1,float col);

        friend Color operator*(const Color& obj1,double col);
        friend Color operator/(const Color& obj1,double col);
};

Color DLL operator+(const Color& obj1,const Color& obj2); ///< operator: +
Color DLL operator-(const Color& obj1,const Color& obj2); ///< operator: -
Color DLL operator*(const Color& obj1,const Color& obj2); ///< operator: *
Color DLL operator/(const Color& obj1,const Color& obj2); ///< operator: /

Color DLL operator+(const Color& obj1,uint8 col); ///< operator: + (col applies to all colors (RGBA))
Color DLL operator-(const Color& obj1,uint8 col); ///< operator: - (col applies to all colors (RGBA))
Color DLL operator*(const Color& obj1,uint8 col); ///< operator: * (col applies to all colors (RGBA))
Color DLL operator/(const Color& obj1,uint8 col); ///< operator: / (col applies to all colors (RGBA))

Color DLL operator*(const Color& obj1,float col); ///< operator: * (col applies to all colors (RGBA))
Color DLL operator/(const Color& obj1,float col); ///< operator: / (col applies to all colors (RGBA))

Color DLL operator*(const Color& obj1,double col); ///< operator: * (col applies to all colors (RGBA))
Color DLL operator/(const Color& obj1,double col); ///< operator: / (col applies to all colors (RGBA))

/**
*@param out Output stream
*@param obj Object
*@brief Write the Object into output stream.
*/
std::ostream& DLL operator<<(std::ostream &out,const Color& obj);

/**
*@param in Input stream
*@param obj Object
*@brief Read the Object from input stream.
*/
std::istream& DLL operator>>(std::istream &in, Color& obj);

}

#endif

