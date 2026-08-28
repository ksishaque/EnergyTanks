/*****************************************************************//**
 * \file   BehaviorShootButton.h
 * \brief  Header for BehaviorShootButton.cpp
 *
 * \author Luke Tseng
 * \date   October 2022
 * \par    Copyright © 2022 DigiPen, All rights reserved.
 *********************************************************************/
#pragma once
#include "Behavior.h"
#include "ButtonAction.h"

class ActionList;
class ActionNode;

class BehaviorShootButton : public Behavior
{
public:
    /**
     * Constructor for BehaviorShootButton
     *
     */
    BehaviorShootButton();
    /**
     * Constructor for BehaviorShootButton setting action
     *
     */
    BehaviorShootButton(void(*act)(void));
    /**
     * Constructor for BehaviorShootButton setting action with functoid
     *
     */
    BehaviorShootButton(ActionNode *act);
    /**
     * Copy Constructor for BehaviorShootButton
     *
     */
    BehaviorShootButton(const BehaviorShootButton& behaviorShootButton);
    /**
     * Destructor for BehaviorShootButton
     *
     */
    ~BehaviorShootButton();
    /**
     * Update function for BehaviorShootButton
     *
     */
    void update(float dt);
    /**
     * Clone function for BehaviorShootButton
     *
     */
    Component* clone() const override;
    /**
     * Adds an action to the button
     *
     * \param Action to add
     */
    void addAction(void(*act)(void));
    /**
     * Adds an action to the button
     *
     * \param Action to add
     */
    void addAction(ActionNode *act);
    /**
     * Sets a list of actions to the button
     *
     * \param Action list to set it to
     */
    void setActions(ActionList *list);
    /**
     * Clears the actions for the button
     *
     */
    void clearActions();
    /**
     * Sets the left or right to true for the button based on game object
     *
     * \param gameobject to check type of 
     */
    void setHit(GameObject* obj);

	void setBoth(bool b);

private:
    ActionList *actions;
    // checks if both players have shot button
    bool left;
    bool right;
	bool both = true; // if false, doesn't need both players to shoot
};
