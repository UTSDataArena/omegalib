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
*	A module that switches a camera stereo mode on or off based on it's tracker
*   position and orientation. Useful to disable stereo rendering when a user is
*   taking off their glasses.
*****************************************************************************/
#ifndef __CAMERA_STEREO_SWITCHER__
#define __CAMERA_STEREO_SWITCHER__

#include "omegaToolkitConfig.h"
#include "omega/Camera.h"
#include "omega/ModuleServices.h"

namespace omegaToolkit {
    ///////////////////////////////////////////////////////////////////////////
    //! A module that switches an application stereo mode on or off based on it's tracker
    //! position and orientation.Useful to disable stereo rendering when a user is
    //! taking off their glasses.
    class OTK_API CameraStereoSwitcher: public EngineModule
    {
    public:
        static CameraStereoSwitcher* create(const String& name);
        virtual void setup(Setting& s);
        virtual void initialize();
        virtual void handleEvent(const Event& evt);

    private:
        bool myEnabled;
        Ref<Camera> myTargetCamera;
        float myYThreshold;
        Vector3f myDisabledOrientation;
        float myOrientationThreshold;
        Vector3f myNeutralHeadPos;
    };
};

#endif