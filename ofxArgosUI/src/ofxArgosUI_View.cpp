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
#include "ofxArgosUI_View.h"

ofxArgosUI_View::ofxArgosUI_View(string name) : ofxArgosUI_Control(name) {
	disableAllEvents();
}

ofxArgosUI_View::~ofxArgosUI_View() {
}


void ofxArgosUI_View::loadFromXML(ofxXmlSettings &XML) {
	for(int i=0; i < controls.size(); i++) {
		controls[i]->loadFromXML(XML);
	}
}


void ofxArgosUI_View::saveToXML(ofxXmlSettings &XML) {
	for(int i=0; i < controls.size(); i++) {
		controls[i]->saveToXML(XML);
	}
}

float ofxArgosUI_View::getNextY(float y) {
	int iy = ceil(y/config->gridSize.y);
//	return y;
	return (iy) * config->gridSize.y;
}


void ofxArgosUI_View::draw(float x, float y) {

	setPos(x += config->offset.x, y += config->offset.y);
	float posX		= 0;
	float posY		= 0;
	
	ofSetRectMode(OF_RECTMODE_CORNER);
	
	for(int i=0; i<controls.size(); i++) {
		float controlX = posX;
		float controlY = posY;
		
		controls[i]->draw(controls[i]->x, controls[i]->y);
		ofNoFill();
		ofSetColor(config->borderColor);
		glLineWidth(0.5f);

		//ofRect(controlX, controlY, controls[i]->width, controls[i]->height);

		//posY = getNextY(posY + controls[i]->height + config->padding.y);
		
		//if(posY + y >= height - controls[i]->height - config->padding.y) {
		//	posX += config->gridSize.x;
		//	posY = 0;
		//}
	}	
}

/*
void ofxArgosUI_View::draw(float x, float y) {

}
*/


ofxArgosUI_Control *ofxArgosUI_View::addControl(ofxArgosUI_Control* control) {
	controls.push_back(control);
	return control;
}

ofxArgosUI_Button *ofxArgosUI_View::addButton(string name, int x, int y, int width, int height, bool *value) {
	return (ofxArgosUI_Button *)addControl(new ofxArgosUI_Button(name, x, y, width, height, value));
}

ofxArgosUI_Content *ofxArgosUI_View::addContent(string name, ofBaseDraws *content, float fixwidth) {
	if(fixwidth == -1) fixwidth = config->gridSize.x - config->padding.x;
	return (ofxArgosUI_Content *)addControl(new ofxArgosUI_Content(name, content, fixwidth));
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

ofxArgosUI_XYPad *ofxArgosUI_View::addXYPad(string name, ofPoint* value, float xmin, float xmax, float ymin, float ymax) {
	return (ofxArgosUI_XYPad *)addControl(new ofxArgosUI_XYPad(name, value, xmin, xmax, ymin, ymax));
}

ofxArgosUI_Title *ofxArgosUI_View::addTitle(string name, bool *value) {
	return (ofxArgosUI_Title *)addControl(new ofxArgosUI_Title(name, value));
}

ofxArgosUI_Toggle *ofxArgosUI_View::addToggle(string name, int x, int y, int width, int height, bool *value) {
	return (ofxArgosUI_Toggle *)addControl(new ofxArgosUI_Toggle(name, x, y, width, height, value));
}

void ofxArgosUI_View::update(ofEventArgs &e) {
	for(int i=0; i<controls.size(); i++) controls[i]->update();
}

void ofxArgosUI_View::mouseMoved(ofMouseEventArgs &e) {
	for(int i=0; i<controls.size(); i++) controls[i]->_mouseMoved(e);
}

void ofxArgosUI_View::mousePressed(ofMouseEventArgs &e) {
	for(int i=0; i<controls.size(); i++) controls[i]->_mousePressed(e);
}

void ofxArgosUI_View::mouseDragged(ofMouseEventArgs &e) {
	for(int i=0; i<controls.size(); i++) controls[i]->_mouseDragged(e);
}

void ofxArgosUI_View::mouseReleased(ofMouseEventArgs &e) {
	for(int i=0; i<controls.size(); i++) controls[i]->_mouseReleased(e);
}

void ofxArgosUI_View::keyPressed(ofKeyEventArgs &e) {
	for(int i=0; i<controls.size(); i++) controls[i]->_keyPressed(e);
}

void ofxArgosUI_View::keyReleased(ofKeyEventArgs &e) {
	for(int i=0; i<controls.size(); i++) controls[i]->_keyReleased(e);
}