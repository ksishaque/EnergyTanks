/*!
\fnile  Window.cpp
\author Kevin Shin (kevin.shin\@digipen.edu)
\date   9-27-2022
\brief
        Functions for creating and maintaining the window
\par    Copyright © 2022 DigiPen, All rights reserved.
*/

#pragma warning(push)
#pragma warning(disable:6262)
#pragma warning(disable:26451)
#include "stb_image.h"
#pragma warning(pop)
#include "glad/glad.h"
#include <glfw/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Engine.h"
#include "General.h"
#include "PauseSystem.h"
#include "ShaderManager.h"
#include "ShutdownSystem.h"
#include "Trace.h"

#include "Window.h"

/*!
\fn     Window::Window()
\brief  See Window.h
*/
Window::Window() : ISystem(sWindow), outdated(true), fullscreen(true), handle(nullptr), monitor(nullptr), scale(0), width(0), height(0), oldWidth(BASEWINDOWWIDTH), oldHeight(BASEWINDOWHEIGHT), oldX(100), oldY(100), camX(0), camY(0), forceAbort(false){}

/*!
\fn     static void updateSize(GLFWwindow *handle, int w, int h)
\param  handle
          handle
\param  w
          width
\param  h
          height
\brief  See Window.h
*/
static void updateWindowSize(GLFWwindow *handle, int w, int h){

	//	Set `width` and `hieght`
	Window::instance -> width = w;
	Window::instance -> height = h;

	//	Set `outdated`
	Window::instance -> outdated = true;

}

/*!
\fn     static void closeWindow(GLFWwindow *handle)
\param  handle
          window
\brief  See Window.h
*/
static void closeWindow(GLFWwindow *handle){

#ifdef _DEBUG
	//	Skip closing sequence in debug mode
	Engine::getInstance() -> stop();
#endif

	//	Focus window
	glfwRequestWindowAttention(Window::instance -> handle);

	//	Setup pause menu
	PauseSystem::getInstance() -> pauseFull();

	//	Initiate the shutdown sequence
	ShutdownSystem::getInstance() -> initiateShutdown();

	//	Check if the close is from ALT+F4
	if(glfwGetKey(Window::instance -> handle, GLFW_KEY_F4) == GLFW_PRESS && (glfwGetKey(Window::instance -> handle, GLFW_KEY_RIGHT_ALT) == GLFW_PRESS || glfwGetKey(Window::instance -> handle, GLFW_KEY_LEFT_ALT) == GLFW_PRESS)){

		//	Check for a forced abort
		if(Window::instance -> forceAbort) abort();

		//	Attempt to stop the engine
		Engine::getInstance() -> stop();

		//	Set `forceAbort`
		Window::instance -> forceAbort = true;

	}

}

/*!
\fn     void checkMonitor(GLFWmonitor *mon, int e)
\param  mon
          monitor
\param  e
          event
\brief  See Window.h
*/
void checkMonitor(GLFWmonitor *mon, int e){

	//	Check `mon` and `e`
	if(e != GLFW_DISCONNECTED || mon != Window::instance -> monitor) return;

	//	Reset `monitor`
	Window::instance -> monitor = glfwGetPrimaryMonitor();

	//	Update `monitor`
	Window::instance -> changeMonitor(0);

}

/*!
\fn     void Window::initialize()
\brief  See Window.h
*/
void Window::initialize(){

	//	Check if the system is already active
	if(isActive()) return;

	//	Initialize the system
	ISystem::initialize();
	
	//	Initialize and check the GLFW library
	if(!glfwInit()){
#ifdef DEBUG_SYSTEM
		Trace::error("Failed to initialize GLFW library");
#else
		assert("Display error!");
#endif
		return;
	}
	
	//	Set window hints
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SRGB_CAPABLE, GLFW_TRUE);

	//	Set `monitor`
	monitor = glfwGetPrimaryMonitor();
	
#ifdef _DEBUG
	
	//	Create, check and save window handle
	handle = glfwCreateWindow(BASEWINDOWWIDTH, BASEWINDOWHEIGHT, "Energy Tanks (Debug)", nullptr, nullptr);
	fullscreen = false;

#else

	//*
	
	//	Variable: Video mode of `monitor`
	const GLFWvidmode *mode = glfwGetVideoMode(monitor);

	//	Create, check and save window handle
	handle = glfwCreateWindow(mode -> width, mode -> height, "Energy Tanks", monitor, nullptr);

	/*/
	
	//	Create, check and save window handle
	handle = glfwCreateWindow(1920, 1080, "Energy Tanks", nullptr, nullptr);
	fullscreen = false;

	//*/

#endif

	//	Check `handle`
	if(handle == nullptr){
#ifdef DEBUG_SYSTEM
		Trace::error("Failed to create window handle");
#else
		assert("Display error!");
#endif
		return;
	}
	
	//	Set the glfw context to focus on `handle`
	glfwMakeContextCurrent(handle);

	//	Set the screen to swap as soon as possible
	glfwSwapInterval(1);

	//	Set the window size minimum
	glfwSetWindowSizeLimits(handle, BASEWINDOWWIDTH * 4 / 5, BASEWINDOWHEIGHT * 4 / 5, GLFW_DONT_CARE, GLFW_DONT_CARE);
	
	//	Load OpenGL to the current context using the glad loader
	if(!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))){
		
		//	Close and terminate window
		glfwDestroyWindow(handle);
		glfwTerminate();

		//	Crash
#ifdef DEBUG_SYSTEM
		Trace::error("Failed to load OpenGL");
#else
		assert("Display error!");
#endif
		return;

	}

	//	Set event-processing for size change, monitors and closing
	glfwSetFramebufferSizeCallback(handle, updateWindowSize);
	glfwSetMonitorCallback(checkMonitor);
	glfwSetWindowCloseCallback(handle, closeWindow);

	//	Variable: Image to set as icon
	GLFWimage icon;

	//	Load `image`
	//TEMPORARY
	icon.pixels = stbi_load("Data/Art/icon.png", &icon.width, &icon.height, nullptr, 4);

	//	Set icon
	glfwSetWindowIcon(handle, 1, &icon);

	//	Disable cursor
	glfwSetInputMode(handle, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

	//	Get `width` and `height` in pixels
	glfwGetFramebufferSize(handle, &width, &height);

}

/*!
\fn     void Window::update()
\param  dt
          dt
\brief  See Window.h
*/
void Window::update(float &dt){

	//	Check if the system is active
	if(!isActive()) return;
	
	// Swap the buffers to display everything from the current loop on thescreen
	glfwSwapBuffers(handle);

	//	Update viewport and `scale`
	if(outdated){

		//	Create a viewport at the correct size
		glViewport(0, 0, width, height);
		checkGLError("Window");

		/*	Variable
		view: Matrix representing the view of the camera
		proj: Projection of the view
		*/
		glm::mat4 view = glm::lookAt(glm::vec3(camX, camY, 0.0f), glm::vec3(camX, camY, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glm::mat4 proj = glm::ortho(camX - (width / 2.0f), camX + (width / 2.0f), camY - (height / 2.0f), camY + (height / 2.0f));

		//	Set matrices to shaders
		ShaderManager::getShader(ShaderManager::ShaderType::color) -> setMatrices(view, proj);
		ShaderManager::getShader(ShaderManager::ShaderType::texture) -> setMatrices(view, proj);

		// Reset the shader
		glUseProgram(0);
		checkGLError("Window");

		//	Calculate scale
		scale = ((float) width) / BASEWINDOWWIDTH;
		if(((float) height) / BASEWINDOWHEIGHT < scale) scale = ((float) height) / BASEWINDOWHEIGHT;

		//	Reset `outdated`
		outdated = false;

	}

}

/*!
\fn     void Window::shutdown()
\brief  See Window.h
*/
void Window::shutdown(){

	//	Check if the system was active
	if(!isActive()) return;

	//	Shutdown the system
	ISystem::shutdown();

	//	Close and terminate window
	glfwDestroyWindow(handle);
	glfwTerminate();

}

/*!
\fn     GLFWwindow *Window::getHandle() const
\brief  See Window.h
*/
GLFWwindow *Window::getHandle() const{
	return handle;
}

/*!
\fn     float Window::getScale() const
\brief  See Window.h
*/
float Window::getScale() const{
	return scale;
}

/*!
\fn     int Window::getWidth() const
\brief  See Window.h
*/
int Window::getWidth() const{
	return width;
}

/*!
\fn     int Window::getHeight() const
\brief  See Window.h
*/
int Window::getHeight() const{
	return height;
}


/*!
\fn     Window *Window::getInstance()
\brief  See Window.h
*/
Window *Window::getInstance(){

	//	Check and make `instance`
	if(instance == nullptr) instance = new Window();

	//	Return
	return instance;
}

/*!
\var    instance
\brief  See Window.h
*/
Window *Window::instance = nullptr;

/*!
\fn     void Window::closeInstance()
\brief  See Window.h
*/
void Window::closeInstance(){

	//	Delete and clear `instance`
	delete instance;
	instance = nullptr;

}

/*!
\fn     void Window::setFullscreen(bool in)
\param  in
          fullscreen
\brief  See Window.h
*/
void Window::setFullscreen(bool in){

	//	Check `in`
	if(in == fullscreen) return;

	//	Set `fullscreen`
	fullscreen = in;
	
#ifdef DEBUG_SYSTEM
	Trace::message("Toggle fullscreen");
#endif

	//	Set to full screen
	if(in){

		//	Save old window information
		glfwGetWindowPos(handle, &oldX, &oldY);
		glfwGetWindowSize(handle, &oldWidth, &oldHeight);
		if(test != oldWidth) test = oldWidth;

		//	Variable: Video mode of `monitor`
		const GLFWvidmode *mode = glfwGetVideoMode(monitor);

		//	Set to fullscreen
		glfwSetWindowMonitor(handle, monitor, 0, 0, mode -> width, mode -> height, GLFW_DONT_CARE);

	}
	else glfwSetWindowMonitor(handle, nullptr, oldX, oldY, oldWidth, oldHeight, GLFW_DONT_CARE);
	
#ifdef DEBUG_SYSTEM
	Trace::message("Toggle fullscreen complete!");
#endif

}

/*!
\fn     void Window::setFullscreen()
\brief  See Window.h
*/
void Window::setFullscreen(){
	setFullscreen(!fullscreen);
}

/*!
\fn     void Window::changeMonitor(int inc)
\param  inc
          increment
\brief  See Window.h
*/
void Window::changeMonitor(int inc){

	//	Check `fullscreen`
	if(!fullscreen) return;

	/*	Variables:
	i: Index of `monitor` in `mons`
	max: Maximum number of monitors
	mons: List of monitors
	*/
	int i = 0, max;
	GLFWmonitor **mons = glfwGetMonitors(&max);

	//	Find `i`
	while(i < max && mons[i] != monitor) i += 1;
	if(i >= max) return;

	//	Increment `i`
	i += max;
	i += inc;
	i %= max;

	//	Get new `monitor`
	monitor = mons[i];

	//	Variable: Video mode of `monitor`
	const GLFWvidmode *mode = glfwGetVideoMode(monitor);

	//	Change monitors
	glfwSetWindowMonitor(handle, monitor, 0, 0, mode -> width, mode -> height, GLFW_DONT_CARE);

}

/*!
\fn     bool Window::isFullscreen()
\brief  See Window.h
*/
bool Window::isFullscreen(){
	return fullscreen;
}