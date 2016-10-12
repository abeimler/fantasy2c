#include<stdio.h>
#include<Fantasy2C/Audio.hpp>

int main(){
    F2C::AudioFile audiofile;

    printf("F2C Simple Audio:\n\n");
    printf("Select Music:\n");
    printf("1: Boss Battle.mp3 (by Elementar-Dragon)\n");
    printf("2: Dallas.mid (by Schiffmeister)\n");

    int selectSound = 1;
    do{
        fflush(stdin);
        scanf("%i",&selectSound);
        if(selectSound != 1 && selectSound != 2)
            printf("Incorrect input, again please\n");
    }while(selectSound != 1 && selectSound != 2);

    try{
        switch(selectSound){
            case 1:
                audiofile.loadFile("Boss Battle.mp3");
            break;
            case 2:
                audiofile.loadFile("Dallas.mid");
            break;
        }
    }catch(F2C::LogError& er){
        F2C::LogError::ClearLog();
        SETLOGERROR(er,er.getError());
        er.writeError();

        printf("Error: %s\n",er.getError().c_str());
    }

    printf("Device: %s\nMIDI Device: %s\n\n",audiofile.getDeviceName().c_str(),audiofile.getMIDIDeviceName().c_str());
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
        fflush(stdin);
        scanf("%c",&press);
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
