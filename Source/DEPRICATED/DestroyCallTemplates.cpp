/*!
\file   DestroyCallTemp.cpp
\author Kevin Shin (kevin.shin\@digipen.edu)
\date   1-30-2023
\brief
        Template functions for maintaining a `DestroyCall`
\par    Copyright © 2022 DigiPen, All rights reserved.
\par    NOTE: These functions have been separated from DestroyCall.cpp and excluded from the build a they are template functions included in DestroyCall.h
*/

#pragma once

#include "DestroyCall.h"

/*!
\fn     template<typename T> DestroyCall::DeleterTemp<T>::DeleterTemp(T *obj)
\tparam T
          Type
\param  obj
          object
\brief  See DestroyCall.h
*/
template<typename T> DestroyCall::DeleterTemp<T>::DeleterTemp(T *obj) : object(obj) {}

/*!
\fn     template<typename T> DestroyCall::DeleterTemp<T>::DeleterTemp(T *obj)
\tparam T
          Type
\param  obj
          object
\brief  See DestroyCall.h
*/
template<typename T> DestroyCall::DeleterTemp<T>::~DeleterTemp(){
	delete object;
}

/*!
\fn     template<typename T> DestroyCall::DeleterTemp<T>::~DeleterTemp()
\tparam T
          Type
\brief  See DestroyCall.h
*/
template<typename T> DestroyCall::DeleterTemp<T>::~DeleterTemp(){
	delete object;
}

/*!
\fn     template<typename T> DestroyCall::DeleterTemp<T>::~DeleterTemp()
\tparam T
          Type
\param  obj
          dependent
\brief  See DestroyCall.h
*/
template<typename T> void DestroyCall::add(T *obj){
	dependents.push_back(new DeleterTemp<T>(obj));
}