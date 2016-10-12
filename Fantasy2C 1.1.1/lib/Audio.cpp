#include <Fantasy2C/Audio.hpp>

namespace F2C{

AudioFile::~AudioFile(){
    if(this->sound)
        this->sound->stop();
}

AudioFile::AudioFile(const AudioFile& copy):
    device(NULL),
    sound(NULL),
    position(0),
    pitch(1.0f),
    loop(false),
    volume(1.0f)
{
    *this = copy;
}
AudioFile& AudioFile::operator = (const AudioFile& copy){
    if(this != &copy){
        this->pitch = copy.pitch;
        this->loop = copy.loop;
        this->volume = copy.volume;
        this->position = copy.position;

        this->device = audiere::OpenDevice();
        if(!this->device){
			std::ostringstream buffer;
			LogError error;
			buffer << "Can't open Device (audiere::OpenDevice()).\n";
			error.setError(buffer.str());
			throw error;
        }

        if(this->device)
            this->sound = copy.sound;
        if(this->sound)
            this->sound->setPosition(copy.sound->getPosition());
        this->filename = copy.filename;
    }

    return *this;
}

AudioFile::AudioFile():
    device(NULL),
    sound(NULL),
    position(0),
    pitch(1.0f),
    loop(false),
    volume(1.0f)
{
    this->device = audiere::OpenDevice();
    if(!this->device){
        std::ostringstream buffer;
		LogError error;
		buffer << "Can't open Device (audiere::OpenDevice()).\n";
		error.setError(buffer.str());
		throw error;
    }
}

AudioFile::AudioFile(std::string _filename):
    device(NULL),
    sound(NULL),
    position(0),
    pitch(1.0f),
    loop(false),
    volume(1.0f)
{
    this->device = audiere::OpenDevice();
    if(!this->device){
        std::ostringstream buffer;
		LogError error;
		buffer << "Can't open Device (audiere::OpenDevice()).\n";
		error.setError(buffer.str());
		throw error;
    }

    //Try to open a sound buffer
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
    this->filename = _filename;
}

AudioFile::AudioFile(std::string _filename,bool loop):
    device(NULL),
    sound(NULL),
    position(0),
    pitch(1.0f),
    loop(loop),
    volume(1.0f)
{
    this->device = audiere::OpenDevice();
    if(!this->device){
        std::ostringstream buffer;
		LogError error;
		buffer << "Can't open Device (audiere::OpenDevice()).\n";
		error.setError(buffer.str());
		throw error;
    }

    //Try to open a sound buffer
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
    this->filename = _filename;
}

void AudioFile::loadFile(std::string _filename){
    this->filename = "";
    this->position = 0;

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
    this->filename = _filename;
}

void AudioFile::loadFile(std::string _filename,bool loop){
    this->filename = "";
    this->loop = loop;
    this->position = 0;

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
    this->filename = _filename;
}

void AudioFile::play(){
    if(!this->sound)
        return;
    this->sound->setRepeat(loop);
    this->sound->setPitchShift(this->pitch);
    this->sound->setVolume(this->volume);
    if(!this->sound->isPlaying()){
        this->sound->setPosition(this->position);
        this->sound->play();
    }
}
void AudioFile::stop(){
    if(!this->sound)
        return;
    this->position = 0;
    this->sound->stop();
}
void AudioFile::pause(){
    if(!this->sound)
        return;
    this->position = this->sound->getPosition();
    this->sound->stop();
}

std::string AudioFile::getFilename() const{
    return this->filename;
}

bool AudioFile::isPlaying() const{
    if(!this->sound)
        return false;
    return this->sound->isPlaying();
}

int AudioFile::getPosition() const{
    if(!this->sound)
        return 0;
    return this->sound->getPosition();
}
void AudioFile::setPostion(int position){
    if(!this->sound)
        return;
    this->sound->setPosition(position);
}

};

