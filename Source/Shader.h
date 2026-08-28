/*!
\file   Shader.h
\author Benedict Yau (benedict.yau\@digipen.edu)
\date   9-30-2022
\brief
        Functions for managing shaders
\par    Copyright © 2022 DigiPen, All rights reserved.
*/
#pragma once

class Shader;

#include "Sprite.h"

class Shader
{
    public:
    /*!
    \fn     Shader()
    \par    This function has no parameters.
    \return The new shader
    \brief
            This function constructs a shader
    */
    Shader();

    /*!
    \fn     ~Shader()
    \par    This function has no parameters.
    \return Nothing
    \brief
            This function destructs a shader
    */
    ~Shader();

    /*!
    \fn     Shader& Use()
    \par    This function has no parameters.
    \return Shader&
    \brief
            This function sets the current shader as active
    */
    Shader& Use();

    /*!
    \fn     unsigned int Sprite::getID() const
    \return The texture
    \brief
            This function gets the Shader ID.
    */
    unsigned int getID() const;

    /*!
    \fn void PrintShaderError(unsigned int shaderID)
    \param shaderID
            The ID of the shader.
    \brief
            This function prints error with the shader.
    */
    void PrintShaderError(unsigned int shaderID);
    // Creates a shader object from the specified files

    /*!
    \fn unsigned int compile(const char* vertexFile, const char* pixelFile)
    \param vertexFile
            The vertex shader file.
    \param pixelFile
            The pixel shader file.
    \brief
            This function creates the shader
    */
    unsigned int compile(const char* vertexFile, const char* pixelFile);

    /*!
    \fn void setMatrices(const char* vertexFile, const char* pixelFile)
    \param viewMatrix
            The view matrix.
    \param projectionMatrix
            The projection matrix.
    \brief
            This function sets matrices to a shader
    */
    void setMatrices(const glm::mat4 &viewMatrix, const glm::mat4 &projectionMatrix);

    private:
        /*!
        \fn void CheckError()
        \brief
                This checks for errors
        */
        // Helper function to check for OpenGL errors
        //void CheckError();


        unsigned int shaderID;
};

