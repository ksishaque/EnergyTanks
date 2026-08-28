/*!
\file   BehaviorTeamButton.cpp
\author Kevin Shin
\date   3-26-2023
\brief
        Functions for managing the behavior of an agreement button confirmation icon
\par    Copyright © 2023 DigiPen, All rights reserved.
*/

#include "SoundSystem.h"

#include "BehaviorTeamButton.h"

/*!
\fn     BehaviorTeamButton::BehaviorTeamButton()
\brief  See BehaviorTeamButton.h
*/
BehaviorTeamButton::BehaviorTeamButton() : BehaviorButton(), team(GameObject::Team::Neutral){}

/*!
\fn     BehaviorTeamButton::BehaviorTeamButton(const BehaviorTeamButton &that)
\param  that
          source
\brief  See BehaviorTeamButton.h
*/
BehaviorTeamButton::BehaviorTeamButton(const BehaviorTeamButton &that) : BehaviorButton(that), team(GameObject::Team::Neutral){}

/*!
\fn     void BehaviorTeamButton::update(float dt)
\param  dt
          dt
\brief  See BehaviorTeamButton.h
*/
void BehaviorTeamButton::update(float dt){

}

/*!
\fn     BehaviorTeamButton *BehaviorTeamButton::clone() const
\brief  See BehaviorTeamButton.h
*/
BehaviorTeamButton *BehaviorTeamButton::clone() const{
	return new BehaviorTeamButton(*this);
}

/*!
\fn     void BehaviorTeamButton::activate(GameObject::Team t)
\param  t
          team
\brief  See BehaviorButton.h
*/
void BehaviorTeamButton::activate(GameObject::Team t){
	
	//	Check `t`
	if(t == GameObject::Team::Neutral || (team != GameObject::Team::Neutral && team != t)) return;

	//	Activate
	BehaviorButton::activate(t);
	BehaviorButton::activate();

	//	Set the current decision to `NULL`
	deactivate(t);

}

/*!
\fn     void BehaviorTeamButton::setParent(GameObject *par)
\param  par
          parent
\brief  See Component.h
*/
void BehaviorTeamButton::setParent(GameObject *par){

	//	Set `parent`
	Component::setParent(par);
	
	//	Set `team`
	if(par) team = par -> getTeam();

}