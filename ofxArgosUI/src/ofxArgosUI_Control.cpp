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
#include "ofxArgosUI_Control.h"


//==============================================================================
ofxArgosUI_Control::ofxArgosUI_Control(string name) {
      
	setName(name);
	controlType = "";

	lock = false; 
	canfocus = true; 

	setup();

	enableAllEvents(); 	

}

//==============================================================================
void ofxArgosUI_Control::setName(string newName) {
	name = newName;
}

//==============================================================================
void ofxArgosUI_Control::setTextColor(bool clickable) {
	if (isMouseOver() && clickable) ofSetColor(param.textOverColor);

	else if (isBeingTouched()) ofSetColor(param.textOverColor);

	else ofSetColor(param.textColor);
}

void ofxArgosUI_Control::setTextBGColor(bool clickable) {
	if (isMouseOver() && clickable) ofSetColor(param.textBGOverColor);

	else if (isBeingTouched()) ofSetColor(param.textBGOverColor);

	else ofSetColor(param.textBGColor);
}

void ofxArgosUI_Control::setFullColor(bool forceActive) {
	if (isMouseDown() || forceActive) ofSetColor(param.fullActiveColor);

	else if (isMouseOver()) ofSetColor(param.fullOverColor);

	else ofSetColor(param.fullColor);
}

void ofxArgosUI_Control::setEmptyColor() {
	ofSetColor(param.emptyColor);
}


//==============================================================================

string *ofxArgosUI_Control::getPropertyRef(const string keyVal) throw(){
	if (properties.count(keyVal) != 0)
		return &properties.find(keyVal)->second;
}

string ofxArgosUI_Control::getPropertyString(const string keyVal, string defaultValue) throw(){
	if (properties.count(keyVal) != 0)
		return properties[keyVal]; 
	else 
		return defaultValue; 
}

float ofxArgosUI_Control::getPropertyFloat( string keyVal, float defaultValue)  throw(){
	if (properties.count(keyVal) != 0)
		return (float) atof(properties[keyVal].c_str()) ;
	else 
		return defaultValue; 
}

bool ofxArgosUI_Control::getPropertyBool( string keyVal, bool defaultValue)  throw(){
	if (properties.count(keyVal) != 0)
		return (bool) atof(properties[keyVal].c_str()) ;
	else 
		return defaultValue; 

}

int ofxArgosUI_Control::getPropertyInt( string keyVal, int defaultValue)  throw(){
	if (properties.count(keyVal) != 0)
		return (int) atof(properties[keyVal].c_str()) ;
	else 
		return defaultValue; 

}

//==============================================================================
void ofxArgosUI_Control::setPropertyString(string keyVal, string value) throw() {
	properties.find(keyVal)->second = value; 
}

void ofxArgosUI_Control::setPropertyFloat(string keyVal, float value) throw() {
	properties.find(keyVal)->second = value; 
}

void ofxArgosUI_Control::setPropertyBool(string keyVal, bool value) throw() {
	properties.find(keyVal)->second = ofToString(value); 
}

void ofxArgosUI_Control::setPropertyInt(string keyVal, int value) throw() {
	properties.find(keyVal)->second = ofToString(value); 
}


//==============================================================================
void ofxArgosUI_Control::createPropertyString(string keyVal, string value) throw() {
	properties.insert(std::pair<string,string>(keyVal, string (value)));
}

void ofxArgosUI_Control::createPropertyFloat(string keyVal, float value) throw() {
	properties.insert(std::pair<string,string>(keyVal, ofToString(value) ));
}

void ofxArgosUI_Control::createPropertyBool(string keyVal, bool value) throw() {
	properties.insert(std::pair<string,string>(keyVal, string ( (value) ? ("1") : ("0") ))); 
}

void ofxArgosUI_Control::createPropertyInt(string keyVal, int value) throw() {
	properties.insert(std::pair<string,string>(keyVal, ofToString(value)));
}

//==============================================================================
void ofxArgosUI_Control::createProperties(){
	createPropertyString("name", name);
	createPropertyInt("x", x);
	createPropertyInt("y", y);
	createPropertyInt("w", width);
	createPropertyInt("h", height);
	createPropertyString("osc", OSCaddress);
}

