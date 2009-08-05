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

class ofxArgosUI_Panel : public ofxArgosUI_Control {

public:
		

	ofxArgosUI_Panel(string name, int x, int y, int width, int height) : ofxArgosUI_Control(name) {

		enabled = true; 
		controlType = "Panel";
		setup(x, y, width, height);

	}
	
	void setup(int _x, int _y, int _width, int _height) {
		setPos(_x, _y); 
		setSize(_width, _height);
	}
	
	void loadFromXML(ofxXmlSettings &XML){

	}

	void saveToXML(ofxXmlSettings &XML){

	}

	void setEnabled(bool x){
		enabled = x; 
	}

	ofxArgosUI_Control *addControl(ofxArgosUI_Control *control) {
		panel_children.push_back(control);
		return control;
	}

	ofxArgosUI_Button *addButton(string name, int x, int y, int width, int height, bool *value) {
		return (ofxArgosUI_Button *)addControl(new ofxArgosUI_Button(name, x, y, width, height, value));
	}

	ofxArgosUI_Content *addContent(string name, ofBaseDraws *content, float fixwidth) {
		return (ofxArgosUI_Content *)addControl(new ofxArgosUI_Content(name, content, fixwidth));
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

	ofxArgosUI_XYPad *addXYPad(string name, ofPoint* value, float xmin, float xmax, float ymin, float ymax) {
		return (ofxArgosUI_XYPad *)addControl(new ofxArgosUI_XYPad(name, value, xmin, xmax, ymin, ymax));
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

	void draw(float x, float y) {

		if (enabled){

			setPos(x, y);

			ofNoFill();
			ofSetColor(config->borderColor);
			glLineWidth(1.0f);
			ofRect(x, y, width, height);
			
			glPushMatrix();
				glTranslatef(x, y, 0);
				myFont.drawString(name, -4, -5);
			glPopMatrix();

			for(int i = 0; i < panel_children.size(); i++) {

				panel_children[i]->draw(panel_children[i]->x, panel_children[i]->y);

			}	
		}
	}
	
	
protected:
	vector <ofxArgosUI_Control*> panel_children; 

}; 