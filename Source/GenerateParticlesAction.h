/*!
\file   GenerateParticlesAction.h
\author Benedict Yau
\date   3-29-2023
\brief
		 Nodes in an action list that generate particles.
\par    Copyright © 2023 DigiPen, All rights reserved.
*/
#pragma once

class ChangeStateAction;

#include <string>

#include "ActionNode.h"

#define generateParticlesAct(pType) new GenerateParticlesAction(pType)


class GenerateParticlesAction : public ActionNode {
	public:

		GenerateParticlesAction(const std::string& pType);

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
		\fn     PlaySoundAction *clone() const
		\brief  See ActionNode.h
		*/
		GenerateParticlesAction* clone() const;

	private:
		std::string particleType;
};
