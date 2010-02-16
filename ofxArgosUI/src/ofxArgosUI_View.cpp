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

#include "ofxArgosUI_View.h"

ofxArgosUI_View::ofxArgosUI_View(string name) : ofxArgosUI_Control(name) {
	disableAllEvents();
}

ofxArgosUI_View::~ofxArgosUI_View() {
}

void ofxArgosUI_View::loadFromXML(ofxXmlSettings &XML) {
	for(int i = 0; i < controls.size(); i++) {
		controls[i]->loadFromXML(XML);
	}
}

void ofxArgosUI_View::saveToXML(ofxXmlSettings &XML) {
	for(int i = 3; i < controls.size(); i++) {
		int tagNum =  XML.addTag(controlType);
			XML.setValue(controls[i]->controlType + ":" + "name", controls[i]->name, tagNum);
			XML.setValue(controls[i]->controlType + ":" + "x", controls[i]->x, tagNum);
			XML.setValue(controls[i]->controlType + ":" + "y", controls[i]->y, tagNum);
			XML.setValue(controls[i]->controlType + ":" + "width", controls[i]->width, tagNum);
			XML.setValue(controls[i]->controlType + ":" + "height", controls[i]->height, tagNum);
			XML.setValue(controls[i]->controlType + ":" + "OSC", controls[i]->OSCaddress, tagNum);
		XML.popTag();
	}
}

void ofxArgosUI_View::update(ofEventArgs &e) {
	for(int i = 0; i<controls.size(); i++){
		controls[i]->update();
	}
}

void ofxArgosUI_View::draw(float x, float y) {

	setPos(0,0);
	setSize(ofGetWidth(), ofGetHeight()); 
	
	ofSetRectMode(OF_RECTMODE_CORNER);

	for (int i = 0; i<systemcontrols.size(); i++){
		//systemcontrols[i]->draw(systemcontrols[i]->x, systemcontrols[i]->y);
	}

	if (stateManager::editing){

		for(int i = 0; i<controls.size(); i++) {
			controls[i]->disableAllInput(); 
			controls[i]->draw(controls[i]->x, controls[i]->y);
		}
	}

	else {
		focus.clear(); 
		for(int i = 0; i<controls.size(); i++) {
			controls[i]->enableAllInput(); 
			controls[i]->draw(controls[i]->x, controls[i]->y);
		}
	}

}

ofxArgosUI_Control *ofxArgosUI_View::addSystemControl(ofxArgosUI_Control* control) {
	systemcontrols.push_back(control);
	return control;
}

ofxArgosUI_Panel *ofxArgosUI_View::addSystemPanel(string name, int x, int y, int width, int height) {
	return (ofxArgosUI_Panel *)addSystemControl(new ofxArgosUI_Panel(name, x, y, width, height));
}

ofxArgosUI_Control *ofxArgosUI_View::addControl(ofxArgosUI_Control* control) {
	controls.push_back(control);
	return control;
}

ofxArgosUI_Panel *ofxArgosUI_View::addPanel(string name, int x, int y, int width, int height) {
	return (ofxArgosUI_Panel *)addControl(new ofxArgosUI_Panel(name, x, y, width, height));
}

ofxArgosUI_Button *ofxArgosUI_View::addButton(string name, int x, int y, int width, int height, bool *value) {
	return (ofxArgosUI_Button *)addControl(new ofxArgosUI_Button(name, x, y, width, height, value));
}

ofxArgosUI_FPSCounter *ofxArgosUI_View::addFPSCounter(int x, int y, int width, int height) {
	return (ofxArgosUI_FPSCounter *)addControl(new ofxArgosUI_FPSCounter(x, y, width, height));
}

ofxArgosUI_SliderInt *ofxArgosUI_View::addSlider(string name, int x, int y, int width, int height, int *value, int min, int max) {
	return (ofxArgosUI_SliderInt *)addControl(new ofxArgosUI_SliderInt(name, x, y, width, height, value, min, max, 0));
}

ofxArgosUI_SliderFloat *ofxArgosUI_View::addSlider(string name, int x, int y, int width, int height, float *value, float min, float max, float smoothing) {
	return (ofxArgosUI_SliderFloat *)addControl(new ofxArgosUI_SliderFloat(name, x, y, width, height, value, min, max, smoothing));
}

ofxArgosUI_XYPad *ofxArgosUI_View::addXYPad(string name, int x, int y, int width, int height, ofPoint* value, float xmin, float xmax, float ymin, float ymax) {
	return (ofxArgosUI_XYPad *)addControl(new ofxArgosUI_XYPad(name, x, y, width, height, value, xmin, xmax, ymin, ymax));
}

ofxArgosUI_TextField *ofxArgosUI_View::addTextField(string name, int x, int y, int width, int height, string *value) {
	return (ofxArgosUI_TextField *)addControl(new ofxArgosUI_TextField(name, x, y, width, height, value));
}

ofxArgosUI_Title *ofxArgosUI_View::addTitle(string name, bool *value) {
	return (ofxArgosUI_Title *)addControl(new ofxArgosUI_Title(name, value));
}

ofxArgosUI_Toggle *ofxArgosUI_View::addToggle(string name, int x, int y, int width, int height, bool *value) {
	return (ofxArgosUI_Toggle *)addControl(new ofxArgosUI_Toggle(name, x, y, width, height, value));
}

ofxArgosUI_Knob	*ofxArgosUI_View::addKnob(string name, int x, int y, int radius, float *value, float min, float max, float smoothing){
	return (ofxArgosUI_Knob *)addControl(new ofxArgosUI_Knob(name, x, y, radius, value, min, max, smoothing));
}

ofxArgosUI_Icon	*ofxArgosUI_View::addIcon(int x, int y, int width, int height){
	return (ofxArgosUI_Icon *)addControl(new ofxArgosUI_Icon(x, y, width, height));
}