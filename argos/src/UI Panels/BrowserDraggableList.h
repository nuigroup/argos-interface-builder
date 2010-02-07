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

#include "ofxArgosUI.h"
#include "ofxArgosUI_Icon.h"
#include "BrowserDraggable.h"
#include "utils.h"

// ============================================================================ Button
class Draggable_Button : public ofxArgosUI_Icon {
	
public:

	ofxArgosUI	*gui; 

	Draggable_Button(ofxArgosUI &gui, int x, int y, int width, int height) : ofxArgosUI_Icon(x, y, width, height) {
		this->gui  = &gui; 
		icon.loadImage("icons/button.png");
		defaultCWidth = 120; 
		defaultCHeight = 40; 
	}

	void dropControl(int x, int y) {
		gui->addButton("New Button", x, y, defaultCWidth, defaultCHeight, &b[bi++]);
	}
};

// ============================================================================ Toggle
class Draggable_Toggle : public ofxArgosUI_Icon {
	
public:

	ofxArgosUI	*gui; 

	Draggable_Toggle(ofxArgosUI &gui, int x, int y, int width, int height) : ofxArgosUI_Icon(x, y, width, height) {
		this->gui  = &gui; 
		icon.loadImage("icons/toggle.png");
		defaultCWidth = 120; 
		defaultCHeight = 20; 
	}
	
	void dropControl(int x, int y) {
		gui->addToggle("New Toggle", x, y, defaultCWidth, defaultCHeight, &b[bi++]);
	}
};

// ============================================================================ Slider
class Draggable_Slider : public ofxArgosUI_Icon {
	
public:

	ofxArgosUI	*gui; 

	Draggable_Slider(ofxArgosUI &gui, int x, int y, int width, int height) : ofxArgosUI_Icon(x, y, width, height) {
		this->gui  = &gui; 
		icon.loadImage("icons/slider.png");
		defaultCWidth = 240; 
		defaultCHeight = 40; 
	}
	
	void dropControl(int x, int y) {
		gui->addSlider("New Slider", x, y, defaultCWidth, defaultCHeight, &f[fi++], 0, 100, 0.85); 
	}
};

// ============================================================================ Knob
class Draggable_Knob : public ofxArgosUI_Icon {
	
public:

	ofxArgosUI	*gui; 

	Draggable_Knob(ofxArgosUI &gui, int x, int y, int width, int height) : ofxArgosUI_Icon(x, y, width, height) {
		this->gui  = &gui; 
		icon.loadImage("icons/knob.png");
		defaultCWidth = 80; 
		defaultCHeight = 80;
	}
	
	void dropControl(int x, int y) {
		gui->addKnob("New Knob", x, y, (defaultCWidth / 2.5), &f[fi++], 0, 1, .85);
	}
};

// ============================================================================ Label
class Draggable_Label : public ofxArgosUI_Icon {
	
public:

	ofxArgosUI	*gui; 

	Draggable_Label(ofxArgosUI &gui, int x, int y, int width, int height) : ofxArgosUI_Icon(x, y, width, height) {
		this->gui  = &gui; 
		icon.loadImage("icons/label.png");
		defaultCWidth = 80; 
		defaultCHeight = 20; 
	}
	
	void dropControl(int x, int y) {

		gui->addButton("3", x, y, 40, 40, &b[bi++]);
		gui->addButton("4", x + 50, y, 40, 40, &b[bi++]);
		gui->addButton("1", x, y - 50, 40, 40, &b[bi++]);
		gui->addButton("2", x + 50, y - 50, 40, 40, &b[bi++]);
		
	}
};

// ============================================================================ Panel
class Draggable_Panel : public ofxArgosUI_Icon {
	
public:

	ofxArgosUI	*gui; 

	Draggable_Panel(ofxArgosUI &gui, int x, int y, int width, int height) : ofxArgosUI_Icon(x, y, width, height) {
		this->gui  = &gui; 
		icon.loadImage("icons/panel.png");
		defaultCWidth = 200; 
		defaultCHeight = 400;
	}
	
	void dropControl(int x, int y) {
	}
};


// ============================================================================ XYPad
class Draggable_XYPad : public ofxArgosUI_Icon {
	
public:

	ofxArgosUI	*gui; 

	Draggable_XYPad(ofxArgosUI &gui, int x, int y, int width, int height) : ofxArgosUI_Icon(x, y, width, height) {
		this->gui  = &gui; 
		icon.loadImage("icons/xypad.png");
		defaultCWidth = 120; 
		defaultCHeight = 120;
	}
	
	void dropControl(int x, int y) {
		gui->addXYPad("New XYPad", x, y, defaultCWidth, defaultCHeight, &v[vi++], 0, 20, 0, 20); 
	}
};
