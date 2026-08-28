/*!
\file   BehaviorDrone.cpp
\author Kevin Shin
\date   2-13-2023
\brief
        Functions for managing the behavior of a player drone
\par    Copyright © 2023 DigiPen, All rights reserved.
*/

#include <glfw/glfw3.h>

#include "Window.h"
#include "Renderer.h"
#include "Trace.h"
#include "TeamSystem.h"
#include "ParticleGenerator.h"

#include "BehaviorDrone.h"

/*!
\fn     BehaviorDrone::BehaviorDrone(int up, int dn, int lf, int rt, int sh, float cd, float sp)
\param  up
          up
\param  dn
          down
\param  lf
          left
\param  rt
          right
\param  sh
          shoot
\param  cd
          cooldown
\param  spd
          speed
\brief  See BehaviorDrone.h
*/
BehaviorDrone::BehaviorDrone(int up, int dn, int lf, int rt, int sh, float cd, float spd) : BehaviorControllable(up, dn, lf, rt, sh, cd), speed(spd), teamSet(false), droneParticleTimer(0.1f) {}

/*!
\fn     BehaviorDrone::BehaviorDrone(const BehaviorDrone &that)
\param  that
          source
\brief  See BehaviorDrone.h
*/
BehaviorDrone::BehaviorDrone(const BehaviorDrone &that) : BehaviorControllable(that), speed(that.speed), teamSet(false), droneParticleTimer(that.droneParticleTimer) {}

/*!
\fn     void BehaviorDrone::update(float dt)
\param  dt
          dt
\brief  See BehaviorDrone.h
*/
void BehaviorDrone::update(float dt){

	//	Get and save `physics` if needed
	if(getPhysics() == nullptr){
		
		//	Variable: game object parent of `this`
		GameObject *parent = getParent();
		
		//	Check `parent`
		if(parent == nullptr) return;

		//	Grab and check `physics`
		setPhysics(dynamic_cast<Physics *>(parent -> get(ComponentTypeEnum::cPhysics)));
		if(getPhysics() == nullptr) return;

		//	Set drag
		getPhysics() -> setDrag(1.5f);
	}

	//	Update team if necessary
	if(!teamSet){
		/*
		//	Variable: parent of the behavior
		GameObject* parent = getParent();

		//	Check `parent`
		if(parent) teamSet = TeamSystem::getInstance() -> incPlayers(parent -> getTeam());
		/*/
		teamSet = true;

	}
	
	/*	Variables:
	a: Acceleration calculated from input
	length: length of `a`
	*/
	glm::vec3 a(x(), y(), 0);
	float length = glm::length(a);

	//	Normalize and scale
	if(length > 0) a *= speed / length;

	//	Set acceleration
    getPhysics() -> setAcceleration(a);

	// generate drone emission
	generateParticles(dt);
}

/*!
\fn     Component *BehaviorDrone::clone() const
\brief  See BehaviorDrone.h
*/
Component *BehaviorDrone::clone() const{
	return new BehaviorDrone(*this);
}

/*!
\fn     void BehaviorDrone::setSpeed(float spd)
\param  speed
          spd
\brief  See BehaviorDrone.h
*/
void BehaviorDrone::setSpeed(float spd){
    speed = spd;
}

/*!
\fn     void generateParticles(float dt)
\param  dt
		  The dt
\brief  See BehaviorDrone.h
*/
void BehaviorDrone::generateParticles(float dt) {
	/*|BENEDICT|*/
	if (droneParticleTimer < 0.0f) // timeout
	{
		// Reset timer and generate particle.
		droneParticleTimer = 0.1f;
		ParticleGenerator* particleGenerator = ParticleGenerator::getInstance();
		glm::vec3 velocity = getPhysics()->getVelocity();
		if (velocity != glm::vec3(0.0f, 0.0f, 0.0f)) {
			GameObject* gameObject = getParent();
			if (gameObject) {
				particleGenerator->spawnParticles(gameObject, Particle::Emission);
			}
		}
	}
	else
	{
		droneParticleTimer -= dt;
	}
}

/*!
\fn    BehaviorDrone::~BehaviorDrone()
\brief See BehaviorDrone.h
*/
BehaviorDrone::~BehaviorDrone(){
	/*
	//	Remove player from team
	if(teamSet){

		//	Variable: parent of the behavior
		GameObject* parent = getParent();

		//	Check `parent`
		if(parent) TeamSystem::getInstance() -> decPlayers(parent -> getTeam());
	}
	//*/
}