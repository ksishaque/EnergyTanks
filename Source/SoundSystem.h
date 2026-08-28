/*****************************************************************//**
 * \file   SoundSystem.h
 * \brief
 *
 * \author Luke
 * \date   September 2022
 *********************************************************************/
#pragma once
#include "ISystem.h"
#include "fmod.hpp"
#include <map>
#include <set>
#include <vector>

#define SOUND_SYSTEM_CLICKER_INTERVAL 0.75f

class SoundSystem : public ISystem
{
public:
	/**
	 * Initializes sound system
	 *
	 */
	void initialize() override;
	/**
	 * Updates system
	 *
	 * \param dt Unused parameter
	 */
	void update(float& dt) override;
	/**
	 * Shuts down system
	 *
	 */
	void shutdown() override;
	/**
	 * Instance calls to play file
	 *
	 * \param name Name of sound file to play
	 * \param pause Whether the sound is paused or not
	 * \return Channel of sound playing
	 */
	static int play(std::string name, bool pause);
	/**
	 * Instance calls to stop the channel
	 *
	 * \param channel Channel to stop playing
	 */
	static void stop(int channel);
	/**
	 * Instance calls to stop all channels
	 * 
	 */
	static void stopAll();
	/**
	 * Instance calls to pause the channel
 	 *
	 * \param channel Channel to pause
	 */
	static void pause(int channel, bool pause);
	/**
	 * Instance calls to pause all channels
	 *
	 */
	static void pauseAll(bool pause = true);
	/**
	 * Checks if name is in the sound list if not creates new sound in the list else returns soundobject
	 *
	 * \param name Name of sound file to get
	 * \return SoundObject of name
	 */
	FMOD::Sound* get(std::string name);
	/**
	 * Checks if channel is in the channels list
	 *
	 * \param channel ChannelID to get
	 * \return Channel Object of channel
	 */
	FMOD::Channel* getChannel(int channel);
	/**
	 * Builds new sound object from the name of file
	 *
	 * \param name Name of sound file to build
	 * \param path Path of sound file to build
	 * \return whether sound was built successfully or not
	 */
	int buildSound(std::string name, std::string path);
	/**
	 * Reduces volume of all music channels
	 *
	 * \param mute If the music should be muted
	 */
	void instanceMuteMusic(bool mute);
	/**
	 * Changes volume of a certain channel
	 *
	 * \param channel Channel to change volume of
	 * \param volume Volume to change to
	 */
	void setVolume(int channel, float volume);
	/**
	 * Changes volume of all sfx channels
	 *
	 * \param volume Volume to change to
	 */
	static void setSfxVolume(float volume);
	/**
	 * Changes volume of all music channels
	 *
	 * \param volume Volume to change to
	 */
	static void setMusicVolume(float volume);
	/**
	 * Reduces volume of all music channels
	 *
	 * \param mute If the music should be muted
	 */
	static void muteMusic(bool mute = true);
	/**
	 * Gets music volume
	 * 
	 * \return Music Volume
	 */
	float getMusicVolume();
	/**
	 * Gets sfx volume
	 *
	 * \return Sfx Volume
	 */
	float getSfxVolume();
	float& getMusicVol();
	float& getSfxVol();
	/**
	 * Checks if string contains the string music
	 * 
	 * \param name String to check
	 * \return Whether it contains music or not
	 */
	bool isMusic(std::string name);
    /**
     * This function accesses the singleton instance of the sound system, creating it if needed.
     *
     * \return Singleton instance of the sound system
    */
    static SoundSystem* getInstance();
    /**
     * This function closes and deletes the singleton instance of the sound system
     *
    */
    static void closeInstance();
	/**
	 * Runs the clicker
	 *
	 */
	void click();

private:

	float sfxVolume;
	float musicVolume;
	float clickerTimer;
	unsigned mute;
    static SoundSystem* instance;
	FMOD::System* system;
	std::map<std::string, std::vector<FMOD::Sound*>> sounds; // name of sound and sound struct
	std::map<int, FMOD::Channel*> channels;
	unsigned int soundCount;
	std::string currentMusic;
    /**
     * Constructor for sound system
     *
     */
    SoundSystem();
    /**
     * Plays sound of soundfile on a channel
     *
     * \param name Name of sound file to play
     * \param pause Whether the sound is paused or not
     * \return Channel of sound playing
     */
    int instancePlay(std::string name, bool pause);
    /**
     * Plays sound of soundfile on the music channel
     *
     * \param name Name of sound file to play
     * \param pause Whether the sound is paused or not
     * \return Channel of sound playing
     */
    int instancePlayMusic(std::string name, bool pause);
    /**
     * Stops playing for specified channel
     *
     * \param channel Channel to stop playing
     */
    void instanceStop(int channel);
    /**
     * Stops all channels
     *
     */
    void instanceStopAll();
	/**
	 * Pauses specified channel
	 *
	 * \param channel Channel to pause
	 */
	void instancePause(int channel, bool pause);
	/**
	 * Pauses all channels
	 *
	 */
	void instancePauseAll(bool pause);
    /**
     * Changes volume of all sfx channels
     *
     * \param volume Volume to change to
     */
    void instanceSetSfxVolume(float volume);
    /**
     * Changes volume of all music channels
     *
     * \param volume Volume to change to
     */
    void instanceSetMusicVolume(float volume);

	void ERRCHECK(FMOD_RESULT checkResult);
};
