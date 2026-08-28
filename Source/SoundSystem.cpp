/*****************************************************************//**
* \file   SoundSystem.cpp
* \brief
*
* \author Luke Tseng
* \date   September 2022
* \par    Copyright © 2022 DigiPen, All rights reserved.
*********************************************************************/

#include <cassert>
#include <iostream>
#include "fmod.hpp"
#include "fmod_errors.h"
#include <vector>
#include <fstream>
#include "General.h"
#include "Trace.h"
#include "PauseSystem.h"
#include "ObjectFactory.h"
#include "ReadFile.h"
#include "SoundSystem.h"

SoundSystem* SoundSystem::instance = nullptr;

SoundSystem::SoundSystem() : ISystem(sSound), mute(0), sfxVolume(0.75f), musicVolume(0.75f), system(nullptr), sounds(), channels(), soundCount(0), currentMusic(), clickerTimer(0)
{
}

void SoundSystem::initialize()
{
	if (isActive())
	{
		return;
	}
	ISystem::initialize();

	FMOD_RESULT result = FMOD::System_Create(&system);
	ERRCHECK(result);

	result = system->init(32, FMOD_INIT_NORMAL, NULL);
	ERRCHECK(result);

	std::map<std::string, std::queue<std::string>> soundFiles;
	const char* objManJson = readWholeFile("Data/Json/sounds.json");
	soundFiles = parseSounds(objManJson);
	delete objManJson;
	std::map<std::string, std::queue<std::string>>::iterator it;
	int error = 1;
	for (it = soundFiles.begin(); it != soundFiles.end(); ++it)
	{
		while (!it->second.empty()) {
			error = buildSound(it->first, it->second.front());
			if (error == 0)
			{
#ifdef DEBUG_SYSTEM
				Trace::error("Sound Build failed");
#else
				assert("Sound error!");
#endif
			}
			it->second.pop();
		}
	}
}

void SoundSystem::update(float& dt)
{
	if (!isActive())
	{
		return;
	}
	if (!system)
	{
		return;
	}
	FMOD_RESULT result = system->update();
	ERRCHECK(result);
	std::vector<int> stoppedChannels;
	std::map<int, FMOD::Channel*>::iterator it;
	for (it = channels.begin(); it != channels.end(); ++it)
	{
		bool isPlaying = false;
		it->second->isPlaying(&isPlaying);
		if (!isPlaying)
		{
			stoppedChannels.push_back(it->first);
		}
	}
	for (int i : stoppedChannels)
	{
		stop(i);
	}
#ifdef DEBUG_SYSTEM
	Trace::message("Music volume: %.2f, Sfx volume %.2f", musicVolume, sfxVolume);
#endif
	if (clickerTimer > 0) clickerTimer -= PauseSystem::getInstance() -> getDt();
	else clickerTimer = 0;
}

void SoundSystem::shutdown()
{
	if (!isActive())
	{
		return;
	}
	ISystem::shutdown();

	if (!system)
	{
		return;
	}
	FMOD_RESULT result;
	stopAll();
	for (auto& i : sounds)
	{
		for (FMOD::Sound* sound : i.second)
		{
			result = sound->release();
			ERRCHECK(result);
		}
	}
	sounds.clear();
	result = system->close();
	ERRCHECK(result);
	result = system->release();
	ERRCHECK(result);
}

int SoundSystem::instancePlay(std::string name, bool pause)
{
	FMOD_RESULT result;
	FMOD::Sound* soundObject = get(name);
	// if sound cannot be found
	if (soundObject == nullptr)
	{
		return -1;
	}
	if (pause)
	{
		FMOD::Channel* temp;
		result = system->playSound(soundObject, 0, pause, &temp);
		ERRCHECK(result);
	}
	// find unused channel
	int channel = 1;
	while (channels.find(channel) != channels.end())
	{
		channel++;
	}
	FMOD::Channel* newChannel = nullptr;
	result = system->playSound(soundObject, 0, pause, &newChannel);
	ERRCHECK(result);
	if (newChannel)
	{
		result = newChannel->setVolume(sfxVolume);
		ERRCHECK(result);
		result = newChannel->setPaused(false);
		ERRCHECK(result);
		channels[channel] = newChannel;
#ifdef DEBUG_SYSTEM
		Trace::message("Playing on Channel: %d", channel);
#endif
		return channel;
	}
	return -1;
}

int SoundSystem::instancePlayMusic(std::string name, bool pause)
{
	if (name == currentMusic) return 0;
	FMOD_RESULT result;
	FMOD::Sound* soundObject = get(name);
	// if sound cannot be found
	if (soundObject == nullptr)
	{
		return -1;
	}
	if (pause)
	{
		FMOD::Channel* temp;
		result = system->playSound(soundObject, 0, pause, &temp);
		ERRCHECK(result);
	}
	FMOD::Channel* newChannel = nullptr;
	result = system->playSound(soundObject, 0, pause, &newChannel);
	ERRCHECK(result);
	if (newChannel)
	{
		result = newChannel->setVolume(musicVolume);
		ERRCHECK(result);
		result = newChannel->setPaused(false);
		ERRCHECK(result);
		instanceStop(0);
		channels[0] = newChannel;
#ifdef DEBUG_SYSTEM
		Trace::message("Playing on Channel: 0");
#endif
		currentMusic = name;
		return 0;
	}
	return -1;
}

void SoundSystem::instanceStop(int channel)
{
	// no channel found
	FMOD::Channel* temp = getChannel(channel);
	if (temp == nullptr)
	{
		return;
	}
	temp->stop();
#ifdef DEBUG_SYSTEM
	Trace::message("Stopped Channel: %d", channel);
#endif
	channels.erase(channel);
}

void SoundSystem::instanceStopAll()
{
	for (const auto& i : channels)
	{
		FMOD::Channel* temp = getChannel(i.first);
		if (temp == nullptr)
		{
			return;
		}
		temp->stop();
#ifdef DEBUG_SYSTEM
		Trace::message("Stopped Channel: %d", i.first);
#endif
	}
	channels.clear();
}

void SoundSystem::instancePause(int channel, bool pause)
{
	// no channel found
	FMOD::Channel* temp = getChannel(channel);
	if (temp == nullptr)
	{
		return;
	}
#ifdef DEBUG_SYSTEM
	Trace::message("Paused Channel: %d", channel);
#endif
	channels.erase(channel);
}

void SoundSystem::instancePauseAll(bool pause)
{
	for (const auto& i : channels)
	{
		FMOD::Channel* temp = getChannel(i.first);
		if (temp == nullptr)
		{
			return;
		}
		temp->setPaused(pause);
#ifdef DEBUG_SYSTEM
		Trace::message("Paused Channel: %d", i.first);
#endif
	}
}

FMOD::Sound* SoundSystem::get(std::string name)
{
	std::map<std::string, std::vector<FMOD::Sound*>>::iterator soundIter = sounds.find(name);
	if (soundIter == sounds.end())
	{
#ifdef DEBUG_SYSTEM
		Trace::message("Can't find sound");
#endif
		return nullptr;
	}
	return soundIter->second[randomInteger((int)soundIter->second.size())];
}


FMOD::Channel* SoundSystem::getChannel(int channel)
{
	if (channels.find(channel) == channels.end())
	{
		return nullptr;
	}
	return channels.find(channel)->second;
}

int SoundSystem::buildSound(std::string name, std::string path)
{
	// creates filepath
	FMOD_MODE mode = FMOD_DEFAULT;
	std::string filePath = "./Data/Audio/";
	filePath.append(path);
	std::ifstream f(filePath.c_str());
	if (f.good() == false)
	{
		return 0;
	}
	if (isMusic(name) == true)
	{
		mode = FMOD_LOOP_NORMAL;
	}
	else
	{
		mode = FMOD_LOOP_OFF;
	}
	FMOD::Sound* temp;
	// creates sound from filepath onto temp
	FMOD_RESULT result = system->createSound(filePath.c_str(), mode, 0, &temp);
	ERRCHECK(result);
	// if temp isn't null, inserts soundObject into sounds map
	if (temp)
	{
		sounds[name].push_back(temp);
		soundCount++;
		return 1;
	}
	return 0;
}

void SoundSystem::setVolume(int channel, float volume)
{
	auto found = channels.find(channel);
	if (found == channels.end())
	{
		return; // channel not found
	}
	FMOD_RESULT result = found->second->setVolume(volume);
	ERRCHECK(result);
}

float SoundSystem::getMusicVolume()
{
	return musicVolume;
}

float SoundSystem::getSfxVolume()
{
	return sfxVolume;
}

float& SoundSystem::getMusicVol()
{
	return musicVolume;
}

float& SoundSystem::getSfxVol()
{
	return sfxVolume;
}

void SoundSystem::instanceSetSfxVolume(float volume) // set all effect volumes to volume
{
	sfxVolume = volume;
	for (auto& channel : channels)
	{
		if (channel.first != 0)
		{
			setVolume(channel.first, sfxVolume);
		}
	}
	return;
}

void SoundSystem::instanceSetMusicVolume(float volume) // set all music volumes to volume
{
	musicVolume = volume;
	for (auto& channel : channels)
	{
		if (channel.first == 0)
		{
			if (mute > 0)
			{
				setVolume(channel.first, musicVolume / 4);
			}
			else
			{
				setVolume(channel.first, musicVolume);
			}
		}
	}
	return;
}

bool SoundSystem::isMusic(std::string name) // checks if sound file is a music file
{
	// make sure music files have the word 'Music' in them
	std::string check = "music";
	if (name.find(check) != std::string::npos)
	{
		return true;
	}
	return false;
}

SoundSystem* SoundSystem::getInstance()
{
	if (instance == nullptr)
	{
		instance = new SoundSystem();
	}
	return instance;
}

void SoundSystem::closeInstance()
{
	delete instance;
	instance = nullptr;
}

int SoundSystem::play(std::string name, bool pause)
{
	if (instance == nullptr)
	{
#ifdef DEBUG_SYSTEM
		Trace::message("SoundSystem instance is NULL");
#endif
		return -1;
	}
	if (instance->isMusic(name)) return instance->instancePlayMusic(name, pause);
	return instance->instancePlay(name, pause);
}

void SoundSystem::stop(int channel)
{
	if (instance == nullptr)
	{
#ifdef DEBUG_SYSTEM
		Trace::message("SoundSystem instance is NULL");
#endif
		return;
	}
	instance->instanceStop(channel);
}

void SoundSystem::stopAll()
{
	if (instance == nullptr)
	{
#ifdef DEBUG_SYSTEM
		Trace::message("SoundSystem instance is NULL");
#endif
		return;
	}
	instance->instanceStopAll();
}

void SoundSystem::pause(int channel, bool pause)
{
	if (instance == nullptr)
	{
#ifdef DEBUG_SYSTEM
		Trace::message("SoundSystem instance is NULL");
#endif
		return;
	}
	instance->instancePause(channel, pause);
}

void SoundSystem::pauseAll(bool pause)
{
	if (instance == nullptr)
	{
#ifdef DEBUG_SYSTEM
		Trace::message("SoundSystem instance is NULL");
#endif
		return;
	}
	instance->instancePauseAll(pause);
}

void SoundSystem::setSfxVolume(float volume)
{
	if (instance == nullptr)
	{
#ifdef DEBUG_SYSTEM
		Trace::message("SoundSystem instance is NULL");
#endif
		return;
	}
	instance->instanceSetSfxVolume(volume);
}

void SoundSystem::setMusicVolume(float volume)
{
	if (instance == nullptr)
	{
#ifdef DEBUG_SYSTEM
		Trace::message("SoundSystem instance is NULL");
#endif
		return;
	}
	instance->instanceSetMusicVolume(volume);
}

void SoundSystem::ERRCHECK(FMOD_RESULT checkResult)
{
	if (checkResult != FMOD_OK)
	{
#ifdef DEBUG_SYSTEM
		Trace::error("There was an error in the audio system: %s (%d)", FMOD_ErrorString(checkResult), checkResult);
#endif
	}
}

void SoundSystem::click() {
	if (clickerTimer <= 0)
	{
		clickerTimer += SOUND_SYSTEM_CLICKER_INTERVAL;
		play("uiClick", false);
	}
}

void SoundSystem::instanceMuteMusic(bool mute) // set all music volumes to volume
{
	if (mute)
	{
		this -> mute += 1;
		if (this -> mute > 1)
		{
			return;
		}
	}
	else
	{
		if (this -> mute < 1)
		{
			return;
		}
		this -> mute -= 1;
	}
	for (auto& channel : channels)
	{
		if (channel.first == 0)
		{
			if (this -> mute > 0)
			{
				setVolume(channel.first, musicVolume / 4);
			}
			else
			{
				setVolume(channel.first, musicVolume);
			}
		}
	}
	return;
}

void SoundSystem::muteMusic(bool mute)
{
	if (instance == nullptr)
	{
#ifdef DEBUG_SYSTEM
		Trace::message("SoundSystem instance is NULL");
#endif
		return;
	}
	instance->instanceMuteMusic(mute);
}