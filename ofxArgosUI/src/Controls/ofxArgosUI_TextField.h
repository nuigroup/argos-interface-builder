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

class ofxArgosUI_TextField : public ofxArgosUI_Control { 
	
public:
	
	string		input;			// Stores user input internally, 
	string		*value;			// then publishes to the external value

	ofxArgosUI_TextField(string name, int x, int y, int width, int height, string *value) : ofxArgosUI_Control(name) {
		this->value = value; 
		input = "Text Field"; 
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
	void onRollOver(int x, int y)						{}
	void onRollOut()									{}
	void onMouseMove(int x, int y)						{}
	void onDragOver(int x, int y, int button)			{}
	void onDragOutside(int x, int y, int button)		{}
	void onPress(int x, int y, int button)				{}
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

		if(key == OF_KEY_DEL || key == OF_KEY_BACKSPACE){
			if (input.size() >= 1) input.erase( input.size() - 1);
		} else {
			input += key; 
		}

		printf("%i \n", key); 
		
		cout << input  << "\n"; 
	}

	void resetInput(){
		input.clear(); 
	}

	void applyInput(){
		*value = input; 
	}

	void update() {}

	void rRectangle(int x, int y, int w, int h, int radius){

        glDisable(GL_TEXTURE_2D);
        
        glBegin(GL_POLYGON);

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

	void draw(float x, float y) {

		setPos(x, y);

		ofEnableAlphaBlending();

		glPushMatrix();
			glTranslatef(x, y, 0);
			
			myFont.drawString(name, -2, -5); 

			ofSetColor(0x919090); 
			rRectangle(0, 0, width, height, 4); 

			ofSetColor(0xffffff); 
			
			if ( (input.size() * 7) < width ){
				myFont.drawString(input, 2, (height/1.5)); 
			}

		glPopMatrix();

		ofDisableAlphaBlending();

	}
	
};


