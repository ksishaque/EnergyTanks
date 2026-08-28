/*****************************************************************//**
 * \file   RenderQueue.cpp
 * \brief  List for the order for object to be drawn and calls draw
 * 
 * \author Luke Tseng
 * \date   October 2022
 * \par    Copyright © 2022 DigiPen, All rights reserved.
 *********************************************************************/

#include "RenderQueue.h"
#include <list>
#include "Trace.h"

RenderQueue* RenderQueue::instance = nullptr;

RenderQueue::RenderQueue() : ISystem(sRender)
{
}

void RenderQueue::initialize()
{

}

void RenderQueue::update(float dt)
{
	
	queue.sort();
	std::list<Sprite *>::iterator it;
	for (it = queue.begin(); it != queue.end(); ++it)
	{
		Sprite* temp = *it;
//      temp->draw(); // no draw function 
	}
}

void RenderQueue::shutdown()
{

}

void RenderQueue::instanceAddToList(Sprite* sprite)
{
	queue.push_back(sprite);
}

void RenderQueue::instanceRemoveFromList(GameObject* obj)
{
    Sprite* sprite = dynamic_cast<Sprite*>(obj->get(ComponentTypeEnum::cSprite));
    if (sprite)
    {
        queue.erase(std::remove(queue.begin(), queue.end(), sprite), queue.end());
    }
}

RenderQueue* RenderQueue::getInstance()
{
	if (instance == nullptr)
	{
		instance = new RenderQueue();
	}
	return instance;
}

void RenderQueue::closeInstance()
{
	delete instance;
	instance = nullptr;
}

void RenderQueue::addToList(Sprite* sprite)
{
	if (instance == nullptr)
	{
        Trace::message("RenderQueue instance is NULL");
		return;
	}
	instance->instanceAddToList(sprite);
}

void RenderQueue::removeFromList(GameObject* obj)
{
	if (instance == nullptr)
	{
        Trace::message("RenderQueue instance is NULL");
		return;
	}
	instance->instanceRemoveFromList(obj);
}