/*!
\file   PlaySoundAction.h
\author Kevin Shin
\date   11-22-2022
\brief
		Functions for creating and managing an action node for changing game states
\par    Copyright © 2022 DigiPen, All rights reserved.
*/
#pragma once

class ChangeStateAction;

#include <string>

#include "ActionNode.h"

#define playSoundAct(name, pause) new PlaySoundAction(name, pause)

/*!
\class  PlaySoundAction
\brief
        Nodes in an action list that plays a sound
*/
class PlaySoundAction : public ActionNode{
	public:

		/*!
		\fn     PlaySoundAction(const std::string& soundName, bool paused = false)
		\param  soundName
		          Name of sound to play
		\param  volume
		          Volume to play at
		\param  paused
		          If the sound is paused
		\return Newly constructed playsound action
		\brief
		        This function constructs a new playsound node.
		*/
		PlaySoundAction(const std::string& soundName, bool paused = false);

		/*!
		\fn     void operator()(GameObject *object, float dt)
		\param  object
		          object
		\param  dt
		          dt
		\brief  See ActionNode.h
		*/
		void operator()(GameObject *object, float dt);

		/*!
		\fn     PlaySoundAction *clone() const
		\brief  See ActionNode.h
		*/
		PlaySoundAction *clone() const;

	private:

		/*!
		\var    sound
		          Sound to play
		*/
		std::string sound;

		/*!
		\var    volume
		          Volume to play at
		*/
		float volume;

		/*!
		\var    paused
		          If sound is paused
		*/
		bool paused;
};