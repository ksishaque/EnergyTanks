/*****************************************************************//**
 * \file   Mesh.h
 * \brief
 *
 * \author Luke Tseng
 *         Benedict Yau
 * \date   September 2022
 * \par    Copyright © 2022 DigiPen, All rights reserved.
 *********************************************************************/
#pragma once

// Using glm for math
#include "glm/glm.hpp"
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <vector>

//#include "GameObject.h"
//#include "Transform.h"
#include "Component.h"
#include "Texture.h"
#include "TextureManager.h"

class Transform;
class Shader;

struct Vertex
{
    glm::vec2 position;         // The position of the vertex relative to the mesh
    glm::vec2 textureCoord;     // The texture coordinate associated with this vertex
    glm::vec4 color;            // The color to be applied to this vertex


    Vertex() : position(glm::vec2(0, 0)), textureCoord(glm::vec2(0, 0)), color(glm::vec4(0, 0, 0, 0))
    {
    }

    // Constructor for ease of use
    Vertex(const glm::vec2& position_, const glm::vec2& uv_, const glm::vec4& color_) :
        position(position_), textureCoord(uv_), color(color_)
    {
    }
};

class Mesh
{
public:
    /**
    * Mesh Default Contructor
    *
    */
    Mesh();

    /**
    * Mesh vertices Contructor
    *
    */
    Mesh(std::vector<Vertex> vertices);

    /**
     * ~Mesh Destructor
     */
    ~Mesh();
    /**
     * createMesh Creates new mesh
     *
     */
    void createMesh();

    void createTextMesh();

    /*!
    \fn     void Draw(unsigned int shader, const Transform* trans, const Sprite* spr)
    \par    shader
                The shader.
    \par    trans
                The translation.
    */
    void Draw(const glm::mat4 &matrix, Texture* texture, const glm::vec4 &color, float u = 0.0f, float v = 0.0f, float scale = 1.0f);

private:
    // id of mesh
    unsigned int meshID;
    // id of vertex buffer
    unsigned int vertexBufferID;

    /*!
    \var    meshVertexCount
                number of vertexes in the mesh
    */
    int meshVertexCount;
};


