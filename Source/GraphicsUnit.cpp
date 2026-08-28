/*!
\file   GraphicsUnit.cpp
\author Kevin Shin
\date   2-14-2023
\brief
		 Nodes in an action list that generate particles.
\par    Copyright © 2023 DigiPen, All rights reserved.
*/
#include "DebugSystem.h"
#include "Mesh.h"
#include "GraphicsUnit.h"

GraphicsUnit::GraphicsUnit(Mesh* mesh, Type type, Texture* texture, float u, float v, const glm::vec4& col) :
    mesh(mesh), type(type), texture(texture), u(u), v(v), color(col), tempColor(1, 1, 1, 1)
{

}

GraphicsUnit::GraphicsUnit(const GraphicsUnit& other) : 
	mesh(other.mesh) , type(other.type), texture(other.texture), u(other.u), v(other.v), color(other.color), tempColor(other.tempColor)
{

}

bool GraphicsUnit::operator<(const GraphicsUnit& graphicsUnit) const
{
    return type < graphicsUnit.type;
}

static glm::vec4 mergeColors(glm::vec4& col1, const glm::vec4& col2) {

	col1.r *= col2.r;
	col1.g *= col2.g;
	col1.b *= col2.b;
	col1.a *= col2.a;

	return col1;

}

void GraphicsUnitMutable::draw(float windowScale) const
{
	mergeColors(tempColor, color);
	if (
#ifdef DEBUG_SYSTEM
	(DebugSystem::getInstance()->getFlag(DebugSystem::DebugFlag::HIDE_UI) && (type == guUI1 || type == guUI2 || type == guDebug)) ||
#endif
		tempColor.a <= 0)
	{
		tempColor = BASE_COLOR_GRAPHICS_UNIT;
		return;
	}
	mesh->Draw((*view) * (*trans) * offset, texture, tempColor, u, v, windowScale);
	tempColor = BASE_COLOR_GRAPHICS_UNIT;
}

void GraphicsUnitConstant::draw(float windowScale) const
{
	mergeColors(tempColor, color);
	if (
#ifdef DEBUG_SYSTEM
	(DebugSystem::getInstance()->getFlag(DebugSystem::DebugFlag::HIDE_UI) && (type == guUI1 || type == guUI2 || type == guDebug)) ||
#endif
		tempColor.a <= 0)
	{
		delete this;
		return;
	}
    mesh->Draw(trans, texture, tempColor, u, v, windowScale);
	delete this;
}

GraphicsUnitMutable::GraphicsUnitMutable(Mesh* mesh, const glm::mat4* trans, Type type, Texture* texture, float u, float v, glm::mat4& offset, const glm::vec4& col) :
    GraphicsUnit(mesh, type, texture, u, v, col), trans(trans), offset(offset), view(&iMatrix)
{
	if (trans == nullptr)
	{
		this->trans = &iMatrix;
	}
}

GraphicsUnitMutable::GraphicsUnitMutable(Mesh* mesh, const glm::mat4* trans, Type type, Texture* texture, float u, float v, float xPos, float yPos, float zPos, float xScale, float yScale, float zScale, float rotation, const glm::vec4& col) :
	GraphicsUnit(mesh, type, texture, u, v, col), trans(trans), view(&iMatrix)
{
	offset = glm::translate(glm::vec3(xPos, yPos, zPos)) * glm::rotate(glm::radians(rotation), glm::vec3(0, 0, 1)) * glm::scale(glm::vec3(xScale, yScale, zScale));
	if (trans == nullptr)
	{
		this->trans = &iMatrix;
	}
}

GraphicsUnitMutable::GraphicsUnitMutable(Mesh* mesh, const glm::mat4* trans, Type type, Texture* texture, float u, float v, const glm::vec3& translation, const glm::vec3& scale, float rotation, const glm::vec4& col) :
	GraphicsUnit(mesh, type, texture, u, v, col), trans(trans), view(&iMatrix)
{
	offset = glm::translate(translation) * glm::rotate(glm::radians(rotation), glm::vec3(0, 0, 1)) * glm::scale(scale);
	if (trans == nullptr)
	{
		this->trans = &iMatrix;
	}
}


GraphicsUnitConstant::GraphicsUnitConstant(Mesh* mesh, const glm::mat4& trans, Type type, Texture* texture, float u, float v, const glm::vec4& col) :
	GraphicsUnit(mesh, type, texture, u, v, col), trans(trans)
{

}

GraphicsUnitConstant::GraphicsUnitConstant(const GraphicsUnitMutable& old) : GraphicsUnit(old) {
	trans = (*old.getView()) * (*old.getTrans()) * old.getOffset();
}

GraphicsUnitMutable* makeGraphicsUnit(Mesh* mesh, const glm::mat4* trans, GraphicsUnit::Type type, Texture* texture, float u, float v, const glm::vec4& col)
{
    return new GraphicsUnitMutable(mesh, trans, type, texture, u, v, 0, 0, 0, 1, 1, 1, 0, col);
}

GraphicsUnitConstant* makeGraphicsUnit(Mesh* mesh, const glm::mat4& trans, GraphicsUnit::Type type, Texture* texture, float u, float v, const glm::vec4& col)
{
    return new GraphicsUnitConstant(mesh, trans, type, texture, u, v, col);
}

void GraphicsUnitMutable::setTransformMatrix(const glm::mat4* trans)
{
	if (trans)
	{
		this->trans = trans;
	}
	else
	{
		this->trans = &iMatrix;
	}
}

Mesh* GraphicsUnitMutable::getMesh(void) {
	return this->mesh;
}

Texture* GraphicsUnitMutable::getTexture(void) {
	return this->texture;
}

const glm::mat4* GraphicsUnitMutable::getTrans(void) const{
	return this->trans;
}
const glm::mat4* GraphicsUnitMutable::getView(void) const{
	return this->view;
}
const glm::mat4& GraphicsUnitMutable::getOffset(void) const{
	return this->offset;
}

GraphicsUnitMutable::GraphicsUnitMutable(const GraphicsUnitMutable& other) : GraphicsUnit(other.mesh, other.type, other.texture, other.u, other.v, other.color), trans(&iMatrix), view(other.view), offset(other.offset)
{

}

void GraphicsUnit::setColor(const glm::vec4& col) {
	color = col;
}

void GraphicsUnit::setTempColor(const glm::vec4& col) {
	mergeColors(tempColor, col);
}

void GraphicsUnit::setUV(float u, float v) {
	this -> u = u;
	this -> v = v;
}

void GraphicsUnitMutable::setViewMatrix(const glm::mat4* view)
{
	if (view)
	{
		this->view = view;
	}
	else
	{
		this->view = &iMatrix;
	}
}

const glm::mat4 GraphicsUnitMutable::iMatrix = glm::mat4(1);