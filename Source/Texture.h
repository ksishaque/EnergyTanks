/*!
\file   Texture.h
\author Benedict Yau (benedict.yau\@digipen.edu)
\date   9-30-2022
\brief
        Functions for managing textures
\par    Copyright © 2022 DigiPen, All rights reserved.
*/
#pragma once

class Texture
{
    public:
    /*!
    \fn     Texture()
    \par    This function has no parameters.
    \return The new texture
    \brief
            This function constructs a texture
    */
    Texture();

    /*!
    \fn     ~Texture()
    \par    This function has no parameters.
    \return Nothing
    \brief
            This function destructs a texture
    */
    ~Texture();

    /*!
    \fn     unsigned int Sprite::getID() const
    \return The texture
    \brief
            This function gets the Texture ID.
    */
    unsigned int getID() const;

	float getAlpha();

	void setAlpha(float newAlpha);


    /*!
    \fn     void setImageFormat(unsigned int imageFormat_)
    \brief
            This function sets the image format
    */
    void setImageFormat(unsigned int imageFormat_);

    /*!
    \fn     void void setInternalFormat(unsigned int internalFormat_)
    \brief
            This function sets the internal format
    */
    void setInternalFormat(unsigned int internalFormat_);

    /*!
    \fn     void createTexture(const char* fileName)
    \param  fileName
                The filename of the texture.
    \brief  This function creates a Texture
    */
    /*
    void createTexture(const char* fileName);
    */

    /*!
    \fn     void generate(unsigned int width, unsigned int height, unsigned char* data)
    \param  width_
                The width
    \param  height_
                The height
    \param  data
                The image data
    \brief  Generate texture from image data
    */
    void generate(unsigned int width_, unsigned int height_, unsigned char* data);

    /*!
    \fn     void bindTexture()
    \brief
            This function binds the texture as the current active GL_TEXTURE_2D.
    */
    void bindTexture();

    /*!
    \fn     void unBindTexture()
    \brief
        This function unbinds the texture.
    */
    void unBindTexture();

    private:
        // The Texture ID.
        unsigned int textureID;

        // The width of the texture
        unsigned int width;

        // The height of the texture
        unsigned int height;

        // The format of the image
        unsigned int imageFormat;

        // The format of the texture
        unsigned int internalFormat;

		float alpha;
};