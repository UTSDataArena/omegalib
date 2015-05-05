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
 *	Implements an Actor that sets the position and orientation of a scene node
 *  based on a events generated from a tracking system
 ******************************************************************************/
#include "omega/TrackedObject.h"

using namespace omega;

NameGenerator sTrackedObjectName("TrackedObject");

///////////////////////////////////////////////////////////////////////////////
TrackedObject::TrackedObject():
        Actor(sTrackedObjectName.generate()),
        myTrackableServiceType(Event::ServiceTypeMocap),
        myTrackableSourceId(-1),
        myOrientationTrackingEnabled(true),
        myPositionTrackingEnabled(true),
        myOffset(0, 0, 0),
        myOrientationOffset(Quaternion::Identity()),
        myTrackedPosition(0, 0, 0),
        myTrackedOrientation(Quaternion::Identity()),
        // Hide objects after one hour. Large enough to basically disable auto-hide.
        myHideTimeout(3600),
        myEventReceivedSinceLastUpdate(false),
        myLastEventTime(0),
        myAutoHideEnabled(false)
{
}

///////////////////////////////////////////////////////////////////////////////
TrackedObject::~TrackedObject()
{
}

///////////////////////////////////////////////////////////////////////////////
void TrackedObject::handleEvent(const Event& evt)
{
    if(evt.getServiceType() == static_cast<enum Service::ServiceType>(myTrackableServiceType) && 
        evt.getSourceId() == myTrackableSourceId)
    {
        myTrackedPosition = evt.getPosition();
        myTrackedOrientation = evt.getOrientation();
        myEventReceivedSinceLastUpdate = true;
    }
}

///////////////////////////////////////////////////////////////////////////////
void TrackedObject::update(const UpdateContext& context)
{
    if(myNode != NULL)
    {
        if(myEventReceivedSinceLastUpdate)
        {
            // If auto-hide mode is enabled and the mode is hidden,
            // make it visible.
            if(myAutoHideEnabled && myNode->isVisible())
            {
                myNode->setVisible(true);
            }

            if(myPositionTrackingEnabled)
            {
                Vector3f pos = myTrackedPosition + myOffset;
                myNode->setPosition(pos);
            }
            if(myOrientationTrackingEnabled)
            {
                Quaternion orientation = myTrackedOrientation;
                myNode->setOrientation(myTrackedOrientation * myOrientationOffset);
            }
            myEventReceivedSinceLastUpdate = false;
            myLastEventTime = context.time;
        }
        else
        {
            // If auto-hide mode is enabled and the no tracking timeout is
            // expired, hide the object.
            if(context.time - myLastEventTime > myHideTimeout)
            {
                myNode->setVisible(false);
            }
        }
    }
}
