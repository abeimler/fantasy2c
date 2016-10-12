#include <Fantasy2C/SimpleSprite.hpp>
#include <Fantasy2C/FontSprite.hpp>
#include <Fantasy2C/Font.hpp>

#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>

#ifdef _WIN32
#undef main
#endif


void initOpenGL(GLuint screenw,GLuint screenh){
    glAlphaFunc(GL_GREATER, 0.0f);
    glDepthFunc(GL_LEQUAL);

    glViewport(0,0,screenw,screenh);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(0,screenw,screenh,0,INT_MIN+1,INT_MAX-1);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int main(int argc, char *argv[]){

    //init SDL
    if( SDL_Init( SDL_INIT_VIDEO ) != 0 ){
        printf("Error Init SDL: %s",SDL_GetError());
        return -1;
    }

    std::string windowtitle = "Fantasy2C Simple: SDL and Fantasy2C";

    //set Window title
    SDL_WM_SetCaption(windowtitle.c_str(),NULL);

    //set SDL Video Settings
    SDL_SetVideoMode(800, 600, 32, SDL_OPENGL );

    SDL_GL_SetAttribute(SDL_GL_RED_SIZE,8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE,8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE,8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE,8);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,16);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE,16);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    //init OpenGL
    initOpenGL(800,600);

    //load image and init Sprite
    F2C::SimpleSprite ssprLogo;
    F2C::FontSprite fsprInfo;
    F2C::Bitmap* bitmap = new F2C::Bitmap;
    F2C::TTFFont* bitmapfont = new F2C::TTFFont;

    //load Files
    try{
        bitmap->loadFile("logo.jpg");
        bitmapfont->loadFile("Arial.ttf",32);
    }catch(F2C::LogError& er){
        SETLOGERROR(er,er.getError());
        er.writeError();
    }

    //load into Sprites
    ssprLogo.setBitmap(bitmap);
    fsprInfo.setBitmap(bitmapfont);

    delete bitmap;
    delete bitmapfont;

    //set coord
    ssprLogo.x = 140;
    ssprLogo.y = 260;
    fsprInfo.x = 8;
    fsprInfo.y = 80;

    //add Text and set certices Color
    fsprInfo.addText(0,0,600,240,windowtitle);
    fsprInfo.vColor[0].set(255,0,0);
    fsprInfo.vColor[1].set(255,0,0);
    fsprInfo.vColor[2].set(0,255,255);
    fsprInfo.vColor[3].set(0,255,255);

    Uint32 LastTime = SDL_GetTicks();
    Uint32 curretFrames = 0;
    bool quit = false;
    while(!quit){
        //Window Events
        SDL_Event event;
        while( SDL_PollEvent(&event) ){
            switch(event.type){
                case SDL_QUIT:
                    quit = true;
                break;

            }
        }

        //Game run
        //Clear Screen
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        //Move
        ssprLogo.angle_y++;

        //Render
        ssprLogo.render();
        fsprInfo.render();

        //Swap Buffers
        SDL_GL_SwapBuffers();

        //calculate the fps
        curretFrames++;
        SDL_Delay(5);
        if((SDL_GetTicks() - LastTime) >= 1000){
            std::ostringstream FPS;
            FPS << windowtitle.c_str() << " :: FPS " << curretFrames;
            SDL_WM_SetCaption(FPS.str().c_str(),NULL);

            curretFrames = 0;
            LastTime = SDL_GetTicks();
        }
    }

    //Quit SDL
    SDL_Quit();

    return 0;
}
