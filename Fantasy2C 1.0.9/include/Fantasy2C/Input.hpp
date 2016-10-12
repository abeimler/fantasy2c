#ifndef __F2C_INPUT_HPP_INCLUDED
#define __F2C_INPUT_HPP_INCLUDED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include "Basic.hpp"

namespace F2C{

/**
*@class Input
*@brief Singleton pattern:
*Input Handle from the keyboard, mouse, joystick and Window.
*/
class DLL Input{
    private:
        bool presskeys[319];
        bool keys[319];
        bool repeaton;

        static void GLFWCALL keyhandler( int key, int action );

        static Input* _instance;

        Input();
        Input(const Input& copy);
        Input& operator=(const Input& copy);

    public:
        static Input* getInstance(); ///< getmethode: Instance

        bool InitInput(); ///< @return Success / failure @brief Initializes the input functions.
        void update(); ///< update Input Handle.

        /**
        *@param x Target reference variable: X-Coordinate
        *@param y Target reference variable: Y-Coordinate
        *@brief getMethode: Mouse position
        */
        void getMousePos(int* x,int* y);

        /**
        *@param ckey Character
        *@brief getMethode: Pressed / released (also query for multiple keys simultaneously)
        */
        bool getPressKey(char ckey);
        /**
        *@param key Special Button
        *@brief getMethode: Pressed / released (also query for multiple keys simultaneously)
        */
        bool getPressKey(KeyboardEvent::Keyboard key);

        /**
        *@param ckey Character
        *@brief getMethode: Pressed / released (compulsive from RepeatMode)
        */
        bool getRepeatKey(char ckey);
        /**
        *@param key Special Button
        *@brief getMethode: Pressed / released (compulsive from RepeatMode)
        */
        bool getRepeatKey(KeyboardEvent::Keyboard key);

        const bool* getRepeatKeyArray(); ///< getMethode: Array of Repeat Keys (size: 319 = 256 (ASCII Chars) + 63 (Special Keys(ESC,Space,Enter,....)) )
        const bool* getPressKeyArray(); ///< getMethode: Array of Pressed Keys (size: 319 = 256 (ASCII Chars) + 63 (Special Keys(ESC,Space,Enter,....)) )
        size_t getSizeKeyArray(); ///< getMethode: Size of keyarray: 319 = 256 (ASCII Chars) + 63 (Special Keys(ESC,Space,Enter,....))

        /**
        *@param on RepeatMode
        *@brief setMethode: set Keyboard RepeatMode On/Off.
        *If RepeatMode is on the pressed key is treated as rapidly pressed key.
        *If RepeatMode is off the pressed key is treated as once pressed.
        */
        void setRepeatMode(bool on);

        /**
        *@brief setMethode: Keyboard RepeatMode On/Off
        */
        bool getRepeatMode();

        /**
        *@param mousekey Mouse button
        *@brief getMethode: Pressed / released
        */
        bool getPressMouse(MouseEvent::Mouse mousekey);
        int getMouseWheel(); ///< getMethode: Mouse wheel position

        /**
        *@param joy Joystick nummer
        *@param param Joystick Param
        *@brief getMethode: Value of Joystick Param.
        */
        int getJoystickParam(JoystickEvent::Joystick joy, JoystickEvent::ParamJoystick param );
        /**
        *@param joy Joystick nummer
        *@param pos Target reference variable: Array in which all the axis positions.
        *@param numaxes Numbers of axes
        *@return returns the actual number of axes that were
        *returned, which could be less than numaxes if the joystick does not support all the requested axes, or if
        *the joystick is not connected.
        *@brief To get the current axis positions of the joystick.
        *The position of an axis can be in the range -1.0 to 1.0, where positive values represent right, forward or
        *up directions, while negative values represent left, back or down directions. If a requested axis is not
        *supported by the joystick, the corresponding array element will be set to zero. The same goes for the
        *situation when the joystick is not connected (all axes are treated as unsupported).
        */
        int getJoystickPos(JoystickEvent::Joystick joy, float *pos, int numaxes );
        /**
        *@param joy Joystick nummer
        *@param buttons Target reference variable: Array in which all the buttons.
        *@param numbuttons Gibt an, wie viele tasten zurueckgegeben werden.
        *@return returns the state of joystick buttons instead of axis positions.
        *@brief To get the current buttonsof the joystick.
        *the buttons argument can be either 1 or 0,
        *telling if the corresponding button is currently held down or not.
        *Unsupported buttons will have the value 0.
        */
        int getJoystickButtons(JoystickEvent::Joystick joy, uint8* buttons, int numbuttons );

        /**
        *@param x X-Coordinate
        *@param y X-Coordinate
        *@brief setMethode: Set mouse position.
        */
        void setMousePos(int x,int y);
        void setMouseWheel(int pos);///< @param pos Mouse wheel position @brief setMethode: Set mouse wheel position
};

}

#endif // __INPUT_H
