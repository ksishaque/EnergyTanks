/*!
\file CircleCollider.h
\author Khaled S. Ishaque
\date 9-27-2022
\brief
    Header file for object CircleCollider class and functions in class
*/

#pragma once

#include "Collider.h"

class CircleCollider : public Collider
{
public:
    CircleCollider();
    ~CircleCollider();
    //void read(Collider* collider, FILE* file);
    float getRadius();
    void setRadius(float newRadius);
    void draw();
    //friend bool collidingWithCircle(Collider* collider1, Collider* collider2);
    Component* clone() const override;
private:
    float radius;
};

bool collidingWithCircle(CircleCollider* collider1, BounceInfo& info1, CircleCollider* collider2, BounceInfo& info2);

bool collidingWithCircle(const glm::vec3& start1, const glm::vec3& end1, BounceInfo& info1, const glm::vec3& start2, const glm::vec3& end2, BounceInfo& info2, float radii, float& i);