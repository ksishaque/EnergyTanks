/*!
\file   Shader.cpp
\author Benedict Yau (benedict.yau\@digipen.edu)
\date   9-30-2022
\brief
        Functions for managing shaders
\par    Copyright © 2022 DigiPen, All rights reserved.
*/

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <fstream>
#include <sstream>

#include "General.h"
#include "Trace.h"

#include "Shader.h"

/*!
\fn     Shader()
\par    This function has no parameters.
\return The new shader
\brief
        This function constructs a shader
*/
Shader::Shader() : shaderID(0) 
{
}

/*!
\fn     ~Shader()
\par    This function has no parameters.
\return Nothing
\brief
        This function destructs a shader
*/
Shader::~Shader() 
{
    if (shaderID) 
    {
        glDeleteShader(shaderID);
    }
}

/*!
\fn     Shader& Use()
\par    This function has no parameters.
\return Shader&
\brief
        This function sets the current shader as active
*/
Shader& Shader::Use() {
    glUseProgram(shaderID);
    return *this;
}

/*!
\fn     unsigned int Sprite::getID() const
\return The texture
\brief
        This function gets the Shader ID.
*/
unsigned int Shader::getID() const 
{
    return shaderID;
}

/*!
\fn void PrintShaderError(unsigned int shaderID)
\param shaderID
        The ID of the shader.
\brief
        This function prints error with the shader.
*/
void Shader::PrintShaderError(unsigned int shaderID) {
    // Create an array to store the message
    GLchar infoLog[256] = { 0 };
    // Store the length of the info message
    GLsizei infoLength = 0;
    // Get the info log from the shader
    glGetShaderInfoLog(shaderID, sizeof(infoLog), &infoLength, infoLog);
    // Print the info message
#ifdef DEBUG_SYSTEM
	Trace::error("Failed to compile shader %u: %s", shaderID, infoLog);
#else
	assert("Shader error");
#endif
}

/*!
\fn unsigned int compile(const char* vertexFile, const char* pixelFile)
\param vertexFile
        The vertex shader file.
\param pixelFile
        The pixel shader file.
\brief
        This function creates the shader
*/
unsigned int Shader::compile(const char* vertexFile, const char* pixelFile) {
    // Load vertex shader data from the file
    std::ifstream vertexShaderFile(vertexFile);     // Open a stream for this file
    std::stringstream vertexShaderData;             // Create a stringstream
    vertexShaderData << vertexShaderFile.rdbuf();   // Store the file data in the stringstream
    vertexShaderFile.close();

    // Load pixel shader data from the file
    std::ifstream pixelShaderFile(pixelFile);
    std::stringstream pixelShaderData;
    pixelShaderData << pixelShaderFile.rdbuf();
    pixelShaderFile.close();

    // Initalize temporarily IDs for shader stages
    unsigned int vertexStage = 0;
    unsigned int pixelStage = 0;
    
    // Create a variable that checks if successful.
    GLint success = false;


    // glCreateShader creates a shader object. It takes in a parameter called
    // shaderType, which specifies the type of shader you want to create. There
    // is a list of them at Khronos. We are using GL_VERTEX_SHADER.
    vertexStage = glCreateShader(GL_VERTEX_SHADER);
    checkGLError("Shader");

    // Get the shader text from the string stream
    std::string shaderString = vertexShaderData.str();
    const char* shaderText = shaderString.c_str();
    GLint textLength = (GLint)shaderString.size();

    // Assign the shader source
    // glShaderSource sets code in shade to source code in the array of strings.
    glShaderSource(vertexStage, 1, &shaderText, &textLength);
    checkGLError("Shader");
    
    // glCompile compiles the vertex shader.
    glCompileShader(vertexStage);
    checkGLError("Shader");

   // glGetShaderiv gets a parameter from the shader object.
   // glGetShaderiv takes in the shader, the specific object parameter, 
   // and the requested object parameter. There is a list of the requestable object parameters
   // on Khronos. We are using GL_COMPILE_STATUS to check if the last
   // compile operation on shader was successful.
    glGetShaderiv(vertexStage, GL_COMPILE_STATUS, &success);
    checkGLError("Shader");

    // If not successful.
    if (!success) {
        PrintShaderError(vertexStage);
        //assert(false);
        return 0;
    }

    // Create the pixel shader ID
    pixelStage = glCreateShader(GL_FRAGMENT_SHADER);
    checkGLError("Shader");

    // Get the shader text from the stringstream
    shaderString = pixelShaderData.str();
    shaderText = shaderString.c_str();
    textLength = (GLint)shaderString.size();
    // Assign the shader source
    glShaderSource(pixelStage, 1, &shaderText, &textLength);
    checkGLError("Shader");

    // Compile the pixel shader
    glCompileShader(pixelStage);
    checkGLError("Shader");

    // Check if the compilation was successful
    glGetShaderiv(pixelStage, GL_COMPILE_STATUS, &success);
    checkGLError("Shader");

    // If not successful, print the error and return
    if (!success)
    {
        PrintShaderError(pixelStage);
        // Use assert to stop the program so we can see what is happening
        //assert(false);
        return 0;
    }

    // Create the shader program with glCreateProgram.
    shaderID = glCreateProgram();
    checkGLError("Shader");

    // Attach the vertex and pixel stage to the shader program.
    glAttachShader(shaderID, vertexStage);
    checkGLError("Shader");
    glAttachShader(shaderID, pixelStage);
    checkGLError("Shader");

    // Link the shader program
    glLinkProgram(shaderID);
    checkGLError("Shader");
    
    // Check if program linked successfully
    glGetProgramiv(shaderID, GL_LINK_STATUS, &success);
    checkGLError("Shader");

    if (!success)
    {
        PrintShaderError(shaderID);
        //assert(false);
        return 0;
    }

    // Delete vertex and pixel shader data.
    glDeleteShader(vertexStage);
    glDeleteShader(pixelStage);

    return shaderID;
}

#if 0
/*!
\fn     void Shader::CheckError()
\brief  See Shader.h
*/
void Shader::CheckError()
{
    // Get the current error value
    GLenum error = glGetError();
    // Check if there is an error
    if (error != GL_NO_ERROR)
    {
		Trace::error("OpenGL error (shader): %u", error);
    }
}
#endif

/*!
\fn     void Shader::setMatrices()
\brief  See Shader.h
*/
void Shader::setMatrices(const glm::mat4 &view, const glm::mat4 &proj){
    glUseProgram(shaderID);
    checkGLError("Shader");
    GLint projectionLoc = glGetUniformLocation(shaderID, "projection");
    checkGLError("Shader");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(proj));
    checkGLError("Shader");
    GLint viewLoc = glGetUniformLocation(shaderID, "view");
    checkGLError("Shader");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    checkGLError("Shader");
}