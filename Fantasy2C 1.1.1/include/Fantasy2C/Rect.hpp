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
};

}

#endif

