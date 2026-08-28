/*!
\file   BehaviorControlsBlocker.h
\author Kevin Shin
\date   4-11-2023
\brief
        Functions for managing the behavior of a temporary player controls invalidator
\par    Copyright © 2023 DigiPen, All rights reserved.
*/

#pragma once

class BehaviorControlsBlocker;

#include "BehaviorControllable.h"

class BehaviorOptionTrack;

/*!
\class  BehaviorControlsBlocker
\brief
        Behavior of a control blocker
*/
class BehaviorControlsBlocker : public BehaviorControllable{
	public:

		/*!
		\fn     BehaviorControlsBlocker()
		\par    This function has no parameters.
		\return Constructed selector behavior
		\brief
		        This function constructs a new behavior for a player selector.
		*/
		BehaviorControlsBlocker();

		/*!
		\fn     BehaviorControlsBlocker(const BehaviorControlsBlocker &source)
		\param  source
		          Selector behavior to copy
		\return Constructed selector behavior
		\brief
		        This function constructs a new selector behavior by copying an existing selector behavior.
		*/
		BehaviorControlsBlocker(const BehaviorControlsBlocker &source);

		/*!
		\fn     BehaviorControlsBlocker *clone() const override
		\brief  See Component.h
		*/
		BehaviorControlsBlocker *clone() const override;

		/*!
		\fn     void update(float dt) override
		\param  dt
		          dt
		\brief  See Component.h
		*/
		void update(float dt) override;

		/*!
		\fn     void setTime(float time)
		\param  time
		          Time to set
		\return Nothing
		\brief
		        This function mutates the time left until control is returned.
		*/
		void setTime(float time);

		/*!
		\fn     void actionCall(ControlType action, ControlManager::KeyState keyState)
		\param  action
		          action
		\param  keyState
		          keyState
		\brief  See BehaviorControllable.h
		*/
		void actionCall(ControlUnit::ControlType action, ControlManager::KeyState keyState) override {};
        
	private:

		/*!
		\var    time
		          Time until control is returned
		*/
		float time;

};
