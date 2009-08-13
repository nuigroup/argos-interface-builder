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

	bool hidden;
	int oWidth; 
	int oHeight;

	float counter;
	float spin;
	float spinPct;
		
	ofxArgosUI_Panel(string name, int x, int y, int width, int height) : ofxArgosUI_Control(name) {

		disableAllEvents();

		hidden = false; 
		oHeight = height; 
		controlType = "Panel";
		setup(x, y, width, height);

		counter = 0.0;
		spin	= 0.0;
		spinPct	= 0.0;

	}
	
	void setup(int _x, int _y, int _width, int _height) {
		setPos(_x, _y); 
		setSize(_width, _height);
	}
	
	void loadFromXML(ofxXmlSettings &XML){

	}

	void saveToXML(ofxXmlSettings &XML){

	}

	void toggleDraw(bool x){
		enabled = !enabled; 
	}

	void showPanel(){

		printf("ofxArgosUI_Panel::showPanel\n");
		
		for(int i = height; i <= oHeight; i++) {
			setSize(width, i); 
		}


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

		// Set new height

		// Stop drawing the controls
		hidden = true; 

		// Disable the controls
		for(int i = 0; i < panel_children.size(); i++) {
			panel_children[i]->enabled = false; 
		}	

	}

	ofxArgosUI_Control *addControl(ofxArgosUI_Control *control) {
		panel_children.push_back(control);
		return control;
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

	ofxArgosUI_Title *addTitle(string name, bool *value) {
		return (ofxArgosUI_Title *)addControl(new ofxArgosUI_Title(name, value));
	}

	ofxArgosUI_Toggle *addToggle(string name, int x, int y, int width, int height, bool *value) {
		return (ofxArgosUI_Toggle *)addControl(new ofxArgosUI_Toggle(name, x, y, width, height, value));
	}

	ofxArgosUI_Knob	*addKnob(string name, int x, int y, int radius, float *value, float min, float max, float smoothing){
		return (ofxArgosUI_Knob *)addControl(new ofxArgosUI_Knob(name, x, y, radius, value, min, max, smoothing));
	}

	void rRectangle(int x, int y, int w, int h, int radius){
        glDisable(GL_TEXTURE_2D);

        glLineWidth(1.0f);
        
        glBegin(GL_POLYGON );
        
        glVertex2f (x + radius, y);
        glVertex2f (x + w - radius, y);
			for(float t  = PI * 1.5f; t < PI * 2; t += 0.1f){
				float sx = x + w - radius + cos(t) * radius;
				float sy = y + radius + sin(t) * radius;
				glVertex2f (sx, sy);
			}

        glVertex2f (x + w, y + radius);
        glVertex2f (x + w, y + h - radius);
			for(float t  = 0; t < PI * 0.5f; t += 0.1f){
				float sx = x + w - radius + cos(t) * radius;
				float sy = y + h - radius + sin(t) * radius;
				glVertex2f (sx, sy);
			}
	        
        glVertex2f (x + w -radius, y + h);
        glVertex2f (x + radius, y + h);
			for(float t  = PI * 0.5f; t < PI; t += 0.1f){
				float sx = x + radius + cos(t) * radius;
				float sy = y + h - radius + sin(t) * radius;
				glVertex2f (sx, sy);
			}
        
        glVertex2f (x, y + h - radius);
        glVertex2f (x, y + radius);
			for(float t  = PI; t < PI * 1.5f; t += 0.1f){
				float sx = x + radius + cos(t) * radius;
				float sy = y + radius + sin(t) * radius;
				glVertex2f (sx, sy);
			}
        
        glEnd();

        glEnable(GL_TEXTURE_2D);    
    }

	void update() {
		if(!enabled) return;
		enabled = false;
	}

	void draw(float x, float y) {

		enabled = true; 

		setPos(x, y);

		ofFill();
		ofSetColor(0x363636);
		rRectangle(x, y, width, height, 13);

		//ofNoFill();
		//glLineWidth(1.0f);

		//rRectangle(x, y, width, height, 13);
		ofEnableAlphaBlending();

		ofSetColor(0xdcfa70); 
		glPushMatrix();
			glTranslatef(x, y, 0);
			myFont.drawString(name, 8, -6);
		glPopMatrix();

		ofDisableAlphaBlending();

		for(int i = 0; i < panel_children.size(); i++) {

			panel_children[i]->draw(panel_children[i]->x, panel_children[i]->y);

		}
	}
	
	
protected:
	vector <ofxArgosUI_Control*> panel_children; 

}; 