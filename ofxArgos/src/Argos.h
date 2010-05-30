/***********************************************************************
 
 Copyright (c) 2009, 2010 Dimitri Diakopoulos, http://argos.dimitridiakopoulos.com/

	Redistribution and use in source and binary forms, with or without modification, 
	are permitted provided that the following conditions are met:

	1. Redistributions of source code must retain the above copyright notice, 
	this list of conditions and the following disclaimer.

	2. Redistributions in binary form must reproduce the above copyright notice, 
	this list of conditions and the following disclaimer in the documentation and/or 
	other materials provided with the distribution.

	3. The name of the author may not be used to endorse or promote products derived 
	from this software without specific prior written permission.

	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND 
	ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
	IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
	ARE DISCLAIMED. IN NOEVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, 
	INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES 
	(INCLUDING, BUT NOT LIMITED TO,PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; 
	LOSS OF USE, DATA, ORPROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED 
	AND ON ANY THEORY OFLIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
	OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT 
	OF THE USE OF THIS SOFTWARE,EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.  

*************************************************************************/ 

#ifndef _ARGOS_
#define _ARGOS_

#include "ofMain.h"				// ofMain


#include "ofxArgosUI.h"			// Argos UI Toolkit
#include "EditorCore.h"			// Widget Editor
#include "BrowserCore.h"		// Widget Browser
#include "LayoutHandler.h"		// Layout
#include "ModeCore.h"			// Mode Changer
#include "StaticFont.h"			// Text @ Static Size
#include "OSCHandler.h"			// OSC Handler
#include "StateManager.h"		// Global Flags


class Argos : public ofSimpleApp{ 
	
public:

	ofxArgosUI		gui;
	EditorPanel		editor;  
	BrowserPanel	browser;
	ModePanel		mode;

	LayoutHandler	layout; 

	string			version; 


	Argos() {

		editor.init(gui); 
		browser.init(gui); 
		mode.init(gui); 
		layout.init(gui); 
	
		argosText::setFont("verdana.ttf", 10);
		version = "v0.21"; 

	}

	void setup();
	void update();
	void draw();

	void resized(int w, int h);
	
	void keyPressed(int key);

};

#endif
