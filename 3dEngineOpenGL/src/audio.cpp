#include "audio.h"

/***************************************************************/
/** \file audio.cpp
	\brief The CAudio implementation                           */


/***************************************************************/
/** The CAudio class constructor           
****************************************************************/
CAudio::CAudio() {
	sound = NULL;
	channel = -1;
}


CAudio::~CAudio() {
	if (sound)
		Mix_FreeChunk(sound);
	sound = NULL;
}

void CAudio::SetSound(Mix_Chunk * s) {
	if (sound)
		Mix_FreeChunk(sound);
	sound = s;
}


void CAudio::SetVolume(float volume)
{
	int v = int(volume);

	if (sound)
		Mix_VolumeChunk(sound, v);

	if (channel != -1)
		Mix_Volume(channel, v);
}

