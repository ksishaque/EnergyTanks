/*!
\file   BehaviorOptionSelector.h
\author Kevin Shin
\date   4-3-2023
\brief
        Functions for managing the behavior of a player selector
\par    Copyright © 2023 DigiPen, All rights reserved.
*/

#pragma once

class BehaviorOptionSelector;

#include "BehaviorControllable.h"

class BehaviorOptionTrack;

/*!
\class  BehaviorOptionSelector
\brief
        Behavior of a selector in a menu
*/
class BehaviorOptionSelector : public BehaviorControllable{
	public:

		/*!
		\fn     BehaviorOptionSelector()
		\par    This function has no parameters.
		\return Constructed selector behavior
		\brief
		        This function constructs a new behavior for a player selector.
		*/
		BehaviorOptionSelector();

		/*!
		\fn     BehaviorOptionSelector(const BehaviorOptionSelector &source)
		\param  source
		          Selector behavior to copy
		\return Constructed selector behavior
		\brief
		        This function constructs a new selector behavior by copying an existing selector behavior.
		*/
		BehaviorOptionSelector(const BehaviorOptionSelector &source);

		/*!
		\fn     ~BehaviorOptionSelector()
		\par    This function has no parameters.
		\return Nothing
		\brief
		        This function destroys a selector behavior.
		*/
		~BehaviorOptionSelector();

		/*!
		\fn     BehaviorOptionSelector *clone() const override
		\brief  See Component.h
		*/
		BehaviorOptionSelector *clone() const override;

		/*!
		\fn     void update(float dt) override
		\param  dt
		          dt
		\brief  See Component.h
		*/
		void update(float dt) override;

		/*!
		\fn     void setOption(const std::string &name)
		\param  name
		          Name of options list to set
		\return Nothing
		\brief
		        This function mutates the name of the options list that the selector is starts at.
		*/
		void setOption(const std::string &name);

		/*!
		\fn     void setOption(unsigned option)
		\param  option
		          Index of option to set
		\return Nothing
		\brief
				This function mutates the option index that the selector is currently looking at.
		*/
		void setOption(unsigned option);

		/*!
		\fn     void actionCall(ControlType action, ControlManager::KeyState keyState)
		\param  action
		          action
		\param  keyState
		          keyState
		\brief  See BehaviorControllable.h
		*/
		void actionCall(ControlUnit::ControlType action, ControlManager::KeyState keyState) override;
        
	private:

		/*!
		\var    optionInit
		          Name of the option selection behavior to look for
		*/
		std::string optionInit;

		/*!
		\var    i
		          Index of the option in the selection to look at
		*/
		unsigned i;

		/*!
		\var    dt
		          Time since previous frame, saved to be used in `actionCall()`
		*/
		float dt;

		/*!
		\var    options
		          Option selection behavior to look at
		*/
		BehaviorOptionTrack *options;

};
