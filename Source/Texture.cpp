/*!
\file   Texture.cpp
\author Benedict Yau (benedict.yau\@digipen.edu)
\date   9-30-2022
\brief
        Functions for managing textures
\par    Copyright © 2022 DigiPen, All rights reserved.
*/

#include "Texture.h"
#include "glad/glad.h"

//TODO: (Benedict): DO TEXTURE MANAGER AFTER.

/*!
\fn     Texture()
\par    This function has no parameters.
\return The new texture
\brief
        This function constructs a texture
*/
Texture::Texture() : textureID(0),
                     width(0),
                     height(0),
                     imageFormat(0),
                     internalFormat(0),
				     alpha(1.0f) {
}

/*!
\fn     ~Texture()
\par    This function has no parameters.
\return Nothing
\brief
        This function destructs a texture
*/
Texture::~Texture() {
    if (textureID) {
        glDeleteTextures(1, &textureID);
    }
}

/*!
\fn     unsigned int Sprite::getID() const
\return The texture
\brief
        This function gets the Texture ID.
*/
unsigned int Texture::getID() const {
    return textureID;
}

/*!
\fn     float Texture::getAlpha()
\return The alpha
\brief
		This function gets the alpha.
*/
float Texture::getAlpha() {
	return alpha;
}

/*!
\fn     void Texture::setAlpha(float newAlpha)
\param	newAlpha The new alpha value.
\brief
		This function sets the alpha.
*/
void Texture::setAlpha(float newAlpha) {
	alpha = newAlpha;
}

/*!
\fn     unsigned int Sprite::getID() const
\return The texture
\brief
        This function gets the Texture ID.
*/
void Texture::setImageFormat(unsigned int imageFormat_) {
    imageFormat = imageFormat_;
}

/*!
\fn     void void setInternalFormat(unsigned int internalFormat_)
\brief
        This function sets the internal format
*/
void Texture::setInternalFormat(unsigned int internalFormat_) {
    internalFormat = internalFormat_;
}

/* This code has been taken from the OpenGL example, it can be found here:
 * https://distance.digipen.edu/2022-fall/mod/resource/view.php?id=61433
 * This code has been understood and repurposed for this project by Benedict Yau.
 */
void Texture::generate(unsigned int width_, unsigned int height_, unsigned char* data) {
    width = width_;
    height = height_;

    // glGenTextures requires the specification of n, the number of texture
    // names to be generated, and the array where the generated texture names are stored.
    // In this case, we are returning to address of textureID because it is not an array,
    // and only generating one single texture.
    glGenTextures(1, &textureID);

    glBindTexture(GL_TEXTURE_2D, textureID);

    // Store the texture data that we have created.
    // glTexStorage2D will be used instead of glTexStorage because it
    // is not in this version of OpenGL.
    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, imageFormat, GL_UNSIGNED_BYTE, data);

    // glTexParameter set the parameters of the texture.
    // glTexParameteri means the parameter is of type integar.
    // GL_TEXTURE_MIN_FILTER is used, and there are 6 minifying functions,
    // 4 of which use mipmaps. The one we want is one of the other 2, GL_LINEAR.
    // GL_LINEAR returns average of the four texture elements which are closest to the texture coordinates.
    // GL_NEAREST returns the value of the texture element nearest to the texture coordinates.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    // GL_TEXTURE_MAG_FILTER is used when the texture should be magified.
    // GL_TEXTURE_MAG_FILTER has to use only the non-mipmap functions,
    // GL_LINEAR and GL_NEAREST.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Set the wrap mode to be mirrored: GL_TEXTURE_WRAP_S sets the wrap parameter
    // for the texture coordinate s, to be 1 of 5 modes.
    // We are picking GL_MIRRORED_REPEAT.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);

    // Use GL_MIRROED_REPEAT
    // GL_TEXTURE_WRAP_T sets the texture coordinate t instead of s.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

    glBindTexture(GL_TEXTURE_2D, 0);
}

/*!
\fn     void bindTexture()
\brief
        This function binds the texture as the current active GL_TEXTURE_2D.
*/
void Texture::bindTexture() {
    // glBindTexture binds the named texture to the texturing target.
    // The target is the target to which the texture is being bound to,
    // there is a list of targets the program must specify in the Khronos
    // OpenGL refpages.
    // The texture is just the name of the texture.
    glBindTexture(GL_TEXTURE_2D, textureID);
}

/*!
\fn     void unBindTexture()
\brief
        This function binds the texture as the current active GL_TEXTURE_2D.
*/
void Texture::unBindTexture() {
    glBindTexture(GL_TEXTURE_2D, 0);
}
