#ifndef __F2C_RECT_HPP_INCLUDED
#define __F2C_RECT_HPP_INCLUDED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <Fantasy2C/Basic.hpp>

namespace F2C{

/**
*@class Rect
*@brief Rectangle (x, y, width, height)
*/
class DLL Rect{
	public:
		int x; ///< X-coordinate
		int y; ///< Y-coordinate
		uint width; ///< Width
		uint height; ///< Height

		Rect(); ///< Default constructor

		/**
		*@param x X-coordinate
        *@param y Y-coordinate
        *@param width Width
        *@param height Height
        *@brief Sets the coordinates and size.
		*/
		Rect(int x,int y,uint width,uint height);

		/**
		*@param x X-coordinate
        *@param y Y-coordinate
        *@param width Width
        *@param height Height
        *@brief setMethode: Sets the coordinates and size.
		*/
		void set(int x,int y,uint width,uint height);

        /**
        *@param rect other rect
        *@brief get true, if is collision with rect
        */
		bool collision(const Rect& rect) const;

		friend std::ostream& operator<<(std::ostream &out,const Rect& obj);
        friend std::istream& operator>>(std::istream &in, Rect& obj);
};

/**
*@param out Output stream
*@param obj Object
*@brief Write the Object into output stream.
*/
std::ostream& DLL operator<<(std::ostream &out,const Rect& obj);

/**
*@param in Input stream
*@param obj Object
*@brief Read the Object from input stream.
*/
std::istream& DLL operator>>(std::istream &in, Rect& obj);


/**
*@class Coord
*@brief Coordinate (x,y,z)
*/
class DLL Coord{
	public:
		int x; ///< X-coordinate
		int y; ///< Y-coordinate
		int z; ///< Z-coordinate

		Coord(); ///< Default constructor

		/**
		*@param x X-coordinate
        *@param y Y-coordinate
        *@param z Z-coordinate
        *@brief Sets the coordinates.
		*/
		Coord(int x,int y,int z);

		/**
		*@param x X-coordinate
        *@param y Y-coordinate
        *@param z Z-coordinate
        *@brief setMethode: Sets the coordinates.
		*/
		void set(int x,int y,int z = 0);

        /**
        *@param coord other coord
        *@brief true, if is collision with coord
        */
		bool collision(const Coord& coord) const;

		friend std::ostream& operator<<(std::ostream &out,const Coord& obj);
        friend std::istream& operator>>(std::istream &in, Coord& obj);
};

/**
*@param out Output stream
*@param obj Object
*@brief Write the Object into output stream.
*/
std::ostream& DLL operator<<(std::ostream &out,const Coord& obj);

/**
*@param in Input stream
*@param obj Object
*@brief Read the Object from input stream.
*/
std::istream& DLL operator>>(std::istream &in, Coord& obj);

}

#endif

