/*****************************************************************//**
 * \file   TeamSystem.cpp
 * \brief
 *
 * \author Luke Tseng
 * \date   October 2022
 * \par    Copyright © 2022 DigiPen, All rights reserved.
 *********************************************************************/

#include "glfw/glfw3.h"

#include <stdexcept>

#include "BehaviorButton.h"
#include "BehaviorControllable.h"
#include "ColorWheel.h"
#include "ControlUnit.h"

#include "TeamSystem.h"

TeamSystem* TeamSystem::instance = nullptr;

TeamSystem::TeamSystem() : ISystem(sTeam), teams(), initContDisplay(true)
{

	//	TEMPORARY
	teams[0].setColor(glm::vec4(0, 1, 1, 1));
	teams[1].setColor(glm::vec4(1, 0, 1, 1));
	ControlUnit *con = teams[0].getControls();
	con -> setKey(ControlUnit::ControlType::UP, GLFW_KEY_W);
	con -> setKey(ControlUnit::ControlType::DOWN, GLFW_KEY_S);
	con -> setKey(ControlUnit::ControlType::LEFT, GLFW_KEY_A);
	con -> setKey(ControlUnit::ControlType::RIGHT, GLFW_KEY_D);
	con -> setKey(ControlUnit::ControlType::FIRST, GLFW_KEY_SPACE);
	con -> setKey(ControlUnit::ControlType::SECOND, GLFW_KEY_ESCAPE);
	con -> update();
	con = teams[1].getControls();
	con -> setKey(ControlUnit::ControlType::UP, GLFW_KEY_UP);
	con -> setKey(ControlUnit::ControlType::DOWN, GLFW_KEY_DOWN);
	con -> setKey(ControlUnit::ControlType::LEFT, GLFW_KEY_LEFT);
	con -> setKey(ControlUnit::ControlType::RIGHT, GLFW_KEY_RIGHT);
	//*
	con -> setKey(ControlUnit::ControlType::FIRST, GLFW_KEY_RIGHT_CONTROL);
	/*/
	con -> setKey(ControlUnit::ControlType::FIRST, GLFW_KEY_RIGHT_ALT);
	//*/
	con -> setKey(ControlUnit::ControlType::SECOND, GLFW_KEY_MENU);
	con -> update();
}

bool TeamSystem::hasShields(GameObject::Team team)
{
    if (team == GameObject::Right)
    {
        return teams[1].hasShields();
    }
    else if (team == GameObject::Left)
    {
        return teams[0].hasShields();
    }
    return false;
}

bool TeamSystem::decShields(GameObject::Team team, unsigned n)
{
    if (team == GameObject::Right)
    {
        teams[1].incShields(- (int) n);
		return true;
    }
    else if (team == GameObject::Left)
    {
        teams[0].incShields(- (int) n);
		return true;
    }
	return false;
}

bool TeamSystem::incShields(GameObject::Team team, int n)
{
    if (team == GameObject::Right)
    {
        teams[1].incShields(n);
		return true;
    }
    else if (team == GameObject::Left)
    {
        teams[0].incShields(n);
		return true;
    }
	return false;
}


TeamSystem* TeamSystem::getInstance()
{
    if (instance == nullptr)
    {
        instance = new TeamSystem();
    }
    return instance;
}

void TeamSystem::closeInstance()
{
    delete instance;
    instance = nullptr;
}

//|LUKE|
/*!
\fn     BehaviorControllable *TeamSystem::getPlayer(GameObject::Team team)
\par    team
          team
\brief  See TeamSystem.h
*/
BehaviorControllable *TeamSystem::getPlayer(GameObject::Team team){
	
	//	Check `team`
	if(team != GameObject::Team::Left && team != GameObject::Team::Right) return nullptr;

	//	Check `teams`
	return teams[(((int) team) + 1) / 2].getPlayer();

}

/*!
\fn     bool TeamSystem::setPlayer(GameObject::Team team, BehaviorControllable *player)
\par    team
          team
\par    player
          player
\brief  See TeamSystem.h
*/
bool TeamSystem::setPlayer(GameObject::Team team, BehaviorControllable *player){
	
	//	Check `team`
	if(team != GameObject::Team::Left && team != GameObject::Team::Right) return false;

	//	Update `teams`
	teams[(((int) team) + 1) / 2].setPlayer(player);

	//	Return
	return true;

}

/*!
\fn     bool TeamSystem::removePlayer(GameObject::Team team, BehaviorControllable *player)
\par    team
          team
\par    player
          player
\brief  See TeamSystem.h
*/
bool TeamSystem::removePlayer(GameObject::Team team, BehaviorControllable *player){
	
	//	Check `team`
	if(team != GameObject::Team::Left && team != GameObject::Team::Right) return false;

	//	Update `teams`
	teams[(((int) team) + 1) / 2].removePlayer(player);

	//	Return
	return true;

}

/*!
\fn     BehaviorControllable *TeamSystem::Team::getPlayer()
\brief  See TeamSystem.h
*/
BehaviorControllable *TeamSystem::Team::getPlayer(){

	//	Check if `player` is empty
	if(player.empty()) return nullptr;

	//	Return
	return player.front();

}

/*!
\fn     bool TeamSystem::Team::hasShields()
\brief  See TeamSystem.h
*/
bool TeamSystem::Team::hasShields(){
    return shieldCount > 0;
}

/*!
\fn     void TeamSystem::Team::setPlayer(BehaviorControllable *player)
\param  player
          player
\brief  See TeamSystem.h
*/
void TeamSystem::Team::setPlayer(BehaviorControllable *player){

	//	Check for `NULL`
	if(player == nullptr) return;
	
	//	Variable: Iterator at which `player` should be placed
	std::list<BehaviorControllable *>::iterator it = this -> player.begin();

	//	Find `it`
	while(it != this -> player.end() && (**it).getPriority() > player -> getPriority()) ++it;

	//	Reassign control unit
	if(it == this -> player.begin()){

		//	Release control unit
		if(!this -> player.empty()) this -> player.front() -> releaseControlUnit();

		//	Set control unit
		player -> setControlUnit(controls);

	}

	//	Insert `player`
	this -> player.insert(it, player);

}

/*!
\fn     void TeamSystem::Team::removePlayer(BehaviorControllable *player)
\param  player
          player
\brief  See TeamSystem.h
*/
void TeamSystem::Team::removePlayer(BehaviorControllable *player){

	//	Check if `player` is empty
	if(this -> player.empty()) return;

	//	Variable: Iterator at which `player` was found
	std::list<BehaviorControllable *>::iterator it = this -> player.begin();

	//	Find `it`
	while(*it != player){

		//	Check if `player` is not here
		if((**it).getPriority() < player -> getPriority()) return;

		//	Iterate
		++it;

		//	Check if we have reached the end
		if(it == this -> player.end()) return;

	}

	//	Variable: If the control unit was released
	bool release = this -> player.front() == player;

	//	Remove a player
	this -> player.erase(it);
	
	//	Release control unit
	if(release){
		
		//	Release control unit
		player -> releaseControlUnit();

		//	Re-add control unit
		if(!this -> player.empty()) this -> player.front() -> setControlUnit(controls);

	}

}

//|LUKE|
int TeamSystem::Team::getShieldCount() const {
	return shieldCount;
}

/*!
\fn     void TeamSystem::Team::incShields(int n)
\param  n
          count
\brief  See TeamSystem.h
*/
void TeamSystem::Team::incShields(int n){
	
	//	Add `n` to `shieldCount`
	shieldCount += n;

	//	Check for negatives
	if(shieldCount < 0) shieldCount = 0;

}

/*!
\fn     TeamSystem::Team::Team()
\brief  See TeamSystem.h
*/
TeamSystem::Team::Team() : player(), shieldCount(0), color(1, 1, 1, 1), controls(new ControlUnit()), decision(nullptr){}

//|LUKE|
int TeamSystem::getShieldCount(GameObject::Team team) const {

	//	Check `team`
	if (team != GameObject::Team::Left && team != GameObject::Team::Right) return -1;

	//	Check `teams`
	return teams[(((int)team) + 1) / 2].getShieldCount();

}

void TeamSystem::Team::setColor(const glm::vec4 &col){
	color = col;
}

const glm::vec4 &TeamSystem::Team::getColor() const{
	return color;
}

glm::vec4 TeamSystem::white(1, 1, 1, 1);

bool TeamSystem::setColor(GameObject::Team team, const glm::vec4 &col){
	
	//	Check `team`
	if(team != GameObject::Team::Left && team != GameObject::Team::Right) return false;

	//	Update `teams`
	teams[(((int) team) + 1) / 2].setColor(col);

	//	Return
	return true;

}

const glm::vec4 &TeamSystem::getColor(GameObject::Team team) const{
	
	//	Check `team`
	if(team != GameObject::Team::Left && team != GameObject::Team::Right) return white;

	//	Retrieve from `teams`
	return teams[(((int) team) + 1) / 2].getColor();

}

void TeamSystem::Team::incColor(float dc){
	incrementColor(color, dc);
}

bool TeamSystem::incColor(GameObject::Team team, float dc){
	
	//	Check `team`
	if(team != GameObject::Team::Left && team != GameObject::Team::Right) return false;

	//	Update `teams`
	teams[(((int) team) + 1) / 2].incColor(dc);

	//	Return
	return true;

}

/*!
\fn     ControlUnit *TeamSystem::Team::getControls() const
\param  n
          count
\brief  See TeamSystem.h
*/
ControlUnit *TeamSystem::Team::getControls() const{
	return controls;
}

/*!
\fn     TeamSystem::Team::~Team()
\brief  See TeamSystem.h
*/
TeamSystem::Team::~Team(){

	//	Release `controls` from `player`
	if(!player.empty()) player.front() -> releaseControlUnit();

	//	Free `controls`
	delete controls;

}

/*!
\fn     bool TeamSystem::setDecision(GameObject::Team team, BehaviorButton *dec)
\param  team
          team
\param  dec
          decision
\brief  See TeamSystem.h
*/
bool TeamSystem::setDecision(GameObject::Team team, BehaviorButton *dec){
	
	//	Check `team`
	if(team != GameObject::Team::Left && team != GameObject::Team::Right) return false;

	//	Variable: Previous decision
	BehaviorButton *pre = teams[(((int) team) + 1) / 2].getDecision();

	//	Deselect previous decision
	if(pre) pre -> deactivate(team);

	//	Update `teams`
	teams[(((int) team) + 1) / 2].setDecision(dec);

	//	Return
	return true;

}

/*!
\fn     void TeamSystem::Team::setDecision(BehaviorButton *dec)
\param  dec
          decision
\brief  See TeamSystem.h
*/
void TeamSystem::Team::setDecision(BehaviorButton *dec){
	decision = dec;
}

/*!
\fn     BehaviorButton *TeamSystem::Team::getDecision()
\param  dec
          decision
\brief  See TeamSystem.h
*/
BehaviorButton *TeamSystem::Team::getDecision(){
	return decision;
}

/*!
\fn     BehaviorButton *TeamSystem::getDecision(GameObject::Team team)
\param  team
          team
\brief  See TeamSystem.h
*/
BehaviorButton *TeamSystem::getDecision(GameObject::Team team){
	
	//	Check `team`
	if(team != GameObject::Team::Left && team != GameObject::Team::Right) return nullptr;

	//	Update `teams`
	return teams[(((int) team) + 1) / 2].getDecision();

}

/*!
\fn     bool TeamSystem::clearDecision(GameObject::Team team)
\param  team
          team
\param  dec
          decision
\brief  See TeamSystem.h
*/
bool TeamSystem::clearDecision(GameObject::Team team){
	
	//	Check `team`
	if(team != GameObject::Team::Left && team != GameObject::Team::Right) return false;

	//	Update `teams`
	teams[(((int) team) + 1) / 2].setDecision(nullptr);

	//	Return
	return true;

}

/*!
\fn     const ControlUnit *TeamSystem::getControls(GameObject::Team team) const
\par    team
          team
\brief  See TeamSystem.h
*/
const ControlUnit *TeamSystem::getControls(GameObject::Team team) const{
	
	//	Check `team`
	if(team != GameObject::Team::Left && team != GameObject::Team::Right) return nullptr;

	//	Check `teams`
	return teams[(((int) team) + 1) / 2].getControls();

}

/*!
\fn     BehaviorControllable *TeamSystem::getPlayer(GameObject::Team team) const
\par    team
          team
\brief  See TeamSystem.h
*/
bool TeamSystem::checkInitContDisplay(){
	
	//	Variable: `initContDisplay` stored
	bool temp = initContDisplay;

	//	Set `initContDisplay` to false
	initContDisplay = false;

	//	Return
	return temp;

}