#include "audiosystem.h"
#include <iostream>
#include <cstdlib>
using namespace std;


CAudioSystem::CAudioSystem(int num_channels)
{
	if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1) {
		cerr << "Mix_OpenAudio: " << Mix_GetError() << endl;
		exit(-1);
	}

	NumChannels = num_channels;
	Mix_AllocateChannels(NumChannels);
	music = NULL;
}


CAudioSystem::~CAudioSystem()
{
    Mix_CloseAudio();
	if (music)
		Mix_FreeMusic(music);
}



void CAudioSystem::Play(CAudio *audio, bool loop)
{
	int repeat = loop ? -1:0;
	int channel = Mix_PlayChannel(-1, audio->GetSound(), repeat);	
	audio->SetChannel(channel);
}


void CAudioSystem::Stop(CAudio *audio)
{
	Mix_HaltChannel(audio->GetChannel());
}



bool CAudioSystem::IsPlaying(CAudio *audio)
{
	return Mix_Playing(audio->GetChannel());
}



CAudio *CAudioSystem::Create(char *filename, bool Is3DSound)
{
	CAudio *audio = new CAudio;
	Mix_Chunk *sample = Mix_LoadWAV(filename);

	audio->SetSound(sample);
	return audio;
}


void CAudioSystem::PlayMusic(char *filename, int repeat) {
	music = Mix_LoadMUS(filename);
	Mix_PlayMusic(music,repeat);
}



void CAudioSystem::StopMusic() {
	Mix_HaltMusic();
}



void CAudioSystem::SetMusicVolume(int volume) {
	Mix_VolumeMusic(volume);
}



bool CAudioSystem::IsMusicPlaying() {
	return Mix_PlayingMusic();
}

