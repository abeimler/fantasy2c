#include "basic.h"

namespace F2C{

F2C::Input& InApp = *F2C::Input::getInstance();
F2C::Window& WinApp = *F2C::Window::getInstance();

int random(int lowest_number, int highest_number){
    if(lowest_number == highest_number)
        return lowest_number;
    srand(static_cast<F2C::uint>(floor(F2C::Window::getInstance()->getTime()*time(NULL))));
    int range = highest_number - lowest_number + 1;
    if(range == 0)
        return 0;
    else
        return (rand() % range) + lowest_number;
}

bool collisionRect(F2C::Rect rect1,F2C::Rect rect2){
    return (rect1.x >= rect2.x && rect1.x <= static_cast<int>(rect2.x+rect2.width) &&
            rect1.y >= rect2.y && rect1.y <= static_cast<int>(rect2.y+rect2.height));
}

Timer::Timer():
    starttime(F2C::WinApp.getTime())
{}

void Timer::reset(){
    this->starttime = F2C::WinApp.getTime();
}

double Timer::getTime(){
    return F2C::WinApp.getTime()-this->starttime;
}

F2C::Rect getStringSize(const F2C::FontSprite& font,std::string str){
    if(font.getTexWidth() < 1 || font.getTexHeight() < 1)
        return F2C::Rect (0,0,0,0);

    //Size of a Char
    F2C::uint x = 0; //current x-pos
    F2C::uint y = 0; //current y-pos/height
    F2C::uint w = 0; //current width

    const F2C::Rect* charrects = font.getCharsRect(); //size of letters(in Bitmapfont)

    for(size_t i = 0;i < str.length();i++){
        if(str[i] == '\0')
            break;
        if(str[i] == '\n'){
            y += charrects[static_cast<size_t>(str[i])].height;
            x = 0;
            continue;
        }else if(str[i] == '\t'){
            x += charrects[static_cast<size_t>(str[i])].width*3;
            continue;
        }else if(str[i] == '\v'){
            y += charrects[static_cast<size_t>(str[i])].height*3;
            x = 0;
            continue;
        }
        x += charrects[static_cast<size_t>(str[i])].width;
        w = (x > w)? x : w; //longest/biggers Line
    }
    F2C::Rect extraletter = charrects[static_cast<size_t>(' ')];
    return F2C::Rect (0,0,w+extraletter.width,y+extraletter.height);
}

void loadShader(std::string frag,std::string vertex){
   int shader_status = F2C::Window::getInstance()->InitGLShader();  //init Shader, get error
   if(shader_status > 0){
      std::string error_string;
      shader_status = F2C::Window::getInstance()->LoadGLFragmentShader(frag,&error_string);
      shader_status = F2C::Window::getInstance()->LoadGLVertexShader(vertex,&error_string);
      F2C::Window::getInstance()->CreateShaderProgram(&error_string);
      if(shader_status > 0){
         if(! error_string.empty()){  //write Shader compiler&linker Log
            F2C::LogError error;
            SETLOGERROR(error,error_string.c_str());
            error.writeError();
         }
         if(F2C::Window::getInstance()->programObj != 0){
            //Shader success
            F2C::Sprite::ShaderProgramObj = F2C::Window::getInstance()->programObj;  //set Sprite Shader Program Object
            F2C::FontSprite::ShaderProgramObj = F2C::Window::getInstance()->programObj;  //set FontSprite Shader Program Object
            F2C::Plane::ShaderProgramObj = F2C::Window::getInstance()->programObj;  //set Background Shader Program Object
         }
      }else{  //load Shaderfile failure
         F2C::LogError error;
         switch(shader_status){
               case -1:
                  SETLOGERROR(error,"Can't open the Shaderfile");
                  error.writeError();
               break;
               case -2:
                  SETLOGERROR(error,"The Shaderfile is empty");
                  error.writeError();
         }
      }
   }else{  //init Shader failure
      F2C::LogError error;
      switch(shader_status){
            case -1:
               SETLOGERROR(error,"This extension string indicates that the OpenGL Shading Language, version 1.00, is supported.");
               error.writeError();
            break;
            case -2:
               SETLOGERROR(error,"GL_ARB_shader_objects extension was not found");
               error.writeError();
            break;
            case -3:
               SETLOGERROR(error,"shading not enabled");
               error.writeError();
      }
   }
}

void loadFragmentShader(std::string filename){
   int shader_status = F2C::Window::getInstance()->InitGLShader();  //init Shader
   if(shader_status > 0){
      std::string error_string;
      shader_status = F2C::Window::getInstance()->LoadGLFragmentShader(filename,&error_string);
      F2C::Window::getInstance()->CreateShaderProgram(&error_string);
      if(shader_status > 0){
         if(! error_string.empty()){  //write Shader compiler&linker Log
            F2C::LogError error;
            SETLOGERROR(error,error_string.c_str());
            error.writeError();
         }
         if(F2C::Window::getInstance()->programObj != 0){
            //Shader success
            F2C::Sprite::ShaderProgramObj = F2C::Window::getInstance()->programObj;  //set Sprite Shader Program Object
            F2C::FontSprite::ShaderProgramObj = F2C::Window::getInstance()->programObj;  //set FontSprite Shader Program Object
            F2C::Plane::ShaderProgramObj = F2C::Window::getInstance()->programObj;  //set Background Shader Program Object
         }
      }else{  //load Shaderfile failure
         F2C::LogError error;
         switch(shader_status){
               case -1:
                  SETLOGERROR(error,"Can't open the Shaderfile");
                  error.writeError();
               break;
               case -2:
                  SETLOGERROR(error,"The Shaderfile is empty");
                  error.writeError();
         }
      }
   }else{  //init Shader failure
      F2C::LogError error;
      switch(shader_status){
            case -1:
               SETLOGERROR(error,"This extension string indicates that the OpenGL Shading Language, version 1.00, is supported.");
               error.writeError();
            break;
            case -2:
               SETLOGERROR(error,"GL_ARB_shader_objects extension was not found");
               error.writeError();
            break;
            case -3:
               SETLOGERROR(error,"shading not enabled");
               error.writeError();
      }
   }
}

void loadVertexShader(std::string filename){
    F2C::Window::getInstance()->InitGLShader();
   int shader_status = F2C::Window::getInstance()->InitGLShader();  //init Shader
   if(shader_status > 0){
      std::string error_string;
      shader_status = F2C::Window::getInstance()->LoadGLVertexShader(filename,&error_string);
      F2C::Window::getInstance()->CreateShaderProgram(&error_string);
      if(shader_status > 0){
         if(! error_string.empty()){  //write Shader compiler&linker Log
            F2C::LogError error;
            SETLOGERROR(error,error_string.c_str());
            error.writeError();
         }
         if(F2C::Window::getInstance()->programObj > 0){
            //Shader success
            F2C::Sprite::ShaderProgramObj = F2C::Window::getInstance()->programObj;  //set Sprite Shader Program Object
            F2C::FontSprite::ShaderProgramObj = F2C::Window::getInstance()->programObj;  //set FontSprite Shader Program Object
            F2C::Plane::ShaderProgramObj = F2C::Window::getInstance()->programObj;  //set Background Shader Program Object
         }
      }else{  //load Shaderfile failure
         F2C::LogError error;
         switch(shader_status){
               case -1:
                  SETLOGERROR(error,"Can't open the Shaderfile");
                  error.writeError();
               break;
               case -2:
                  SETLOGERROR(error,"The Shaderfile is empty");
                  error.writeError();
         }
      }
   }else{  //init Shader failure
      F2C::LogError error;
      switch(shader_status){
            case -1:
               SETLOGERROR(error,"This extension string indicates that the OpenGL Shading Language, version 1.00, is supported.");
               error.writeError();
            break;
            case -2:
               SETLOGERROR(error,"GL_ARB_shader_objects extension was not found");
               error.writeError();
            break;
            case -3:
               SETLOGERROR(error,"shading not enabled");
               error.writeError();
      }
   }
}

}
