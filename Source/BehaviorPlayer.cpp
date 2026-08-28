/*!
\file   BehaviorPlayer.cpp
\author Kevin Shin
\date   2-13-2023
\brief
        Functions for managing the behavior of a player tank
\par    Copyright © 2023 DigiPen, All rights reserved.
*/

#include <glfw/glfw3.h>
#include <chrono>
#include <thread>

#include "BehaviorBullet.h"
#include "CircleCollider.h"
//#include "ControllerInput.h"
#include "GraphicsUnit.h"
#include "MeshManager.h"
#include "ObjectContainer.h"
#include "ParticleGenerator.h"
#include "PauseSystem.h"
#include "PowerUp.h"
#include "PowerUpMoreBullets.h"
#include "PowerUpBurst.h"
#include "Renderer.h"
#include "SoundSystem.h"
#include "Trace.h"
#include "TeamSystem.h"
#include "Window.h"

#include "BehaviorPlayer.h"
#ifdef BEHAVIOR_PLAYER_UNIQUE_SHOOT_SOUND
#endif

/*!
\fn     BehaviorPlayer::BehaviorPlayer(float cd, float fore, float back, float turn)
\param  cd
          cooldown
\param  fore
          forSpeed
\param  back
          backSpeed
\param  turn
          turnSpeed
\brief  See BehaviorPlayer.h
*/
#ifdef BEHAVIOR_PLAYER_UNIQUE_SHOOT_SOUND
BehaviorPlayer::BehaviorPlayer(float cd, float fore, float back, float turn) : BehaviorControllable(), cd(0), mCd(cd), moveSoundTimer(0), fore(fore), back(back), turn(turn), powerup(nullptr), tracksParticleTimer(15), dt(0), active(false), shootSound(""){}
#else
BehaviorPlayer::BehaviorPlayer(float cd, float fore, float back, float turn) : BehaviorControllable(), cd(0), mCd(cd), moveSoundTimer(0), fore(fore), back(back), turn(turn), powerup(nullptr), tracksParticleTimer(15), dt(0), active(false){}
#endif

/*!
\fn     BehaviorPlayer::BehaviorPlayer(const BehaviorPlayer &that)
\param  that
          source
\brief  See BehaviorPlayer.h
*/
#ifdef BEHAVIOR_PLAYER_UNIQUE_SHOOT_SOUND
BehaviorPlayer::BehaviorPlayer(const BehaviorPlayer &that) : BehaviorControllable(), cd(0), mCd(that.mCd), moveSoundTimer(0), fore(that.fore), back(that.back), turn(that.turn), powerup(nullptr), tracksParticleTimer(15), dt(0), active(that.active), shootSound(that.shootSound){}
#else
BehaviorPlayer::BehaviorPlayer(const BehaviorPlayer &that) : BehaviorControllable(), cd(0), mCd(that.mCd), moveSoundTimer(0), fore(that.fore), back(that.back), turn(that.turn), powerup(nullptr), tracksParticleTimer(15), dt(0), active(that.active){}
#endif

/*!
\fn     void BehaviorPlayer::update(float dt)
\param  dt
          dt
\brief  See BehaviorPlayer.h
*/
void BehaviorPlayer::update(float dt){

	//	Get and save `physics` if needed
	if(getPhysics() == nullptr){
		
		//	Variable: game object parent of `this`
		GameObject *parent = getParent();
		
		//	Check `parent`
		if(parent == nullptr) return;

		//	Grab and check `physics`
		setPhysics(dynamic_cast<Physics *>(parent -> get(ComponentTypeEnum::cPhysics)));
		if(getPhysics() == nullptr) return;

	}

	if (powerup != nullptr) {
		bool stop = powerup->update(*this, dt);
		if (stop == true){// powerup->update(*this, dt)) {
 			active = false;
			powerup->shutdown(*this);
			delete powerup;
			powerup = nullptr;
		}
	}

	//	Update `dt` and `cd`
	this -> dt = dt;
	if(cd > 0) cd -= dt;
	else cd = 0;

	//	Update `moveSoundTimer`
	if(moveSoundTimer > 0) moveSoundTimer -= dt;
	else moveSoundTimer = 0;

	//	Update parent
	BehaviorControllable::update(dt);

}

/*!
\fn     Component *BehaviorPlayer::clone() const
\brief  See BehaviorPlayer.h
*/
Component *BehaviorPlayer::clone() const{
	return new BehaviorPlayer(*this);
}

/*!
\fn     void generateTankTracks(float spd)
\param  spd
		  speed
\brief  See BehaviorPlayer.h
*/
void BehaviorPlayer::generateTankTracks(float speed) {
	/*|BENEDICT|*/
	if (tracksParticleTimer < 0.0f) // timeout
	{
		// Reset timer and generate particle.
		while(tracksParticleTimer < 0) tracksParticleTimer += 15;
		ParticleGenerator* particleGenerator = ParticleGenerator::getInstance();
		particleGenerator->spawnParticles(getParent(), Particle::Tracks);
	}
	tracksParticleTimer -= dt * speed;
}

/*!
\fn    BehaviorPlayer::~BehaviorPlayer()
\brief See BehaviorPlayer.h
*/
BehaviorPlayer::~BehaviorPlayer(){}

/*!
\fn     void BehaviorPlayer::setPowerUp(PowerUp *powerup)
\param  speed
          spd
\brief  See BehaviorPlayer.h
*/
void BehaviorPlayer::setPowerUp(PowerUp *powerup){

	if(powerup == nullptr) return;

	if(this -> powerup != nullptr) this -> powerup -> shutdown(*this);

	//	set `active`
	active = true;

	//	set `powerup` and initialize
	this -> powerup = powerup;
	this->powerup->initialize(*this);
}

#ifdef BEHAVIOR_PLAYER_UNIQUE_SHOOT_SOUND
void BehaviorPlayer::setShootSound(std::string str)
{
	shootSound = str;
}
#endif

/*!
\fn     void BehaviorPlayer::setFore(float spd)
\param  spd
          speed
\brief  See BehaviorPlayer.h
*/
void BehaviorPlayer::setFore(float spd){
	fore = spd;
}

/*!
\fn     float BehaviorPlayer::getFore() const
\brief  See BehaviorPlayer.h
*/
float BehaviorPlayer::getFore() const{
	return fore;
}

/*!
\fn     void BehaviorPlayer::setBack(float spd)
\param  spd
          speed
\brief  See BehaviorPlayer.h
*/
void BehaviorPlayer::setBack(float spd){
	back = spd;
}

/*!
\fn     float BehaviorPlayer::getBack() const
\brief  See BehaviorPlayer.h
*/
float BehaviorPlayer::getBack() const{
	return back;
}

/*!
\fn     void BehaviorPlayer::setTurn(float spd)
\param  spd
          speed
\brief  See BehaviorPlayer.h
*/
void BehaviorPlayer::setTurn(float spd){
	turn = spd;
}

/*!
\fn     float BehaviorPlayer::getTurn() const
\brief  See BehaviorPlayer.h
*/
float BehaviorPlayer::getTurn() const{
	return turn;
}

/*!
\fn     void actionCall(ControlType act, ControlManager::KeyState key)
\param  act
          action
\param  key
          keyState
\brief  See BehaviorControllable.h
*/
void BehaviorPlayer::actionCall(ControlUnit::ControlType act, ControlManager::KeyState key){

	//	Check if the game is paused or if `physics` is `NULL`
	if(PauseSystem::getInstance() -> isPaused() || getPhysics() == nullptr) return;
	
	//	Up input
	if(act == ControlUnit::ControlType::UP && key == ControlManager::KeyState::HELD){

		//	Set velocity
		getPhysics() -> setRotatedVelocity(glm::vec3(0, fore, 0));

		//	Draw tracks
		generateTankTracks(fore);

		//	Make movement sound
		if(moveSoundTimer <= 0){
			
			//	Play sound
			SoundSystem::play("playerMove", false);

			//	Reset `moveSoundTimer`
			moveSoundTimer += 0.125f;

		}

		//	Return
		return;

	}
	
	//	Down input
	if(act == ControlUnit::ControlType::DOWN && key == ControlManager::KeyState::HELD){

		//	Set velocity
		getPhysics() -> setRotatedVelocity(glm::vec3(0, -back, 0));

		//	Draw tracks
		generateTankTracks(back);

		//	Make movement sound
		if(moveSoundTimer <= 0){
			
			//	Play sound
			SoundSystem::play("playerMove", false);

			//	Reset `moveSoundTimer`
			moveSoundTimer += 0.11f;

		}

		//	Return
		return;

	}

	//	If neither up nor down inputs are active, then Y_NEUTRAL will be used
	if(act == ControlUnit::ControlType::Y_NEUTRAL){
 
		//	Set velocity
		getPhysics() -> setRotatedVelocity(glm::vec3(0, 0, 0));

		//	Return
		return;

	}
	
	//	Left input
	if(act == ControlUnit::ControlType::LEFT){
		
		if(key == ControlManager::KeyState::HELD){

			//	Set velocity
			getPhysics() -> setVelocityRotate(turn);

			//	Return
			return;

		}

	}
	
	//	Right input
	if(act == ControlUnit::ControlType::RIGHT && key == ControlManager::KeyState::HELD){

		//	Set velocity
		getPhysics() -> setVelocityRotate(-turn);

		//	Return
		return;

	}

	//	If neither up nor down inputs are active, then X_NEUTRAL will be used
	if(act == ControlUnit::ControlType::X_NEUTRAL){

		//	Set velocity
		getPhysics() -> setVelocityRotate(0);

		//	Return
		return;

	}
	
	//	First input
	if(act == ControlUnit::ControlType::FIRST && key == ControlManager::KeyState::HELD && cd <= 0){

		// Check "powerup"
 		if (powerup != nullptr) {
			if (powerup->getType() == PowerUp::moreBullets) {
				// Cast to MoreBullets class
				MoreBullets* pup = dynamic_cast<MoreBullets*>(powerup);
				// Get tier of class
				int tier = pup->getTier();
				// Make bullets based on current tier
				if (tier == 2) {
					// Make 2 bullets
					spawnBullet(10);
					spawnBullet(0);
					spawnBullet(-10);
				}
			}
			else if (powerup->getType() == PowerUp::burst) {
				spawnBullet(0); //temp fix
				powerup->shootEffect(*this);
			}
			else if (powerup->getType() == PowerUp::pierce) {
				powerup->shootEffect(*this);
			}
			else if (powerup->getType() == PowerUp::stealth) {
				powerup->shootEffect(*this);
			}
			else {
				spawnBullet(0);
			}
		}
		else {
			// Make 1 Bullet
			spawnBullet(0);
		}

		//	Return
		return;

	}
	
	//	Second input
	if(act == ControlUnit::ControlType::SECOND && key == ControlManager::KeyState::PRESSED) PauseSystem::getInstance() -> pauseFull();

}

/*!
\fn     void BehaviorPlayer::setCooldown(float t)
\param  t
          time
\brief  See BehaviorPlayer.h
*/
void BehaviorPlayer::setCooldown(float t){
	cd = t;
}

/*!
\fn     float BehaviorPlayer::getCooldown() const
\brief  See BehaviorPlayer.h
*/
float BehaviorPlayer::getCooldown() const{
	return cd;
}

/*!
\fn     void BehaviorPlayer::setMaxCooldown(float t)
\param  t
		  time
\brief  See BehaviorPlayer.h
*/
void BehaviorPlayer::setMaxCooldown(float t){
	mCd = t;
}

/*!
\fn     float BehaviorPlayer::getMaxCooldown() const
\brief  See BehaviorPlayer.h
*/
float BehaviorPlayer::getMaxCooldown() const{
	return mCd;
}

void BehaviorPlayer::spawnBullet(float xOffset, bool passThrough, float newAlpha){
	//	Update `cd`
   	cd += mCd;

	// Limit Cooldown if goes over
	if (cd > mCd) {
		cd = mCd;
	}

	//	Variable: game object parent of `this`
	GameObject* parent = getParent();

	//	Check `parent`
	if (parent == nullptr) return;

	//	Variable: Transform of `parent`
	Transform* parTransform = dynamic_cast<Transform*>(parent->get(ComponentTypeEnum::cTransform));

	/*	Variables:
	manager: manager to add the new bullet to
	bullet: bullet to add to `manager`
	col: collider of `bullet`
	cranberry: sprite of `bullet`
	shot: physics of `bullet`
	*/
	ObjectContainer* manager = parent->getManager();
	GameObject* bullet = new GameObject();
	CircleCollider* col = new CircleCollider();
	Sprite* cranberry = new Sprite();
	Physics* shot = new Physics();
	BehaviorBullet* status = new BehaviorBullet(passThrough);

	//|KEVIN|
	if (newAlpha < 1.0f && newAlpha > 0.0f) {
		cranberry->setColor(glm::vec4(1, 1, 1, newAlpha));
		status->doTrailing(false);
	}

	//	Set `cranberry`
	Mesh* mesh;
	MeshManager::getInstance()->getMesh(MeshManager::MeshType::single, mesh);
	cranberry->addToGraphics(makeGraphicsUnit(mesh, nullptr, GraphicsUnit::Type::guBullet));
	MeshManager::getInstance()->getMesh(MeshManager::MeshType::circle, mesh);
	for (float i = 2; i < 6; i += 0.25f) cranberry->addToGraphics(new GraphicsUnitMutable(mesh, nullptr, GraphicsUnit::Type::guGlow3, nullptr, 0, 0, 0, 0, 0, i, i, 1, 0, glm::vec4(1, 1, 1, 0.03125f)));

	//	Set `col`
	col->setRadius(10);
	col->setType(Collider::Type::circle);

	//	Set `bullet`
	bullet->setTeam(parent->getTeam()); // temp set as none
	bullet->setType(GameObject::Bullet);
	bullet->add(status);
	bullet->add(col);
	bullet->add(shot);
	bullet->add(new Transform(parTransform->getTranslation(), glm::vec3(10, 10, 1), parTransform->getRotation()));
	bullet->add(cranberry);

	//  Offset `bullet`
	shot->setRotatedVelocity(glm::vec3(0, 65, 0));
	shot->setVelocityRotate(xOffset);
	shot->update(1);
	shot->setRotatedVelocity(glm::vec3(0, 10, 0));
	shot->update(1);

	//  Set 'shot'
	shot->setRotatedVelocity(glm::vec3(0, 500, 0));

	//	Add `bullet` to `man`
	manager->addObject(bullet);

	// Shooting sound
#ifdef BEHAVIOR_PLAYER_UNIQUE_SHOOT_SOUND
	SoundSystem::play(shootSound, false);
#else
	SoundSystem::play("playerShoot", false);
#endif

	// Generate bullet emission
	ParticleGenerator::getInstance()->spawnParticles(bullet, Particle::Emission);

	return;
}

/*!
\fn     void BehaviorPlayer::gainControl()
\brief  See BehaviorPlayer.h
*/
void BehaviorPlayer::gainControl(){
	cd = mCd;
}

/*!
\fn     void BehaviorPlayer::activePowerUp()
\brief  See BehaviorPlayer.h
*/
bool BehaviorPlayer::activePowerUp() {
	if(this == nullptr) return false;
	return active;
}

/*!
\fn     void BehaviorPlayer::getPowerUp()
\brief  See BehaviorPlayer.h
*/
PowerUp* BehaviorPlayer::getPowerUp() const{
	if (this == nullptr) return nullptr;
	return powerup;
}