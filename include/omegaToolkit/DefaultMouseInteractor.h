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
* Redistribution and use in source and binary forms, with or without modification,
* are permitted provided that the following conditions are met:
*
* Redistributions of source code must retain the above copyright notice, this
* list of conditions and the following disclaimer. Redistributions in binary
* form must reproduce the above copyright notice, this list of conditions and
* the following disclaimer in the documentation and/or other materials provided
* with the distribution.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
* ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
* LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
* DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE  GOODS OR
* SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
* CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
* OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*-----------------------------------------------------------------------------
* What's in this file
* An actor to move/rotate scene nodes using a mouse.
******************************************************************************/
#ifndef __DEFAULT_MOUSE_INTERACTOR_H__
#define __DEFAULT_MOUSE_INTERACTOR_H__

#include "omegaToolkitConfig.h"
#include "omega/Actor.h"

namespace omegaToolkit {
	///////////////////////////////////////////////////////////////////////////
	class OTK_API DefaultMouseInteractor: public Actor
	{
	public:
		DefaultMouseInteractor():
		    Actor("DefaultMouseInteractor"),
			myMoveButtonFlag(Event::Left),
			myRotateButtonFlag(Event::Right)
			{
				// Setting the interactor priority to low: we can set the target object in the 
				// application event handler and start manipulating the objec tright away, without
				// requiring a new click.
				setPriority(PriorityLow);
				myNodeActive = false;
			}

		virtual void handleEvent(const Event& evt);

		Event::Flags getMoveButtonFlag() { return myMoveButtonFlag; }
		void setMoveButtonFlag(Event::Flags value) { myMoveButtonFlag = value; }

		Event::Flags getRotateButtonFlag() { return myRotateButtonFlag; }
		void setRotateButtonFlag(Event::Flags value) { myRotateButtonFlag = value; }

	private:
		void updateNode();

	private:
		Event::Flags myMoveButtonFlag;
		Event::Flags myRotateButtonFlag;

		Vector3f myHandlePosition;
		float myHandleDistance;
		Sphere myStartBSphere;
		Quaternion myStartOrientation;
		float myStartScale;

		// pointer event data.
		bool myPointerEventReceived;
		Vector2f myPointerPosition;
		Ray myPointerRay;
		Event::Type myPointerEventType;
		int myPointerEventData;
		bool myPointerButton1Pressed;
		bool myPointerButton2Pressed;
		bool myNodeActive;
	};
}; // namespace omegaToolkit

#endif