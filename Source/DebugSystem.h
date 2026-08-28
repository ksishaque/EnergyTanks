/*****************************************************************//**
 * \file   DebugSystem.h
 * \brief
 *
 * \author Luke
 * \date   November 2022
 * \par    Copyright © 2022 DigiPen, All rights reserved.
 *********************************************************************/
 #pragma once

#include "Trace.h"

#ifdef DEBUG_SYSTEM

#define DEBUG_SYSTEM_AVERAGE_SAMPLE_SIZE 100
#define DEBUG_SYSTEM_HOLD_TIME 0.25f
#define DEBUG_SYSTEM_LAG_TIME 125
#define DEBUG_SYSTEM_SLOW_MOTION_RATIO 8

#include <glm/glm.hpp>

#include <list>
#include <vector>

#include "ISystem.h"

class Mesh;
class Texture;
class ObjectManager;
class GameObject;

class DebugSystem : public ISystem
{
public:

	enum DebugFlag{DEBUG_MAIN, DRAW, HIDE_FPS, MANUAL_LAG, HIDE_UI, SLOW_MOTION, HIDE_DEBUG, MAX};
	static DebugSystem *getInstance();
	static void closeInstance();
    ~DebugSystem();
    void initialize();
    void update(float& dt);
    void shutdown();
	void toggleFlag(DebugFlag flag);
	void closeFlag(DebugFlag flag);
	bool getFlag(DebugFlag flag);



private:

	class DebugButton
	{
	public:
		DebugButton(int key, const std::string &name);
		void activate();
		void deactivate();
	protected:
		virtual void addAction() = 0;
		int key;
	private:
		bool active;
		std::string name;
	};

	class DebugPressButton : public DebugButton
	{
	public:
		DebugPressButton(int key, void (*fn)(), const std::string &name);
		void addAction() override;
	private:
		void (*fn)();
	};

	class DebugHoldButton : public DebugButton
	{
	public:
		DebugHoldButton(int key, void (*fn)(float), const std::string &name);
		void addAction() override;
	private:
		void (*fn)(float);
	};

	class DebugFlagButton : public DebugButton
	{
	public:
		DebugFlagButton(int key, DebugFlag flag, const std::string &name);
		void addAction() override;
	private:
		DebugFlag flag;
	};

    DebugSystem();
	void addHotkey(int key, void (*fn)(), const std::string &name = "TEST");
	void addHotkey(int key, void (*fn)(float), const std::string &name = "TEST");
	void addHotkey(int key, DebugFlag flag, const std::string &name = "TEST");
	void setHotkeys();

	static DebugSystem *instance;
    Mesh* mesh;
    Texture* texture;
    glm::mat4 trans, trans1, trans2, trans3;
    glm::mat4 offset, offsetFps;
    float flags[DebugFlag::MAX];
    std::list<float> history;
	std::vector<DebugButton *> hotkeys;
};

#endif