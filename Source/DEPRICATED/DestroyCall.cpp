/*!
\file   DestroyCall.cpp
\author Kevin Shin (kevin.shin\@digipen.edu)
\date   1-30-2023
\brief
        Functions for maintaining a `DestroyCall`
\par    Copyright © 2022 DigiPen, All rights reserved.
*/

#include "DestroyCall.h"

/*!
\fn     DestroyCall::DestroyCall()
\brief  See DestroyCall.h
*/
DestroyCall::DestroyCall() : dependents() {}

/*!
\fn     DestroyCall::~DestroyCall()
\brief  See DestroyCall.h
*/
DestroyCall::~DestroyCall(){
	 
	//	Activate all `Deleter`s
	while(!dependents.empty()){

		//	
	}
}