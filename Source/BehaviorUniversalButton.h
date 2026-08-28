/*!
\file   BehaviorUniversalButton.h
\author Kevin Shin
\date   2-13-2023
\brief
        Functions for managing the behavior of a player-controlled object
\par    Copyright © 2023 DigiPen, All rights reserved.
*/

#pragma once

class BehaviorUniversalButton;

#include "Behavior.h"

class BehaviorUniversalButton : public Behavior{
	public:

		/*!
		\fn     BehaviorUniversalButton(int button)
		\param  key
		          Key code for input
		\return Constructed universal button behavior
		\brief
		        This function constructs a new behavior for a gamestate dependent button.
		*/
		BehaviorUniversalButton(int key = -1);

		/*!
		\fn     BehaviorUniversalButton(const BehaviorUniversalButton &source)
		\param  source
		          Universal button behavior to copy
		\return Constructed controllable object behavior
		\brief
		        This function constructs a new universal button behavior by copying an existing behavior.
		*/
		BehaviorUniversalButton(const BehaviorUniversalButton &source);

		/*!
		\fn     ~BehaviorControllablle()
		\par    This function has no parameters
		\return Nothing
		\brief
		        This function decontructs a universal button behavior.
		*/
		~BehaviorUniversalButton();

		/*!
		\fn     BehaviorUniversalButton *clone() const
		\brief  See Component.h
		*/
		BehaviorUniversalButton *clone() const;

		/*!
		\fn     void update(float dt)
		\param  dt
		          Time since previous frame
		\return Nothing
		\brief
		        This function updates a universal button's key claims if necessary.
		*/
		void update(float dt);

		/*!
		\fn     void setUp(int key)
		\param  key
		          Key code for up input
		\return Nothing
		\brief
		        This function mutates a universal button behavior's designated input.
		*/
		void setButton(int key);

		/*!
		\fn     void addAction(ActionNode *action, int keyState)
		\param  action
		          Action node to add
		\param  keyState
		          State of key during which to activate, according to the following key:
		            0: Released
		            1: Pressed
		            2: Held
		\return Nothing
		\brief
		        This function adds an action node to the key.
		*/
		void addAction(ActionNode *action, int keyState);
        
	private:

		/*!
		\var    button
		          Key code for input
		*/
		int button;

		/*!
		\var    claim
		          If the key has been claimed
		*/
		bool claim;

		/*!
		\var    list
		          Backup list in case `button` could not be claimed
		*/
		ActionNode **list;

};
