#include <Fantasy2C/Audio.hpp>

namespace F2C{

std::string AudioFile::getDeviceName(){
    return AudioFile::deviceName;
}
std::string AudioFile::getMIDIDeviceName(){
    return AudioFile::midiDeviceName;
}

AudioFile::~AudioFile(){
    this->stop();
}

AudioFile::AudioFile():
    midiDevice(NULL),
    device(NULL),
    isInitDev(false),
    isInitMidiDev(false),
    sound(NULL),
    midiSound(NULL),
    position(0),
    midiPosition(0),
    pitch(1.0f),
    loop(false),
    volume(1.0f)
{}

AudioFile::AudioFile(std::string _filename):
    midiDevice(NULL),
    device(NULL),
    isInitDev(false),
    isInitMidiDev(false),
    sound(NULL),
    midiSound(NULL),
    position(0),
    midiPosition(0),
    pitch(1.0f),
    loop(false),
    volume(1.0f)
{
    this->loadFile(_filename);
}

AudioFile::AudioFile(std::string _filename,bool loop):
    midiDevice(NULL),
    device(NULL),
    isInitDev(false),
    isInitMidiDev(false),
    sound(NULL),
    midiSound(NULL),
    position(0),
    midiPosition(0),
    pitch(1.0f),
    loop(loop),
    volume(1.0f)
{
    this->loadFile(_filename);
}

AudioFile::AudioFile(const AudioFile& copy):
    midiDevice(NULL),
    device(NULL),
    isInitDev(false),
    isInitMidiDev(false),
    sound(NULL),
    midiSound(NULL),
    position(0),
    midiPosition(0),
    isMidi(false),
    pitch(1.0f),
    loop(false),
    volume(1.0f)
{
    *this = copy;
}

std::vector< std::string > AudioFile::getSupportDevices(){
    std::vector< audiere::AudioDeviceDesc > devs;
    audiere::GetSupportedAudioDevices(devs);

    std::vector< std::string > re (devs.size());
    for(size_t i = 0;i < devs.size();i++)
        re[i] = devs[i].name;

    return re;
}

void AudioFile::loadDevice(bool isMidi){

    std::vector< std::string > devices = AudioFile::getSupportDevices();
    if(devices.empty()){
        std::ostringstream buffer;
        LogError error;
        buffer << "No device(s) found (audiere::GetSupportedAudioDevices()).\n";
        error.setError(buffer.str());
        error.setErrorCode(ErrorCode::AUDIERE_ERROR);
        throw error;
    }

    if(isMidi){
        this->midiDevice = NULL;
        this->midiDeviceName = "";

        this->midiDevice = audiere::OpenMIDIDevice("");
        for(size_t i = 0;!this->midiDevice && i < devices.size();i++){
            if(!devices[i].empty()){
                this->midiDevice = audiere::OpenMIDIDevice(devices[i].c_str());
                if(this->midiDevice){
                    this->midiDeviceName = this->midiDevice->getName();
                    break;
                }
            }
        }

        if(!this->midiDevice){
            std::ostringstream buffer;
            LogError error;
            buffer << "Can't open Midi Device (audiere::OpenMIDIDevice()).\n";
            error.setError(buffer.str());
            error.setErrorCode(ErrorCode::AUDIERE_ERROR);
            throw error;
        }
        this->isInitMidiDev = true;
    }else{
        this->device = NULL;
        this->deviceName = "";

        this->device = audiere::OpenDevice();
        if(this->device != NULL)
            this->deviceName = this->device->getName();
        for(size_t i = 0;!this->device && i < devices.size();i++){
            if(!devices[i].empty()){
                this->device = audiere::OpenDevice(devices[i].c_str());
                if(this->device){
                    this->deviceName = this->device->getName();
                    break;
                }
            }
        }
        if(!this->device){
            std::ostringstream buffer;
            LogError error;
            buffer << "Can't open Device (audiere::OpenDevice()).\n";
            error.setError(buffer.str());
            error.setErrorCode(ErrorCode::AUDIERE_ERROR);
            throw error;
        }
        this->isInitDev =  true;
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

void AudioFile::loadFile(std::string _filename){
    this->filename = "";
    this->position = 0;
    this->midiPosition = 0;
    this->isMidi = false;

    this->sound = NULL;
    this->midiSound = NULL;

    std::fstream tmpFile(_filename.c_str());
    if(!tmpFile.is_open()){
        std::ostringstream buffer;
        LogError error;
        buffer << "No such file or directory: " << _filename.c_str() << std::endl;
        error.setError(buffer.str());
        error.setErrorCode(ErrorCode::NO_SUCH_FILE_OR_DIR);
        throw error;
    }

    //is right format, look suffix
    std::string suf = _filename.substr(_filename.length()-4);
    std::string suf2 = _filename.substr(_filename.length()-5);
    std::locale loc;
    for(size_t i = 0;i < suf.length(); ++i)
        suf[i] = std::tolower(suf[i],loc);
    for(size_t i = 0;i < suf2.length(); ++i)
        suf2[i] = std::tolower(suf2[i],loc);

    bool ismid = suf == ".mid" || suf2 == ".midi";
    bool isOtherFormat = false;

    std::vector<audiere::FileFormatDesc> ffd;
    audiere::GetSupportedFileFormats(ffd);

    if (ffd.empty()) {
        std::ostringstream buffer;
        LogError error;
        buffer << "No Formats supported (audiere::GetSupportedFileFormats())" << std::endl;
        error.setError(buffer.str());
        error.setErrorCode(ErrorCode::AUDIERE_ERROR);
        throw error;
    }

    for (size_t i = 0;!isOtherFormat && i < ffd.size(); ++i) {
        for (int j = 0;!isOtherFormat && j < ffd[i].extensions.size(); ++j) {
          isOtherFormat = suf == ("."+ffd[i].extensions[j]) || suf2 == ("."+ffd[i].extensions[j]);
        }
    }

    if(ismid){
        if(!this->isInitMidiDev)
            this->loadDevice(true);

        //Try to open a sound buffer.
        if(AudioFile::midiDevice){
             this->midiSound = AudioFile::midiDevice->openStream(_filename.c_str());
        }

        //throw exception, if No such file or directory File
        if(!this->midiSound){
            std::ostringstream buffer;
            LogError error;
            buffer << "Cant load file (AudioFile::midiDevice->openStream())" << std::endl;
            error.setError(buffer.str());
            error.setErrorCode(ErrorCode::AUDIERE_ERROR);
            throw error;
        }
    }else if(isOtherFormat){
        if(!this->isInitDev)
            this->loadDevice(false);

        //Try to open a sound buffer.
        if(AudioFile::device){
            this->sound = audiere::OpenSound(AudioFile::device, _filename.c_str(), false);
        }

        //throw exception, if No such file or directory File
        if(!this->sound){
            std::ostringstream buffer;
            LogError error;
            buffer << "Cant load file (audiere::OpenSound())" << std::endl;
            error.setError(buffer.str());
            error.setErrorCode(ErrorCode::AUDIERE_ERROR);
            throw error;
        }
    }else{
        std::ostringstream buffer;
        LogError error;
        buffer << "Format " << suf << " not supported" << std::endl;
        error.setError(buffer.str());
        error.setErrorCode(ErrorCode::AUDIERE_ERROR);
        throw error;
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

