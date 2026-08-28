/*!
\file Text.h
\author Khaled S. Ishaque
\date 11-17-2022
\brief
    Header file for Font and FontBasic class and functions in both classes
\par Copyright © 2022 DigiPen, All rights reserved.
\par SOURCE CITED: https://learnopengl.com/In-Practice/Text-Rendering
*/
#pragma once

//Standard Library
#include <map>
#include <string>
#include <iostream>
//Graphics
#include <glad/glad.h>
//Math
#include <glfw/glfw3.h>
#include <glm/glm.hpp>
//Font
#include <ft2build.h>
#include FT_FREETYPE_H
//Self-Created
#include "SpriteSource.h"
#include "Sprite.h"
#include "Shader.h"
#include "Mesh.h"
#include "Transform.h"
#include "Trace.h"

class Font
{
public:
    struct Character
    {
        unsigned int textureID;
        glm::vec2 glyphSize;
        glm::vec2 glyphBearing;
        unsigned int nextGlyph;
    };

    Font();
    ~Font();
    Character* makeChar(unsigned int ID, glm::vec2 size, glm::vec2 bearing, unsigned int next);
    void loadChar();
    void setPixelSize();
    void renderText(Shader* shader, std::string text, Transform* transform, glm::vec3 color);
private:
    FT_Library fontSheet;
    FT_Face fontFace;
    std::map<GLchar, Character> CharacterList;
};

class FontBasic
{
public:
    FontBasic();
    ~FontBasic();

private:
    Sprite sprite;
    SpriteSource fontSheet;
    Mesh fontMesh;
};