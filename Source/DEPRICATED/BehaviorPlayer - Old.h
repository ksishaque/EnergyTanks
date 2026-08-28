/*!
\file   BehaviorPlayer.h
\author Kevin Shin
\date   10-4-2022
\brief
        Functions for managing the behavior of a player tank
\par    Copyright © 2022 DigiPen, All rights reserved.
*/

#pragma once

class BehaviorPlayer;

#include "GameObject.h"

#include "Behavior.h"

class PowerUp;
struct GLFWwindow;
class GameObject;

static const float bulletSpeed = 500.0f;

class BehaviorPlayer : public Behavior{
	public:

		/*!
		\fn     BehaviorPlayer(int up, int down, int left, int right)
		\param  up
		          Key code for up input; Defaulted to GLFW_KEY_UP
		\param  down
		          Key code for down input; Defaulted to GLFW_KEY_DOWN
		\param  left
		          Key code for left input; Defaulted to GLFW_KEY_LEFT
		\param  right
		          Key code for right input; Defaulted to GLFW_KEY_RIGHT
		\param  shoot
		          Key code for shoot input; Defaulted to GLFW_KEY_SPACE
		\return Constructed player behavior
		\brief
		        This function constructs a new behavior for a player.
		*/
		BehaviorPlayer(int up = 265, int down = 264, int left = 263, int right = 262, int shoot = 32, float fireCooldown = 0.75f, float speed = 200, float rotationalSpeed = 90, int gamepadCode = -1);

		/*!
		\fn     BehaviorPlayer(const BehaviorPlayer &source)
		\param  source
		          Player behavior to copy
		\return Constructed player behavior
		\brief
		        This function constructs a new player behavior by copying an existing player behavior.
		*/
		BehaviorPlayer(const BehaviorPlayer &source);

		/*!
		\fn     ~BehaviorPlayer()
		\par    This function has no parameters
		\return Nothing
		\brief
		        This function decontructs a player behavior.
		*/
		~BehaviorPlayer();

		/*!
		\fn     Component *clone() const
		\par    This function has no parameters.
		\return Copy of the player behavior
		\brief
		        This function copies a player's behavior.
		*/
		Component *clone() const;

		/*!
		\fn     void update(float dt)
		\param  dt
		          Time since previous frame
		\return Nothing
		\brief
		        This function updates a player's physics according to their
		*/
		void update(float dt);

		/*!
		\fn     void setUp(int key)
		\param  key
		          Key code for up input
		\return Nothing
		\brief
		        This function mutates a player behavior's designated up input.
		*/
		void setUp(int key);

		/*!
		\fn     void setDown(int key)
		\param  key
		          Key code for down input
		\return Nothing
		\brief
		        This function mutates a player behavior's designated down input.
		*/
		void setDown(int key);

		/*!
		\fn     void setLeft(int key)
		\param  key
		          Key code for left input
		\return Nothing
		\brief
		        This function mutates a player behavior's designated left input.
		*/
		void setLeft(int key);

		/*!
		\fn     void setRight(int key)
		\param  key
		          Key code for right input
        \return Nothing
        \brief
                This function mutates a player behavior's designated right input.
        */
        void setRight(int key);
        
        /*!
        \fn     void setShoot(int key)
        \param  key
                  Key code for shoot input
        \return Nothing
        \brief
                This function mutates a player behavior's designated    shootinput.
        */
        void setShoot(int key);

		/*!
		\fn     void setGamepad(int key)
		\param  key
				  Key code for gamepad input
		\return Nothing
		\brief
				This function mutates a player behavior's designated    gamepad.
		*/
		void setGamepad(int key);

        //|KEVIN|
        void setPowerUp(PowerUp *powerup);
        
        /*!
        \fn     void setCooldown(float cooldown)
        \param  cooldown
                  new cooldown to set
        \return Nothing
        \brief
                This function mutates the cooldown of a player behavior
        */
        void setCooldown(float cooldown);
        
        /*!
        \fn     float getCooldown()
        \par    This function has no parameters.
        \return Cooldown of the player behavior
        \brief
                This function accesses the cooldown of a player behavior
        */
        float getCooldown();

        //|KEVIN|
        void setSpeed(float speed);
        
        //|KEVIN|
        float getSpeed();

        //|KEVIN|
        int getUp();

        //|KEVIN|
        int getDown();

        //|KEVIN|
        int getLeft();

        //|KEVIN|
        int getRight();

        //|KEVIN|
        int getShoot();
        
	private:

        //|KEVIN|
        enum FB{B = -1, N = 0, F = 1} inFB = N;
        enum LR{R = -1, S = 0, L = 1} inLR = S;

		/*!
		\var    up
		          Key code for up input
		\var    down
		          Key code for down input
		\var    left
		          Key code for left input
		\var    right
		          Key code for right input
		\var    shoot
		          Key code for shoot input
		*/
		int up, down, left, right, shoot;

        /*!
        \var    transform
                  Transform component of the parent game object, stored fo      convenience
        */
        Transform *transform;
        
        /*!
        \var    cooldown
                  Time since the previous shot was done
        \var    maxCooldown
                  maximum cooldown time
        */
        float cooldown, maxCooldown;
        
        /*!
        \var    spd
                  movement speed of the tank
        \var    rotSpd
                  rotational speed of the tank
        */
        float speed, rotSpeed;
        
        
        /*!
        \var    powerup
                  powerup held by the player
        */
        PowerUp* powerup;

		/*!
		\var    teamSet
				  If the team of the player has been updated
		*/
		bool teamSet;

        /*!
        \var    tracksParticleTimer
                  Timer countdown before tank track particles are spawned.
        */
        float tracksParticleTimer;

        /*!
        \fn     void inputMovement()
        \par    This function has no parameters.
        \return Nothing
        \brief
                This funcion updates movement based on player inputs.
        */
        void inputMovement();
        
        /*!
        \fn     void inputBullet(float dt)
        \param  dt
                  Time since previous frame
        \param  team
                  Team that the behavior is set to
        \param  yOffset
                  Y axis Offset of where the bullet may spawn
        \return Nothing
        \brief
                This function updates the shooting input for the    playerbehavior.
        */
        void inputBullet(float dt, GameObject::Team team, float yOffset = 0, bool activeCD = true);

        /*!
        \fn     void generateTracks(float dt)
        \param  dt
                  Time since previous frame
        \return Nothing
        \brief
                This funcion generates tracks every tracksParticleTimer timeout.
        */
        void generateTracks(float dt);

		//|KEVIN|
		void generateBulletEmissions(GameObject* bullet, float dt);

		/*!
		\var    checkGamepad
				  Gamepad that will be used for player
		*/
		unsigned int gamepadNum;
};
