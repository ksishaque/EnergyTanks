/*!
\file   GeneralTemplates.cpp
\author Kevin Shin
\date   11-11-2022
\brief
		Functions for general use
\par    Copyright � 2022 DigiPen, All rights reserved.
\par    NOTE: Due to templatized functions, this file is excluded from being built, and is instead included in General.h.
*/

#pragma once

#include <random>

#include "General.h"

/*!
\fn     template<typename Type> bool pointerCompare(Type *op1, Type *op2)
\tparam T
		  Type
\param  op1
		  left
\param  op2
		  right
\brief  See General.h
*/
template<typename T> bool pointerCompare(T *op1, T *op2){
	return *op1 < *op2;
}

/*!
\fn     template<typename T, typename Cont, typename Val> T binarySearch(Cont &cont, int (*checkFn)(T, Val), Val x)
\tparam T
		  ElementType
\tparam Cont
		  Container
\tparam Val
		  SearchValueType
\param  cont
		  container
\param  checkFn
		  checkFunction
\param  val
		  searchValue
\brief  See General.h
*/
template<typename T, typename Cont, typename Val> T *binarySearch(const Cont &cont, int (*checkFn)(T *, Val), Val x){

	/*	Variables:
	start: start of the range being checked
	end: end of the range being checked
	*/
	unsigned start = 0, end = (unsigned) cont.size();
	
	//	Binary search for the system
	while(start < end){
	
		//	Variables: center of the range
		unsigned mid = (start + end) / 2;
		int check = checkFn(cont[mid], x);
	
		//	Shorten range from `start` or `end` as needed
		if(check > 0) end = mid;
		else if(check < 0) start = mid + 1;
	
		//	Check for a match at `mid`
		else return cont[mid];
	}

	//	Return a reference to null upon failure
	return nullptr;
}