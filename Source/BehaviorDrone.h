/*!
\file   BehaviorDrone.h
\author Kevin Shin
\date   2-13-2023
\brief
        Functions for managing the behavior of a player drone
\par    Copyright © 2023 DigiPen, All rights reserved.
*/

#pragma once

class BehaviorDrone;

#include "GameObject.h"

#include "BehaviorControllable.h"

class PowerUp;
struct GLFWwindow;
class GameObject;

class BehaviorDrone : public BehaviorControllable{
	public:

		/*!
		\fn     BehaviorDrone(int up, int down, int left, int right)
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
		\param  cooldown
		\param  speed
		         Base movement speed at which the drone moves
		\return Constructed drone behavior
		\brief
		        This function constructs a new behavior for a player drone.
		*/
		BehaviorDrone(int up = 265, int down = 264, int left = 263, int right = 262, int shoot = 32, float cooldown = 1, float speed = 400);

		/*!
		\fn     BehaviorDrone(const BehaviorDrone &source)
		\param  source
		          Drone behavior to copy
		\return Constructed drone behavior
		\brief
		        This function constructs a new drone behavior by copying an existing drone behavior.
		*/
		BehaviorDrone(const BehaviorDrone &source);

		/*!
		\fn     ~BehaviorPlayer()
		\par    This function has no parameters
		\return Nothing
		\brief
		        This function decontructs a drone behavior.
		*/
		~BehaviorDrone();

		/*!
		\fn     Component *clone() const
		\par    This function has no parameters.
		\return Copy of the player behavior
		\brief
		        This function copies a drone's behavior.
		*/
		Component *clone() const;

		/*!
		\fn     void update(float dt)
		\param  dt
		          Time since previous frame
		\return Nothing
		\brief
		        This function updates a drone's physics according to their inputs
		*/
		void update(float dt);

		/*!
		\fn     void setSpeed(float speed)
		\param  speed
		          Speed of the drone
		\brief
		        This function mutates the speed of the drone
		*/
		void setSpeed(float speed);
        
	private:
        
        /*!
        \var    spd
                  movement speed of the tank
        */
        float speed;

		/*!
		\var    teamSet
		          If the team of the player has been updated
		*/
		bool teamSet;

		/*!
		\var    drone ParticleTimer
				  Timer countdown before drone emission particles are spawned.
		*/
		float droneParticleTimer;

		/*!
		\fn     void generateParticles(float dt)
		\param  dt
				  Time since previous frame
		\return Nothing
		\brief
				This funcion generates particles every droneParticleTimer timeout.
		*/
		void generateParticles(float dt);
};
