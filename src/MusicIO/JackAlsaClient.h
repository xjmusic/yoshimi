/*
    JackAlsaClient.h - Jack audio + Alsa midi
    
    Copyright 2009, Alan Calvert

    This file is part of yoshimi, which is free software: you can
    redistribute it and/or modify it under the terms of the GNU General
    Public License as published by the Free Software Foundation, either
    version 3 of the License, or (at your option) any later version.

    yoshimi is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with yoshimi.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef JACK_ALSA_CLIENT_H
#define JACK_ALSA_CLIENT_H

#include <string>
#include <pthread.h>
#include <semaphore.h>
#include <jack/jack.h>
#include <jack/ringbuffer.h>

using namespace std;

#include "Misc/Config.h"
#include "MusicIO/MusicClient.h"
#include "MusicIO/JackEngine.h"
#include "MusicIO/AlsaEngine.h"

class JackAlsaClient : public MusicClient
{
    public:
        JackAlsaClient() : MusicClient() { };
        ~JackAlsaClient() { Stop(); Close(); };

        bool openAudio(void);
        bool openMidi(void) { return alsaEngine.openMidi(); };
        bool Start(void) { return jackEngine.Start() && alsaEngine.Start(); };
        void Stop(void) { alsaEngine.Stop(); };
        void Close(void) { jackEngine.Close(); alsaEngine.Close(); };

        unsigned int getSamplerate(void) { return jackEngine.getSamplerate(); };
        int getBuffersize(void) { return jackEngine.getBuffersize(); };

        string audioClientName(void) { return jackEngine.clientName(); };
        string midiClientName(void) { return alsaEngine.midiClientName(); };
        int audioClientId(void) { return jackEngine.clientId(); };
        int midiClientId(void) { return alsaEngine.midiClientId(); };

        void startRecord(void) { jackEngine.StartRecord(); };
        void stopRecord(void) { jackEngine.StopRecord(); };
        bool setRecordFile(const char* fpath, string& errmsg)
            { return jackEngine.SetWavFile(fpath, errmsg); };
        bool setRecordOverwrite(string& errmsg)
            { return jackEngine.SetWavOverwrite(errmsg); };
        string wavFilename(void)
            { return jackEngine.WavFilename(); };
        void Mute(void) { jackEngine.Mute(); alsaEngine.Mute(); };
        void unMute(void) { jackEngine.unMute(); alsaEngine.Mute(); };

    private:
        JackEngine jackEngine;
        AlsaEngine alsaEngine;
};

#endif
