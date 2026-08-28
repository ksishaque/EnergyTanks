/*!
\file Trace.cpp
\author Khaled S. Ishaque
        Kevin Shin
\date 9-27-2022
\brief
     function definitions for the trace message system.
     Modeled after CS 230 Trace.c, So all code does not
     Count towards amyone's code count
par  Copyright © 2022 DigiPen, All rights reserved.
*/


#include "glfw/glfw3.h"

#include <algorithm>

#include "Collider.h"
#include "General.h"
#include "ObjectManager.h"
#include "Trace.h"
#include "Window.h"
#include "TeamSystem.h"
//#include "ControllerInput.h"

#include "Engine.h"

#include <cassert>
#include "windows.h"
#include <fstream>
#include <stdarg.h>
#include <iostream>
#include <stdio.h>
#include "Trace.h"

#ifdef DEBUG_SYSTEM

Trace *Trace::instance = nullptr;

void Trace::message(const char* formatString, va_list traceArgument) {
	char temp[TRACEMESSAGELIMIT];
	vsprintf_s(temp, sizeof(temp) - 1, formatString, traceArgument);
	if(traceFile){
		if (traceFile != nullptr) {
			*traceFile << temp << std::endl;
		}
		std::cout << temp << std::endl;
	}
#ifdef _DEBUG
	OutputDebugStringA(temp);
	OutputDebugStringA("\n");
#endif
}

Trace::Trace(const char *name) : ISystem(sTrace), traceFile(nullptr) {
#ifdef _DEBUG
	forceLog(name);
#endif
}

void Trace::message(const char* formatString, ...) {
	va_list args;
	va_start(args, formatString);
	instance -> message(formatString, args);
	va_end(args);
}

Trace::~Trace() {
    if (traceFile != nullptr) {
        traceFile->close();
		delete traceFile;
    }
}

Trace *Trace::getInstance(const char *name) {
	if (instance == nullptr) {
		instance = new Trace(name);
	}
	return instance;
}

void Trace::closeInstance() {
	delete instance;
	instance = nullptr;
}

bool Trace::error(const char* formatString, ...) {
    char temp[TRACEMESSAGELIMIT];
    sprintf_s(temp, sizeof(temp) - 1, "[ERROR]: %s", formatString);
	va_list args;
	va_start(args, formatString);
	instance->forceLog();
	instance->message(temp, args);
	va_end(args);
#ifdef _DEBUG
	bool traceError = false;
	assert(traceError);
	return false;
#endif
#ifndef _DEBUG
	return true;
#endif
}

bool Trace::forceLog(const char* name) {
	if (traceFile == nullptr) {
		//std::string path = System.IO.Directory.GetParent(Application.CommonAppDataPath).ToString();
		traceFile = new std::ofstream(name, std::ios::out);
		if(AllocConsole()) {
			FILE *file;
			freopen_s(&file, "CONOUT$", "w", stdout);
		}
		return true;
	}
	return false;
}
	
void Trace::update(float &dt) {
	Trace::message("\n\n\n\n\n\t\t\t~~~~~~~~~~~~ Engine update: %1.5f ~~~~~~~~~~~~", dt);
}
#endif