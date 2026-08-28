/*!
\file   ReadFile.h
\author Kevin Shin (kevin.shin\@digipen.edu)
\date   9-15-2022
\brief
        Functions for reading files
\par    Copyright © 2022 DigiPen, All rights reserved.
*/

#pragma once
#include <cstdio>

/*!
\fn     const char *readWholeFile(const char *fileName)
\param  fileName:
          name of the file to read
\return A newly allocated c-style string containing all of the contents of the file
\par    NOTE: THE RETURN VALUE POINTS TO DYNAMIC MEMORY, WHICH MUST BE FREED
\brief
        This function reads a whole file into a c-style string.
*/
const char *readWholeFile(const char *fileName);