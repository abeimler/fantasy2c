#ifndef __F2C_AUDIOFILE_HPP_INCLUDED
#define __F2C_AUDIOFILE_HPP_INCLUDED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <Fantasy2C/Basic.hpp>
#include <Fantasy2C/GameError.hpp>

template class DLL audiere::RefPtr<audiere::MIDIDevice>;
template class DLL audiere::RefPtr<audiere::AudioDevice>;
template class DLL audiere::RefPtr<audiere::OutputStream>;
template class DLL audiere::RefPtr<audiere::MIDIStream>;

namespace F2C{

    /**
    *@class AudioFile
    *@brief Playing audio files. \n
    *@brief Audiere Supported Formats: \n
    *@brief  *MIDI \n
    *@brief  *Ogg Vorbis \n
    *@brief  *MP3 \n
    *@brief  *FLAC \n
    *@brief  *Speex \n
    *@brief  *WAV \n
    *@brief  *AIFF \n
    *@brief  *MOD, S3M, XM, IT \n
    */
    class DLL AudioFile{
        private:
            audiere::MIDIDevicePtr midiDevice;
            audiere::AudioDevicePtr device;
            bool isInitDev;
            bool isInitMidiDev;
            std::string deviceName;
            std::string midiDeviceName;

            std::string filename;
            audiere::OutputStreamPtr sound;
            audiere::MIDIStreamPtr midiSound;
            int position;
            int midiPosition;
            bool isMidi;

            void loadDevice(bool isMidi);

        public:
            float pitch; ///< Pitch (0.5f - 2.0f), does not work with midi files
            bool loop; ///< Repeat On/Off
            float volume; ///< Volume (0.0f - 1.0f), does not work with midi files

            static std::vector< std::string > getSupportDevices(); ///< get Supported Devices
            std::string getDeviceName(); ///< Device Name (like: directsound, winmm, oss,...)
            std::string getMIDIDeviceName(); ///< MIDI Device Name (like: directsound, winmm, oss,...)

            AudioFile(); ///< Default constructor (load Device)
            virtual ~AudioFile(); ///< Stops the sound
            AudioFile(std::string filename); ///< @param filename Audio filename @brief Load a sound file.
            AudioFile(const AudioFile& copy); ///< Copy constructor
            AudioFile& operator = (const AudioFile& copy); ///< Assignment operator with deep copy.

            /**
            *@param filename Audio filename
            *@param loop Repeat On/Off
            *@brief Load a sound file and set repeat.
            */
            AudioFile(std::string filename, bool loop);
            void loadFile(std::string filename); ///< @param filename Audio filename @brief Load a sound file.

            /**
            *@param filename Audio filename
            *@param loop Repeat On/Off
            *@brief Load a sound file and set repeat.
            */
            void loadFile(std::string filename,bool loop);

            void play(); ///< Play (update Volume,Pitch and Repeat)
            void stop(); ///< Stop
            void pause(); ///< Pause

            bool isPlaying() const; ///< getMethode: Returns true if the sound is playing, false otherwise.
            int getPosition() const; ///< getMethode: Current position of the sound
            void setPostion(int position); ///< @param position position of the sound @brief setMethode: Set current position of the sound

            std::string getFilename() const; ///< getMethode: Audio filename
    };
}

#endif // __AUDIO_H
