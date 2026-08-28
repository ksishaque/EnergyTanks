/*!
\file   BoxCollider.h
\author Benedict Yau (benedict.yau\@digipen.edu)
\date   10-12-2022
\par    Copyright © 2022 DigiPen, All rights reserved.
*/
#pragma once

#include "Collider.h"
#include "CircleCollider.h"
#include <glm/glm.hpp>

class BoxCollider : public Collider
{
public:

    BoxCollider();

    ~BoxCollider();

    void setWidth(int w);

    void setHeight(int h);

    int getWidth(void);

    int getHeight(void);

	void draw();

	Component* clone() const override;

private:
    int width;
    int height;
};


bool collidingWithBounds(CircleCollider* collider1, BoxCollider* collider2);