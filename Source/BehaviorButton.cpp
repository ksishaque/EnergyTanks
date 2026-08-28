/*****************************************************************//**
 * \file   BehaviorButton.cpp
 * \brief  Functions for managing the behavior of buttons
 * 
 * \author Luke
 * \date   October 2022
 *********************************************************************/
 #include <glm/glm.hpp>
 #include <glfw/glfw3.h>
 #include "ActionList.h"
 #include "GameObject.h"
 #include "SoundSystem.h"
 #include "TeamSystem.h"
 #include "Trace.h"
 #include "Window.h"
 #include "BehaviorButton.h"


BehaviorButton::BehaviorButton() : Behavior(), action(new ActionList()), name("")
{
}

BehaviorButton::BehaviorButton(const BehaviorButton& behaviorButton) : Behavior(), action(behaviorButton.action)
{
	name = "~" + behaviorButton.name;
}

void BehaviorButton::addAction(ActionNode* node)
{
	action->add(node);
}

void BehaviorButton::activate()
{
	action->update(0);
}

void BehaviorButton::setParent(GameObject* obj)
{
	Component::setParent(obj);
	action->setParent(obj);
}

BehaviorButton::~BehaviorButton()
{
	delete action;
}

void BehaviorButton::clearAction()
{
	action->clear();
}

ActionList* BehaviorButton::getAction()
{
	return action;
}

void BehaviorButton::activate(GameObject::Team team)
{
	SoundSystem::play(confirmSound, false);
#ifdef DEBUG_SYSTEM
	Trace::message("Button %s activated by player %d", name, team);
#endif
	TeamSystem::getInstance() -> setDecision(team, this);
}

void BehaviorButton::deactivate(GameObject::Team team)
{
	SoundSystem::play(denySound, false);
	TeamSystem::getInstance() -> clearDecision(team);
}

void BehaviorButton::setDecName(const std::string &name)
{
	this -> name = name;
}

bool BehaviorButton::checkDecName(const std::string &name) const
{
	return this -> name == name;
}

void BehaviorButton::setConfirmSound(const std::string &name)
{
	confirmSound = name;
}

void BehaviorButton::setDenySound(const std::string &name){
	denySound = name;
}