#include "GameRunState.hpp"

void GameRunState::Init(){
    //load Image "logo.jpg" into Bitmap
    //load Bitmap into Sprite
    F2CLoadBitmapintoSprite(this->ssprSimple,"logo.jpg");

    F2C::uint wndWidth = 0;
    F2C::uint wndHeight = 0;

    //get Screen Size
    F2C::WinApp.getScreenSize(&wndWidth,&wndHeight);

    //get Sprite Size
    int ssprWidth = this->ssprSimple.getTexWidth();
    int ssprHeight = this->ssprSimple.getTexHeight();

    //set Position: Center
    this->ssprSimple.x = wndWidth/2 - ssprWidth/2;
    this->ssprSimple.y = wndHeight/2 - ssprHeight/2;
}

void GameRunState::Update(){
    this->ssprSimple.angle_y++; //Rotate Sprite
}
void GameRunState::Render(){
    this->ssprSimple.render();
}
