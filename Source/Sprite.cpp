/*!
\file   Sprite.cpp
\author Benedict Yau (benedict.yau\@digipen.edu)
		Kevin Shin (kevin.shin\@digipen.edu)
\date   9-23-2022
\brief
		Functions for managing a sprite
\par    Copyright © 2022 DigiPen, All rights reserved.
*/

#include "Mesh.h"
#include "MeshManager.h"
#include "ObjectContainer.h"
#include "ObjectManager.h"
#include "Shader.h"
#include "Sprite.h"
#include "TeamSystem.h"
#include "Texture.h"
#include "Transform.h"
#include "Renderer.h"
#include "GraphicsUnit.h"
#include "GameObject.h"



/*!
\fn     Sprite()
\brief  See Sprite.h
*/
Sprite::Sprite() : Component(ComponentTypeEnum::cSprite),
trans(nullptr),
graphicsList(),
color(1, 1, 1, 1),
view(nullptr)
{
}

/*!
\fn     Sprite(const Sprite& other)
\brief  See Sprite.h
*/
Sprite::Sprite(const Sprite& other) : Component(other),
trans(other.trans),
graphicsList(), color(other.color), view(nullptr) {
	for (std::pair<GraphicsUnitMutable*, float> graphic : other.graphicsList) {
		graphicsList.emplace_back(new GraphicsUnitMutable(*graphic.first), graphic.second);

	}
}

/*!
\fn     ~Sprite()
\brief  See Sprite.h
*/
Sprite::~Sprite() {
	clearGraphics();
}

/*!
\fn     void setParent(GameObject *parent)
\param  parent
		  parent
\brief  See Sprite.h
*/
void Sprite::setParent(GameObject* parent) {
	//	Set `parent`
	Component::setParent(parent);

	//	Get the `Transform` of `parent` and set as `trans`
	if(parent){
		trans = (Transform*)parent->get(ComponentTypeEnum::cTransform);

		//	Set transform matrices
		for (std::pair<GraphicsUnitMutable*, float> graphic : graphicsList) {
			graphic.first->setTransformMatrix(&(trans->getMatrix()));
		}
	}
}

/*!
\fn     void update(float dt)
\param  dt
		  dt
\brief  See Sprite.h
*/
void Sprite::update(float dt) {
		
	//	Get `parent`
	GameObject* parent = getParent();

	//	Set `trans` and `view`
	if(parent) {
		if(trans == nullptr) {

			trans = dynamic_cast<Transform *>(parent->get(ComponentTypeEnum::cTransform));
			if(trans == nullptr) return;
		
			//	Set transform matrices
			for (std::pair<GraphicsUnitMutable*, float> graphic : graphicsList) {
				graphic.first->setTransformMatrix(&(trans->getMatrix()));
			}

		}
		if(view == nullptr) {

			//	Get parent manager
			ObjectContainer *man = parent->getManager();
			if(man == nullptr) return;
		
			//	Set viewing matrices
			view = &(man -> getViewMatrix());
			for (std::pair<GraphicsUnitMutable*, float> graphic : graphicsList) {
				graphic.first->setViewMatrix(view);
			}

		}

	}

	//	Update transform matrix
	if(trans) trans->updateMatrix();

	for (std::pair<GraphicsUnit*, float> graphic : graphicsList) if (graphic.first) {

		//	Calculate the final current color
		//*
		if(parent){
			glm::vec4 finalColor = TeamSystem::getInstance()->getColor(parent->getTeam());
			finalColor *= graphic.second;
			finalColor += glm::vec4(1 - graphic.second, 1 - graphic.second, 1 - graphic.second, 1 - graphic.second);
			finalColor *= color;
			graphic.first->setTempColor(finalColor);
		}
		/*/
		if(false) ;
		//*/
		else graphic.first->setTempColor(color);

		//	Render
		Renderer::getInstance()->addToList(graphic.first);

	}

}

/*!
\fn     Component *clone() const
\brief  See Sprite.h
*/
Component* Sprite::clone() const {
	return nullptr;
}

/*!
\fn     Transform* getTransform() const
\par    This function has no parameters.
\return `transform`
\brief
		See Sprite.h
*/
Transform* Sprite::getTransform() const {
	return this->trans;
}

/*!
\fn     void setTransform(Transform* transform)
\brief
		See Sprite.h
*/
void Sprite::setTransform(Transform* transform) {
	this->trans = transform;
}

/*!
\deprecated
\fn     void Draw()
\brief  See Sprite.h
*/
void Sprite::Draw() {

	//	Get `parent`
	GameObject* parent = getParent();

	//	Set transform matrices
	for (std::pair<GraphicsUnitMutable*, float> graphic : graphicsList) {
		graphic.first->setTransformMatrix(&(trans->getMatrix()));
	}

	//	Set viewing matrices
	view = &(ObjectManager::getInstance()->getViewMatrix());
	for (std::pair<GraphicsUnitMutable*, float> graphic : graphicsList) {
		graphic.first->setViewMatrix(view);
	}

	//	Update transform matrix
	if (trans) trans->updateMatrix();

	for (std::pair<GraphicsUnit*, float> graphic : graphicsList) if (graphic.first) {

		//	Calculate the final current color
		/*
		if (parent) {
			glm::vec4 finalColor = TeamSystem::getInstance()->getColor(parent->getTeam());
			finalColor *= graphic.second;
			finalColor += glm::vec4(1 - graphic.second, 1 - graphic.second, 1 - graphic.second, 1 - graphic.second);
			finalColor *= color;
			graphic.first->setTempColor(finalColor);
		}
		else graphic.first->setTempColor(color);
		//*/

		//	Variable: Temporary instance of `graphic.first`
		GraphicsUnitConstant *temp = new GraphicsUnitConstant(*static_cast<GraphicsUnitMutable *>(graphic.first));

		//	Set color
		temp->setTempColor(color);

		//	Render
		Renderer::getInstance()->addToList(temp);

	}

}

unsigned Sprite::addToGraphics(GraphicsUnitMutable* unit, float t)
{
	unsigned size = static_cast<unsigned>(graphicsList.size());
	graphicsList.emplace_back(unit, t);
	if(trans) unit->setTransformMatrix(&(trans->getMatrix()));
	if(view) unit->setViewMatrix(view);
	return size;
}

GraphicsUnitMutable* Sprite::getGraphics(unsigned unitIndex) {
	if (unitIndex < graphicsList.size()) {
		return graphicsList[unitIndex].first;
	}
	return nullptr;
}

void Sprite::removeFromGraphics(unsigned unitIndex)
{
	if(unitIndex < graphicsList.size()){
		Renderer::getInstance()->removeFromList(graphicsList[unitIndex].first);
		delete graphicsList[unitIndex].first;
		graphicsList[unitIndex].first = nullptr;
	}
}

/*!
\fn     bool clearGraphics()
\brief  See Sprite.h
*/
void Sprite::clearGraphics()
{
	for(std::pair<GraphicsUnitMutable*, float> unit : graphicsList){
		Renderer::getInstance()->removeFromList(unit.first);
		delete unit.first;
	}
	graphicsList.clear();
}

unsigned Sprite::getGraphicsListSize()
{
	return static_cast<unsigned>(graphicsList.size());
}


/*!
\fn     void setColor(float r, float g, float b, float a)
\param  r
			The red value.
\param  g
			The green value.
\param  b
			The blue value.
\param  a
			The alpha value.
\brief  See Sprite.h
*/
void Sprite::setColor(float r, float g, float b, float a)
{
	color.r = r;
	color.g = g;
	color.b = b;
	color.a = a;
}

/*!
\fn     void setColor(const glm::vec4& col)
\param  col
			The color vector.
\brief  See Sprite.h
*/
void Sprite::setColor(const glm::vec4& col)
{
	color = col;
}