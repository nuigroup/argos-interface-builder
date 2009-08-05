/***********************************************************************
 
 Copyright (c) 2009 Dimitri Diakopoulos, http://www.dimitridiakopoulos.com/
 === Google Summer of Code 2009 - NUI Group === 

 Portions Copyright (c) 2008, 2009 Memo Atkens, http://www.memo.tv/
 -> Based on ofxSimpleGuiToo
 
 Portions Copyright (c) 2008 Todd Vanderlin, http://toddvanderlin.com/
 -> Inspired by ofxSimpleGui API

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
#pragma once

#include "ofxArgosUI_Includes.h"

class ofxArgosUI_View : public ofxArgosUI_Control {

public:

	ofxArgosUI_View(string name);

	~ofxArgosUI_View();
	
	void					draw(float x = 0, float y = 0);
	
	void					loadFromXML(ofxXmlSettings &XML);
	void					saveToXML(ofxXmlSettings &XML);
	
	ofxArgosUI_Control		*addControl(ofxArgosUI_Control *control);

	ofxArgosUI_Panel		*addPanel(string name, int x, int y, int width, int height); 

	ofxArgosUI_Button		*addButton(string name, int x, int y, int width, int height, bool *value);
	ofxArgosUI_Toggle		*addToggle(string name, int x, int y, int width, int height, bool *value);
	ofxArgosUI_Knob			*addKnob(string name, int x, int y, int radius, float *value, float min, float max, float smoothing);
	ofxArgosUI_SliderInt	*addSlider(string name, int x, int y, int width, int height, int *value, int min, int max);
	ofxArgosUI_SliderFloat	*addSlider(string name, int x, int y, int width, int height, float *value, float min, float max, float smoothing = 0);
	ofxArgosUI_XYPad		*addXYPad(string name, ofPoint* value, float xmin, float xmax, float ymin, float ymax);
	ofxArgosUI_FPSCounter	*addFPSCounter(int x, int y, int width, int height);
	ofxArgosUI_Title		*addTitle(string name, bool *value = NULL);
	ofxArgosUI_Content		*addContent(string name, ofBaseDraws *content, float fixwidth = -1);
	
	//void setup(ofEventArgs &e);
	void update(ofEventArgs &e);
	//void draw(ofEventArgs &e);
	//void exit(ofEventArgs &e);
	
	void mouseMoved(ofMouseEventArgs &e);
	void mousePressed(ofMouseEventArgs &e);	
	void mouseDragged(ofMouseEventArgs &e);	
	void mouseReleased(ofMouseEventArgs &e);
	
	void keyPressed(ofKeyEventArgs &e);
	void keyReleased(ofKeyEventArgs &e);	
	
protected:
	vector <ofxArgosUI_Control*> controls;
	vector <ofxArgosUI_Control*> panels; 

};