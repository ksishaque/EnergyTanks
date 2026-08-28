/*!
\file   FontManager.cpp
\author Benedict Yau (benedict.yau\@digipen.edu)
\date   11-6-2022
\brief
        Functions for managing fonts.
\par    Copyright © 2022 DigiPen, All rights reserved.
*/

#include <glad/glad.h>
#include <iostream>
#include <cassert>

#include "FontManager.h"
#include "Trace.h"

#include "rapidjson/document.h"
#include "readFile.h"

#include <ft2build.h>
#include FT_FREETYPE_H


using rapidjson::Document;

FontManager* FontManager::instance = nullptr;

/*!
\fn     static FontManager* getInstance()
\return Singleton instance of the font manager system
\brief
        This function accesses the singleton instance of the font manager system, creating it if needed.
*/
FontManager* FontManager::getInstance() {
    if (instance == nullptr) {
        instance = new FontManager();
    }
    return instance;
}

/*!
\fn     FontManager()
\par    This function has no parameters.
\return The new font manager
\brief
        This function constructs a font manager.
*/
FontManager::FontManager() : ISystem(sFontMan)
{
}

/*!
\fn     ~FontManager()
\par    This function has no parameters.
\return Nothing
\brief
        This function destructs a font manager.
*/
FontManager::~FontManager() 
{
}

/*!
\fn     void initialize()
\par    This function has no parameters.
\return Nothing
\brief
        This function initializes the font manager.
*/
void FontManager::initialize() 
{
    if (isActive()) {
        return;
    }
    ISystem::initialize();

    //TODO: read TTF font files from JSON.

    FT_Library ft;

    if (FT_Init_FreeType(&ft)) {
        std::cout << "Error: cannot initialize FreeType library" << std::endl;
        assert(false);
        return;
    }

    std::string font_name = std::string("./Data/Fonts/Bombing.ttf");

    FT_Face face;
    if (FT_New_Face(ft, font_name.c_str(), 0, &face)) {
        std::cout << "Error: cannot load font " << font_name << std::endl;
        assert(false);
        return;
    }

    // set size to load glyphs as
    FT_Set_Pixel_Sizes(face, 0, 48);

    // disable byte-alignment restriction
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    // load first 128 characters of ASCII set
    for (unsigned char c = 0; c < 128; c++)
    {
        // Load character glyph 
        if (FT_Load_Char(face, c, FT_LOAD_RENDER))
        {
            std::cout << "Error: Failed to load glyph for character " << c << std::endl;
            continue;
        }

        // generate texture
        unsigned int texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RED,
            face->glyph->bitmap.width,
            face->glyph->bitmap.rows,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            face->glyph->bitmap.buffer
        );

        // set texture options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // now store character for later use
        Character character = {
            texture,
            glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
            glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
            static_cast<unsigned int>(face->glyph->advance.x)
        };

        charactersMap.insert(std::pair<char, Character>(c, character));
    }
    glBindTexture(GL_TEXTURE_2D, 0);

    // Destroy freetype once character textures have been built.
    FT_Done_Face(face);
    FT_Done_FreeType(ft);
}

/*!
\fn     void update(float dt)
\param  dt
            time since previous frame
\return Nothing
\brief
        This function does nothing.
*/
void FontManager::update(float dt) 
{
}

/*!
\fn     void shutdown()
\par    This function has no parameters.
\return Nothing
\brief
        This function shuts down and cleans up the shader manager.
*/
void FontManager::shutdown() 
{
    if (isActive()) {
        ISystem::shutdown();

        for (auto iter : charactersMap)
        {   
            // Delete character textures.
            unsigned int textureID = iter.second.TextureID;
            glDeleteTextures(1, &textureID);
        }

        charactersMap.clear();
    }
}

