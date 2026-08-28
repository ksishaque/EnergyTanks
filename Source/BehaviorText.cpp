/*!
\file   BehaviorText.cpp
\author Luke Tseng
\date   3-7-2023
\brief
		Functions for managing the behavior of text
\par    Copyright © 2023 DigiPen, All rights reserved.
*/

#include "BehaviorText.h"
#include "MeshManager.h"
#include "SoundSystem.h"
#include "Renderer.h"
#include "GraphicsUnit.h"

BehaviorText::BehaviorText() : text(0)
{
	texture = &TextureManager::getTexture("font");
	MeshManager::getInstance()->getMesh(MeshManager::MeshType::text, mesh);
	offset = glm::translate(glm::vec3(-15, 0, 0));
	trans = glm::translate(glm::vec3(0, 0, 1)) * glm::scale(glm::vec3(0, 0, 1));
}

BehaviorText::BehaviorText(const BehaviorText& behaviorText) : text(behaviorText.text)
{
	texture = &TextureManager::getTexture("font");
	MeshManager::getInstance()->getMesh(MeshManager::MeshType::text, mesh);
	offset = glm::translate(glm::vec3(-15, 0, 0));
	trans = glm::translate(glm::vec3(0, 0, 1)) * glm::scale(glm::vec3(0, 0, 1));
}

BehaviorText::~BehaviorText()
{
}

void BehaviorText::update(float dt)
{
	int num = static_cast<int>(*text * 100);
	glm::mat4 temp = trans;
	if (num == 0)
	{
		Renderer::getInstance()->addToList(makeGraphicsUnit(mesh, trans, GraphicsUnit::guText, texture, ((float)0 + 16) / 96, 0));
	}
	else {
		while (num > 0)
		{
			int digit = num % 10;
			Renderer::getInstance()->addToList(makeGraphicsUnit(mesh, trans, GraphicsUnit::guText, texture, ((float)digit + 16) / 96, 0));
			num /= 10;
			trans = offset * trans;
		}
	}

	trans = temp;
}

Component* BehaviorText::clone() const
{
	BehaviorText* clone = new BehaviorText();
	return clone;
}

void BehaviorText::setText(float& var)
{
	text = &var;
}

void BehaviorText::setTrans(glm::vec3 transform, glm::vec3 scale)
{
	trans = glm::translate(transform) * glm::scale(scale);;
}
