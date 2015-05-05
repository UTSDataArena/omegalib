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
 *	A class to hold and parse color values
 ******************************************************************************/
#include "omega/Color.h"

using namespace omega;

const Color Color::White = Color(1.0f, 1.0f, 1.0f);
const Color Color::Black = Color(0.0f, 0.0f, 0.0f);
const Color Color::Orange = Color(1.0f, 0.65f, 0.0f);
const Color Color::Silver = Color(0.75f, 0.75f, 0.75f);
const Color Color::Gray = Color(0.5f, 0.5f, 0.5f);
const Color Color::Red = Color(1.0f, 0.0f, 0.0f);
const Color Color::Maroon = Color(0.5f, 0.0f, 0.0f);
const Color Color::Yellow = Color(1.0f, 1.0f, 0.0f);
const Color Color::Olive = Color(0.5f, 0.5f, 0.0f);
const Color Color::Lime = Color(0.2f, 1.0f, 0.0f);
const Color Color::Green = Color(0.0f, 1.0f, 0.0f);
const Color Color::Aqua = Color(0.0f, 1.0f, 1.0f);
const Color Color::Teal = Color(0.0f, 0.5f, 0.5f);
const Color Color::Blue = Color(0.0f, 0.0f, 1.0f);
const Color Color::Navy = Color(0.0f, 0.0f, 0.5f);
const Color Color::Fuchsia = Color(1.0f, 0.0f, 1.0f);
const Color Color::Purple = Color(0.5f, 0.0f, 0.5f);

////////////////////////////////////////////////////////////////////////////////
const Color& Color::getColorByIndex(int index)
{
    switch(index)
    {
    case 0:	return Red;
    case 1:	return Lime;
    case 2: return Teal;
    case 3: return Purple;
    case 4:	return Orange;
    case 5: return Navy;
    case 6:	return Olive;
    case 7:	return Yellow;
    case 8:	return Green;
    case 9:	return Maroon;
    case 10: return Aqua;
    case 11: return Blue;
    case 12: return Fuchsia;
    case 13: return White;
    case 14: return Silver;
    case 15: return Gray;
    case 16: return Black;
    }
    return Black;
}

////////////////////////////////////////////////////////////////////////////////
String Color::toString() const
{
    return ostr("#%02x%02x%02x%02x", 
        %(int)(myData[0]*255)
        %(int)(myData[1]*255)
        %(int)(myData[2]*255)
        %(int)(myData[3]*255));
}

