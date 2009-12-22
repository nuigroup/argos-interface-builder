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
#include "ofxArgosUI_Control.h"

ofxArgosUI_Control::ofxArgosUI_Control(string name) {
                                     
	lock = false; 

	controlType = "";

	setName(name);
	setKey(key);

	canfocus = true; 

	myFont.loadFont("segoeui.ttf", 10);

	setup();
	enableAllEvents(); 

}


void ofxArgosUI_Control::setName(string newName) {
	name = newName;
	if(key.compare("") == 0) setKey("");
}


void ofxArgosUI_Control::setKey(string newKey) {
	if(newKey.compare("") == 0) key = name;
	else key = newKey;
	for(int i=0; i<key.size(); i++) {
		if(key[i] == ' ') key[i] = '_';
	}
}

void ofxArgosUI_Control::setTextColor(bool clickable) {
	if (isMouseOver() && clickable) ofSetColor(param.textOverColor);
	else if (isBeingTouched()) ofSetColor(param.textOverColor);
	else ofSetColor(param.textColor);
}

void ofxArgosUI_Control::setTextBGColor(bool clickable) {
	if(isMouseOver() && clickable) ofSetColor(param.textBGOverColor);
	else if (isBeingTouched()) ofSetColor(param.textBGOverColor);
	else ofSetColor(param.textBGColor);
}

void ofxArgosUI_Control::setFullColor(bool forceActive) {
	if(isMouseDown() || forceActive) ofSetColor(param.fullActiveColor);
	else if(isMouseOver()) ofSetColor(param.fullOverColor);
	else ofSetColor(param.fullColor);
}

void ofxArgosUI_Control::setEmptyColor() {
	ofSetColor(param.emptyColor);
}
