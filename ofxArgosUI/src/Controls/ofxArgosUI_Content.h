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


//------------------------------------------------------------------------------ toggle
class ofxArgosUI_Content  : public ofxArgosUI_Control {
public:
	float			fixwidth;
	float			fixheight;
	ofBaseDraws		*content;
	
	//---------------------------------------------------------------------
	ofxArgosUI_Content(string name, ofBaseDraws* content, float fixwidth=250.0) : ofxArgosUI_Control(name) {
		this->content = content;
		this->fixwidth  = fixwidth;
		controlType = "Content";
		setup();
	}
	
	void setup() {
		fixheight = fixwidth * content->getHeight()/content->getWidth();
		setSize(fixwidth, fixheight + config->sliderTextHeight);
	}
	
	void draw(float x, float y) {
		setPos(x, y);
		setup();
		
		glPushMatrix();
		glTranslatef(x, y, 0);
		ofEnableAlphaBlending();
		ofFill();
		glColor4f(0, 0, 0, 0.8f);
		ofRect(0, 0, width, fixheight);

		ofSetColor(0xffffff);
		content->draw(0, 0, width, fixheight); 
		
		ofFill();
		setTextBGColor();
		ofRect(0, fixheight, width, config->sliderTextHeight);

		setTextColor();
		ofDrawBitmapString(name, 3, fixheight + 15);
		ofDisableAlphaBlending();
		glPopMatrix();
	}
	
};
