/*****************************************************************//**
 * \file   Mesh.cpp
 * \brief  
 * 
 * \author Luke Tseng
 *         Benedict Yau
 * \date   September 2022
 * \par    Copyright © 2022 DigiPen, All rights reserved.
 *********************************************************************/


// Using glad to help with loading OpenGL
#include "glad/glad.h"
#include <glm/gtx/transform.hpp>

#include "General.h"
#include "Transform.h"
#include "Trace.h"
#include "ShaderManager.h"

#include "Mesh.h"

//TODO: Benedict: Move all of the OpenGL stuff OUT OF SPRITE AND INTO MESH CLASS.

/**
* Mesh Default Contructor
*
*/
Mesh::Mesh() : meshID(0),
               vertexBufferID(0),
               meshVertexCount(0)
{
}

/**
* Mesh vertices Contructor
*
*/
Mesh::Mesh(std::vector<Vertex> vertices) : meshID(0),
                                           vertexBufferID(0),
                                           meshVertexCount(0)
{

    // Generate the mesh
    glGenVertexArrays(1, &meshID);

    // Bind the mesh as the current OpenGL object
    glBindVertexArray(meshID);

    // Generate the vertex buffer
    glGenBuffers(1, &vertexBufferID);

    // Bind the vertex buffer as the current object
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);

    // Create an array of vertex data for this mesh

    Vertex verticesArray[1077];
    std::copy(vertices.begin(), vertices.end(), verticesArray);

    // Assign the vertex data to the mesh
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticesArray), &verticesArray, GL_STATIC_DRAW);

    // These attribute layout values are assigned in the vertex shader
    GLint posAttribute = 0;
    GLint uvAttribute = 1;
    GLint colorAttribute = 2;

    // Set the position attribute (2 float values)
    glVertexAttribPointer(posAttribute, 2, GL_FLOAT, false, sizeof(Vertex), 0);

    // Set the texture coordinate attribute (2 float values, offset by the size of a vec2)
    glVertexAttribPointer(uvAttribute, 2, GL_FLOAT, false, sizeof(Vertex), (void*)(sizeof(glm::vec2)));

    // Set the color attribute (4 float values, offset by the size of 2 vec2s)
    glVertexAttribPointer(colorAttribute, 4, GL_FLOAT, false, sizeof(Vertex), (void*)(sizeof(glm::vec2) * 2));

    // Enable the attributes
    glEnableVertexAttribArray(posAttribute);
    glEnableVertexAttribArray(uvAttribute);
    glEnableVertexAttribArray(colorAttribute);

    // Unbind the vertex array to reset
    const unsigned int unbindAll = 0;
    glBindVertexArray(unbindAll);

    meshVertexCount = (int)vertices.size();
}

/**
* ~Mesh Destructor
*/
Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &meshID);

    //	Delete mesh
    if (meshID) {
        //	Delete mesh and check for errors
        glDeleteVertexArrays(1, &meshID);
		checkGLError("mesh");
    }

    if (vertexBufferID) {
        //	Delete vertex buffer and check for errors
        glDeleteBuffers(1, &vertexBufferID);
		checkGLError("mesh");
    }
}

/* This code has been taken from the OpenGL example, it can be found here:
 * https://distance.digipen.edu/2022-fall/mod/resource/view.php?id=61433
 * This code has been understood and repurposed for 
 * this project by Luke Tseng and Benedict Yau.*/
void Mesh::createMesh()
{
    meshID = 0;
    vertexBufferID = 0;
    
	// Generate the mesh
	glGenVertexArrays(1, &meshID);
	
	// Bind the mesh as the current OpenGL object
	glBindVertexArray(meshID);
	
	// Generate the vertex buffer
	glGenBuffers(1, &vertexBufferID);
	
	// Bind the vertex buffer as the current object
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
	
	// Create an array of vertex data for this mesh

    /*
	vertices.push_back(Vertex(glm::vec2(0.75f, 0.75f), glm::vec2(1.0f, 0.0f), glm::vec4(0.5f, 0.5f, 1.0f, 1.0f)));
    vertices.push_back(Vertex(glm::vec2(0.75f, -0.75f), glm::vec2(1.0f, 1.0f), glm::vec4(1.0f, 1.0f, 0.5f, 1.0f)));
    vertices.push_back(Vertex(glm::vec2(-0.75f, -0.75f), glm::vec2(0.0f, 1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)));
    vertices.push_back(Vertex(glm::vec2(0.75f, 0.75f), glm::vec2(1.0f, 0.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)));
    vertices.push_back(Vertex(glm::vec2(-0.75f, -0.75f), glm::vec2(0.0f, 1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)));
    vertices.push_back(Vertex(glm::vec2(-0.75f, 0.75f), glm::vec2(0.0f, 0.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)));
    */

    
    Vertex verticess[] = {
        Vertex(glm::vec2(0.5f, 0.5f), glm::vec2(1.0f, 0.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)),
        Vertex(glm::vec2(0.5f, -0.5f), glm::vec2(1.0f, 1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)),
        Vertex(glm::vec2(-0.5f, -0.5f), glm::vec2(0.0f, 1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)),
        Vertex(glm::vec2(0.5f, 0.5f), glm::vec2(1.0f, 0.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)),
        Vertex(glm::vec2(-0.5f, -0.5f), glm::vec2(0.0f, 1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)),
        Vertex(glm::vec2(-0.5f, 0.5f), glm::vec2(0.0f, 0.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)),
    };
    

	// Assign the vertex data to the mesh
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticess), &verticess, GL_STATIC_DRAW);

	// These attribute layout values are assigned in the vertex shader
	GLint posAttribute = 0;
	GLint uvAttribute = 1;
	GLint colorAttribute = 2;

	// Set the position attribute (2 float values)
	glVertexAttribPointer(posAttribute, 2, GL_FLOAT, false, sizeof(Vertex), 0);
	
	// Set the texture coordinate attribute (2 float values, offset by the size of a vec2)
	glVertexAttribPointer(uvAttribute, 2, GL_FLOAT, false, sizeof(Vertex), (void*)(sizeof(glm::vec2)));
	
	// Set the color attribute (4 float values, offset by the size of 2 vec2s)
	glVertexAttribPointer(colorAttribute, 4, GL_FLOAT, false, sizeof(Vertex), (void*)(sizeof(glm::vec2) * 2));

	// Enable the attributes
	glEnableVertexAttribArray(posAttribute);
	glEnableVertexAttribArray(uvAttribute);
	glEnableVertexAttribArray(colorAttribute);	

	// Unbind the vertex array to reset
	const unsigned int unbindAll = 0;
	glBindVertexArray(unbindAll);

    meshVertexCount = sizeof(verticess) / sizeof(verticess[0]);
}

/* This function is taken from the DigiPen OpenGL example, and the source can be found here:
 * https://distance.digipen.edu/2022-fall/mod/resource/view.php?id=61433
 * The code in the function has been remodeled after understanding how the meshes are made
 * By: Khaled Ishaque
 */
void Mesh::createTextMesh()
{
    //setting ID of the mesh
    meshID = 0;
    vertexBufferID = 0;

    // Generate the mesh and bind as current OpenGL object to work with
    glGenVertexArrays(1, &meshID);
    glBindVertexArray(meshID);

    // Generate and bind vertex buffer(s) to current object being made
    glGenBuffers(1, &vertexBufferID);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);

    //Making the vertices of the 2 triangles
    Vertex textVertices[] =
    {
        Vertex(glm::vec2(0.5f, 0.5f), glm::vec2(1.0f / 16, 0.0f), glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)),
        Vertex(glm::vec2(0.5f, -0.5f), glm::vec2(1.0f / 16, 1.0f / 6), glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)),
        Vertex(glm::vec2(-0.5f, -0.5f), glm::vec2(0.0f, 1.0f / 6), glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)),
        Vertex(glm::vec2(0.5f, 0.5f), glm::vec2(1.0f / 16, 0.0f), glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)),
        Vertex(glm::vec2(-0.5f, -0.5f), glm::vec2(0.0f, 1.0f / 6), glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)),
        Vertex(glm::vec2(-0.5f, 0.5f), glm::vec2(0.0f, 0.0f), glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)),
    };

    //Assign vertex data to mesh and make shader attribute layouts
    glBufferData(GL_ARRAY_BUFFER, sizeof(textVertices), &textVertices, GL_STATIC_DRAW);
    GLint posAttribute = 0;
    GLint uvAttribute = 1;
    GLint colorAttribute = 2;

    //set position and texture coordinate attributes
    glVertexAttribPointer(posAttribute, 2, GL_FLOAT, false, sizeof(Vertex), 0);
    glVertexAttribPointer(uvAttribute, 2, GL_FLOAT, false, sizeof(Vertex), (void*)(sizeof(glm::vec2)));

    // Enable the attributes and unbind vertex array to reset mesh making
    glEnableVertexAttribArray(posAttribute);
    glEnableVertexAttribArray(uvAttribute);
    glEnableVertexAttribArray(colorAttribute);
    const unsigned int unbindAll = 0;
    glBindVertexArray(unbindAll);

    //Set the new vertex count
    meshVertexCount = sizeof(textVertices) / sizeof(textVertices[0]);
}

/*!
\fn     void Draw(unsigned int shader, const Transform* trans, const Sprite* spr)
\par    shader
            The shader.
\par    trans
            The translation.
*/
void Mesh::Draw(const glm::mat4& matrix, Texture* texture, const glm::vec4& color, float u, float v, float scale)
{

	//|BENEDICT|
	Shader *shader;
	if(texture == nullptr) shader = ShaderManager::getShader(ShaderManager::ShaderType::color);
	else shader = ShaderManager::getShader(ShaderManager::ShaderType::texture);
	glUseProgram(shader->getID());
    
    checkGLError("mesh");

    // Bind the texture
    if(texture) texture->bindTexture();
    checkGLError("mesh");

	//|BENEDICT|
	glm::mat4 newMatrix = glm::scale(glm::vec3(scale, scale, 1)) * matrix;

    // Set the transformation matrix on the shader
    GLint transformLoc = glGetUniformLocation(shader->getID(), "world");
    checkGLError("mesh");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(newMatrix));
    checkGLError("mesh");

    GLint textOffset = glGetUniformLocation(shader->getID(), "texOffset");
    checkGLError("mesh");
    glUniform2f(textOffset, u, v);
    checkGLError("mesh");
	
	GLint alpha = glGetUniformLocation(shader->getID(), "color");
	checkGLError("mesh");
	glUniform4f(alpha, color.r, color.g, color.b, color.a);
	checkGLError("mesh");
	
    if (&meshID != nullptr)
    {
        // Draw the currently bound mesh
        // Bind the mesh
        // Reset the mesh, shader, and texture
        glBindVertexArray(meshID);
        checkGLError("mesh");
        glDrawArrays(GL_TRIANGLES, 0, meshVertexCount);
        checkGLError("mesh");
        glBindVertexArray(0);
        checkGLError("mesh");
    }
}
