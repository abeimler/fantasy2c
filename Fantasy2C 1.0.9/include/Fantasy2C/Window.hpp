#ifndef __F2C_WINDOWS_HPP_INCLUDED
#define __F2C_WINDOWS_HPP_INCLUDED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include "Basic.hpp"
#include <fstream>
#include <string>

namespace F2C{

/**
*@class Window
*@brief Singleton pattern:
*Create window and loading shader files.
*/
class DLL Window{
    private:
        double FPS;
        double startTime;
        double startTick;
        double activTime;
        unsigned int frames;
        bool shading_enabled;
        bool vbo_enabled;
        bool multitexel_enabled;
        int maxTexelUnits;
        bool showmouse;

        static Window* _instance;

        Window();
        Window(const Window& copy);
        Window& operator=(const Window copy);

        void setupExtensionsShader();
        void setupExtensionsVBO();
        void setupExtensionsMultiTexel();
        void printLog(uint obj,std::string* error);
        int loadshader(std::string filename,std::string& ShaderSource);

    public:
        GLhandleARB programObj; ///< Handle of ARB program object.
        GLhandleARB fragmentShader; ///< Handle of ARB fragment object.
        GLhandleARB vertexShader; ///< Handle of ARB vertex object.

        static Window* getInstance(); ///< getMethode: Instance

        uint getFrame(); ///< getMethode: Current Frame.

        void UpdateGLScreen(); ///< Updates the window. (Buffer Swapping)
        /**
        *@param wndwidth Width of window
        *@param wndheight height of window
        *@param screenwidth Width of the resolution
        *@param screenheight Height of the resolution
        *@brief setMethode: Sets the size of the window and the resolution.
        */
        void ReSize(uint wndwidth, uint wndheight,uint screenwidth,uint screenheight);
        void InitGL(); ///< Initializes the OpenGL functions.

        /**
        *@return -1, This extension string indicates that the OpenGL Shading Language,version 1.00, is supported.
        *@return -2, GL_ARB_shader_objects extension was not found.
        *@return -3, not support shader.
        *@brief Initialisiert die ARB Shader Funktionen.
        */
        int InitGLShader();

        /**
        *@return -1, Can't open the Shaderfile.
        *@return -2, The Shaderfile is empty.
        *@param shaderfilename Dateiname
        *@param error Ziehl-Varaible: Log Text
        *@brief Ladet die Fragmentshader Datei und erstellt das ARB Fragmentobjekt.
        *Der Build Log beim erstellen des ARB Fragmentobjekt wird in der "error" Variable gespeichert.
        */
        int LoadGLFragmentShader(std::string shaderfilename,std::string* error);
        /**
        *@return -1, Can't open the Shaderfile.
        *@return -2, The Shaderfile is empty.
        *@param shaderfilename Dateiname
        *@param error Ziehl-Varaible: Log Text
        *@brief Ladet die Vertexshader Datei und erstellt das ARB Vertexobjekt.
        *Der Build Log beim erstellen des ARB Vertexobjekt wird in der "error" Variable gespeichert.
        */
        int LoadGLVertexShader(std::string shaderfilename,std::string* error);

        /**
        *@param error Target reference varaible: Log text
        *@brief Creates the ARB shader program object loaded by the ARB and ARB fragment object Vertex object.
        */
        void CreateShaderProgram(std::string* error);

        void ClearGLScene(); ///< Clear Window. (glClear)
        void ShutdownGLWindow(); ///< Exits the window, and deletes it from memory.
        /**
        *@param title Window Title
        *@param width Width of the window and the resolution.
        *@param height Height of the window and the resolution.
        *@param bits Color depth (8,12,16,24 or 32)
        *@param fullscreen In full-screen Start On / Off.
        *@brief Creates the window
        */
        bool CreateGLWindow(std::string title,uint width,uint height, int bits, bool fullscreen);

        /**
        *@param x X coordinate
        *@param y Y coordinate
        *@brief setMethode: Set window position.
        */
        void setWindowPosition(int x,int y);
        /**
        *@param wndwidth Width of window
        *@param wndheight Height of window
        *@brief setMethode: Sets size of window.
        */
        void setWindowSize(uint wndwidth, uint wndheight);
        void setWindowTitle(std::string title); ///< @param title Window Title @brief setMethode: Sets Window Title

        /**
        *@param paramwindow Window-Param
        *@param value Value
        *@brief setMethode: Value of the Window Param (1 = true 0 = false)
        *Note: Before the window is created, will have to set the Window Param.
        */
        void setWindowHint(WindowProperty::ParamWindow paramwindow,int value);

        int getWindowParam(WindowProperty::ParamWindow param);///< @param param Window-Param @brief getMethode: Value of the Window Param (1 = true 0 = false)

        /**
        *@param width Target reference varaible: Width of window
        *@param height Target reference varaible: Height of window
        *@brief getMethode: Size of Window.
        */
        void getWindowSize(int* width,int* height);
        /**
        *@param wndwidth Target reference varaible: Width of window
        *@param wndheight Target reference varaible: Height of window
        *@param screenwidth Target reference varaible: Width of the resolution
        *@param screenheight Target reference varaible: Height of the resolution
        *@brief setMethode: Size of the window and the resolution.
        */
        void getSize(int* wndwidth, int* wndheight,uint* screenwidth,uint* screenheight);
        /**
        *@param screenwidth Width of the resolution
        *@param screenheight Height of the resolution
        *@brief setMethode: Sets the size of resolution.
        */
        void getScreenSize(uint* screenwidth,uint* screenheight);

        void startTicks(); ///< Starts ticks
        double getTicks(); ///< Returns the current ticks (in seconds)

        void setTime(double time); ///< setMethode: Sets the time (in seconds)
        double getTime(); ///< getMethode: Current time (in seconds)
        void Sleep(double time); ///< @param time Time (in seconds) @brief Sometimes it can be useful to put a program to sleep for a short time. It can be used to reduce the CPU load in various situations.

        double getFPS(); ///< getMethode: FPS (Frames per second)
        bool getSupportedShader(); ///< getMethode: Shader supported Yes / No.
        bool getSupportedVBO(); ///< getMethode: VBO(Vertex Buffer Object) supported Yes / No.
        bool getSupportedMultiTexel(); ///< getMethode: MultiTexturing supported Yes / No.
        int getMaxTexelUnits(); ///< getMethode: Maximum number of texel pipelines.
        void showMouseCursor(bool show);///< @param show Hides mouse cursor @brief Hides the mouse cursor.
        bool getShowMouseCursor(); ///< getMethode: Hides mouse cursor
};

}

#endif // __WINDOWS_H


