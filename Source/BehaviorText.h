/*!
\file   BehaviorText.h
\author Luke Tseng
\date   3-7-2023
\brief
		Functions for managing the behavior of text
\par    Copyright © 2023 DigiPen, All rights reserved.
*/
#include "Behavior.h"
#include "Texture.h"
#include "Mesh.h"

class BehaviorText : public Behavior
{
public:
	BehaviorText();
	BehaviorText(const BehaviorText& behaviorText);
	~BehaviorText();
	void update(float dt);
	Component* clone() const override;
	void setText(float& var);
	void setTrans(glm::vec3 translation, glm::vec3 scale);
private:
	float* text;
	Texture* texture;
	Mesh* mesh;
	glm::mat4 offset;
	glm::mat4 trans;
};
