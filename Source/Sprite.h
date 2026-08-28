/*!
\file   Sprite.h
\author Benedict Yau (benedict.yau\@digipen.edu)
        Kevin Shin (kevin.shin\@digipen.edu)
\date   9-23-2022
\brief
        Functions for managing a sprite
\par    Copyright © 2022 DigiPen, All rights reserved.
*/
#pragma once

#include <string>
#include <vector>
#include <glm/glm.hpp>
#include "Component.h"
class GraphicsUnitMutable;
class Transform;
class Texture;
class Shader;
class Mesh;

class Sprite : public Component {
	public:
		/*!
		\fn     Sprite()
		\par    This function has no parameters.
		\return Constructed sprite
		\brief
		        This function constructs a sprite.
		*/
		Sprite();

        /*!
        \fn Sprite(const Sprite& other)
        \param  other
                    The sprite being copied.
        \return Constructed sprite
        \brief
                This function copy constructs a sprite.
        */
        Sprite(const Sprite& other);

		/*!
		\fn     ~Sprite()
		\par    This function has no parameters.
		\return Nothing
		\brief
		        This function destructs a sprite.
		*/
		~Sprite();

		/*!
		\fn     void update(float dt)
		\param  dt
		          time since the previous frame
		\return Nothing
		\brief
		        This function adds the sprite to the drawing queue.
		*/
		Component *clone() const override;

		/*!
		\fn     void setParent(GameObject *parent)
		\param  parent
		          game object that owns the component
		\return Nothing
		\brief
		        This function mutates the parent game object of a component, and saves the transformation pointer.
		*/
		void setParent(GameObject* parent) override;

		/*!
		\fn     void update(float dt)
		\param  dt
		          time since the previous frame
		\return Nothing
		\brief
		        This function adds the sprite to the drawing queue.
		*/
		void update(float dt) override;

        /*!
        \fn     Transform* getTransform() const
        \par    This function has no parameters.
        \return `transform`
        \brief
                This function returns the transform that can be used
                to retrieve the transform (needed for Particles to not be GameObjects)
        */
        Transform* getTransform() const;

        /*!
        \fn     void setTransform(Transform* transform)
        \brief
                This function sets the transform
                (needed for Particles to not be GameObjects)
        */
        void setTransform(Transform* transform);

        /*!
        \fn     void setColor(float red, float green, float blue, float alpha)
        \brief
                This function sets a temporary color for the next update
        */
        void setColor(float red, float green, float blue, float alpha);

        /*!
        \fn     void setColor(const glm::vec4& color)
        \brief
                This function sets a temporary color for the next update
        */
        void setColor(const glm::vec4& color);

        //|BENEDICT|
        /**
         * getType Returns the type of the sprite
         * 
         * \return Type of the sprite
         *
        void setType(GraphicsUnit::Type type);*/

		unsigned addToGraphics(GraphicsUnitMutable* unit, float teamCol = 0);

		GraphicsUnitMutable* getGraphics(unsigned unitIndex);

		void removeFromGraphics(unsigned unitIndex);

		void clearGraphics();

		unsigned getGraphicsListSize();


        /*!
        \fn     void Draw()
        */
        void Draw();


        //friend bool operator<(Sprite& sprite1, Sprite& sprite2);


	private:

		/*!
		\var    trans
		          transformation of the object, stored for conveniece and speed.
		*/
		Transform* trans;

        /*!
        \var    mesh
                  mesh used to draw the `texture`
        */
        //Mesh* mesh;

        /**
         * type Type of sprite (background, tank, walls)
         * 
         */
        //GraphicsUnit::Type type;

		std::vector<std::pair<GraphicsUnitMutable*, float>> graphicsList;
		
		glm::vec4 color;
		const glm::mat4 *view;
};



