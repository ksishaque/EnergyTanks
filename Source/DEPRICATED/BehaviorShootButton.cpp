/*****************************************************************//**
 * \file   BehaviorShootButton.cpp
 * \brief  Functions for managing the behavior of buttons
 *
 * \author Luke
 * \date   October 2022
 *********************************************************************/
#include "BehaviorShootButton.h"
#include <glm/glm.hpp>
#include <glfw/glfw3.h>
#include "ActionList.h"
#include "GameObject.h"
#include "Window.h"
#include "Trace.h"


BehaviorShootButton::BehaviorShootButton() : actions(new ActionList()), left(false), right(false)
{
}

BehaviorShootButton::BehaviorShootButton(void(*act)(void)) : actions(new ActionList()), left(false), right(false)
{
	actions->addFunction(act);
}

BehaviorShootButton::BehaviorShootButton(ActionNode* act) : actions(new ActionList()), left(false), right(false)
{
	actions->add(act);
}

BehaviorShootButton::BehaviorShootButton(const BehaviorShootButton& behaviorShootButton) :
	actions(behaviorShootButton.actions -> clone()),
	left(false),
	right(false)
{
}

BehaviorShootButton::~BehaviorShootButton()
{
	delete actions;
}

void BehaviorShootButton::update(float dt)
{
	if (left && right)
	{
		left = false;
		right = false;
		actions->update(dt);
	}
}

Component* BehaviorShootButton::clone() const
{
	BehaviorShootButton* clone = new BehaviorShootButton(*this);
	return clone;
}

void BehaviorShootButton::addAction(void(*act)(void))
{
	actions->addFunction(act);
}

void BehaviorShootButton::setHit(GameObject* obj)
{
	if (both == false)
	{
		right = true;
		left = true;
	}
	else if (obj->getTeam() == GameObject::Left)
	{
		left = true;
	}
	else if (obj->getTeam() == GameObject::Right)
	{
		right = true;
	}
}

void BehaviorShootButton::addAction(ActionNode* act)
{
	actions->add(act);
}

void BehaviorShootButton::setActions(ActionList* list)
{
	delete actions;
	actions = list;
}

void BehaviorShootButton::setBoth(bool b)
{
	both = b;
}
