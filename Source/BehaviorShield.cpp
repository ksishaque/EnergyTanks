/*****************************************************************//**
 * \file   BehaviorShield.cpp
 * \brief  Functions for managing the behavior of shields
 *
 * \author Luke Tseng
 * \author Kevin Shin
 * \date   October 2022
 * \par    Copyright © 2022 DigiPen, All rights reserved.
 *********************************************************************/
#include "TeamSystem.h"
#include "BehaviorShield.h"

BehaviorShield::BehaviorShield() : teamSet(false)
{
}

BehaviorShield::BehaviorShield(const BehaviorShield& behaviorShield) : teamSet(false)
{
}

BehaviorShield::~BehaviorShield()
{

	//	Remove shield from team
	if(teamSet){

		//	Variable: parent of the behavior
		GameObject* parent = getParent();

		//	Check `parent`
		if(parent) TeamSystem::getInstance() -> decShields(parent -> getTeam());
	}
}

void BehaviorShield::update(float dt)
{

	//	Add shield to team if necessary
	if(!teamSet){

		//	Variable: parent of the behavior
		GameObject* parent = getParent();

		//	Check `parent`
		if(parent) teamSet = TeamSystem::getInstance() -> incShields(parent -> getTeam());
	}
}

Component* BehaviorShield::clone() const
{
    BehaviorShield* clone = new BehaviorShield();
    return clone;
}