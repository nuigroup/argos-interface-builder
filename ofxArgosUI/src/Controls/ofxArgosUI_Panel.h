/***********************************************************************
 
 Copyright (c) 2009, 2010 Dimitri Diakopoulos, http://www.dimitridiakopoulos.com/

 Portions Copyright (c) 2008, 2009 Memo Aktens, http://www.memo.tv/
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

class ofxArgosUI_Panel : public ofxArgosUI_Control {

public:

	bool hidden;
	bool isprotected;

	int oWidth; 
	int oHeight;

	int cornerRadius;
		
	ofxArgosUI_Panel(string name, int x, int y, int width, int height) : ofxArgosUI_Control(name) {

		disableAllEvents();
		disableAllInput();	// Adds the FocusActive listener we can hack to clear the editor

		oHeight = height; 
		controlType = "Panel";
		setup(x, y, width, height);

		cornerRadius = 12; 

		isprotected = false;
		hidden = false; 

	}
	
	void setup(int _x, int _y, int _width, int _height) {
		setPos(_x, _y); 
		setSize(_width, _height);
	}
	
	void loadFromXML(ofxXmlSettings &XML){}

	void saveToXML(ofxXmlSettings &XML){}

	void toggleDraw(){
		enabled = !enabled; 
	}

	void focusActive(){}

	void showPanel(){

		printf("ofxArgosUI_Panel::showPanel\n");

		// Show the controls
		hidden = false; 

		// Enable the controls
		for(int i = 0; i < panel_children.size(); i++) {
			panel_children[i]->enabled = true; 
		}	

	}

	void hidePanel(){

		printf("ofxArgosUI_Panel::hidePanel\n");

		// Save height
		oHeight = height;

		// Hide the controls
		hidden = true; 

		// Disable the controls
		for(int i = 0; i < panel_children.size(); i++) {
			panel_children[i]->enabled = false; 
		}	

	}

	void lockPanel(){
		this->canfocus = false; 
	}
	
	void resetPanel(string nN, int nW, int nH){
		setName(nN);
		setSize(nW,nH); 

		for(int i = 0; i < panel_children.size(); i++) {
			panel_children[i]->killMe();  
		}	

		panel_children.clear(); 
	}

	int numControls(){
		return panel_children.size(); 
	}

	ofxArgosUI_Control *addControl(ofxArgosUI_Control *control) {
		// Rather than glTranslate the controls every draw, 
		// this adds them them relative to the panel's (0,0); 
		control->setPos(x + control->x, y + control->y); 

		panel_children.push_back(control);
		return control;
	}

	void setCornerRadius(int radius){
		cornerRadius = radius; 
	}

	ofxArgosUI_Button *addButton(string name, int x, int y, int width, int height, bool *value) {
		return (ofxArgosUI_Button *)addControl(new ofxArgosUI_Button(name, x, y, width, height, value));
	}

	ofxArgosUI_FPSCounter *addFPSCounter(int x, int y, int width, int height) {
		return (ofxArgosUI_FPSCounter *)addControl(new ofxArgosUI_FPSCounter(x, y, width, height));
	}

	ofxArgosUI_SliderInt *addSlider(string name, int x, int y, int width, int height, int *value, int min, int max) {
		return (ofxArgosUI_SliderInt *)addControl(new ofxArgosUI_SliderInt(name, x, y, width, height, value, min, max, 0));
	}

	ofxArgosUI_SliderFloat *addSlider(string name, int x, int y, int width, int height, float *value, float min, float max, float smoothing) {
		return (ofxArgosUI_SliderFloat *)addControl(new ofxArgosUI_SliderFloat(name, x, y, width, height, value, min, max, smoothing));
	}

	ofxArgosUI_XYPad *addXYPad(string name, int x, int y, int width, int height, ofPoint* value, float xmin, float xmax, float ymin, float ymax) {
		return (ofxArgosUI_XYPad *)addControl(new ofxArgosUI_XYPad(name, x, y, width, height, value, xmin, xmax, ymin, ymax));
	}

	ofxArgosUI_TextField *addTextField(string name, int x, int y, int width, int height, string *value){
		return (ofxArgosUI_TextField *)addControl(new ofxArgosUI_TextField(name, x, y, width, height, value)); 
	}

	ofxArgosUI_Title *addTitle(string name, bool *value) {
		return (ofxArgosUI_Title *)addControl(new ofxArgosUI_Title(name, value));
	}

	ofxArgosUI_Toggle *addToggle(string name, int x, int y, int width, int height, bool *value) {
		return (ofxArgosUI_Toggle *)addControl(new ofxArgosUI_Toggle(name, x, y, width, height, value));
	}

	ofxArgosUI_Knob	*addKnob(string name, int x, int y, int radius, float *value, float min, float max, float smoothing){
		return (ofxArgosUI_Knob *)addControl(new ofxArgosUI_Knob(name, x, y, radius, value, min, max, smoothing));
	}

	ofxArgosUI_Icon *addIcon(int x, int y, int width, int height) {
		return (ofxArgosUI_Icon *)addControl(new ofxArgosUI_Icon(x, y, width, height));
	}

	void update() {
		if(!enabled) return;
		enabled = false;
	}

	void draw(float x, float y) {

		if(!enabled) return; 

		setPos(x, y);

		ofEnableAlphaBlending();

		ofSetColor(0x363636);

		rRectangle(x, y, width, height, cornerRadius);

		ofSetColor(0xf0f0f0);
		argosText::font.drawString(name, x + 5, y - 3);


		for(int i = 0; i < panel_children.size(); i++) {
			panel_children[i]->draw(panel_children[i]->x, panel_children[i]->y);
		}

		ofDisableAlphaBlending();

	}
	
protected:
	vector <ofxArgosUI_Control*> panel_children; 

};