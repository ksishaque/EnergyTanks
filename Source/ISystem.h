/*!
\file   ISystem.h
\author Kevin Shin (kevin.shin\@digipen.edu)
        Benedict Yau (benedict.yau\@digipen.edu)
\date   9-9-2022
\brief
        Functions for managing a sprite
\par    Copyright © 2022 DigiPen, All rights reserved.
*/

#pragma once
#include <string>

class ISystem
{
	public:

		/*!
		\enum   Type
		          Type of system the ISystem is.
		\par    NOTE: All positive values are systems that need to be updated, while any system that only holds information is negative.
		\par    NOTE: THIS LIST MUST BE IN THE ORDER IN WHICH EACH SYSTEM IS RUN! PLEASE MAKE SURE THIS ORDER IS CORRECT WHENEVER YOU ADD A NEW SYSTEM!
		\var    sTeam
		          Team System
		\var    sShaMan
		          Shader Manager
		\var    sTexMan
		          Texture Manager
		\var    sMeshMan
		          Mesh Manager
		\var    sShutdown
		          Shutdown system
		\var    sInvalid
		          Invalid System Type
		\var    sObjMan
		          Object Managers
		\var    sCollide
		          Collision Managers
		\var    sParticle
		          Particle Generator
		\var    sDebug
		          Debug System
		\var    sRender
		          Render Queue
		\var    sSound
		          SoundSystem
		\var    sCuller
		          Object Cullers
		\var    sWindow
		          Window Systems
		\var    sGSMan
		          Game State Manager (should be after sObjMan)
		*/
		enum Type{sTeam = -5, sShaMan = -4, sTexMan = -3, sMeshMan = -2, sShutdown = -1, sInvalid = 0, sTrace = 1, sDebug = 2, sPause = 3, sObjMan = 4, sConMan = 5, sCollide = 6, sParticle = 7, sRender = 8, sSound = 9, sCuller = 10, sWindow = 11};

		/*!
		\fn     ISystem(Type type = sInvalid)
		\param  type
		          Type of system
		\return Constructed system
		\brief
		        This function constructs a system
		*/
		ISystem(Type type = sInvalid);

		/*!
		\fn     virtual ~ISystem()
		\par    This function has no parameters.
		\return Nothing
		\brief
		        This function deconstructs a system.
		*/
		virtual ~ISystem();

		/*!
		\fn     virtual void initialize()
		\par    This function has no parameters.
		\return Nothing
		\brief
		        This function initializes a system.
		*/
		virtual void initialize();

		/*!
		\fn     virtual void update(float dt)
		\param  dt
		          time since previous frame
		\return Nothing
		\brief
		        This function updates a system.
		*/
		virtual void update(float &dt){}

		/*!
		\fn     virtual void shutdown()
		\par    This function has no parameters.
		\return Nothing
		\brief
		        This function shuts down a system.
		*/
		virtual void shutdown();

		/*!
		\fn     void setParent(ISystem* parent)
		\param  parent
		          system to set as parent
		\return Nothing
		\brief
		        This function retrieves the system's parent system.
		*/
		void setParent(ISystem* parent);

		/*!
		\fn     ISystem* getParent() const
		\par    This function has no parameters.
		\return Parent `ISystem` of the current system
		\brief
		        This function accesses the system's parent system.
		*/
		ISystem* getParent() const;

		/*!
		\fn     Type getType()
		\par    This function has no parameters.
		\return Type of the system
		\brief
		        This function gets the type of the system.
		*/
		Type getType() const;

		/*!
		\fn     bool isActive() const
		\par    This function has no parameters.
		\return If the system is active
		\brief
		        This function checks if a system has been initialized and not yet shut down.
		*/
		bool isActive() const;

		/*!
		\fn     friend bool operator>(ISystem &sys1, ISystem &sys2)
		\param  sys1
		          lefthand operand of the operator
		\param  sys2
		          righthand operand of the operator
		\return If `sys1` is greater than `sys2`
		\brief
		        This function compares two systems according to their types.
		*/
		friend bool operator<(ISystem &sys1, ISystem &sys2);

	private:

		/*!
		\var    cParent
		          parent of the system
		*/
		ISystem* cParent;

		/*!
		\var    type
		          type of system
		*/
		Type type;

		/*!
		\var    active
		          if the system has been initialized and is currently active
		*/
		bool active;

};