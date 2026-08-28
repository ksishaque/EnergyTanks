/*!
\file   BehaviorPlayer.cpp
\author Kevin Shin
\date   10-4-2022
\brief
        Functions for managing the behavior of a player tank
\par    Copyright © 2022 DigiPen, All rights reserved.
*/

#include <glfw/glfw3.h>

#include "BehaviorBullet.h"
#include "CircleCollider.h"
#include "Collider.h"
#include "GraphicsUnit.h"
#include "SoundSystem.h"
#include "Window.h"
#include "Renderer.h"
#include "Trace.h"

#include "MeshManager.h"
#include "ParticleGenerator.h"
#include "PowerUp.h"
#include "PowerUpConfuse.h"
#include "PowerUpGhosting.h"
#include "PowerUpMoreBullets.h"
#include "PowerUpRapidFire.h"
#include "PowerUpRapidSpeed.h"
#include "PowerUpVudoo.h"
#include "TeamSystem.h"

#include "BehaviorPlayer.h"

static float timer = 0; // sound timer

/*!
\fn     BehaviorPlayer::BehaviorPlayer()
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
\brief  See BehaviorPlayer.h
*/
BehaviorPlayer::BehaviorPlayer(int up, int dn, int lf, int rt, int sh, float cd, float spd, float rotSpd, int gamepadCode) :
	Behavior(), up(up), down(dn), left(lf), right(rt), 
	shoot(sh), transform(nullptr), cooldown(0), maxCooldown(cd), 
	speed(spd), rotSpeed(rotSpd), powerup(nullptr), 
	tracksParticleTimer(0.1f), teamSet(false), gamepadNum(gamepadCode) {
}

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

    //	Get and save `transform` if needed
    if(transform == nullptr){

        //	Variable: game object parent of `this`
        GameObject* parent = getParent();

        //	Check `parent`
        if(parent == nullptr) return;

        //	Grab and check `transform`
        transform = dynamic_cast<Transform *>(parent -> get(ComponentTypeEnum::cTransform));
        if(transform == nullptr) return;
    }

	//	Update team if necessary
	if(!teamSet){

		//	Variable: parent of the behavior
		GameObject* parent = getParent();

		//	Check `parent`
		if(parent) teamSet = TeamSystem::getInstance() -> incPlayers(parent -> getTeam());
	}
	
	//	Run input controller
    inputMovement();

    //|KEVIN|
    GameObject* object = getParent();

    MoreBullets* check = dynamic_cast<MoreBullets*>(powerup);
    if (check) {

        // Activate "MoreBullets" power up
        if (glfwGetKey(Window::getInstance() -> getHandle(), GLFW_KEY_N) == GLFW_PRESS) {
            check->increaseTier();
        }
        else {
            check->resetIncreaseCheck();
        }

        float startOff = -15.0f * (check -> getTier() - 1);
        for(int i = 1; i < check->getTier(); i += 1){
            inputBullet(dt, object->getTeam(), startOff, false);
            startOff += 30;
        }
        inputBullet(dt, object->getTeam(), startOff);
        //Trace::message("Bullet Count: %i", check -> getTier());
    }
    else inputBullet(dt, object -> getTeam());

    //|KEVIN|
    // Activate "RapidFire" power up
    if(glfwGetKey(Window::getInstance() -> getHandle(), GLFW_KEY_R) == GLFW_PRESS){
        setPowerUp(new RapidFire());
    }

    // Activate "RapidSpeed" power up
    if (glfwGetKey(Window::getInstance() -> getHandle(), GLFW_KEY_F) == GLFW_PRESS){
        setPowerUp(new RapidSpeed());
    }

    // Activate "Ghosting" power up
    if (glfwGetKey(Window::getInstance() -> getHandle(), GLFW_KEY_G) == GLFW_PRESS){
        setPowerUp(new Ghosting());
    }

    if(glfwGetKey(Window::getInstance() -> getHandle(), GLFW_KEY_B) == GLFW_PRESS){
        setPowerUp(new MoreBullets(5, 2));
    }

    if(glfwGetKey(Window::getInstance() -> getHandle(), GLFW_KEY_V) == GLFW_PRESS){
        setPowerUp(new Vudoo());
    }

    if (glfwGetKey(Window::getInstance()->getHandle(), GLFW_KEY_C) == GLFW_PRESS) {
        setPowerUp(new Confuse());
    }

    if(powerup) if(powerup -> update(*this, dt)){
        powerup -> shutdown(*this);
        delete powerup;
        powerup = nullptr;
    }
    
    int o = 0;

    timer -= dt;
    if (glfwGetKey(Window::getInstance() -> getHandle(), GLFW_KEY_O) == GLFW_PRESS && timer < 0)
    {
        SoundSystem::play("shooting", 1.0f, false);
        timer = 5;
    }
    if (glfwGetKey(Window::getInstance() -> getHandle(), GLFW_KEY_I) == GLFW_PRESS)
    {
        SoundSystem::stopAll();
        timer = 0;
    }

    //|BENEDICT|
    generateTracks(dt);
}

/*!
\fn     void inputMovement()
\brief  See InputController.h
*/
void BehaviorPlayer::inputMovement(){
	
	//	Check parameters
	if(getPhysics() == nullptr) return;
	
#if 0
    //Archived code for future purposes

	/*	Variables:
	inFB: front-back input from window
		B: input state is going backwards
		N: input state is staying still
		F: input state is going forewards
	inLR: left-right input from window
		R: input state is going right
		S: input state is going straight
		L: input state is going left
	*/
	enum FB{B = -1, N = 0, F = 1} inFB = N;
	enum LR{R = -1, S = 0, L = 1} inLR = S;

    //	Check and add inputs
    if(glfwGetKey(Window::getInstance() -> getHandle(), up) == GLFW_PRESS) inFB = (FB)(inFB + 1);
    if(glfwGetKey(Window::getInstance() -> getHandle(), down) == GLFW_PRESS) inFB = (FB)(inFB - 1);
    if(glfwGetKey(Window::getInstance() -> getHandle(), left) == GLFW_PRESS) inLR = (LR)(inLR + 1);
    if(glfwGetKey(Window::getInstance() -> getHandle(), right) == GLFW_PRESS) inLR = (LR)(inLR - 1);
#endif
	
    //|KEVIN|
    if(powerup && powerup->getType() == PowerUp::powerType::ghosting){

        // Get 'Ghosting' class
        Ghosting *ghost = dynamic_cast<Ghosting *>(powerup);
        FB inFBt = N;
        LR inLRt = S;
        bool set = !ghost->isDisturbed();

        //	Check and add inputs
        if(glfwGetKey(Window::getInstance() -> getHandle(), up) == GLFW_PRESS){
            inFBt = (FB)(inFBt + 1);
            if(ghost->getValue() == Ghosting::DisruptionValue::up) ghost -> setDisturbed();
        }
        else if(ghost->getValue() == Ghosting::DisruptionValue::up) ghost -> setDisturbed(false);
        if(glfwGetKey(Window::getInstance() -> getHandle(), down) == GLFW_PRESS){
            inFBt = (FB)(inFBt - 1);
            if(ghost->getValue() == Ghosting::DisruptionValue::down) ghost -> setDisturbed();
        }
        else if(ghost->getValue() == Ghosting::DisruptionValue::down) ghost -> setDisturbed(false);
        if(glfwGetKey(Window::getInstance() -> getHandle(), left) == GLFW_PRESS){
            inLRt = (LR)(inLRt + 1);
            if(ghost->getValue() == Ghosting::DisruptionValue::left) ghost -> setDisturbed();
        }
        else if(ghost->getValue() == Ghosting::DisruptionValue::left) ghost -> setDisturbed(false);
        if(glfwGetKey(Window::getInstance() -> getHandle(), right) == GLFW_PRESS){
            inLRt = (LR)(inLRt - 1);
            if(ghost->getValue() == Ghosting::DisruptionValue::right) ghost -> setDisturbed();
        }
        else if(ghost->getValue() == Ghosting::DisruptionValue::right) ghost -> setDisturbed(false);

        if(set){
            inFB = inFBt;
            inLR = inLRt;
        }

    }
    else{
        inFB = N;
        inLR = S;

        //	Check and add inputs
        if(glfwGetKey(Window::getInstance() -> getHandle(), up) == GLFW_PRESS) inFB = (FB)(inFB + 1);
        if(glfwGetKey(Window::getInstance() -> getHandle(), down) == GLFW_PRESS) inFB = (FB)(inFB - 1);
        if(glfwGetKey(Window::getInstance() -> getHandle(), left) == GLFW_PRESS) inLR = (LR)(inLR + 1);
        if(glfwGetKey(Window::getInstance() -> getHandle(), right) == GLFW_PRESS) inLR = (LR)(inLR - 1);
    }
	
	//	Rotate according to `inLR`
	getPhysics()->setVelocityRotate(rotSpeed * inLR);
	
	//	Set movement
	if(inFB == N) getPhysics() -> setVelocity(glm::vec3(0, 0, 0));
	else if(inFB > N) getPhysics() -> setRotatedVelocity(glm::vec3(0, speed, 0));
	else getPhysics() -> setRotatedVelocity(glm::vec3(0, speed * -0.8, 0));

}

/*!
\fn     void generateTracks(float dt)
\brief  See BehaviorPlayer.h
*/
void BehaviorPlayer::generateTracks(float dt) {
    /*|BENEDICT|*/
    if (tracksParticleTimer < 0.0f) // timeout
    {
        // Reset timer and generate particle.
        tracksParticleTimer = 0.1f;
        ParticleGenerator* particleGenerator = ParticleGenerator::getInstance();
        glm::vec3 velocity = getPhysics()->getVelocity();
        if (velocity != glm::vec3(0.0f, 0.0f, 0.0f)) {
            GameObject* gameObject = getParent();
            if (gameObject) {
                particleGenerator->spawnParticles(gameObject, Particle::Tracks ,1);
            }
        }
    }
    else
    {
        tracksParticleTimer -= dt;
    }

}

/*!
\fn     BehaviorPlayer::BehaviorPlayer()
\param  source
          that
\brief  See BehaviorPlayer.h
*/
BehaviorPlayer::BehaviorPlayer(const BehaviorPlayer &that) : 
	Behavior(that), up(that.up), down(that.down), left(that.left), right(that.right), 
	shoot(that.shoot), transform(nullptr), cooldown(0), maxCooldown(that.maxCooldown), 
	speed(that.speed), rotSpeed(that.speed), powerup(nullptr), 
	tracksParticleTimer(that.tracksParticleTimer), teamSet(false), gamepadNum(that.gamepadNum) {
}

/*!
\fn     Component *BehaviorPlayer::clone() const
\brief  See BehaviorPlayer.h
*/
Component *BehaviorPlayer::clone() const{
	return new BehaviorPlayer(*this);
}

/*!
\fn     void BehaviorPlayer::setUp(int key)
\param  key
          key
\brief  See BehaviorPlayer.h
*/
void BehaviorPlayer::setUp(int key){
	if(key > -1) up = key;
}

/*!
\fn     void BehaviorPlayer::setDown(int key)
\param  key
          key
\brief  See BehaviorPlayer.h
*/
void BehaviorPlayer::setDown(int key){
	if(key > -1) down = key;
}

/*!
\fn     void BehaviorPlayer::setLeft(int key)
\param  key
          key
\brief  See BehaviorPlayer.h
*/
void BehaviorPlayer::setLeft(int key){
	if(key > -1) left = key;
}

/*!
\fn     void BehaviorPlayer::setRight(int key)
\param  key
          key
\brief  See BehaviorPlayer.h
*/
void BehaviorPlayer::setRight(int key){
	if(key > -1) right = key;
}

/*!
\fn     void BehaviorPlayer::setShoot(int key)
\param  key
          key
\brief  See BehaviorPlayer.h
*/
void BehaviorPlayer::setShoot(int key){
    if(key > -1) shoot = key;
}

/*!
\fn     void BehaviorPlayer::setShoot(int key)
\param  key
		  key
\brief  See BehaviorPlayer.h
*/
void BehaviorPlayer::setGamepad(int key) {
	if (key > -1) gamepadNum = key;
}

/*!
\fn     void BehaviorPlayer::inputBullet(float dt)
\param  dt
          dt
\brief  See BehaviorPlayer.h
*/
void BehaviorPlayer::inputBullet(float dt, GameObject::Team team, float off, bool activeCD){
	
	//	Check parameters
	if(getPhysics() == nullptr || transform == nullptr) return;
	
	//  Update `cooldown`
	if(cooldown < maxCooldown){
        if(activeCD) cooldown += dt;
    }
	
	//  Check if the tank is shooting
	else if(glfwGetKey(Window::getInstance() -> getHandle(), shoot) == GLFW_PRESS){
	
		//	Variable: game object parent of `this`
		GameObject* parent = getParent();
	
		//  Check `parent`
		if (parent == nullptr) return;
		
		/*	Variables:
		manager: manager to add the new bullet to
		bullet: bullet to add to `manager`
		col: collider of `bullet`
		cranberry: sprite of `bullet`
		shot: physics of `bullet`
		*/
		ObjectManager* manager = parent->getManager();
		GameObject *bullet = new GameObject();
		CircleCollider *col = new CircleCollider();
		Sprite *cranberry = new Sprite();
		Physics* shot = new Physics();
        BehaviorBullet* status = new BehaviorBullet();

        //  Set `cranberry`
		Mesh *mesh;
		MeshManager::getInstance()->getMesh(MeshManager::MeshType::single, mesh);

		cranberry -> addToGraphics(makeGraphicsUnit(mesh, nullptr, GraphicsUnit::Type::guParticle));

        //	Set `col`
        col -> setRadius(7);
        col -> setType(Collider::Type::circle);

        //	Set `bullet`
        bullet -> setTeam(team); // temp set as none
        bullet -> setType(GameObject::Bullet);
        bullet -> add(status);
        bullet -> add(col);
        bullet -> add(shot);
        bullet -> add(new Transform(transform -> getTranslation(), glm::vec3(10, 10, 1), transform -> getRotation()));
        bullet -> add(cranberry);
        
        //  Offset `bullet`
        shot -> setRotatedVelocity(glm::vec3(off, 75, 0));
        shot -> update(1);
        shot -> updateOldTrans();
        
        //  Set 'shot'
        shot -> setRotatedVelocity(glm::vec3(0, bulletSpeed, 0));
        
        //	Add `bullet` to `man`
        manager -> addObject(bullet);
        
        //  Reset `cooldown`
        if(activeCD) cooldown = 0;
        
        // Shooting sound
        SoundSystem::play("shooting", 1.0f, false);

		// Generate bullet emission
		generateBulletEmissions(bullet, dt);

        //  Debug rapid fire
#if _DEBUG
        if(glfwGetKey(Window::getInstance() -> getHandle(), GLFW_KEY_BACKSPACE) == GLFW_PRESS) cooldown = maxCooldown * 0.9f;
#endif
	}
}

/*!
\fn     void generateBulletEmissions(GameObject* bullet, float dt)
\brief  See BehaviorPlayer.h
*/
void BehaviorPlayer::generateBulletEmissions(GameObject* bullet, float dt) {
	/*|BENEDICT|*/
	ParticleGenerator* particleGenerator = ParticleGenerator::getInstance();
	particleGenerator->spawnParticles(bullet, Particle::Emission, 10);
}

/*!
\fn     void BehaviorPlayer::setCooldown(float cooldown)
\param  cooldown
          cooldown
\brief  See BehaviorPlayer.h
*/
void BehaviorPlayer::setCooldown(float cooldown){
    maxCooldown = cooldown;
}

/*!
\fn     float BehaviorPlayer::getCooldown()
\brief  See BehaviorPlayer.h
*/
float BehaviorPlayer::getCooldown(){
    return maxCooldown;
}

//|KEVIN|
void BehaviorPlayer::setPowerUp(PowerUp *powerup){
    if(powerup == nullptr) return;
    if(this -> powerup){
        this -> powerup -> shutdown(*this);
        delete this -> powerup;
    }
    this -> powerup = powerup;
    powerup -> initialize(*this);
}

//|KEVIN|
void BehaviorPlayer::setSpeed(float speed){
    this->speed = speed;
}

//|KEVIN|
float BehaviorPlayer::getSpeed(){
    return speed;
}

//|KEVIN|
int BehaviorPlayer::getUp(){
    return up;
}

//|KEVIN|
int BehaviorPlayer::getDown(){
    return down;
}

//|KEVIN|
int BehaviorPlayer::getLeft(){
    return left;
}

//|KEVIN|
int BehaviorPlayer::getRight(){
    return right;
}

//|KEVIN|
int BehaviorPlayer::getShoot() {
    return shoot;
}

/*!
\fn    BehaviorPlayer::~BehaviorPlayer()
\brief See BehaviorPlayer.h
*/
BehaviorPlayer::~BehaviorPlayer(){

	//	Remove player from team
	if(teamSet){

		//	Variable: parent of the behavior
		GameObject* parent = getParent();

		//	Check `parent`
		if(parent) TeamSystem::getInstance() -> decPlayers(parent -> getTeam());
	}
}