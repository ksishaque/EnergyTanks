/*!
\file   GraphicsUnit.h
\author Kevin Shin
\date   2-14-2023
\brief
		 Nodes in an action list that generate particles.
\par    Copyright © 2023 DigiPen, All rights reserved.
*/
#pragma once
#include <glm/glm.hpp>
class Mesh;
class Texture;

static const glm::vec3 BASE_SCALE_GRAPHICS_UNIT(1.f, 1.f, 1.f);
static const glm::vec4 BASE_COLOR_GRAPHICS_UNIT(1.f, 1.f, 1.f, 1.f);

class GraphicsUnit
{
public:
	enum Type {
		guBackground3,
		guBackground2,
		guGlow3,
		guBackground1,
		guTrack,
		guGlow2,
		guGlow1,
		guInvalid,
		guWall2,
		guWall1,
		guTrail,
		guSparks,
		guBullet,
		guShield1,
		guShield2,
		guMapButton1,
		guMapButton2,
		guTank,
		guShell,
		guSmoke,
		guButton1,
		guButton2,
		guButton3,
		guUI2,
		guUI1,
		guText,
		guPawsPopBackground,
		guPawsPopIcon,
		guPawsPopSelector,
		guPawsPopText,
		guCtrlPopBackground,
		guCtrlPopIcon2,
		guCtrlPopIcon1,
		guCtrlPopText,
		guHTPlPopBackground,
		guHTPlPopText,
		guOptnPopBackground,
		guOptnPopIcon,
		guOptnPopSelector,
		guOptnPopText1,
		guOptnPopSlider1,
		guOptnPopText2,
		guOptnPopSlider2,
		guScreen,
		guShutPopBackground,
		guShutPopIcon,
		guShutPopSelector,
		guShutPopText,
		guPaLiPopBackground,
		guPaLiPopIcon,
		guBorder,
		guDebug,
		guTest
	};

	virtual void draw(float windowScale) const = 0;
	bool operator<(const GraphicsUnit& graphicsUnit) const;
	void setColor(const glm::vec4& color);
	void setTempColor(const glm::vec4& color);
	void setUV(float u, float v);

protected:
	GraphicsUnit(Mesh* mesh, Type type, Texture* texture, float u, float v, const glm::vec4& color = BASE_COLOR_GRAPHICS_UNIT);
	GraphicsUnit(const GraphicsUnit& other);
	Mesh* mesh;
	Texture* texture;
	float u;
	float v;
	Type type;
	glm::vec4 color;
	mutable glm::vec4 tempColor;
};

class GraphicsUnitMutable : public GraphicsUnit
{
public:
	GraphicsUnitMutable(Mesh* mesh, const glm::mat4* trans, Type type, Texture* texture, float u, float v, glm::mat4& offset, const glm::vec4& color = BASE_COLOR_GRAPHICS_UNIT);

	GraphicsUnitMutable(Mesh* mesh, const glm::mat4* trans, Type type, Texture* texture, float u, float v, float xPos = 0, float yPos = 0, float zPos = 0, float xScale = 1, float yScale = 1, float zScale = 1, float rotation = 0, const glm::vec4& color = BASE_COLOR_GRAPHICS_UNIT);

	GraphicsUnitMutable(Mesh* mesh, const glm::mat4* trans, Type type, Texture* texture, float u, float v, const glm::vec3& translation, const glm::vec3& scale = BASE_SCALE_GRAPHICS_UNIT, float rotation = 0, const glm::vec4& color = BASE_COLOR_GRAPHICS_UNIT);

	GraphicsUnitMutable(const GraphicsUnitMutable& other);

	void draw(float windowScale) const;

	void setTransformMatrix(const glm::mat4* trans);
	void setViewMatrix(const glm::mat4* trans);

	Mesh* getMesh(void);

	Texture* getTexture(void);

	const glm::mat4* getTrans(void) const;
	const glm::mat4* getView(void) const;
	const glm::mat4& getOffset(void) const;

private:
	const glm::mat4* trans;
	const glm::mat4* view;
	glm::mat4 offset;
	static const glm::mat4 iMatrix;
};

class GraphicsUnitConstant : public GraphicsUnit
{
public:
	GraphicsUnitConstant(Mesh* mesh, const glm::mat4& trans, Type type, Texture* texture, float u, float v, const glm::vec4& color = BASE_COLOR_GRAPHICS_UNIT);
	GraphicsUnitConstant(const GraphicsUnitMutable &old);
	void draw(float windowScale) const;
private:
	glm::mat4 trans;
};

GraphicsUnitMutable* makeGraphicsUnit(Mesh* mesh, const glm::mat4* trans = nullptr, GraphicsUnit::Type type = GraphicsUnit::Type::guInvalid, Texture* texture = nullptr, float u = 0.0f, float v = 0.0f, const glm::vec4& color = BASE_COLOR_GRAPHICS_UNIT);

GraphicsUnitConstant* makeGraphicsUnit(Mesh* mesh, const glm::mat4& trans, GraphicsUnit::Type type = GraphicsUnit::Type::guInvalid, Texture* texture = nullptr, float u = 0.0f, float v = 0.0f, const glm::vec4& color = BASE_COLOR_GRAPHICS_UNIT);
