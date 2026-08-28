/*!
\file LineCollider.h
\author Khaled S. Ishaque
\date 9-27-2022
\brief
    Header file for object LineCollider class and functions in class
*/

#pragma once

#include "Collider.h"
#include <vector>
#include <iostream>
#include <stdio.h>
#include <glm/glm.hpp>

struct BounceInfo;
class CircleCollider;

class LineCollider : public Collider
{
public:
    struct lineSegments
    {
        glm::vec3 lineSegment[2];
    };
    /*!
    * @brief:
    * Default Constructor for LineCollider class
    * @param:
    * None
    * @return:
    * Nothing
    */
    LineCollider();
    /*!
    * @brief:
    * Default Destructor for LineCollider class
    * @param:
    * None
    * @return:
    * Nothing
    */
    ~LineCollider();
    /*!
     * @brief:
     * read collider variables in a file
     * @param:
     * file - the file to read the values from
     * @return:
     * Nothing
     */
    //void read(FILE* file);
    void addSegment(glm::vec3 point0, glm::vec3 point1);
	//|KHALED|
	void clearSegments();
    unsigned int getLineCount();
    std::vector<lineSegments> &getSegment();
    Component* clone() const override;
    void draw();
    //friend bool collidingWithLine(Collider* collider1,  Collider* collider2);
private:
    std::vector<lineSegments> segments;
};

bool collidingWithLine(CircleCollider* collider1, BounceInfo& info1, LineCollider* collider2);