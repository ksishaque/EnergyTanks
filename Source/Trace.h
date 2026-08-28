/*!
\file Trace.h
\author Khaled S. Ishaque
        Kevin Shin
\date 9-27-2022
\brief
    Header file for Trace Message system
*/

#pragma once

#define DEBUG_SYSTEM

#ifndef DEBUG_SYSTEM
#ifdef _DEBUG
#define DEBUG_SYSTEM
#endif
#endif

#ifdef DEBUG_SYSTEM

#define TRACEFILENAME "Trace.log"
#define TRACEMESSAGELIMIT 256

#include <iostream>

#include "ISystem.h"

class Trace : public ISystem
{
public:

	/*!
	\fn     static Trace *getInstance(const char* traceLog)
	\param  traceLog
	          Name of trace log file
	\return Singleton instance of the trace system
	\brief
	        This function accesses the singleton instance of the trace system, creating it if needed.
	*/
    static Trace *getInstance(const char* traceLog = TRACEFILENAME);

	/*!
	\fn     static void closeInstance()
	\par    This function has no parameters.
	\return Nothing
	\brief
	        This function closes and deletes the singleton instance of the trace system.
	*/
    static void closeInstance();

	/*!
	\fn     void update(float dt)
	\param  dt
	          dt
	\brief  See ISystem.h
	*/
	void update(float &dt) override;

	/*!
	\fn     static void message(const char* formatString, ...)
	\param  formatString
	          String to use for formatting the trace message
	\return Nothing
	\brief
	        This function sends a trace message.
	*/
    static void message(const char* formatString, ...);

	/*!
	\fn     static bool error(const char* formatString, ...)
	\param  formatString
	          String to use for formatting the trace message
	\return If the engine is still running (i.e. the build is in release mode)
	\brief
	        This function sends a trace error message and shuts down the engine.
	*/
    static bool error(const char* formatString, ...);

	/*!
	\fn     bool forceLog(const char *traceLog)
	\param  traceLog
	          Name of file to trace to
	\return If the log was forced open (i.e. The log was not already running)
	\brief
	        This function opens a trace file if needed.
	*/
    bool forceLog(const char* traceLog = TRACEFILENAME);

private:

	/*!
	\var    instance
	          Singleton instance of the Trace system
	*/
	static Trace *instance;

	/*!
	\var    traceFile
	          File to trace to
	*/
    std::ofstream *traceFile;

	/*!
	\fn     Trace(const char *traceLog)
	\param  traceLog
	          Name of file to trace to
	\return constructed trace system
	\brief
	        This fuction constructs a new trace system
	*/
	Trace(const char* traceLog);

	/*!
	\fn     ~Trace()
	\par    This function has no paramaters.
	\return Nothing
	\brief
	        This fuction destructs a trace system
	*/
	~Trace();

	/*!
	\fn     void message(const char* formatString, va_list traceArgument, std::ostream &out)
	\param  formatString
	          String to use for formatting the trace message
	\param  traceArgument
	          Variadic list of arguments to print
	\param  out
	          Output stream to print to
	\return Nothing
	\brief
	        This function sends a trace message.
	*/
    void message(const char* formatString, va_list traceArgument);
};
#endif