/*****************************************************************//**
 * \file   BehaviorButton.h
 * \brief  Header for BehaviorButton.cpp
 * 
 * \author Luke Tseng
 * \date   October 2022
 * \par    Copyright © 2022 DigiPen, All rights reserved.
 *********************************************************************/
#pragma once

#include "Behavior.h"
#include "GameObject.h"

class ActionNode;
class ActionList;

class BehaviorButton : public Behavior
{
public:
    /**
     * Constructor for BehaviorButton
     *
     */
    BehaviorButton();
    /**
     * Copy Constructor for BehaviorButton
     *
     */
    BehaviorButton(const BehaviorButton& behaviorButton);
    /**
     * Destructor for BehaviorButton
     *
     */
    virtual ~BehaviorButton();
    /**
     * Sets the parent for the button
     * 
     * \param Object to set it to
     */
    void setParent(GameObject* parent) override;
    /**
     * Sets the action for the button
     * 
     * \param Action to set it to
     */
    void addAction(ActionNode* act);
    /**
     * Gets the action for the button
     * 
     */
    ActionList* getAction();
    /**
     * Clears the action for the button
     * 
     */
    void clearAction();
    /**
     * Activates the button with a given team's input
     * 
     * \param Team providing input
     */
    virtual void activate(GameObject::Team team);
    /**
     * Deactivates the button with a given team's input
     * 
     * \param Team providing input
     */
    virtual void deactivate(GameObject::Team team);
    /**
     * Sets the decision name for the button
     * 
     * \param Name to set it to
     */
    void setDecName(const std::string &name);
    /**
     * Checks the decision name for the button
     * 
     * \param Name to compare it to
     */
    bool checkDecName(const std::string &name) const;
    /**
     * Sets the sound to play when the button activates
     * 
     * \param Name of sound to set it to
     */
    void setConfirmSound(const std::string &name);
    /**
     * Sets the sound to play when the button deactivates
     * 
     * \param Name of sound to set it to
     */
    void setDenySound(const std::string &name);

protected:
	void activate();

private:
    ActionList *action;
	std::string name;
	std::string confirmSound, denySound;
};
