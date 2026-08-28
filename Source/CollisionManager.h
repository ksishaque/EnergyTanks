/*!
\file CollisionManager.h
\author Khaled S. Ishaque
\date 10-25-2022
\brief
	H file for object CollisionManager class and functions in class
\par    Copyright © 2022 DigiPen, All rights reserved.
*/
#pragma once

#include <vector>

#include "ISystem.h"
#include "Collider.h"

class CollisionManager : public ISystem
{
public:
    void initialize() override;
    void update(float& dt) override;
    void shutdown() override;
    static void addToList(Collider* collider);
    static void removeFromList(Collider* collider);
    static CollisionManager* getInstance();
    static void closeInstance();
private:
    std::vector<Collider*> queue;
    CollisionManager();
	void recheck(unsigned i, float dt, unsigned iteration = 0);
    void instanceAddToList(Collider* collider);
    void instanceRemoveFromList(Collider* collider);
    static CollisionManager* instance;
};