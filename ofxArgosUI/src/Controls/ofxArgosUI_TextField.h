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

#include "ofxArgosUI_Control.h"

class ofxArgosUI_TextField : public ofxArgosUI_Control { 
	
public:
	
	string		input;			// Stores user input internally, 
	string		output;			// Applied output
	string		*value;			// then publishes to the external value

	// For eventual callback function
	//void		(*onApply)(string); 

	ofxArgosUI_TextField(string name, int x, int y, int width, int height, string *value) : ofxArgosUI_Control(name) {
		this->value = value; 
		input = *value; 
		controlType = "TextField";
		setup(x, y, width, height);
	}
	
	void setup(int _x, int _y, int _width, int _height) {
		setPos(_x, _y); 
		setSize(_width, _height);
	}
	
	void loadFromXML(ofxXmlSettings &XML) {}
	
	void saveToXML(ofxXmlSettings &XML) {}
	
	// ============================================= Mouse
	void onRollOver(int x, int y)						{
		glutSetCursor(GLUT_CURSOR_TEXT);
	}

	void onRollOut()									{
		glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
	}

	void onMouseMove(int x, int y)						{}
	void onDragOver(int x, int y, int button)			{}
	void onDragOutside(int x, int y, int button)		{}
	void onPress(int x, int y, int button)				{
		if (canfocus) { textfocus.set(this); }
	}
	void onRelease(int x, int y, int button)			{}
	void onReleaseOutside(int x, int y, int button)		{}

	// ============================================= Touch
	void onTouchDown(float x, float y, int ID)			{}
	void onTouchUp(float x, float y, int ID)			{}
	void onTouchUpOutside(float x, float y, int ID)		{}
	void onTouchMove(float x, float y, int ID)			{}
	void onTouchMoveOver(float x, float y, int ID)		{}
	void onTouchMoveOutside(float x, float y, int ID)	{}
	
	// ============================================= Key
	void keyPressed(int key){
		if (textfocus.focused != NULL && textfocus.focused == this) {
			
			// Delete text?
			if(key == OF_KEY_BACKSPACE){
				if (input.size() >= 1) input.erase( input.size() - 1);
			} 
			
			// Apply Input
			else if (key == OF_KEY_RETURN){
				applyInput(); 
			}

			// Input we don't want
			else if (key == OF_KEY_UP || key ==  OF_KEY_DOWN || key == OF_KEY_LEFT || key == OF_KEY_RIGHT || key == OF_KEY_DEL) {
				// Do nothing. 
			}

			// Otherwise take input. 
			else {
				input += key; 
			}
		}
	}

	void resetInput(){
		input.clear(); 
	}

	void applyInput(){
		*value = input; 
	}

	void update() {
		enabled = false;
	}

	void draw(float x, float y) {

		enabled = true;

		setPos(x, y);

		glPushMatrix();
			glTranslatef(x, y, 0);
			
			ofSetColor(255, 255, 255); 

			argosText::font.drawString(name, -2, -5); 

			ofSetColor(0x767676); 

			rRectangle(0, 0, width, height, 3); 

			ofSetColor(0xffffff); 

			if ( (input.size() * 6) < width ){
				argosText::font.drawString(input, 2, (height/1.5)); 
			}

		glPopMatrix();

	}
	
};


