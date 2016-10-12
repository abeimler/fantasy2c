#ifndef __BASIC_H_INCLUDED
#define __BASIC_H_INCLUDED

#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cmath>

#include <string>
#include <vector>
#include <map>
#include <stack>
#include <iostream>
#include <sstream>
#include <iomanip>

#include <Fantasy2C/Basic.hpp>
#include <Fantasy2C/Window.hpp>
#include <Fantasy2C/Input.hpp>
#include <Fantasy2C/ShaderGL.hpp>
#include <Fantasy2C/ArraySprite.hpp>
#include <Fantasy2C/Sprite.hpp>
#include <Fantasy2C/SimpleSprite.hpp>
#include <Fantasy2C/FontSprite.hpp>
#include <Fantasy2C/Plane.hpp>
#include <Fantasy2C/Audio.hpp>
#include <Fantasy2C/Font.hpp>


//Macro Load Image
#define F2CLoadBitmap(bitmap,filename); \
    try{ \
        bitmap.loadFile(filename);  \
    }catch(F2C::LogError& er){ \
        SETLOGERROR(er,er.getError()); \
        er.writeError(); \
    }

//Macro Load Audiofile
#define F2CLoadAudioFile(audiofile,filename); \
    try{ \
        audiofile.loadFile(filename);  \
    }catch(F2C::LogError& er){ \
        SETLOGERROR(er,er.getError()); \
        er.writeError(); \
    }

//Macro Load Fontfile
#define F2CLoadFontFile(fontfile,filename); \
    try{ \
        fontfile.loadFile(filename);  \
    }catch(F2C::LogError& er){ \
        SETLOGERROR(er,er.getError()); \
        er.writeError(); \
    }

#define F2CLoadBitmapintoSprite(sprite,filename) \
    if(true){ \
        F2C::Bitmap* __sprite_bitmap = new F2C::Bitmap; \
        F2CLoadBitmap((*__sprite_bitmap),filename); \
        sprite.setBitmap(__sprite_bitmap); \
        delete __sprite_bitmap; \
    }

///returns strings that are separated by one letter
void getStringsSeparatedByLetter(std::vector<std::string>& words,std::string word,std::string letter);

///Get random Number
int random(int lowest_number, int highest_number);

template<class T>
std::ostream& operator<< (std::ostream& out,std::vector<T>& vec){
    out << vec.size();
    for(size_t i = 0;i < vec.size();++i)
        out << vec[i];
    return out;
}

template<class T>
std::istream& operator>> (std::istream& in,std::vector<T>& vec){
    size_t size = 0;
    in >> size;
    vec.resize(size);
    for(size_t i = 0;i < vec.size();++i){
        in >> vec[i];
    }
    return in;
}


namespace F2C{

void loadFragmentShader(std::string filename); //Load Fragment Shader file
void loadVertexShader(std::string filename); //Load Vertex Fragment file
void loadShader(std::string frag,std::string vertex); //Load Fragment und Vertex shader file

}

#endif // BASIC_H_INCLUDED
