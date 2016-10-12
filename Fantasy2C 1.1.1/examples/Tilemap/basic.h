#ifndef __BASIC_H_INCLUDED
#define __BASIC_H_INCLUDED

#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cmath>

#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <sstream>

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
    { \
        F2C::Bitmap* __sprite_bitmap = new F2C::Bitmap; \
        F2CLoadBitmap((*__sprite_bitmap),filename); \
        sprite.setBitmap(__sprite_bitmap); \
        delete __sprite_bitmap; \
    }


namespace F2C{

//Get random Number
int random(int lowest_number, int highest_number);

F2C::Rect getStringSize(const F2C::FontSprite& font,std::string str); //Size of String (from FontSprite)
void loadFragmentShader(std::string filename); //Load Fragment Shader file
void loadVertexShader(std::string filename); //Load Vertex Fragment file
void loadShader(std::string frag,std::string vertex); //Load Fragment und Vertex shader file
bool collisionRect(F2C::Rect rect1,F2C::Rect rect2); //2D-collision for 2 Rects

class Timer{
    private:
    double starttime;

    public:
    Timer();
    void reset(); //restart/reset Timer
    double getTime(); //in Sec
};

}
#endif // BASIC_H_INCLUDED
