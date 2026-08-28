/*!
\file   BehaviorPopup.h
\author Kevin Shin
\date   3-25-2023
\brief
        Functions for managing the behavior of a pop up
\par    Copyright © 2023 DigiPen, All rights reserved.
*/

#pragma once

#include "Behavior.h"

class ActionList;
class PopupObjectList;
class ObjectCuller;

/*!
\class  BehaviorPopup
\brief
        Behavior of a pop up
*/
class BehaviorPopup : public Behavior{
	public:

		/*!
		\fn     BehaviorPopup()
		\par    This function has no parameters.
		\return Constructed pop up behavior
		\brief
		        This function constructs a new behavior for an pop up.
		*/
		BehaviorPopup();

		/*!
		\fn     BehaviorPopup(const BehaviorPopup &source)
		\param  source
		          Icon behavior to copy
		\return Constructed pop up behavior
		\brief
		        This function constructs a new pop up behavior by copying an existing pop up behavior.
		*/
		BehaviorPopup(const BehaviorPopup &source);

		/*!
		\fn     ~BehaviorPopup()
		\par    This function has no parameters
		\return Nothing
		\brief
		        This function decontructs an pop up behavior.
		*/
		~BehaviorPopup();

		/*!
		\fn     BehaviorPopup *clone() const override
		\brief  See Component.h
		*/
		BehaviorPopup *clone() const override;
		
		/*!
		\fn     void setParent(GameObject *parent) override
		\param  parent
		          parent
		\brief  See Component.h
		*/
		void setParent(GameObject *parent) override;

		/*!
		\fn     void update(float dt)
		\param  dt
		          dt
		\brief  See Component.h
		*/
		void update(float dt) override;
		
		/*!
		\fn     void setPAWSable(bool pawsable)
		\param  pawsable
		          If the pop up should be affected by the pause system
		\return Nothing
		\brief
		        This function sets the pop up to be pausable.
		*/
		void setPAWSable(bool pawsable = false);

		/*!
		\fn     void setOpenActions(ActionList *actions)
		\param  actions
		          Actions to set
		\return Nothing
		\brief
		        This function mutates the pop up's opening actions.
		*/
		void setOpenActions(ActionList *actions);

		/*!
		\fn     void setCloseActions(ActionList *actions)
		\param  actions
		          Actions to set
		\return Nothing
		\brief
		        This function mutates the pop up's closing actions.
		*/
		void setCloseActions(ActionList *actions);
		
		/*!
		\fn     void open()
		\par    This function has no parameters.
		\return Nothing
		\brief
		        This function initiates the opening sequence of the pop up.
		*/
		void open();
		
		/*!
		\fn     void close()
		\par    This function has no parameters.
		\return Nothing
		\brief
		        This function initiates the closing sequence of the pop up.
		*/
		void close();
		
		/*!
		\fn     void setToClose()
		\par    This function has no parameters.
		\return Nothing
		\brief
		        This function sets the pop up to close.
		*/
		void setToClose();

		/*!
		\class  ActivatePopupAction
		\brief  See ActivatePopupAction.h
		*/
		friend class ActivatePopupAction;

		/*!
		\class  HidePopupAction
		\brief  See HidePopupAction.h
		*/
		friend class HidePopupAction;
        
	private:

		/*!
		\var    visible
		          If the pop up is currently being displayed
		\var    active
		          If the pop up is currently completely opened
		*/
		bool visible, active;

		/*!
		\var    opening
		          If the pop up was opening
		*/
		bool opening;

		/*!
		\var    toClose
		          If the pop up needs to be closed
		*/
		bool toClose;

		/*!
		\var    pawsable
		          If the pop up is affected by the pause system
		*/
		bool pawsable;

		/*!
		\var    passiveList
		          List of objects that are drawn whenever the pop up is displayed
		\var    activeList
		          List of objects that can be acted upon while the popup is displayed
		*/
		PopupObjectList *passiveList, *activeList;

		/*!
		\var    activeCuller
		          List of objects that can be acted upon while the popup is displayed
		*/
		ObjectCuller *activeCuller;

		/*!
		\var    openActions
		          List of actions that occur when opening
		\var    closeActions
		          List of actions that occur when closing
		*/
		ActionList *openActions, *closeActions;

		/*
		\var    currentActions
		          List of actions that are currently occuring
		*/
		ActionList *currentActions;

		/*
		\var    trans
		          Pointer to the transformation component, for convenience
		*/
		Transform *trans;
		
		/*!
		\fn     void activate()
		\par    This function has no parameters.
		\return Nothing
		\brief
		        This function activates the popup's active objects.
		*/
		void activate();
		
		/*!
		\fn     void hide()
		\par    This function has no parameters.
		\return Nothing
		\brief
		        This function hides the popup's passive objects.
		*/
		void hide();

};