#ifndef __F2C_AUDIOFILE_HPP_INCLUDED
#define __F2C_AUDIOFILE_HPP_INCLUDED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include "Basic.hpp"
#include "GameError.hpp"

namespace F2C{
    #if defined(WIN32) || defined(_Windows) || defined(__WIN32__)
	template class DLL audiere::RefPtr< audiere::AudioDevice >;
	template class DLL audiere::RefPtr< audiere::OutputStream >;
	#endif

    /**
    *@class AudioFile
    *@brief Playing audio files. \n
    *@brief Audiere Supported Formats: \n
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
            std::string filename;
            audiere::AudioDevicePtr device;
            audiere::OutputStreamPtr sound;
            int position;

        public:
            float pitch; ///< Pitch (0.5f - 2.0f)
            bool loop; ///< Repeat On/Off
            float volume; ///< Volume (0.0f - 1.0f)

            AudioFile(); ///< Default constructor
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
            void setPostion(int position); /// setMethode: Set current position of the sound

            std::string getFilename() const; ///< getMethode: Audio filename

    };
}

#endif // __AUDIO_H
