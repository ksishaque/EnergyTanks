/*!
\file   TransformAction.cpp
\author Kevin Shin
\date   4-5-2023
\brief
        Functions for creating and managing an action node for moving an object
\par    Copyright © 2023 DigiPen, All rights reserved.
*/

#include "GameObject.h"
#include "Physics.h"
#include "Transform.h"

#include "TransformAction.h"

/*!
\fn     TransformAction::TransformAction(float dur, const std::vector<float> &cos)
\param  dur
          time
\param  cos
          coefficients
\brief  See TransformAction.h
*/
TransformAction::TransformAction(float dur, const std::vector<float> &cos) : xFinal(0), t(0), dtScale(1 / dur), dTrans(), fTrans(), iTrans(), bTrans(false), dScale(), fScale(), iScale(), bScale(false), dRot(0), fRot(0), iRot(0), bRot(false), trans(nullptr){

	//	Initialize `size` and `cos`
	size = (unsigned) cos.size();
	this -> cos = new float[size];

	//	Calculate `cos` and `xFinal`
	for(unsigned i = 0; i < size; i += 1){

		//	Copy values of `cos`
		this -> cos[i] = cos[i];

		//	Calculate `xFinal`
		xFinal += cos[i];

	}
	 
}

/*!
\fn     static float &circleMod(float &rot)
\param  rot
          Angle to clamp
\return `rot`, for chaining
\brief
        This function rotates an angle by increments of 360 to get a number in [0, 360).
*/
static float &circleMod(float &rot){

	//	Rotate clockwise
	while(rot < 0) rot += 360;

	//	Rotate counter clockwise;
	while(rot >= 360) rot -= 360;

	//	Return;
	return rot;

}

/*!
\fn     static float circleMod(const float &rot)
\param  rot
          Angle to clamp
\return Clamped angle
\brief
        This function rotates an angle by increments of 360 to get a number in [0, 360).
*/
static float circleMod(const float &rot){

	//	Variable: Return value / clamped angle
	float ans = rot;

	//	Rotate clockwise
	while(ans < 0) ans += 360;

	//	Rotate counter clockwise;
	while(ans >= 360) ans -= 360;

	//	Return;
	return ans;

}

/*!
\fn     void TransformAction::operator()(GameObject *obj, float dt)
\param  obj
          object
\param  dt
          dt
\brief  See ActionNode.h
*/
void TransformAction::operator()(GameObject *obj, float dt){

	//	Attempt to initialize
	if(trans == nullptr){

		//	Get `trans`
		trans = dynamic_cast<Transform *>(obj -> get(ComponentTypeEnum::cTransform));

		//	Check `trans`
		if(trans == nullptr) return;

		//	Variable: `Physics` of the object
		Physics *phys = dynamic_cast<Physics *>(obj -> get(ComponentTypeEnum::cPhysics));

		//	Deactivate `phys`, if applicable
		if(phys){

			//	Zero velocity, rotational velocity and acceleration
			phys -> setVelocity({0, 0, 0});
			phys -> setVelocityRotate(0);
			phys -> setAcceleration({0, 0, 0});

		}

		//	Set translation values
		if(bTrans){

			//	Record `iTrans`
			iTrans = trans -> getTranslation();

			//	Check for no movement
			if(iTrans == fTrans) bTrans = false;

			//	Calculate `dTrans` and `fTrans`
			dTrans = fTrans - iTrans;
			fTrans = iTrans + (dTrans * xFinal);

		}

		//	Set scale values
		if(bScale){

			//	Record `iScale`
			iScale = trans -> getScale();

			//	Check for no scaling
			if(iScale == fScale) bScale = false;

			//	Calculate `dScale` and `fScale`
			dScale = fScale - iScale;
			fScale = iScale + (dScale * xFinal);

		}

		//	Set rotation values
		if(bRot){

			//	Record `iRot`
			iRot = circleMod(trans -> getRotation());

			//	Check for no turning
			if(iRot == fRot) bRot = false;
			else{

				//	Get `dRot` in either direction
				dRot = fRot;
				if(iRot > fRot) dRot += 360;
				else fRot -= 360;
				fRot -= iRot;
				dRot -= iRot;

				//	Compare `dRot`s
				if(dRot > -fRot) dRot = fRot;

				//	Find `fRot`
				fRot = dRot;
				fRot *= xFinal;
				fRot += iRot;
				circleMod(fRot);

			}

		}

	}

	//	Variable: Current pre-scale 1-dimensional velocity
	float x = 0;

	//	Calculate `x`
	for(unsigned i = 0; i < size; i += 1){

		//	Calculate `x`
		x += cos[i];
		x *= t;

	}
	
	//	Set tranformation
	if(bTrans) trans -> setTranslation(iTrans + (dTrans * x));
	if(bScale) trans -> setScale(iScale + (dScale * x));
	if(bRot) trans -> setRotatePos(iRot + (dRot * x));

	//	Update `t`
	t += dt * dtScale;

	//	Check for final position
	if(t >= 1){

		//	Set final values
		if(bTrans) trans -> setTranslation(fTrans);
		if(bScale) trans -> setScale(fScale);
		if(bRot) trans -> setRotatePos(fRot);

		//	Declare the action complete
		completed(obj, (t - 1) / dtScale);

		//	Return
		return;

	}

}

/*!
\fn     TransformAction *TransformAction::clone() const
\brief  See ActionNode.h
*/
TransformAction *TransformAction::clone() const{

	//	Variable: return value / clone of `this`
	TransformAction *ans = new TransformAction(*this);

	//	Set `next`
	ans -> operator<<(*cloneNext());

	//	Return
	return ans;

}

/*!
\fn     TransformAction::TransformAction(const TransformAction &that)
\param  that
          source
\brief  See TransformAction.h
*/
TransformAction::TransformAction(const TransformAction &that) : xFinal(that.xFinal), size(that.size), t(0), dtScale(that.dtScale), dTrans(), fTrans(that.fTrans), iTrans(), bTrans(that.bTrans), dScale(), fScale(that.fScale), iScale(), bScale(that.bScale), dRot(0), fRot(that.fRot), iRot(0), bRot(that.bRot), trans(nullptr){

	//	Initialize `cos`
	cos = new float[size];
	for(unsigned i = 0; i < size; i += 1) cos[i] = that.cos[i];
	 
}

/*!
\var    DEFAULT_COEFFICIENTS
          See TransformAction.h
*/
const std::vector<float> TransformAction::DEFAULT_COEFFICIENTS{-2, 3, 0};

/*!
\fn     TransformAction::~TransformAction()
\brief  See TransformAction.h
*/
TransformAction::~TransformAction(){
	delete[] cos;
}

/*!
\fn     void TransformAction::setTranslation(const glm::vec3 &trans)
\param  trans
          translaton
\brief  See TransformAction.h
*/
void TransformAction::setTranslation(const glm::vec3 &trans){

	//	Set `fTrans` and `bTrans`
	fTrans = trans;
	bTrans = true;

}

/*!
\fn     void TransformAction::setScale(const glm::vec3 &scale)
\param  scale
          scale
\brief  See TransformAction.h
*/
void TransformAction::setScale(const glm::vec3 &scale){

	//	Set `fScale` and `bScale`
	fScale = scale;
	bScale = true;

}

/*!
\fn     void TransformAction::setRotation(float rot)
\param  rot
          rotation
\brief  See TransformAction.h
*/
void TransformAction::setRotation(float rot){

	//	Set `fRot` and `bRot`
	fRot = circleMod(rot);
	bRot = true;

}