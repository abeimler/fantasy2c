#ifndef __F2C_GAMEERROR_HPP_INCLUDED
#define __F2C_GAMEERROR_HPP_INCLUDED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include "Basic.hpp"
#include <string>
#include <iostream>
#include <fstream>

#if defined(__FUNCTION__)
	#define SETLOGERROR(error,string) error.setError(__FILE__,__FUNCTION__,__LINE__,string)
	#define P_SETLOGERROR(error,pointer,string) error.setError(__FILE__,__FUNCTION__,__LINE__,pointer,string)
#else
	#define SETLOGERROR(error,string) error.setError(__FILE__,"",__LINE__,string)
	#define P_SETLOGERROR(error,pointer,string) error.setError(__FILE__,"",__LINE__,pointer,string)
#endif

namespace F2C{

/**
*@class LogError
*@brief Writing log files and exception handler.
*@brief \n
*@code #define SETLOGERROR(error,string) error.setError(__FILE__,__FUNCTION__,__LINE__,string) @endcode
*@brief Sets the filename, line, and the function name.
*@brief \n
*@code #define P_SETLOGERROR(error,pointer,string) error.setError(__FILE__,__FUNCTION__,__LINE__,pointer,string) @endcode
*@brief Sets the filename, line, function name, and the address.
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
                std::string error;
		};
		LEError error;

	public:
		LogError(){}; ///< Default destructor

		static std::string filename; ///< Log file name (default: "logfile.txt")
		static bool writelog; ///< Logfile write allowed/forbidden (default: true)

        static void ClearLog(); ///< Clears the text in the Log file.
        static void writeString(std::string string); ///< @param string Text @brief Writes a text into the Log text.

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

};

}

#endif



