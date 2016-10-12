#include <Fantasy2C/Window.hpp>
#include <Fantasy2C/Sprite.hpp>
#include <Fantasy2C/FontSprite.hpp>
#include <Fantasy2C/Plane.hpp>

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
            F2C::Plane::ShaderProgramObj = F2C::Window::getInstance()->programObj;  //set Plane Shader Program Object
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

int main(){
    //get Instance
    F2C::Window& WinApp = *F2C::Window::getInstance();

    //Window title
    std::string title = "Fantasy2C Simple: Shader and Grayscale";

    //Window size
    F2C::uint wndWidth = 800;
    F2C::uint wndHeight = 600;

    //Window color depth
    F2C::uint wndBPP = 32;

    //Fullscreen On/Off
    bool fullscreen = false;

    //set Maximum FPS
    double framerate = 60.0f;

    WinApp.setWindowHint(F2C::WindowProperty::NoResize,true);  //set Window Option: Window No Resize = true
    WinApp.CreateGLWindow(title.c_str(),wndWidth,wndHeight,wndBPP,fullscreen);  //create Window
    WinApp.setWindowPosition(160,120); //set Window Pos.

    WinApp.InitGL(); //init OpenGL
    F2C::LogError::ClearLog(); //clear LogFile

    loadFragmentShader("grayscale.afs"); //load ARB Fragment Shader file(code/text file) with grayscale-effect

    F2C::Bitmap* bitmap = new F2C::Bitmap;
    try{
        bitmap->loadFile("logo.jpg"); //load Image into Bitmap
    }catch(F2C::LogError& er){
        SETLOGERROR(er,er.getError());
        er.writeError();
    }

    F2C::Sprite sprLogo;
    sprLogo.setBitmap(bitmap); //load Bitmap into Sprite

    delete bitmap;

    //set Coord.
    sprLogo.x = wndWidth/2 - sprLogo.getTexWidth()/2;
    sprLogo.y = wndHeight/2 - sprLogo.getTexHeight()/2;
    sprLogo.tone.grayscale = 255; //full grayscale

    bool quit = false;
    while(!quit){
        WinApp.startTicks(); //start Timer

        //Game Update

        //End Game Update

        WinApp.ClearGLScene(); //clear Screen

        //Rendering

        sprLogo.render();

        //End Rendering

        WinApp.UpdateGLScreen(); //update Screen

        //FPS brake
        do{
            if(! WinApp.getWindowParam(F2C::WindowProperty::Open)){  //Window not open
                quit = true;
            }

            if(WinApp.getTicks() <= 1.0f/framerate)
                F2C::Window::getInstance()->Sleep(0.001f); //sleep
        }while(WinApp.getTicks() <= 1.0f/framerate); //get Time(in sec) <= FPS
    }

    //shutdown Window
	WinApp.ShutdownGLWindow();

    return 0;
}
