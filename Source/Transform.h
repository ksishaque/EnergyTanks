/*!
\file Transform.h
\author Khaled S. Ishaque
        Kevin Shin
\date 9-15-2022
\brief
    function declarations for object transform components
\par Copyright © 2022 DigiPen, All rights reserved.
*/
#pragma once

#include "Component.h"
#include <glm/glm.hpp>
#include <stdio.h>

typedef class Transform* TransformPtr;

static const glm::vec3 BASE_SCALE_TRANSFORM(1.f, 1.f, 1.f);

class Transform : public Component
{
private:
    /*!
        \var    translation
                  vector of the object's current translation
    */
    glm::vec3 translation;
    /*!
        \var    scale
                  vector of the object's scale
    */
    glm::vec3 scale;
    /*!
        \var    transformMatrix
                  matrix of the object's transform
    */
    mutable glm::mat4 transformMatrix;
    /*!
        \var    rotation
                  object's rotation as a float
    */
    float rotation;
    /*!
        \var    dirtyMatrix
                  bool to say if the object's matrix is bad or not
    */
    mutable bool dirtyMatrix;
public:
    /*!
        \fn     Transform(const glm::vec3 &translation, const glm::vec3 &scale = BASE_SCALE, float rotation = 0)
        \par    translation
                    The initial translation
        \par    scale
                    The initial scale
        \par    rotation
                    The initial rotation
        \return Nothing
        \brief
                This function creates a new transform class and set all values to 0
     */
    Transform(const glm::vec3 &translation, const glm::vec3 &scale = BASE_SCALE_TRANSFORM, float rotation = 0);
    /*!
        \fn     Transform(float x = 0, float y = 0, float z = 0, float scale = 1, float rotation = 0)
        \par    xPos
                    The initial x position
        \par    yPos
                    The initial y position
        \par    zPos
                    The initial z position
        \par    xScale
                    The initial x scale
        \par    yScale
                    The initial y scale
        \par    zScale
                    The initial z scale
        \par    rotation
                    The initial rotation
        \return Nothing
        \brief
                This function creates a new transform class and set all values to 0
     */
    Transform(float xPos = 0, float yPos = 0, float zPos = 1, float xScale = 1, float yScale = 1, float zScale = 1, float rotation = 0);
    /*!
        \fn     Transform(const Transform& baseTransform)
        \par    baseTransform
                    A transform class to copy values over
        \return Nothing
        \brief
                This function creates a new transform class and set all values to
                the given base transform class
     */
    Transform(const Transform& baseTransform);
    /*!
        \fn     ~Transform()
        \par    This function has no parameters.
        \return Nothing
        \brief
                This function destroys a transform class
     */
    ~Transform();
    /*!
        \fn     void read(File* file)
        \par    file
                    opened file to read values from
        \return Nothing
        \brief
                This function reads and sets transform values from files
     */
    void read(FILE* file);
    /*!
        \fn     void setTranslation(glm::vec3 &newTrans)
        \par    newTrans
                    new translation value given
        \return Nothing
        \brief
                This function sets the translation value the vector given
     */
    void setTranslation(const glm::vec3 &newTrans);
    /*!
        \fn     void setTranslation(float x, float y, float z = 0)
        \par    x
                    new x position given
        \par    y
                    new y position given
        \par    z
                    new z position given
        \return Nothing
        \brief
                This function sets the scale value the vector given
     */
    void setTranslation(float x, float y, float z = 0);
    /*!
        \fn     void setScale(glm::vec3 newScale)
        \par    newScale
                    new scale value given
        \return Nothing
        \brief
                This function sets the scale value the vector given
     */
    void setScale(float newScale);
    /*!
        \fn     void setScale(glm::vec3 &newScale)
        \par    newScale
                    new scale value given
        \return Nothing
        \brief
                This function sets the scale value the vector given
     */
    void setScale(const glm::vec3 &newScale);
    /*!
        \fn     void setScale(float x, float y, float z = 1)
        \par    x
                    new x scale given
        \par    y
                    new y scale given
        \par    z
                    new z scale given
        \return Nothing
        \brief
                This function sets the translation value the vector given
     */
    void setScale(float x, float y, float z = 1);
    /*!
        \fn     void setRotatePos(float newRotate)
        \par    newRotate
                    new Rotation value given
        \return Nothing
        \brief
                This function sets the rotation value the float given
     */
    void setRotatePos(float newRotate);
    /*!
        \fn     glm::vec3 translationGetting()
        \par    None
        \return Translation vector
        \brief
                This function gets the translation value
     */
    glm::vec3 getTranslation() const;
    /*!
        \fn     glm::vec3 getScale()
        \par    None
        \return Scale vector
        \brief
                This function gets the scale value
     */
    glm::vec3 getScale() const;
    /*!
        \fn     void updateMatrix()
        \par    None
        \return Nothing
        \brief
                This function updates the transform matrix
     */
    void updateMatrix() const;
    /*!
        \fn     glm::vec3 getMatrix()
        \par    None
        \return Transform matrix
        \brief
                This function gets the transform matrix
     */
    const glm::mat4& getMatrix() const;
    /*!
        \fn     float getRotation()
        \par    None
        \return Rotation float
        \brief
                This function gets the rotation value
     */
    float getRotation() const;

    Component* clone() const override;

    //void update(float dt) override;
};