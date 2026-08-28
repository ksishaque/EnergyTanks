/*!
\file SpriteSource.h
\author Khaled S. Ishaque
\date 11-16-2022
\brief
    Header file for SpriteSource class and functions in class
\par    Copyright © 2022 DigiPen, All rights reserved.
*/
#pragma once

#include "Texture.h"
#include "Shader.h"

class SpriteSource
{
public:
    SpriteSource(int rows = 0, int cols = 0, Texture* texture = nullptr);
    ~SpriteSource();
    Texture* getTexture();
    unsigned int getFrameCount();
    void getUV(unsigned int frameIndex, float* u, float* v);
private:
    int rows;
    int cols;
    Texture* sTexture;
};