/*!
\file SpriteSource.cpp
\author Khaled S. Ishaque
\date 11-16-2022
\brief
    CPP file for SpriteSource class and functions in class
\par    Copyright © 2022 DigiPen, All rights reserved.
*/
#include "SpriteSource.h"
#include "Texture.h"
#include "Trace.h"

/*!
 * @brief:
 * Constructor for the SpriteSource Class
 * @param:
 * rows - amount of rows for the sprite source sheet
 * cols - amount of cols for the sprite source sheet
 * texture - the sheet itself
 * @return:
 * Nothing
 */
SpriteSource::SpriteSource(int rows, int cols, Texture* texture) :
    rows(rows),
    cols(cols),
    sTexture(texture) {
    Trace::message("SpriteSource Ctor Called.");
}

/*!
 * @brief:
 * Destructor for the SpriteSource Class
 * @param:
 * None
 * @return:
 * Nothing
 */
SpriteSource::~SpriteSource() {
    Trace::message("Attempting to destroy SpriteSource...");
    try {
        rows = 0;
        cols = 0;
        delete sTexture;
        //texture is somehow not deleted
        if (sTexture != nullptr) {
            //Something caused sTexture to not be deleted
            throw -1;
        }
        else {
            Trace::message("SpriteSource Deleted");
        }
    }
    catch (int error) {
        if (error == -1) {
            Trace::message("Error: SpriteSource Texture Can't be Deleted");
        }
    }
}

/*!
 * @brief:
 * Get the current texture picture of the Sprite Source Sheet
 * @param:
 * None
 * @return:
 * sTexture - The current texture of the Sprite Source
 * nullptr - The texture was not allocated correctly
 */
Texture* SpriteSource::getTexture() {
    try {
        //null ptr chck
        if (sTexture) {
            Trace::message("Texture Returned.");
            return sTexture;
        }
        else {
            //no texture was set
            throw -1;
        }
    }
    catch (int error) {
        if (error == -1) {
            Trace::message("Error: Texture is NOT SET");
        }
        return nullptr;
    }
}

/*!
 * @brief:
 * Gets the frame count for the current sprite source
 * @param:
 * None
 * @return:
 * frame - The frame count of the current sprite source
 * NULL - No rows or columns were stated in the sprite source
 */
unsigned int SpriteSource::getFrameCount() {
    Trace::message("Attempting Frame Count...");
    try {
        //garbage check
        if (rows && cols) {
            //making and sending frame count
            unsigned int frame = rows * cols;
            Trace::message("Frame Count made. Returning Frame Count...");
            return frame;
        }
        else {
            //either rows or cols are not initialized
            throw -1;
        }
    }
    catch (int error) {
        if (error == -1) {
            Trace::message("Error While Making Frame Count. Rows = %f, Cols = %f.", rows, cols);
        }
        return NULL;
    }
}

/*!
 * @brief:
 * Gets the current F32 U and F32 V of the current sprite source
 * @param:
 * frameIndex - Frame index in sprite source sheet
 * *u - Pointer to the F32 U coordinate
 * *v - Pointer to the F32 V coordinate
 * @return:
 * None
 */
void SpriteSource::getUV(unsigned int frameIndex, float* u, float* v) {
    //size of current u and v via cols and rows
    float uSize = 1.0f / cols;
    float vSize = 1.0f / rows;
    //Aquiring F32 values. Requires ints for computation, no floats should be used when computing F32s
    *u = uSize * (frameIndex % cols);
    *v = vSize * (frameIndex / cols);
}