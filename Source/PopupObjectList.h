/*!
\file   PopupObjectList.h
\author Kevin Shin (kevin.shin\@digipen.edu)
\date   3-24-2023
\brief
        Functions for creating and maintaining a game object container
\par    Copyright © 2023 DigiPen, All rights reserved.
*/

#pragma once
#include <vector>
#include <queue>
#include <string>

class PopupObjectList;

#include "ObjectContainer.h"

class BehaviorPopup;

class PopupObjectList : public ObjectContainer{
    public:

		/*!
		\fn     PopupObjectList(BehaviorPopup *parent, bool passive)
		\param  parent
		          Parent pop up of the list
		\param  passive
		          If the list is passive (i.e. if "/Passive" should be added to the filepath)
		\return Constructed object container
		\brief
		        This function constructs a game object container.
		*/
		PopupObjectList(BehaviorPopup *parent, bool passive);

		/*!
		\fn     void addObject(GameObject *object)
		\param  object
		          object
		\brief  See ObjectContainer.h
		*/
		void addObject(GameObject *object) override;

		/*!
		\fn     const std::string &getName() const override
		\brief  See ObjectContainer.h
		*/
		const std::string &getName() const override;

		/*!
		\fn     BehaviorPopup *getPopup()
		\par    This function has no parameters.
		\return Pop up behavior parent of the list
		\brief
		        This function accesses the pop up behavior parent of the list.
		*/
		BehaviorPopup *getPopup();

	protected:

		/*!
		\var    passive
		          If the object list is passive
		*/
		bool passive;

		/*!
		\var    nameMade
		          If the name has been made
		\var    name
		          File path for the list
		*/
		mutable bool nameMade;
		mutable std::string name;

		/*!
		\var    parent
		          Pop up behavior that owns the sublist
		*/
		BehaviorPopup *parent;

		/*!
		\fn     void makeName() const;
		\par    This function has no parameters.
		\return Nothing
		\brief
		        This function generates the list's name based on the name of the parent object and list(s).
		*/
		void makeName() const;

};