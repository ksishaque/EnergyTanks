/*!
\file   Window.h
\author Kevin Shin (kevin.shin\@digipen.edu)
\date   9-27-2022
\brief
        Functions for creating and maintaining the window
\par    Copyright © 2022 DigiPen, All rights reserved.
*/

#pragma once
#include "ISystem.h"

#define BASEWINDOWWIDTH 1280
#define BASEWINDOWHEIGHT 720

struct GLFWmonitor;
struct GLFWwindow;

class Window : public ISystem{
    public:

		/*!
		\fn     static Window *getInstance()
		\par    This function has no parameters.
		\return Singleton instance of the window
		\brief
		        This function retrieves the Singleton instance of the window.
		*/
		static Window *getInstance();

		/*!
		\fn     static void closeInstance()
		\par    This function has no parameters.
		\return Nothing
		\brief
		        This function closes the Singleton instance of the window.
		*/
		static void closeInstance();

		/*!
		\fn     void initialize()
		\par    This function has no parameters.
		\return Nothing
		\brief
		        This function initializes the window.
		*/
        void initialize() override;

		/*!
		\fn     void update(flost dt)
		\param  dt
		          time since previous frame
		\return Nothing
		\brief
		        This function updates the window.
		*/
        void update(float &dt) override;

		/*!
		\fn     void shutdown()
		\par    This function has no parameters.
		\return Nothing
		\brief
		        This function shuts down the window system.
		*/
        void shutdown() override;

		/*!
		\fn     GLFWwindow *getHandle() const
		\par    This function has no parameters.
		\return Nothing
		\brief
		        This function accesses the handle of the window.
		*/
        GLFWwindow *getHandle() const;

		/*!
		\fn     float getScale() const
		\par    This function has no parameters
		\return Scale of the window compared to base size
		\brief
		        This function accesses the scale of the active window when compared to the base 1280 by 720 size.
		*/
		float getScale() const;

		/*!
		\fn     int getWidth() const
		\par    This function has no parameters
		\return window width in px
		\brief
				This function returns the current window width.
		*/
		int getWidth() const;

		/*!
		\fn     int getHeight() const
		\par    This function has no parameters
		\return window height in px
		\brief
				This function returns the current window height.
		*/
		int getHeight() const;

		/*!
		\fn     void setFullscreen()
		\par    This function has no parameters.
		\return Nothing
		\brief
		        This function toggles the full screen state of the window.
		*/
        void setFullscreen();

		/*!
		\fn     void setFullscreen(bool fullscreen)
		\param  fullscreen
		          If the window should be set to full screen
		\return Nothing
		\brief
		        This function mutates the full screen state of the window.
		*/
        void setFullscreen(bool fullscreen);

		/*!
		\fn     bool isFullscreen()
		\par    This function has no parameters.
		\return If the window is in full screen mode
		\brief
		        This function checks if the window is in full screen mode.
		*/
        bool isFullscreen();

		/*!
		\fn     void changeMonitor(int increment)
		\param  increment
		          Number of monitors to "move" by
		\return Nothing
		\brief
		        This function moves the full screen window to another monitor.
		*/
        void changeMonitor(int increment);

		/*!
		\fn     friend void updateWindowSize(GLFWwindow *handle, int width, int height)
		\param  handle
		          Handle of the window
		\param  width
		          New width of the window
		\param  height
		          New heigth of the window
		\return Nothing
		\brief
		        This function updates the window size.
		*/
		friend void updateWindowSize(GLFWwindow *handle, int width, int height);

		/*!
		\fn     friend void checkMonitor(GLFWmonitor *monitor, int event)
		\param  monitor
		          Monitor affected
		\param  event
		          Event that occurred
		\return Nothing
		\brief
		        This function checks if the current monitor was disconnected.
		*/
		friend void checkMonitor(GLFWmonitor *monitor, int event);

		/*!
		\fn     friend void closeWindow(GLFWwindow *handle)
		\param  handle
		          Handle of the window
		\return Nothing
		\brief
		        This function attempts to close the window.
		*/
		friend void closeWindow(GLFWwindow *handle);

	private:

		/*!
		\fn     Window()
		\par    This function has no parameters
		\return Constructed window system
		\brief
		        This function constructs a window system.
		*/
		Window();

		/*!
		\var    instance
		          Singleton instance of the window
		*/
		static Window *instance;

		/*!
		\var    outdated
		          If the window size or camera position are outdated
		*/
		bool outdated;

		/*!
		\var    fullscreen
		          If the window is displayed in full screen
		*/
		bool fullscreen;

		/*!
		\var    handle
		          Pointer to the window
		*/
		GLFWwindow *handle;

		/*!
		\var    monitor
		          Pointer to the current fullscreen monitor
		*/
		GLFWmonitor *monitor;

		/*!
		\var    scale
		          Scale of window when compared to base size
		*/
		float scale;

		/*!
		\var    width
		          Width of the window
		\var    height
		          Height of the window
		*/
		int width, height;

		/*!
		\var    oldWidth
		          Width of the window before full screen
		\var    oldHeight
		          Height of the window before full screen
		\var    oldX
		          X-position of the window before full screen
		\var    oldY
		          Y-position of the window before full screen
		*/
		int oldWidth, oldHeight, oldX, oldY;
		int test = BASEWINDOWWIDTH;

		/*!
		\var    camX
		          X-position of the camera
		\var    camY
		          Y-position of the camera
		*/
		float camX, camY;

		/*!
		\var    forceAbort
		          If the window should be forced to abort at the next close input
		*/
		bool forceAbort;

};