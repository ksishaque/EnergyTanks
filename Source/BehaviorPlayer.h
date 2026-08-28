/*!
\file   BehaviorPlayer.h
\author Kevin Shin
\date   2-13-2023
\brief
        Functions for managing the behavior of a player tank
\par    Copyright © 2023 DigiPen, All rights reserved.
*/

#pragma once

#define BEHAVIOR_PLAYER_UNIQUE_SHOOT_SOUNDx

class BehaviorPlayer;

#include "GameObject.h"

#include "BehaviorControllable.h"

class MoreBullets;
class PowerUp;

class BehaviorPlayer : public BehaviorControllable{
	public:

		/*!
		\fn     BehaviorPlayer(int up, int down, int left, int right)
		\param  cooldown
		          Cooldown for shooting
		\param  forSpeed
		          Forward movement speed
		\param  backSpeed
		          Backward movement speed
		\param  turnSpeed
		          Rotationing speed
		\return Constructed tank behavior
		\brief
		        This function constructs a new behavior for a player tank.
		*/
		BehaviorPlayer(float cooldown = 1, float forSpeed = 200, float backSpeed = 160, float turnSpeed = 160);

		/*!
		\fn     BehaviorPlayer(const BehaviorPlayer &source)
		\param  source
		          Tank behavior to copy
		\return Constructed tank behavior
		\brief
		        This function constructs a new tank behavior by copying an existing tank behavior.
		*/
		BehaviorPlayer(const BehaviorPlayer &source);

		/*!
		\fn     ~BehaviorPlayer()
		\par    This function has no parameters
		\return Nothing
		\brief
		        This function decontructs a tank behavior.
		*/
		~BehaviorPlayer();

		/*!
		\fn     Component *clone() const
		\par    This function has no parameters.
		\return Copy of the player behavior
		\brief
		        This function copies a tank's behavior.
		*/
		Component *clone() const;

		/*!
		\fn     void update(float dt)
		\param  dt
		          Time since previous frame
		\return Nothing
		\brief
		        This function updates a tank's physics according to their inputs.
		*/
		void update(float dt);

		/*!
		\fn     void setFore(float speed)
		\param  speed
		          Speed of the tank
		\brief
		        This function mutates the speed of the tank.
		*/
		void setFore(float speed);

		/*!
		\fn     float getFore() const
		\par    This function has no parameters.
		\return Speed of the tank
		\brief
				This function accesses the speed of the tank.
		*/
		float getFore() const;

		/*!
		\fn     void setBack(float speed)
		\param  speed
		          Backwards speed of the tank
		\brief
		        This function mutates the backwards speed of the tank.
		*/
		void setBack(float speed);

		/*!
		\fn     float getBack() const
		\par    This function has no parameters.
		\return Backwards speed of the tank
		\brief
				This function accesses the backwards speed of the tank.
		*/
		float getBack() const;

		/*!
		\fn     void setTurn(float speed)
		\param  speed
		          Turning speed of the tank
		\brief
		        This function mutates the turning speed of the tank.
		*/
		void setTurn(float speed);

		/*!
		\fn     float getTurn() const
		\par    This function has no parameters.
		\return Turning speed of the tank
		\brief
				This function accesses the turning speed of the tank.
		*/
		float getTurn() const;

		/*!
		\fn     void setCooldown(float time)
		\param  time
		          Cooldown time to set
		\brief
		        This function mutates the cooldown time between shots for the tank.
		*/
		void setCooldown(float time);

		/*!
		\fn     float getCooldown() const
		\par    This function has no parameters.
		\return Max cooldown of tank
		\brief
				This function accesses the cooldown time between shots for the tank.
		*/
		float getMaxCooldown() const;

		/*!
		\fn     void setMaxCooldown(float time)
		\param  time
				  Max cooldown time to set
		\brief
				This function mutates the cooldown time between shots for the tank.
		*/
		void setMaxCooldown(float time);

		/*!
		\fn     float getMaxCooldown() const
		\par    This function has no parameters.
		\return Turning speed of the tank
		\brief
				This function accesses the cooldown time between shots for the tank.
		*/
		float getCooldown() const;

		/*!
		\fn     void setPowerUp(PowerUp* powerup)
		\param  powerup
				  Power up of the tank
		\brief
				This function mutates the power up of the tank.
		*/
		void setPowerUp(PowerUp *powerup);

#ifdef BEHAVIOR_PLAYER_UNIQUE_SHOOT_SOUND
		void setShootSound(std::string str);
#endif

		/*!
		\fn     void actionCall(ControlUnit::ControlType action, ControlManager::KeyState keyState)
		\param  action
		          action
		\param  keyState
		          keyState
		\brief  See BehaviorControllable.h
		*/
		void actionCall(ControlUnit::ControlType action, ControlManager::KeyState keyState) override;

		/*!
		\fn     void gainControl()
		\brief  See BehaviorControllable.h
		*/
		void gainControl() override;

		/*!
		\fn     bool activePowerUp()
		\brief  This function returns whether or not a powerup is currently active for the player character
		*/
		bool activePowerUp();

		/*!
		\fn     float getPowerUp() const
		\par    This function has no parameters.
		\return Player's current powerup
		\brief
				This function returns the powerup the player got.
		*/
		PowerUp* getPowerUp() const;

		friend class Burst;

		friend class Pierce;

		friend class StealthBullet;
        
	private:
        
        /*!
        \var    fore
                  Forward movement speed
        \var    back
                  Backward movement speed
        \var    turn
                  Turn movement speed
        */
        float fore, back, turn;

		/*
        \var    cd
                  Shoot cooldown
        \var    mCd
                  Maximum shoot cooldown
        */
        float cd, mCd;
		
		/*
		\var	moveSoundTimer
					Timer for movement sound
		*/
		float moveSoundTimer;
		/*
        \var    dt
                  Time since previous frame, saved for particle generation
        */
        float dt;

		/*!
		\var    powerup
		          Current powerup for the player
		*/
		PowerUp* powerup;

		/*!
		\var    tracksParticleTimer
				  Timer for making the particle tracks
		*/
		float tracksParticleTimer;

#ifdef BEHAVIOR_PLAYER_UNIQUE_SHOOT_SOUND
		std::string shootSound;
#endif

		/*!
		\fn     void generateTankTracks(float speed)
		\param  speed
				  Movement speed during frame
		\return Nothing
		\brief
				This funcion generates tank track particles every `tracksParticleTimer` timeout.
		*/
		void generateTankTracks(float speed);


		void spawnBullet(float xOffset, bool passThrough = false, float newAlpha = 0.0f);

		/*!
		\var    active
				  There is a powerup for the player character
		*/
		bool active = false;



};
