/***********************************************************************
 
 Copyright (c) 2009 Dimitri Diakopoulos, http://argos.dimitridiakopoulos.com/
 === Google Summer of Code 2009 - NUI Group === 

 - Requires ofxTouchAPI
	- ofxTUIO/ofxOSC
 - Requires ofxArgosUI
	- ofxXMLSettings

	Redistribution and use in source and binary forms, with or without modification, 
	are permitted provided that the following conditions are met:

	1. Redistributions of source code must retain the above copyright notice, 
	this list of conditions and the following disclaiwelmer.

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

#include "Argos.h"
#include "utils.h"

bool  b[300];
float f[300];
int	  iindex;

int fi;
int bi; 
int vi;

ofPoint *points;
ofPoint	v[300];

int WindowWidth;
int WindowHeight;


// ========================================================== Setup
void Argos::setup(){	
	
	WindowWidth = ofGetWidth();
	WindowHeight = ofGetHeight();
	ofSetVerticalSync(false);
	ofSetFrameRate(60);
	ofBackground(0, 0, 0);
	
	// Open TUIO on Port 3333
	tuio.start(3333);

	argos_tag.loadImage("Argos.png");

	editor  = new Argos_editor(gui); 
	browser = new Argos_browser(gui); 
	
	// addFPSCounter(X, Y, Width, Height)
	gui.addFPSCounter((WindowWidth - 100), (WindowHeight - 20), 100, 20); 

	/*
	// addButton(Name, X, Y, Width, Height, Value)
	gui.addButton("Button 1", 400, 120, 200, 20, &b[bi++]);
	gui.addButton("Button 2", 400, 150, 200, 20, &b[bi++]);
	gui.addButton("Button 3", 400, 180, 200, 20, &b[bi++]);

	// addToggle(Name, X, Y, Width, Height, Value)
	gui.addToggle("Toggle 1", 400, 210, 100, 20, &b[bi++]);
	gui.addToggle("Toggle 2", 500, 210, 100, 20, &b[bi++]);

	// addSlider(Name, X, Y, Width, Height, Value, Min, Max, Smoothing)
	gui.addSlider("Slider 1", 400, 240, 200, 30, &f[fi++], 0, 100, 0.85); 

	// addSlider(Name, X, Y, Width, Height, Value, Min, Max, Smoothing)
	gui.addSlider("Slider 2", 400, 280, 200, 30, &f[fi++], 0, 100, 0.85); 

	// addKnob(Name, X, Y, Width, Radius, Value, Min, Max, Smoothing)
	gui.addKnob("Knob 1", 420, 35, 30, &f[fi++], 0, 100, .85);
	gui.addKnob("Knob 2", 490, 35, 30, &f[fi++], 0, 100, .85); 
	
	// addXYPad(Name, X, Y, Width, Height, Value, XMin, XMax, YMin, YMax); 
	gui.addXYPad("XYPad 1", 620, 120, 120, 120, &v[vi++], 0, 20, 0, 20); 
	*/ 
}

// ========================================================== Update 
void Argos::update(){

	tuio.getMessage();
	
	//cout << f[1] << "\n"; 
}

// ========================================================== Draw
void Argos::draw(){

	// Good for testing
	tuio.drawCursors();

	gui.draw();

	ofSetColor(0xffffff); 
	argos_tag.draw(900,700); 

}

// ========================================================== Resized
void Argos::resized(int w, int h){

}

// ========================================================== Key Pressed
void Argos::keyPressed (int key){ 

	//if(key == '-') gui.toggleDraw();

	if(key == '-') editor->editor->move();
	//if(key == '=') editor->editor->hidePanel();

}