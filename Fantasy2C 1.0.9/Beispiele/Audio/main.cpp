#include<stdio.h>
#include<conio.h>
#include<Fantasy2C/Audio.hpp>

int main(){
    printf("F2C Simple Audio:\n");
    printf("Musik: Boss Battle (by Elementar-Dragon)\n");

    F2C::AudioFile audiofile;
    try{
        audiofile.loadFile("Boss Battle.mp3");
    }catch(F2C::LogError& er){
        SETLOGERROR(er,er.getError());
        er.writeError();

        printf("Error: %s\n",er.getError().c_str());
    }
    printf("\n");
    printf("Press:\n");
    printf("1: Play\n");
    printf("2: Pause\n");
    printf("3: Stop\n");
    printf("4,5,6: Volume (0%%, 50%%,100%%)\n");
    printf("7,8,9: Pitch  (low, normal, hight)\n");
    printf("q: Exit\n");

    char press = 0;
    do{
        press = getch();
        switch(press){
            case '1':
                audiofile.play();
            break;
            case '2':
                audiofile.pause();
            break;
            case '4':
            case '5':
            case '6':
                if(press == '4') audiofile.volume = 0.0f;
                else if(press == '5') audiofile.volume = 0.5f;
                else if(press == '6') audiofile.volume = 1.0f;
                audiofile.play();
            break;
            case '7':
            case '8':
            case '9':
                if(press == '7') audiofile.pitch = 0.5f;
                else if(press == '8') audiofile.pitch = 1.0f;
                else if(press == '9') audiofile.pitch = 2.0f;
                audiofile.play();
            break;
            case '3':
                audiofile.stop();
            break;
        }
    }while(press != 'q');

    return 0;
}
