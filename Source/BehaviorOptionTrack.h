/*!
\file   BehaviorOptionTrack.h
\author Kevin Shin
\date   4-3-2023
\brief
        Functions for managing the behavior of a options track or menu
\par    Copyright © 2023 DigiPen, All rights reserved.
*/

#pragma once

class BehaviorOptionTrack;

#include <vector>

#include "Behavior.h"

class MenuOption;

/*!
\class  BehaviorOptionTrack
\brief
        Behavior of a set of options
*/
class BehaviorOptionTrack : public Behavior{
	public:

		/*!
		\fn     BehaviorOptionTrack()
		\par    This function has no parameters.
		\return Constructed menu behavior
		\brief
		        This function constructs a new behavior for a player menu.
		*/
		BehaviorOptionTrack();

		/*!
		\fn     BehaviorOptionTrack(const BehaviorOptionTrack &source)
		\param  source
		          Selector behavior to copy
		\return Constructed menu behavior
		\brief
		        This function constructs a new menu behavior by copying an existing menu behavior.
		*/
		BehaviorOptionTrack(const BehaviorOptionTrack &source);

		/*!
		\fn     ~BehaviorOptionTrack()
		\par    This function has no parameters
		\return Nothing
		\brief
		        This function decontructs a menu behavior.
		*/
		~BehaviorOptionTrack();

		/*!
		\fn     BehaviorOptionTrack *clone() const override
		\brief  See Component.h
		*/
		BehaviorOptionTrack *clone() const override;

		/*!
		\fn     void setOptions(const std::vector<MenuOption *> &options)
		\param  options
		          List of options to set
		\return Nothing
		\brief
		        This function mutates the options list of the menu.
		*/
		void setOptions(const std::vector<MenuOption *> &options);

		/*!
		\fn     MenuOption *getOption(unsigned option)
		\param  option
		          Index of option to get
		\return Menu option at the given index
		\brief
				This function accesses the option at a given index in the menu.
		*/
		MenuOption *getOption(unsigned option);
        
	private:

		/*!
		\var    size
		          Size of `options`
		*/
		unsigned size;

		/*!
		\var    options
		          List of options in the track
		*/
		MenuOption **options;

};
