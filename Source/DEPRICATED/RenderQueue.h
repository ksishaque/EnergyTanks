/*****************************************************************//**
 * \file   RenderQueue.h
 * \brief
 *
 * \author Luke
 * \date   October 2022
 *********************************************************************/
#pragma once
#include "ISystem.h"
#include "Sprite.h"

class RenderQueue : public ISystem
{
public:
	/**
	 * Initializes render queue
	 *
	 */
	void initialize() override;
	/**
	 * Sorts queue
	 *
	 * \param dt Unused parameter
	 */
	void update(float dt) override;
	/**
	 * Shuts down system
	 *
	 */
	void shutdown() override;
	/**
	 * Adds sprite the queue
	 * 
	 * \param sprite Sprite object to add to render queue
	 */
	static void addToList(Sprite* sprite);
	/**
	 * Removes sprite the queue
	 *
	 * \param sprite Sprite object to remove from render queue
	 */
	static void removeFromList(GameObject* obj);
	/**
	 * This function accesses the singleton instance of the renderqueue system, creating it if needed.
	 * 
	 * \return Singleton instance of the renderqueue system
	*/
	static RenderQueue* getInstance();
	/**
	 * This function closes and deletes the singleton instance of the renderqueue system
	 *
	*/
	static void closeInstance();
private:
	static RenderQueue* instance;
	/**
	 * List of sprites to render
	 */
	std::list<Sprite *> queue;
    /**
     * Constructor for render queue
     *
     */
    RenderQueue();
	/**
	 * Adds sprite the queue
	 *
	 * \param sprite Sprite object to add to render queue
	 */
	void instanceAddToList(Sprite* sprite);
	/**
	 * Adds sprite the queue
	 *
	 * \param sprite Sprite object to add to render queue
	 */
	void instanceRemoveFromList(GameObject* obj);
};