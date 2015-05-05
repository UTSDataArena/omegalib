/******************************************************************************
 * THE OMEGA LIB PROJECT
 *-----------------------------------------------------------------------------
 * Copyright 2010-2015		Electronic Visualization Laboratory, 
 *							University of Illinois at Chicago
 * Authors:										
 *  Alessandro Febretti		febret@gmail.com
 *-----------------------------------------------------------------------------
 * Copyright (c) 2010-2015, Electronic Visualization Laboratory,  
 * University of Illinois at Chicago
 * All rights reserved.
 * Redistribution and use in source and binary forms, with or without 
 * modification, are permitted provided that the following conditions are met:
 * 
 * Redistributions of source code must retain the above copyright notice, this 
 * list of conditions and the following disclaimer. Redistributions in binary 
 * form must reproduce the above copyright notice, this list of conditions and 
 * the following disclaimer in the documentation and/or other materials 
 * provided with the distribution. 
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO THE 
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE 
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
 * CONSEQUENTIAL  DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
 * SUBSTITUTE  GOODS OR  SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
 * INTERRUPTION) HOWEVER  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
 * CONTRACT, STRICT LIABILITY,  OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
 * ARISING IN ANY WAY OUT OF THE USE  OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
 * POSSIBILITY OF SUCH DAMAGE.
 *-----------------------------------------------------------------------------
 * What's in this file
 *	The Actor class - a specialied EngineModule used to control objects 
 *	in a scene and define custom behaviors.
 *****************************************************************************/
#ifndef __ACTOR_H__
#define __ACTOR_H__

#include "osystem.h"
#include "omega/Application.h"
#include "omega/ModuleServices.h"

namespace omega {
	class SceneNode;

	///////////////////////////////////////////////////////////////////////////
	//! A specialied EngineModule used to control objects in a scene and 
	//! define custom behaviors.
	class OMEGA_API Actor: public EngineModule
	{
	public:
		Actor(const String& name): EngineModule(name), myNode(NULL), 
			myUpdateEnabled(false), myEventsEnabled(false), 
			myCommandsEnabled(false)  
		{}
		Actor(): EngineModule(), myNode(NULL),
			myUpdateEnabled(false), myEventsEnabled(false), 
			myCommandsEnabled(false)  
		{}

		void kill()
		{
			ModuleServices::removeModule(this);
		}

		void setSceneNode(SceneNode* node);
		SceneNode* getSceneNode();

		//! Callbacks
		//! These callbacks can be enabled / disabled using the corresponding
		//! callback filter functions.
		//@{
		virtual void onUpdate(const UpdateContext& context) {}
		virtual void onEvent(const Event& evt) {}
		virtual bool onCommand(const String& cmd) { return false; }
		//@}

		//! Callback filter functions
		//@{
		void setUpdateEnabled(bool value) { myUpdateEnabled = value; }
		void setCommandsEnabled(bool value) { myCommandsEnabled = value; }
		void setEventsEnabled(bool value) { myEventsEnabled = value; }
		bool isUpdateEnabled() { return myUpdateEnabled; }
		bool areCommandsEnabled() { return myCommandsEnabled; }
		bool areEventsEnabled() { return myEventsEnabled; }
		//@}

		virtual void update(const UpdateContext& context) 
		{
			if(myUpdateEnabled) onUpdate(context);
		}

		virtual void handleEvent(const Event& evt) 
		{
			if(myEventsEnabled) onEvent(evt);
		}

		virtual bool handleCommand(const String& cmd) 
		{ 
			if(myCommandsEnabled) return onCommand(cmd);
			return false; 
		}

	protected:
		SceneNode* myNode;
		bool myUpdateEnabled;
		bool myEventsEnabled;
		bool myCommandsEnabled;
	};

	///////////////////////////////////////////////////////////////////////////
	inline void Actor::setSceneNode(SceneNode* node)
	{ myNode = node; }

	///////////////////////////////////////////////////////////////////////////
	inline SceneNode* Actor::getSceneNode()
	{ return myNode; }
}; // namespace omega

#endif