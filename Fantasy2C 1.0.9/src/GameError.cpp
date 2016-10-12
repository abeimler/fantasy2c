#include "GameError.hpp"

namespace F2C{

std::string LogError::filename = "logfile.txt";
bool LogError::writelog = true;

void LogError::setError(std::string string){this-> error.error = string;}
std::string LogError::getError() const {return this->error.error;}

void LogError::ClearLog(){
   std::ofstream outfile;
   outfile.open (LogError::filename.c_str());
   outfile.clear();
   outfile.close();
}

LogError::LEError::LEError():
    file(""),
    funk(""),
	line(0),
	ptr(NULL),
	error("")
{}

void LogError::writeError(){
	if (LogError::writelog){
		std::ofstream outfile;
		outfile.open (LogError::filename.c_str(),std::ios_base::out | std::ios_base::app);
		outfile << "Filename: " << this->error.file << std::endl
				<< "Adress: " << this->error.ptr << std::endl
				<< "Function: " << this->error.funk << std::endl
				<< "Line: " << this->error.line << std::endl
				<< "Log: " << std::endl
				<< this->error.error << std::endl;
		outfile.close();
	}
}

void LogError::writeString(std::string string){
	if (!string.empty() && LogError::writelog){
		std::ofstream outfile;
		outfile.open (LogError::filename.c_str(),std::ios_base::out | std::ios_base::app);
		outfile << string;
		outfile.close();
	}
}

void LogError::setError(std::string file,std::string funk,uint line,std::string string){
	this->error.file = file;
	this->error.funk = funk;
	this->error.line = line;
	this->error.ptr = NULL;
	this->error.error = string;
}

void LogError::setError(std::string file,std::string funk,uint line,void* ptr,std::string string){
	this->error.file = file;
	this->error.funk = funk;
	this->error.line = line;
	this->error.ptr = ptr;
	this->error.error = string;
}

};
