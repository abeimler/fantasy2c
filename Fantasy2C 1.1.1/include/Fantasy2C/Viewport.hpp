#ifndef __F2C_VIEWPORT_HPP_INCLUDED
#define __F2C_VIEWPORT_HPP_INCLUDED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <Fantasy2C/Basic.hpp>
#include <Fantasy2C/Rect.hpp>
#include <Fantasy2C/Color.hpp>
#include <Fantasy2C/ColorTone.hpp>

namespace F2C{

/**
*@class Viewport
*@brief Additional show, Z-coordinate, colortone-Variable, and a clip_rect.
*/
class DLL Viewport{
	public:
		Viewport(); ///< Default constructor

		/**
		*@param x X-coordinate
        *@param y Y-coordinate
        *@param width Width
        *@param height Height
        *@brief Set chip_rect
		*/
		Viewport(int x,int y,uint width,uint height);
		/**
		*@param rect chip_rect
        *@brief Set chip_rect
		*/
		Viewport(const Rect& rect);

		Rect clip_rect; ///< Clipping Rect, Cutting the sprites on the screen the desired section or window.
		bool show; ///< Show Sprite On/Off
		int z; ///< Z-coordinate
		ColorTone tone; ///<  Color tone

};

}

#endif

