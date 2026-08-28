/*!
\file Text.cpp
\author Khaled S. Ishaque
\date 11-17-2022
\brief
    CPP file for Font and FontBasic class and functions in both classes
\par Copyright © 2022 DigiPen, All rights reserved.
\par SOURCE(S) CITED: https://learnopengl.com/In-Practice/Text-Rendering, https://learn.microsoft.com/en-us/windows/win32/opengl/glteximage2d
*/

#include "Text.h"

Font::Font()
{
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    FT_Init_FreeType(&fontSheet); //initialize the using font sheet bitmap
    //load the font sheet for use via the file location and the bitmap
    FT_New_Face(fontSheet, "./Data/Fonts/Lato-Black.ttf", 0, &fontFace);
}

Font::~Font()
{
    //precedence: free the face of the fonts (sheet), then the bitmap
    FT_Done_Face(fontFace);
    FT_Done_FreeType(fontSheet);
}

Font::Character* Font::makeChar(unsigned int ID, glm::vec2 size, glm::vec2 bearing, unsigned int next)
{
    Character* newChar = new Character();
    newChar->textureID = ID;
    newChar->glyphSize = size;
    newChar->glyphBearing = bearing;
    newChar->nextGlyph = next;
    return newChar;
}

void Font::loadChar()
{
    //TEST: only using the first 128 Characters of ASCII
    for (unsigned char c = 0; c < 128; c++)
    {
        //error check for when a character wanted from the true/free type can't be loaded
        FT_Error fontErr = FT_Load_Char(fontFace, c, FT_LOAD_RENDER);
        if (fontErr)
        {
            Trace::message("Error: True/Free Type Font Can't Load Font Glyph");
            continue; // proceed to next char
        }
        //Proceed to Generate Char Texture
        unsigned int textureNum;
        glGenTextures(1, &textureNum);
        glBindTexture(GL_TEXTURE_2D, textureNum);
        //Store Relevant Text Texture Information
        /*KEY THINGS:
        target - the target texture (MUST BE 2D)
        level - level of detail, 0 means we are using base image level
        internalFormat - number of texture color components
        width - width of texture image
        height - height of texture image
        border - texture boarder. either 0 or 1
        format - pixel data format
        type - pixel data type
        pixels - POINTER to image data in memory
        source - https://learn.microsoft.com/en-us/windows/win32/opengl/glteximage2d
        */
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, fontFace->glyph->bitmap.width, fontFace->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, fontFace->glyph->bitmap.buffer);
        //texture options for the now made character
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        //storing the character for later use
        Character* characters;
        characters = makeChar(textureNum, glm::ivec2(fontFace->glyph->bitmap.width, fontFace->glyph->bitmap.rows), glm::ivec2(fontFace->glyph->bitmap_left, fontFace->glyph->bitmap_top), (unsigned int)fontFace->glyph->advance.x);
        CharacterList.insert(std::pair<char, Character>(c, *characters));
    }
}

