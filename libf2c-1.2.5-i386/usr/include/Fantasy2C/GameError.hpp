#ifndef __F2C_GAMEERROR_HPP_INCLUDED
#define __F2C_GAMEERROR_HPP_INCLUDED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <Fantasy2C/Basic.hpp>
#include <string>
#include <iostream>
#include <fstream>

#if defined(__FUNCTION__)
    #if defined(_DEBUG)
        #define SETLOGERROR(error,string) error.setError(__FILE__,__FUNCTION__,__LINE__,string)
    #else
        #define SETLOGERROR(error,string) error.setError(string)
	#endif
#else
	#if defined(_DEBUG)
        #define SETLOGERROR(error,string) error.setError(__FILE__,"",__LINE__,string)
    #else
        #define SETLOGERROR(error,string) error.setError(string)
	#endif
#endif

namespace F2C{

/**
*@brief Error code
*/
namespace ErrorCode{
    typedef enum Error_Code{
        NO_ERRORCODE = 0, ///< No Error
        ERRORCODE = -1, ///< General Error
        NO_SUCH_FILE_OR_DIR = -2, ///< No such file or directory
        FILESTREAM_ERROR = -3, ///< file-stream is NULL (possibly error by loading)
        OPENIL_ERROR = -4, ///< Error in OpenIL function (ilLoad(),ilLoadL(),ilConvertImage(),...)
        FREETYPE_ERROR = -5, ///< Error in FreeType2 function (FT_New_Face(),FT_Init_FreeType(),...)
        AUDIERE_ERROR = -6  ///< Error in Audiere function (OpenDevice(),openStream(),openSound(),...)
    } Error_Code;
}

/**
*@class LogError
*@brief Writing log files and exception handler. \n
*@brief \n
*@brief Debug Version (with _DEBUG Macro): \n
*@code #define SETLOGERROR(error,string) error.setError(__FILE__,__FUNCTION__,__LINE__,string) @endcode
*@brief Sets the error-string, filename, line, and the function name. \n
*@brief \n
*@brief Debug Version (without _DEBUG Macro): \n
*@code #define SETLOGERROR(error,string) error.setError(string) @endcode
*@brief Sets only error-string.
*/
class DLL LogError{
	private:
		class DLL LEError{
		    public:
                LEError();

                std::string file;
                std::string funk;
                uint line;
                void* ptr;
                ErrorCode::Error_Code code;
                std::string error;
		} error;

	public:
		LogError(){}; ///< Default destructor

		static std::string filename; ///< Log file name (default: logfile)
		static bool writelog; ///< Logfile write allowed/forbidden (default: true)

        static void ClearLog(); ///< Clears the text in the Log file.
        static void writeString(std::string string); ///< @param string Text @brief Writes a text into the Log text.
        static std::string getOpenGLError(); ///< getMethode: OpenGL Error

		void writeError(); ///< Creates and writes the log file.

        /**
        *@param file Filename
        *@param func Function name
        *@param line Line
        *@param string Text
        *@brief Sets the filename, line, function, and the Log text.
        */
		void setError(std::string file,std::string func,uint line,std::string string);
		/**
        *@param file Filename
        *@param func Function name
        *@param line line
        *@param ptr Adress
        *@param string Text
        *@brief Sets the file name, line, function, and the Log text and the adress.
        */
		void setError(std::string file,std::string func,uint line,void* ptr,std::string string);
		std::string getError() const; ///< getMethode: Log text
		void setError(std::string string); ///< @param string LogFile Text @brief setMethode: Set the Log text
        void setErrorCode(ErrorCode::Error_Code code); ///< @param code Error Code @brief setMethode: Set ErrorCode
        friend std::ostream& operator<<(std::ostream &out,const LogError& obj);
        friend std::istream& operator>>(std::istream &in,LogError& obj);

};

/**
*@param out Output stream
*@param obj Object
*@brief Write the Object into output stream. (dont write pointer (Viewport,clip_rect))
*/
std::ostream& DLL operator<<(std::ostream &out,const LogError& obj);

/**
*@param in Input stream
*@param obj Object
*@brief Read the Object from input stream. (dont read pointer (Viewport,clip_rect))
*/
std::istream& DLL operator>>(std::istream &in,LogError& obj);

}

#endif



