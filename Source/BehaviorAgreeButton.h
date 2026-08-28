/*****************************************************************//**
 * \file   BehaviorAgreeButton.h
 * \brief  Header for BehaviorAgreeButton.cpp
 *
 * \author Luke Tseng
 * \date   October 2022
 * \par    Copyright © 2022 DigiPen, All rights reserved.
 *********************************************************************/
#pragma once
#include "BehaviorButton.h"

class ActionList;
class ActionNode;

class BehaviorAgreeButton : public BehaviorButton
{
public:
    /**
     * Constructor for BehaviorAgreeButton
     *
     */
    BehaviorAgreeButton();
    /**
     * Copy Constructor for BehaviorAgreeButton
     *
     */
    BehaviorAgreeButton(const BehaviorAgreeButton& behaviorAgreeButton);
    /**
     * Destructor for BehaviorAgreeButton
     *
     */
    ~BehaviorAgreeButton();
	/**
	 * Update function for BehaviorAgreeButton
	 * 
	 * \param Time since previous frame
	 */
	void update(float dt) override;
	/**
     * Clone function for BehaviorAgreeButton
     *
     */
    Component* clone() const override;
    /**
     * Activates the button with a given team's input
     * 
     * \param Team providing input
     */
    void activate(GameObject::Team team) override;
    /**
     * Deactivates the button with a given team's input
     * 
     * \param Team providing input
     */
    void deactivate(GameObject::Team team) override;
    /**
     * Sets the button's time buffer
     * 
     * \param Time to set
     */
    void setBuffer(float time);

private:
    // checks if both players have shot button
    bool teams[3];
	float timer;
	float buffTime;
};
