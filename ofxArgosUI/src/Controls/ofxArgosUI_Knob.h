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

#include "ofxArgosUI_Control.h"

class ofxArgosUI_Knob : public ofxArgosUI_Control {
	
public:
	
	float	*value;

	int radius;

	float	min;
	float	max; 

	float	knobAngle;
	int		knobDisplay;

	float	pct; 

	float	lerpSpeed;
	float	targetValue;
	float	oldValue;
	
	ofxArgosUI_Knob(string name, int x, int y, int radius, float *value, float min, float max, float smoothing) : ofxArgosUI_Control(name) {

		this->value	= value;
		this->min = min; 
		this->max = max; 
		this->radius = radius; 

		lerpSpeed	= 1.0f - smoothing * 0.99;
		targetValue	= *value;
		oldValue	= targetValue;

		controlType = "Knob";
	
		setup(x, y, 2*radius, 2*radius);

	}
	
	void setup(int _x, int _y, int _width, int _height) {
		setPos(_x, _y); 
		setSize(_width, _height);

		pct = ofMap((*value), min, max, 0.0, width);
		knobAngle = pct;
	}
	
	void loadFromXML(ofxXmlSettings &XML) {
		set(XML.getValue("controls:" + controlType + "_" + key + ":value", 0));
	}
	
	void saveToXML(ofxXmlSettings &XML) {
		XML.addTag(controlType + "_" + key);
			XML.pushTag(controlType + "_" + key);
				XML.addValue("name", name);
				XML.addValue("value", getValue());
		XML.popTag();
	}
	
	
	bool getValue() {
		return (*value);
	}

	void set(bool b) {
		(*value) = b;
	}

	// Uses yMovement
	void updateKnob(int xMovement, int yMovement) {
		if(!enabled) return;
		
		if(pct > width) {
			pct = width;
		}
		else {

			// Inverse movement on y-axis -> mouse up = bigger value, mouse down = smaller value
			pct = (y-yMovement) + (2 * radius);

			float temp = ofMap(pct, 0.0, (float)width, min, max);


			//temp = ofClamp(temp, min, max);
			
			if(temp >= max)			temp = max;
			else if(temp <= min)	temp = min;
			
			targetValue = temp;	
			oldValue = *value;	
		}
	}

	// ============================================= Mouse
	void onPress(int x, int y, int button) {
		updateKnob(x,y);  
	}

	void onDragOver(int x, int y, int button){
		updateKnob(x, y); 
	}

	void onDragOutside(int x, int y, int button){
		updateKnob(x,y);
	}

	// ============================================= Touch
	void onTouchDown(float x, float y, int ID){
		updateKnob(x,y);
	}

	void onTouchMove(float x, float y, int ID){
		updateKnob(x,y);
	}

	void onTouchMoveOutside(float x, float y, int ID){
		updateKnob(x,y);
	}

	void drawArc(double xctr, double yctr, double radius, double startAngle, double endAngle){
		double vectorX1, vectorY1;
		double vectorX0, vectorY0;
		double angle, ang0, ang1;

		ang0 = startAngle * (3.14/180.0);
		ang1 = endAngle * (3.14/180.0);
		glBegin(GL_TRIANGLES);

		vectorX1 = xctr + radius*cos(ang0);
		vectorY1 = yctr + radius*sin(ang0);

		for(angle = ang0 + 3.14/180.0;	
			angle < ang1 + 3.14/180.0; angle += 3.14/180.0)
		{											
			vectorX0 = vectorX1;
			vectorY0 = vectorY1;
			vectorX1 = xctr + radius*cos(angle);
			vectorY1 = yctr + radius*sin(angle);
			glVertex2d(xctr, yctr);
			glVertex2d(vectorX0, vectorY0);
			glVertex2d(vectorX1, vectorY1);
		}

		glEnd();
		glFlush();

		vectorY1 = yctr;
		vectorX1 = xctr;
	}

	void update() {
		if(!enabled) return;
		enabled = false;
	}
	 
	void draw(float x, float y) {

		enabled = true;

		if(oldValue != *value) {
			oldValue = targetValue = *value;
		} else {
			*value += (targetValue - *value) * lerpSpeed;
			oldValue = *value;
		}

		setPos(x, y);

		knobAngle = ofMap((*value), min, max, 0.0, (float)width);
		
		if(knobAngle >= width)	knobAngle = 405; 
		else if(knobAngle <= 0)	knobAngle = 0;

		// Take the LERP'd value and scale it across the full range of the knob
		knobDisplay = (( 315 / (2*radius)) * knobAngle);

		ofEnableAlphaBlending();

		glPushMatrix();
			glTranslatef(x + radius , y + radius , 0);

			ofEnableSmoothing();
				ofFill();
				// Draw outside
					ofSetColor(0x363895);
					ofCircle(0.f, 0.f, radius);
				// Draw knob arcs
					ofSetColor(0xdddddd);
					drawArc(0.0f, 0.0f, radius, 135, 135 + knobDisplay);
				// Draw bottom arc
					ofSetColor(0x22234c);
					drawArc(0.0f, 0.0f, radius, 45, 135);
				// Draw donut center
					ofSetColor(0x000000);
					ofCircle(0.f, 0.f, (radius * 0.5));

				// Draw the outside and center again as outlines (for anti-aliasing)
				ofNoFill();
					ofSetColor(0x363895);
					ofSetColor(0x000000);
					ofCircle(0.f, 0.f, radius);
					ofCircle(0.f, 0.f, (radius * 0.5));
			ofDisableSmoothing();

			// ToDo: Reposition the knob value somewhere other than the center
			setTextColor();
			myFont.drawString(ofToString((*value), 0), -12 , 3 );

		glPopMatrix();

		ofDisableAlphaBlending();

	}
	
};
