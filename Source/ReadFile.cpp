/*!
\file   ReadFile.cpp
\author Kevin Shin (kevin.shin\@digipen.edu)
\date   9-15-2022
\brief
        Functions for reading files
\par    Copyright © 2022 DigiPen, All rights reserved.
*/

#include "ReadFile.h"

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

/*!
\def    fCheck(val):
          checks if a file function returned an unexpected outcome, and returns from the current function accordingly
*/
#define fCheck(val) if(val != 0) [[unlikely]] return 0

/*!
\fn     char *readWholeFile(const char *name)
\param  name:
          fileName
\brief
        See ReadFile.h
*/
const char *readWholeFile(const char *name){
	/*	Variables:
	file: stream for the file named `name`
	data: stream for the information inside `file`
	*/
	std::ifstream file(name);
	std::stringstream data;

	//	Read information from `file` to `data`
	data << file.rdbuf();
	file.close();

	//	Variable: return value / file information as a c-style string
	char *ans = new char[data.str().length() + 1];

	//	Convert `data` to c-style string and return
	strcpy_s(ans, data.str().length() + 1, data.str().c_str());
	return ans;
}