/*!
\file   BehaviorDisplayControlKey.h
\author Kevin Shin
\date   3-27-2023
\brief
        Functions for managing the behavior of a keybind display
\par    Copyright © 2023 DigiPen, All rights reserved.
*/

#pragma once

#include "ControlUnit.h"
#include "GameObject.h"
#include "GraphicsUnit.h"

#include "Behavior.h"

class BehaviorDisplayControlKey : public Behavior{
	public:

		/*!
		\fn     BehaviorDisplayControlKey()
		\par    This function has no parameters.
		\return Constructed icon behavior
		\brief
		        This function constructs a new behavior for an icon.
		*/
		BehaviorDisplayControlKey();

		/*!
		\fn     BehaviorDisplayControlKey(const BehaviorDisplayControlKey &source)
		\param  source
		          Icon behavior to copy
		\return Constructed icon behavior
		\brief
		        This function constructs a new icon behavior by copying an existing icon behavior.
		*/
		BehaviorDisplayControlKey(const BehaviorDisplayControlKey &source);

		/*!
		\fn     BehaviorDisplayControlKey *clone() const
		\brief  See Component.h
		*/
		BehaviorDisplayControlKey *clone() const override;

		/*!
		\fn     void update(float dt)
		\param  dt
		          dt
		\brief  See Component.h
		*/
		void update(float dt) override;

		/*!
		\fn     void setTarget(ControlUnit::ControlType type)
		\param  type
		          Control type to display
		\return Nothing
		\brief
		        This function mutates what control type is displayed.
		*/
		void setTarget(ControlUnit::ControlType type);

		/*!
		\fn     void setFont(unsigned fontIndex, Texture *font, float size)
		\param  fontIndex
		          Index of font to set
		\param  font
		          Font to set
		\param  size
		          Size of font
		\return Nothing
		\brief
		        This function mutates what font is used to display.
		*/
		void setFont(unsigned fontIndex, Texture *font, float size);

		/*!
		\fn     void setFont(GraphicsUnit::Type layer)
		\param  layer
		          Layer to draw on
		\return Nothing
		\brief
		        This function mutates what font is used to display.
		*/
		void setLayer(GraphicsUnit::Type layer);
        
	private:

		/*!
		\var    target
		          Keybinding to display
		\var    preTarget
		          Previous keybinding
		*/
		const int *target;
		int preTarget;

		/*!
		\var    type
		          Control key to display
		*/
		ControlUnit::ControlType type;

		/*!
		\var    fonts
		          Texture fonts to use to render different controls
		\var    fontSizes
		          Sizes of each font
		*/
		Texture *(fonts[3]);
		float fontSizes[3];

		/*!
		\var    layer
		          Layer to draw on
		*/
		GraphicsUnit::Type layer;

};
