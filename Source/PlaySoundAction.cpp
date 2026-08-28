/*!
\file   PlaySoundAction.cpp
\author Kevin Shin
\date   11-22-2022
\brief
        Functions for creating and managing an action node for changing game states
\par    Copyright © 2022 DigiPen, All rights reserved.
*/

#include "SoundSystem.h"
#include "Trace.h"

#include "PlaySoundAction.h"

/*!
\fn     PlaySoundAction::PlaySoundAction(const std::string& name, bool pause)
\param  name
          soundName
\param  vol
          volume
\param  pause
          paused
\brief  See PlaySoundAction.h
*/
PlaySoundAction::PlaySoundAction(const std::string& name, bool pause) : ActionNode(), sound(name), paused(pause){}

/*!
\fn     void PlaySoundAction::operator()(GameObject *obj, float dt)
\param  obj
          object
\param  dt
          dt
\brief  See ActionNode.h
*/
void PlaySoundAction::operator()(GameObject *obj, float dt){

	//	Trace message for debug
#ifdef DEBUG_SYSTEM
    Trace::message("Play sound action: %d", sound);
#endif

	//	Play sound
    SoundSystem::play(sound, paused);

	//	Recursive call to next
	ActionNode::operator()(obj, dt);
}

/*!
\fn     PlaySoundAction *PlaySoundAction::clone() const
\brief  See PlaySoundAction.h
*/
PlaySoundAction *PlaySoundAction::clone() const{

	//	Variable: return value / clone of `this`
	PlaySoundAction *ans = new PlaySoundAction(sound, paused);

	//	Set `next`
	ans -> operator<<(*cloneNext());

	//	Return
	return ans;
}