#include <Fantasy2C/Window.hpp>
#include <Fantasy2C/Input.hpp>
#include <Fantasy2C/ShaderGL.hpp>
#include <Fantasy2C/Sprite.hpp>
#include <Fantasy2C/FontSprite.hpp>
#include <Fantasy2C/Plane.hpp>
#include <Fantasy2C/ArraySprite.hpp>

void loadShader(F2C::ShaderGL& shader,std::string fragmentfile,std::string vertexfile){
    int shader_status = shader.InitGLShader();  //init Shader
    F2C::LogError error;
    if(shader_status > 0){
        std::string error_string;
        if(!fragmentfile.empty())
            shader_status = shader.LoadGLFragmentShader(fragmentfile,&error_string);
        if(!vertexfile.empty())
            shader_status = shader.LoadGLVertexShader(vertexfile,&error_string);
        shader.CreateShaderProgram(&error_string);
        if(shader_status > 0){
            if(! error_string.empty()){  //write Shader compiler&linker Log
                error.writeString(error_string.c_str());
            }
        }else{  //load Shaderfile failure
         switch(shader_status){
               case -1:
                  error.writeString("Can't open the Shaderfile");
               break;
               case -2:
                  error.writeString("The Shaderfile is empty");
         }
        }
    }else{  //init Shader failure
        switch(shader_status){
            case -1:
               error.writeString("This extension string indicates that the OpenGL Shading Language, version 1.00, is supported.");
            break;
            case -2:
               error.writeString("GL_ARB_shader_objects extension was not found");
            break;
            case -3:
               error.writeString("shading not enabled");
        }
    }
}

int main(){
    //get Instance
    F2C::Window WinApp;
    F2C::Input InApp;

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

    F2C::ShaderGL shadergrayscale;
    loadShader(shadergrayscale,"grayscale.afs","vertex.avs"); //load ARB Fragment Shader file(code/text file) with grayscale-effect

    F2C::ShaderGL shadersepia;
    loadShader(shadersepia,"sepia.afs","vertex.avs"); //load ARB Fragment and Vertex Shader file(code/text file) with sepia-effect

    F2C::ShaderGL shaderblur;
    loadShader(shaderblur,"blur.afs","vertex.avs"); //load ARB Fragment and Vertex Shader file(code/text file) with blur-effect

    F2C::Bitmap* bitmap = new F2C::Bitmap;
    F2C::Bitmap* bitmapfont = new F2C::Bitmap;
    try{
        bitmap->loadFile("logo.jpg"); //load Image into Bitmap
        bitmapfont->loadFile("Font.png");
    }catch(F2C::LogError& er){
        SETLOGERROR(er,er.getError());
        er.writeError();
    }

    F2C::Sprite sprLogo;
    sprLogo.setBitmap(bitmap); //load Bitmap into Sprite

    F2C::FontSprite fsprFont;
    fsprFont.setBitmap(bitmapfont); //load Bitmap into Sprite

    delete bitmap;
    delete bitmapfont;

    //set Coord.
    sprLogo.x = wndWidth/2 - sprLogo.getTexWidth()/3 + 32;
    sprLogo.y = wndHeight/2 - sprLogo.getTexHeight()/3;
    sprLogo.tone.grayscale = 255; //full grayscale (full shader effect)

    //set Coord.
    fsprFont.x = 0;
    fsprFont.y = 0;

    std::ostringstream buffer;
    buffer << "OpenGL" << '\n';
    buffer << "Version: " << F2C::ShaderGL::getGLVersion() << '\n'; //Version
    buffer << '\n';
    buffer << "Graphic: " <<'\n'; //Graphic
    buffer << F2C::ShaderGL::getGLVendor() <<'\n';
    buffer << F2C::ShaderGL::getGLRenderer() <<'\n';
    buffer << '\n';
    buffer << "System: "; //System
    if(F2C::ShaderGL::getSupportedGLX())
        buffer << "GLX" <<'\n';
    if(F2C::ShaderGL::getSupportedWGL())
        buffer << "Windows (WGL)" <<'\n';
    if(!F2C::ShaderGL::getSupportedGLX() && !F2C::ShaderGL::getSupportedWGL())
        buffer <<"Other" << 'n'; //Other
    buffer << '\n';
    buffer << "Supported" << '\n'; //Supported
    //Shader
    buffer << "Shader: " << ((F2C::ShaderGL::getSupportedShader())? "Supported" : "Not Supported") << '\n';
    //VBO
    buffer << "VBO: " << ((F2C::ShaderGL::getSupportedVBO())? "Supported" : "Not Supported") << '\n';
    //MultiTexel
    buffer << "MultiTexel: " << ((F2C::ShaderGL::getSupportedMultiTexel())? "Supported" : "Not Supported") << '\n';
    if(F2C::ShaderGL::getSupportedMultiTexel())
        buffer << "Number of MultiTexel: " << F2C::ShaderGL::getMaxTexelUnits() << '\n'; // Number of MultiTexel
    fsprFont.addText(8,4,800,600,buffer.str());

    fsprFont.addText(16,356,192,256,"Press:\n1: Normal\n2: Grayscale\n3: Sepia\n4: Blur");

    bool quit = false;
    while(!quit){
        WinApp.startTicks(); //start Timer

        //Game Update
        InApp.update();
        //set Sprite Shader Program Object
        if(InApp.getPressKey('1')){
            F2C::Sprite::ShaderProgramObj = 0; //none
        }
        if(InApp.getPressKey('2')){
            F2C::Sprite::ShaderProgramObj = shadergrayscale.getProgramObj(); //grayscale
        }
        if(InApp.getPressKey('3')){
            F2C::Sprite::ShaderProgramObj = shadersepia.getProgramObj(); //sepia
        }
        if(InApp.getPressKey('4')){
            shaderblur.setUniformf("textureWidth",sprLogo.getTexWidth()); //set Unform variable: textureWidth
            shaderblur.setUniformf("textureHeight",sprLogo.getTexHeight()); //set Unform variable: textureHeight
            F2C::Sprite::ShaderProgramObj = shaderblur.getProgramObj(); //blur
        }

        //End Game Update

        WinApp.ClearGLScene(); //clear Screen

        //Rendering

        sprLogo.render();
        fsprFont.render();

        //End Rendering

        WinApp.UpdateGLScreen(); //update Screen

        //FPS brake
        do{
            if(! WinApp.getWindowParam(F2C::WindowProperty::Open)){  //Window not open
                quit = true;
            }

            if(WinApp.getTicks() <= 1.0f/framerate)
                WinApp.Sleep(0.001f); //sleep
        }while(WinApp.getTicks() <= 1.0f/framerate); //get Time(in sec) <= FPS
    }

    //shutdown Window
	WinApp.ShutdownGLWindow();

    return 0;
}
