/*!
\file   TransformAction.h
\author Kevin Shin
\date   4-5-2023
\brief
        Functions for creating and managing an action node for moving an object
\par    Copyright © 2023 DigiPen, All rights reserved.
*/
#pragma once

class TransformAction;

#include <glm/glm.hpp>
#include <vector>

#include "SequentialAction.h"

#define transformActCo(time, cos) new TransformAction(time, cos)
#define transformAct(time) new TransformAction(time)

class Transform;

/*!
\class  TransformAction
\brief
        Nodes in an action list that moves the object
*/
class TransformAction : public SequentialAction{
	private:

		/*!
		\var    DEFAULT_COEFFICIENTS
		          Default coefficients to use
		*/
		static const std::vector<float> DEFAULT_COEFFICIENTS;

	public:

		/*!
		\fn     TransformAction(float time, const std::vector<float> &coefficients)
		\param  time
		          Duration of the action
		\param  coeffecicients
		          List of coefficients to use for the movement equation
		\return Newly constructed move action
		\brief
		        This function constructs a new moving node.
		*/
		TransformAction(float time, const std::vector<float> &coefficients = DEFAULT_COEFFICIENTS);

		/*!
		\fn     TransformAction(const TransformAction &source)
		\param  source
		          Transform action to copy
		\return Newly constructed move action
		\brief
		        This function constructs a new moving node by copying an existing node.
		*/
		TransformAction(const TransformAction &source);

		/*!
		\fn     ~TransformAction()
		\par    This function has no parameters.
		\return Nothing
		\brief
		        This function destructs a moving node.
		*/
		~TransformAction();

		/*!
		\fn     void setTranslation(const glm::vec3 &translation);
		\param  translation
		          Translation to set
		\return Nothing
		\brief
		        This function sets what translation to reach.
		*/
		void setTranslation(const glm::vec3 &translation);

		/*!
		\fn     void setScale(const glm::vec3 &scale);
		\param  scale
		          Scale to set
		\return Nothing
		\brief
		        This function sets what scale to reach.
		*/
		void setScale(const glm::vec3 &scale);

		/*!
		\fn     void setRotation(float rotation);
		\param  rotation
		          Rotation to set
		\return Nothing
		\brief
		        This function sets what rotation to reach.
		*/
		void setRotation(float rotation);

		/*!
		\fn     void operator()(GameObject *object, float dt)
		\param  object
		          object
		\param  dt
		          dt
		\brief  See ActionNode.h
		*/
		void operator()(GameObject *object, float dt);

		/*!
		\fn     TransformAction *clone() const
		\brief  See ActionNode.h
		*/
		TransformAction *clone() const;

	private:

		/*!
		\var    cos
		          Derived coefficients for the movement equation
		\var    xFinal
		          Final "position" of the movement equation
		\var    size
		          Size of `cos`
		*/
		float *cos, xFinal;
		unsigned size;

		/*!
		\var    t
		          Time value on a scale of durations (i.e. the action will start at t = 0 and finish at t = 1)
		\var    dtScale
		          Scale from seconds to durations
		*/
		float t, dtScale;

		/*!
		\var    dTrans
		          Scale from equation units to translation
		\var    fTrans
		          Final translation reached
		\var    iTrans
		          Initial translation
		\var    bTrans
		          If translation will be changed
		*/
		glm::vec3 dTrans, fTrans, iTrans;
		bool bTrans;

		/*!
		\var    dScale
		          Scale from equation units to scale
		\var    fScale
		          Final scale reached
		\var    iScale
		          Initial scale
		\var    bScale
		          If scale will be changed
		*/
		glm::vec3 dScale, fScale, iScale;
		bool bScale;

		/*!
		\var    dRot
		          Scale from equation units to rotation
		\var    fRot
		          Final rotation reached
		\var    iRot
		          Initial rotation
		\var    bRot
		          If rotation will be changed
		*/
		float dRot, fRot, iRot;
		bool bRot;

		/*!
		\var    trans
		          Pointer to the object's transform component, for convenience
		*/
		Transform *trans;

};