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

	ToDo
	- Add visual indicators of last position on the side (almost like a slider), x and y

*************************************************************************/ 
#pragma once

#include "ofxArgosUI_Control.h"

class ofxArgosUI_XYPad : public ofxArgosUI_Control {

public:

	ofPoint		*value;
	ofPoint		point, min, max;

	ofxArgosUI_XYPad(string name, int x, int y, int width, int height, ofPoint* value, float xmin, float xmax, float ymin, float ymax) : ofxArgosUI_Control(name) {

		min.set(xmin, ymin);
		max.set(xmax, ymax);
		this->value = value;
		controlType = "XYPad";

		OSCaddress = "/xypad"; 

		setup(x, y, width, height);
	}
	
	void setup(int _x, int _y, int _width, int _height) {
		setPos(_x, _y); 
		setSize(_width, _height);
	}

	void loadFromXML(ofxXmlSettings &XML) {
		value->set(XML.getValue("controls:" + controlType + "_" + key + ":valueX", 0.0f), XML.getValue("controls:" + controlType + "_" + key + ":valueY", 0.0f));
	}
	
	void saveToXML(ofxXmlSettings &XML) {
		XML.addTag(controlType + "_" + key);
			XML.pushTag(controlType + "_" + key);
				XML.addValue("name", name);
				XML.addValue("valueX", value->x);
				XML.addValue("valueY", value->y);
			XML.popTag();
	}
	
	void set(float x, float y) {
		(*value).x = x;
		(*value).y = y;
	}
	void setMin(float x, float y) {
		min.x = x;
		min.y = y;
	}	
	void setMax(float x, float y) {
		max.x = x;
		max.y = y;
	}	
	
	// ============================================= Mouse
	void onPress(int x, int y, int button) {
		lock = true;
		point.set(x, y);
		focus.set(this); 
	}
	
	void onDragOver(int x, int y, int button) {
		if(lock)
			point.set(x, y);
	}
	
	void onDragOutside(int x, int y, int button) {
		if(lock)
			point.set(x, y);
	}

	void onRelease() {
		lock = false;
	}

	// ============================================= Touch
	void onTouchDown(float x, float y, int ID){
		lock = true;
		point.set(x, y);
	}

	void onTouchMove(float x, float y, int ID){
		if(lock)
			point.set(x, y);
	}

	void onTouchMoveOutside(float x, float y, int ID){
		if(lock)
			point.set(x, y);
	}

	void onTouchUp(float x, float y, int ID){
		lock = false;
	}

	void update() {

		if(!enabled) return;
		enabled = false;

		if(point.x > x + width)
			point.x = x + width; 

		else if(point.x < x)
			point.x = x; 
		
		if(point.y > y + height)
			point.y = y + height;

		else if(point.y < y)
			point.y = y;
		
		if(lock){
			(*value).x = ofMap(point.x, x, x + width, min.x, max.x); 
			(*value).y = ofMap(point.y, y, y + height, min.y, max.y); 
		}

	}

	void draw(float x, float y) {

		enabled = true;

		setPos(x, y);

		ofPoint	pointv;

		pointv.x = ofMap((*value).x, min.x, max.x, x, x + width);
		pointv.y = ofMap((*value).y, min.y, max.y, y, y + height);
		
		//ofEnableAlphaBlending();

		glPushMatrix();
			glTranslatef(x, y, 0);		
			
			ofFill();
			setFullColor();

			// Pad Area
			rRectangle(0, 0, width, height, 4);
			
			// Bottom text area
			//setTextBGColor();
			//ofRect(0, height, width, 20);

			// Draw the text
			setTextColor();
			myFont.drawString("" + ofToString(value->x, 1) + "/" + ofToString(value->y, 1), 2, height - 5 );

			// Draw the crosshairs 
			//setTextBGColor();
			//ofLine(pointv.x - x, 0, pointv.x - x, height);
			// ofLine(0, pointv.y - y, width, pointv.y - y);
			
			// Draw circle in middle of crosshairs
			setTextColor();
			ofCircle(pointv.x - x, pointv.y - y, 8);

			ofSetColor(240, 240, 240); 
			ofCircle(pointv.x - x, pointv.y - y, 6);

		glPopMatrix();

		//ofDisableAlphaBlending();
		
	}
	
};