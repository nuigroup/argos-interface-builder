/***********************************************************************
 
 Copyright (c) 2009 Dimitri Diakopoulos, http://argos.dimitridiakopoulos.com/
 === Google Summer of Code 2009 - NUI Group === 

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

class ofxArgosUI_Icon : public ofxArgosUI_Control {

public:

	ofImage		icon; 
	
	int			defaultCWidth;
	int			defaultCHeight; 

	ofxArgosUI_Icon(int x, int y, int width, int height) : ofxArgosUI_Control("Icon") {

		dragging = false; 

		setup(x, y, width, height);
	}
	
	void setup(int _x, int _y, int _width, int _height) {
		setPos(_x, _y); 
		setSize(_width, _height);
	}

	// ============================================= Mouse
	void onRollOver(int x, int y)						{}
	void onRollOut()									{}
	void onMouseMove(int x, int y)						{}
	void onDragOver(int x, int y, int button)			{}
	void onDragOutside(int x, int y, int button){
	
		//printf("onDragOutside\n"); 
		//printf("X: %i, Y: %i", x, y;
	
			dragging = true; 
			dragX = (floor(((float) x / 20)) * 20);
			dragY = (floor(((float) y / 20)) * 20);
	}

	void onRelease(int x, int y, int button){
	
		dragging = false; 

		dropControl(dragX, dragY); 
		
	}

	void onReleaseOutside(int x, int y, int button)	{
		
		dragging = false; 

		dropControl(dragX, dragY); 
		
	}

	// ============================================= Touch
	void onTouchDown(float x, float y, int ID)			{}
	void onTouchUp(float x, float y, int ID)			{}
	void onTouchUpOutside(float x, float y, int ID)		{}
	void onTouchMove(float x, float y, int ID)			{}
	void onTouchMoveOver(float x, float y, int ID)		{}
	void onTouchMoveOutside(float x, float y, int ID)	{}

	void update() {}

	void draw() {

		setPos(x, y);

		ofEnableAlphaBlending();

		if (dragging){
			ofNoFill(); 
				ofSetColor(100, 100, 100, 255); 
				ofRect((floor(((float)dragX / 20)) * 20),(floor(((float)dragY / 20)) * 20), defaultCWidth, defaultCHeight);
			ofFill(); 
		}

		glPushMatrix();

			glTranslatef(x, y, 0);

			ofSetColor(0xffffff); 

			icon.draw(0,0); 

		glPopMatrix();

		ofDisableAlphaBlending();


	}

};