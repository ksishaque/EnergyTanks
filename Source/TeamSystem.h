/*****************************************************************//**
 * \file   TeamSystem.h
 * \brief
 * \par    Copyright © 2022 DigiPen, All rights reserved.
 *
 * \author Luke Tseng
 * \author Kevin Shin
 * \date   October 2022
 * \par    Copyright © 2022 DigiPen, All rights reserved.
 *********************************************************************/
#pragma once

class TeamSystem;

#include <glm/glm.hpp>
#include <list>
#include "GameObject.h"
#include "ISystem.h"

class BehaviorButton;
class BehaviorControllable;
class ControlUnit;

class TeamSystem : public ISystem {
public:

    /**
     * Default constructor
     * 
     */
    TeamSystem();
    /**
     * Checks if there are shields for specified team
     * 
     * \param team Team to check
     * \return If the team has sheilds
     */
    bool hasShields(GameObject::Team team);
	/**
	 * Checks if there are shields for specified team
	 *
	 * \param team Team to check
	 * \return If the team has sheilds
	 */
	int getShieldCount(GameObject::Team team) const;
    /**
     * Decreases Shields of specified team by 1
     * 
     * \param team Team to remove shield from
     * \param count Number of shields to remove
     * \return If the team is valid
     */
    bool decShields(GameObject::Team team, unsigned count = 1);
    /**
     * Increases shields of specified team by 1
     *
     * \param team Team to add shield to
     * \param count Number of shields to add
     * \return If the team is valid
     */
    bool incShields(GameObject::Team team, int count = 1);
    /**
     * Checks if there are players for specified team
     * 
     * \param team Team to check
     * \return If the team has sheilds
     * \return If the team is valid
     */
    BehaviorControllable *getPlayer(GameObject::Team team);
    /**
     * Decreases Players of specified team by 1
     * 
     * \param team Team to remove shield from
     * \param count Number of shields to remove
     * \return If the team is valid
     */
    bool removePlayer(GameObject::Team team, BehaviorControllable *player);
    /**
     * Increases players of specified team by 1
     *
     * \param team Team to add shield to
     * \param count Number of shields to add
     * \return If the team is valid
     */
    bool setPlayer(GameObject::Team team, BehaviorControllable *player);
    
	//|LUKE|
    const glm::vec4 &getColor(GameObject::Team team) const;
    bool setColor(GameObject::Team team, const glm::vec4 &color);
    bool incColor(GameObject::Team team, float dc);
    bool setDecision(GameObject::Team team, BehaviorButton *decision);
    BehaviorButton *getDecision(GameObject::Team team);
    bool clearDecision(GameObject::Team team);
	const ControlUnit *getControls(GameObject::Team team) const;
	bool checkInitContDisplay();

    /**
     * This function accesses the singleton instance of the team system, creating it if needed.
     *
     * \return Singleton instance of the team system
    */
    static TeamSystem* getInstance();
    /**
     * This function closes and deletes the singleton instance of the team system
     *
    */
    static void closeInstance();

private:

	//|LUKE|
	class Team{
	public:

		/**
		 * Default constructor
		 * 
		 */
		Team();

		/**
		 * Default destructor
		 * 
		 */
		~Team();
	
	    /**
	     * Increases shields of team
	     *
	     * \param count Number of shields to add
	     */
		void incShields(int count);
	
	    /**
	     * Increases players of team
	     *
	     * \param count Number of players to add
	     */
		void setPlayer(BehaviorControllable *player);
	
	    /**
	     * Decreases players of team
	     *
	     */
		void removePlayer(BehaviorControllable *player);
		
	    /**
	     * Checks if the team has shields
	     * 
	     * \return If the team has shields
	     */
	    bool hasShields();
		
	    /**
	     * Checks if the team has players
	     * 
	     * \return If the team has players
	     */
		BehaviorControllable *getPlayer();

		//|LUKE|
		int getShieldCount() const;
		const glm::vec4 &getColor() const;
		void setColor(const glm::vec4 &color);
		void incColor(float dc);
		ControlUnit *getControls() const;
		void setDecision(BehaviorButton *decision);
		BehaviorButton *getDecision();

	private:
		std::list<BehaviorControllable *> player;
		ControlUnit *controls;
		int shieldCount;
		glm::vec4 color;
		BehaviorButton *decision;
	} teams[2];
	bool initContDisplay;
	static glm::vec4 white;

    static TeamSystem* instance;
};
