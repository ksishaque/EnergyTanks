/*****************************************************************//**
 * \file   BehaviorAgreeButton.cpp
 * \brief  Functions for managing the behavior of buttons
 *
 * \author Luke
 * \date   October 2022
 *********************************************************************/

#include "SoundSystem.h"
#include "TeamSystem.h"

#include "BehaviorAgreeButton.h"

BehaviorAgreeButton::BehaviorAgreeButton() : BehaviorButton(), timer(0), buffTime(2)
{
	teams[0] = false;
	teams[2] = false;
}

BehaviorAgreeButton::BehaviorAgreeButton(const BehaviorAgreeButton& behaviorAgreeButton) :
	BehaviorButton(behaviorAgreeButton), timer(0), buffTime(behaviorAgreeButton.buffTime)
{
	teams[0] = false;
	teams[2] = false;
}

Component* BehaviorAgreeButton::clone() const
{
	BehaviorAgreeButton* clone = new BehaviorAgreeButton(*this);
	return clone;
}

void BehaviorAgreeButton::activate(GameObject::Team team)
{
	if (team == GameObject::Neutral)
	{
		return;
	}
	if (teams[team + 1]) deactivate(team);
	else
	{
		BehaviorButton::activate(team);
		teams[team + 1] = true;
	}
}

BehaviorAgreeButton::~BehaviorAgreeButton()
{
	if (teams[0])
	{
		BehaviorButton::deactivate(GameObject::Team::Left);
	}
	if (teams[2])
	{
		BehaviorButton::deactivate(GameObject::Team::Right);
	}
}

void BehaviorAgreeButton::deactivate(GameObject::Team team)
{
	if (team == GameObject::Neutral || !teams[team + 1])
	{
		return;
	}
	BehaviorButton::deactivate(team);
	teams[team + 1] = false;
	timer = 0;
}

void BehaviorAgreeButton::update(float dt)
{
	if (teams[0] && teams[2])
	{
		timer += dt;
		if (timer > buffTime)
		{
			teams[0] = false;
			teams[2] = false;
			TeamSystem::getInstance() -> clearDecision(GameObject::Team::Left);
			TeamSystem::getInstance() -> clearDecision(GameObject::Team::Right);
			BehaviorButton::activate();
			timer = 0;
		}
	}
}

void BehaviorAgreeButton::setBuffer(float t)
{
	buffTime = t;
}