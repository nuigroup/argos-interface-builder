/***********************************************************************
 
 Copyright (c) 2009, 2010 Dimitri Diakopoulos, http://argos.dimitridiakopoulos.com/

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
	
	ofSetWindowTitle("Argos Interface Builder " + version); 

	WindowWidth = ofGetWidth();
	WindowHeight = ofGetHeight();
	ofSetVerticalSync(false);
	ofSetFrameRate(30);

	ofSetBackgroundAuto(true); 

	ofBackground(40, 40, 40);
	
	tuio.start(3333);
	oschandler.start(3335);

	gui.addFPSCounter((WindowWidth - 100), (WindowHeight - 20), 100, 20);

}

// ========================================================== Update 
void Argos::update(){
	tuio.getMessage();
	editor.update();
}

// ========================================================== Draw
void Argos::draw(){

	tuio.drawCursors();

	gui.draw();

	ofSetColor(0xffffff); 
}

// ========================================================== Resized
void Argos::resized(int w, int h){

}

// ========================================================== Key Pressed
void Argos::keyPressed (int key){ 

	// Eventually forward these directly to editor... 
	if (key == OF_KEY_DEL) editor.deleteControl(); 

	if (key == OF_KEY_LEFT) editor.moveXY_Arrows("x", "left"); 
	if (key == OF_KEY_RIGHT) editor.moveXY_Arrows("x", "right"); 
	if (key == OF_KEY_UP) editor.moveXY_Arrows("y", "up"); 
	if (key == OF_KEY_DOWN) editor.moveXY_Arrows("y", "down"); 

	if (key == 257) layout.saveToXML("Preset1.xml");
	if (key == 258) layout.saveToXML("Preset2.xml");
	if (key == 259) layout.saveToXML("Preset3.xml");
	if (key == 260) layout.saveToXML("Preset4.xml");

	if (key == 261) layout.loadFromXML("Preset1.xml");
	if (key == 262) layout.loadFromXML("Preset2.xml");
	if (key == 263) layout.loadFromXML("Preset3.xml");
	if (key == 264) layout.loadFromXML("Preset4.xml");

	//if (key == '-') gui.toggleDraw();
	//if (key == '=') browser.browser->toggleDraw();

	if (key == 's') gui.saveToXML(gui.xmlFile); 
	if (key == 'l') gui.loadFromXML(gui.xmlFile); 
    //if(key == '-') editor.editor->toggleDraw();

}