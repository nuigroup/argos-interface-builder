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

#include "ofxTouchAPI_IO.h"
#include "ofxArgosUI_Parameter.h"
#include "ofxXmlSettings.h"
#include "OSCHandler.h"

class ofxArgosUI_Control : public ofxTouchAPI_IO {

public:

	ofTrueTypeFont			myFont;
	ofxArgosUI_Parameter	param;  

	string		name;			// Human readable name
	string		key;			// Machine readable name
	string		controlType;	// ...
	bool		lock;			// ... 

	bool		dragging;		// Is the control currently being dragged?

	bool		selected;		// Is the control currently being selected?
	bool		selectable;		// Can the control be selected?

	string		OSCaddress;		// OSC address

	int			dragX;
	int			dragY; 
	
	// ========================================= Constructor
	ofxArgosUI_Control(string name);

	// ========================================= Basic Settings
	void setName(string newName);
	void setKey(string newKey);
	void setConfig(ofxArgosUI_Parameter *config);

	// ========================================= Visual Settings
	void setTextColor(bool clickable = true);
	void setTextBGColor(bool clickable = true);
	void setFullColor(bool forceActive = false);
	void setEmptyColor();

	// ========================================= Drawing
	virtual void setup() {}
	virtual void draw(float x, float y) {}
	virtual void draw() { draw(x, y); }	

	// ========================================= Drag/Drop
	virtual void dropControl(int x, int y) {}

	// ========================================= XML Settings (deprecated)
	virtual void loadFromXML(ofxXmlSettings &XML) {}
	virtual void saveToXML(ofxXmlSettings &XML) {}

};