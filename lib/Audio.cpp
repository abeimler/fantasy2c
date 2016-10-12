#include <Fantasy2C/Audio.hpp>

namespace F2C{

std::vector< audiere::AudioDeviceDesc > AudioFile::devices;
bool AudioFile::isFindDevs = false;

AudioFile::~AudioFile(){
    if(this->sound)
        this->sound->stop();
}

AudioFile::AudioFile(const AudioFile& copy):
    device(NULL),
    sound(NULL),
    midiDevice(NULL),
    midiSound(NULL),
    position(0),
    midiPosition(0),
    isMidi(false),
    pitch(1.0f),
    loop(false),
    volume(1.0f)
{
    if(!AudioFile::isFindDevs){
        audiere::GetSupportedAudioDevices(AudioFile::devices);
        AudioFile::isFindDevs = true;
    }

    *this = copy;
}

void AudioFile::loadDevice(){
    if(AudioFile::devices.empty()){
        std::ostringstream buffer;
        LogError error;
        buffer << "No device found (audiere::GetSupportedAudioDevices()).\n";
        error.setError(buffer.str());
        throw error;
    }
    this->midiDevice = audiere::OpenMIDIDevice(AudioFile::devices[0].name.c_str());

    if(!this->midiDevice){
        std::ostringstream buffer;
		LogError error;
		buffer << "Can't open Midi Device (audiere::OpenMIDIDevice()).\n";
		error.setError(buffer.str());
		throw error;
    }

    this->device = audiere::OpenDevice();
    if(!this->device){
        std::ostringstream buffer;
		LogError error;
		buffer << "Can't open Device (audiere::OpenDevice()).\n";
		error.setError(buffer.str());
		throw error;
    }
}

AudioFile& AudioFile::operator = (const AudioFile& copy){
    if(this != &copy){
        this->pitch = copy.pitch;
        this->loop = copy.loop;
        this->volume = copy.volume;
        this->position = copy.position;
        this->midiPosition = copy.midiPosition;
        this->isMidi = copy.isMidi;

        this->midiSound = NULL;
        this->sound = NULL;

        if(this->isMidi){
            if(this->midiDevice)
                this->midiSound = copy.midiSound;
            if(this->midiSound)
                this->midiSound->setPosition(this->getPosition());
        }else{
            if(this->device)
                this->sound = copy.sound;
            if(this->sound)
                this->sound->setPosition(this->getPosition());
        }

        this->filename = copy.filename;
    }

    return *this;
}

AudioFile::AudioFile():
    device(NULL),
    sound(NULL),
    midiDevice(NULL),
    midiSound(NULL),
    position(0),
    midiPosition(0),
    pitch(1.0f),
    loop(false),
    volume(1.0f)
{
    if(!AudioFile::isFindDevs){
        audiere::GetSupportedAudioDevices(AudioFile::devices);
        AudioFile::isFindDevs = true;
    }

    this->loadDevice();
}

AudioFile::AudioFile(std::string _filename):
    device(NULL),
    sound(NULL),
    midiDevice(NULL),
    midiSound(NULL),
    position(0),
    midiPosition(0),
    pitch(1.0f),
    loop(false),
    volume(1.0f)
{
    if(!AudioFile::isFindDevs){
        audiere::GetSupportedAudioDevices(AudioFile::devices);
        AudioFile::isFindDevs = true;
    }

    this->loadDevice();
    this->loadFile(_filename);
}

AudioFile::AudioFile(std::string _filename,bool loop):
    device(NULL),
    sound(NULL),
    midiDevice(NULL),
    midiSound(NULL),
    position(0),
    midiPosition(0),
    pitch(1.0f),
    loop(loop),
    volume(1.0f)
{
    if(!AudioFile::isFindDevs){
        audiere::GetSupportedAudioDevices(AudioFile::devices);
        AudioFile::isFindDevs = true;
    }

    this->loadDevice();
    this->loadFile(_filename);
}

void AudioFile::loadFile(std::string _filename){
    this->filename = "";
    this->position = 0;
    this->midiPosition = 0;
    this->isMidi = false;

    this->sound = NULL;
    this->midiSound = NULL;

    //is midi file, look suffix
    bool ismid = ( _filename[_filename.length()-4] == '.' &&
                   _filename[_filename.length()-3] == 'm' &&
                   _filename[_filename.length()-2] == 'i' &&
                   _filename[_filename.length()-1] == 'd');

    if(ismid){
        //Try to open a sound buffer.
        if(this->midiDevice){
             this->midiSound = this->midiDevice->openStream(_filename.c_str());
        }

        //throw exception, if No such file or directory File
        if(!this->midiSound){
            std::ostringstream buffer;
            LogError error;
            buffer << "No such file or directory: " << _filename.c_str() << '\n';
            error.setError(buffer.str());
            throw error;
        }
    }else{
        //Try to open a sound buffer.
        if(this->device){
            this->sound = audiere::OpenSound(this->device, _filename.c_str(), true);
        }

        //throw exception, if No such file or directory File
        if(!this->sound){
            std::ostringstream buffer;
            LogError error;
            buffer << "No such file or directory: " << _filename.c_str() << '\n';
            error.setError(buffer.str());
            throw error;
        }
    }
    this->filename = _filename;
    this->isMidi = ismid;
}

void AudioFile::loadFile(std::string _filename,bool loop){
    this->loop = loop;
    this->loadFile(_filename);
}

void AudioFile::play(){
    if(this->sound && !this->isMidi){
        this->sound->setRepeat(loop);
        this->sound->setPitchShift(this->pitch);
        this->sound->setVolume(this->volume);
        if(!this->sound->isPlaying()){
            this->sound->setPosition(this->position);
            this->sound->play();
        }
    }else if(this->midiSound && this->isMidi){
        this->midiSound->setRepeat(loop);
        //this->midiSound->setPitchShift(this->pitch);
        //this->midiSound->setVolume(this->volume);
        if(!this->midiSound->isPlaying()){
            this->midiSound->setPosition(this->position);
            this->midiSound->play();
        }
    }
}
void AudioFile::stop(){
    this->position = 0;
    this->midiPosition = 0;
    if(this->sound && !this->isMidi){
        this->sound->stop();
    }else if(this->midiSound && this->isMidi){
        this->midiSound->stop();
    }
}
void AudioFile::pause(){
    if(this->sound && !this->isMidi){
        this->position = this->sound->getPosition();
        this->sound->stop();
    }else if(this->midiSound && this->isMidi){
        this->midiPosition = this->midiSound->getPosition();
        this->midiSound->stop();
    }
}

std::string AudioFile::getFilename() const{
    return this->filename;
}

bool AudioFile::isPlaying() const{
    if(this->sound && !this->isMidi){
        return this->sound->isPlaying();
    }else if(this->midiSound && this->isMidi){
        return this->midiSound->isPlaying();
    }
    return false;
}

int AudioFile::getPosition() const{
    if(this->sound && !this->isMidi){
        return this->sound->getPosition();
    }else if(this->midiSound && this->isMidi){
        return this->midiSound->getPosition();
    }
    return 0;
}
void AudioFile::setPostion(int position){
    if(this->sound && !this->isMidi){
        this->sound->setPosition(position);
    }else if(this->midiSound && this->isMidi){
        this->midiSound->setPosition(position);
    }
}

};

