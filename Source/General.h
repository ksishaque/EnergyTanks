/*!
\file   General.h
\author Kevin Shin
\date   11-11-2022
\brief
		Functions for general use
\par    Copyright © 2022 DigiPen, All rights reserved.
*/

#pragma once

/*!
\fn     template<typename Type> bool pointerCompare(Type *left, Type *right)
\tparam Type
		  Type of dereferenced values to compare
\param  left
		  First operand of the comparison
\param  right
		  Second operand of the comparison
\return If `left` is less than `right`
\brief
		This function compares the dereferenced value of two pointers, which can help with sorting.
\par    TEMPLATE REQUIREMENTS:
		  `bool operator<(Type left, Type right)`: compares the values
*/
template<typename Type> bool pointerCompare(Type *left, Type *right);

/*!
\fn     template<typename ElementType, typename Container, typename SearchValueType> ElementType &binarySearch(Container &container, int (*checkFunction)(ElementType, SearchValueType), SearchValueType searchValue)
\tparam ElementType
		  Type of element to search for
\tparam Container
		  Type of container holding the elements to search through
\tparam SearchValueType
		  Type of value used to check if the correct element is found
\param  container
		  SORTED container of elements to search through
\param  checkFunction
		  Function which, when called with parameters `a` and `b`, returns according to the following key:
			< 0: element `a` is too low on the list according to `b`
			0: element `a` is the element searched for according to `b`
			> 0: element `a` is too high on the list according to `b`
\param  searchValue
		  Value to check elements with, which will be used as the second parameter of `checkFunction`
\return Element in `container` for which `checkFunction(`RETURN VALUE`, searchValue)` returns zero
\brief
		This function uses binary search to find an element in a container.
\par    TEMPLATE REQUIREMENTS:
		  `ElementType *Container::operator[](unsigned i)`: accesses the element of the container at index `i`

*/
template<typename ElementType, typename Container, typename SearchValueType> ElementType *binarySearch(const Container &container, int (*checkFunction)(ElementType *, SearchValueType), SearchValueType searchValue);

/*!
\fn     int randomInteger(int max, int min = 0)
\param  max
          Maximum value (exclusive)
\param  min
          Minimum value (inclusive)
\return Random integer in [min, max)
\brief
        This function generates a random integer between a given maximum and minimum.
*/
int randomInteger(int max, int min = 0);

/*!
\fn     bool quadraticFormula(float a, float b, float c, float &x, bool less)
\param  a
          Second degree coefficient
\param  b
          First degree coefficient
\param  c
          Constant
\param  less
          If the root found should be the smaller of the two possible roots
\param  x
          Return reference for the root value in the equation "a(x ^ 2) + bx + c = 0"
\return If a real, non-complex root was found
\brief
        This function uses the quadratic formula to calculate the root of a given quadratic equation.
*/
bool quadraticFormula(float a, float b, float c, float &x, bool less = true);

/*!
\fn     void checkGLError(const char *info = nullptr)
\param  info
          Information to detail where the error occured
\return Nothing
\brief
        This function checks for an OpenGL error.
*/
void checkGLError(const char *info = nullptr);

#include "GeneralTemplates.cpp"