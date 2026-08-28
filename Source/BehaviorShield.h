/*****************************************************************//**
 * \file   BehaviorShield.h
 * \brief  Header for BehaviorShield.cpp
 * 
 * \author Luke Tseng
 * \author Kevin Shin
 * \date   October 2022
 * \par    Copyright © 2022 DigiPen, All rights reserved.
 *********************************************************************/
#pragma once
#include "Behavior.h"

class BehaviorShield : public Behavior
{
public:
	//|LUKE|
    /**
     * Constructor for BehaviorShield
     * 
     */
    BehaviorShield();
    /**
     * Copy Constructor for BehaviorShield
     *
     */
    BehaviorShield(const BehaviorShield& behaviorShield);
    /**
     * Destructor for BehaviorShield
     *
     */
    ~BehaviorShield();
    /**
     * Update function for BehaviorShield
     *
     */
    void update(float dt);
    /**
     * Clone function for BehaviorShield
     *
     */
    Component* clone() const override;

//|LUKE|
private:
	
	/*!
	\var    teamSet
	          If the team of the player has been updated
	*/
	bool teamSet;

};
