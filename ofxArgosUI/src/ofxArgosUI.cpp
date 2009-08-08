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
#include "ofxArgosUI.h"

ofxArgosUI::ofxArgosUI() {

	config			= &defaultConfiguration;
	
//	guiFocus		= 0;
	
	verbose			= true;
	
	xmlFile			= OFX_ARGOS_XML_NAME;

	doSave			= false;
	doSaveBackup	= false;
	changeView		= false;
	
	drawHeader(); 
}

void ofxArgosUI::drawHeader(){

	headerView	= addView("Header");
	//headerView->height = config->buttonHeight * 2;
	//headerView->width = 0;

	//headerView->addToggle("Auto Save", &doAutoSave);
	//headerView->addButton("Save Settings", &doSave);
	//headerView->addButton("Backup XML", &doSaveBackup);

	addView();
	setAutoSave(false);
	setDraw(true);
	setView(1);
}


void ofxArgosUI::addListeners() {
	//ofAddListener(ofEvents.setup, this, &ofxArgosUI::setup);
	ofAddListener(ofEvents.update, this, &ofxArgosUI::update);
	//ofAddListener(ofEvents.draw, this, &ofxArgosUI::draw);
	//ofAddListener(ofEvents.exit, this, &ofxArgosUI::exit);

	ofAddListener(ofEvents.mousePressed, this, &ofxArgosUI::mousePressed);
	ofAddListener(ofEvents.mouseMoved, this, &ofxArgosUI::mouseMoved);
	ofAddListener(ofEvents.mouseDragged, this, &ofxArgosUI::mouseDragged);
	ofAddListener(ofEvents.mouseReleased, this, &ofxArgosUI::mouseReleased);
	
	ofAddListener(ofEvents.keyPressed, this, &ofxArgosUI::keyPressed);
	ofAddListener(ofEvents.keyReleased, this, &ofxArgosUI::keyReleased);

}


void ofxArgosUI::removeListeners() {
	//ofRemoveListener(ofEvents.setup, this, &ofxArgosUI::setup);
	ofRemoveListener(ofEvents.update, this, &ofxArgosUI::update);
	//ofRemoveListener(ofEvents.draw, this, &ofxArgosUI::draw);
	//ofRemoveListener(ofEvents.exit, this, &ofxArgosUI::exit);
	
	ofRemoveListener(ofEvents.mousePressed, this, &ofxArgosUI::mousePressed);
	ofRemoveListener(ofEvents.mouseMoved, this, &ofxArgosUI::mouseMoved);
	ofRemoveListener(ofEvents.mouseDragged, this, &ofxArgosUI::mouseDragged);
	ofRemoveListener(ofEvents.mouseReleased, this, &ofxArgosUI::mouseReleased);
	
	ofRemoveListener(ofEvents.keyPressed, this, &ofxArgosUI::keyPressed);
	ofRemoveListener(ofEvents.keyReleased, this, &ofxArgosUI::keyReleased);
}

void ofxArgosUI::setDraw(bool b) {
	doDraw = b;
	if(doDraw) addListeners();
	else removeListeners();	
	if(doAutoSave) saveToXML(xmlFile);
}

void ofxArgosUI::toggleDraw() {
	setDraw(!doDraw);
}

bool ofxArgosUI::isOn() {
	return doDraw;
}


void ofxArgosUI::setAutoSave(bool b) {
	doAutoSave = b;
}


void ofxArgosUI::loadFromXML(string file) {
	if(verbose) printf("ofxArgosUI::loadFromXML( %s )\n", file.c_str());
	
	if(file.compare("NULL") != 0) xmlFile = file;
	else {
		xmlFile = OFX_ARGOS_XML_NAME;
	}
	
	if(XML.loadFile(xmlFile) == false) {
		if(verbose) printf("Error loading XMLFile: %s\n", xmlFile.c_str());
		return;	
	}
	
	doDraw		= XML.getValue("options:doDraw", true);
	doAutoSave	= XML.getValue("options:doAutoSave", false);
	currentView	= XML.getValue("options:currentView", 1);
	
	for(int i=1; i < views.size(); i++) {
		views[i]->loadFromXML(XML);
	}
	
	setView(currentView);
	setDraw(doDraw);
}


void ofxArgosUI::saveToXML(string file) {
	doSave = false;
	
	XML.clear();	// clear cause we are building a new xml file
	
	XML.addTag("options");
		XML.pushTag("options");
			XML.addValue("doDraw", doDraw);
			XML.addValue("doAutoSave", doAutoSave);
			XML.addValue("currentView", currentView);
	XML.popTag();
	
	XML.addTag("controls");
		XML.pushTag("controls");
		for(int i=1; i < views.size(); i++) {
			views[i]->saveToXML(XML);
		}
	XML.popTag();
	
	XML.saveFile(file);

	if(doSaveBackup) XML.saveFile(file+".bak");
	printf("ofxArgosUI::saveToXML( %s )\n", file.c_str());
}


void ofxArgosUI::setVerbose(bool v) {
	verbose = v;
}

void ofxArgosUI::drawFocus(float x, float y) {
	glPushMatrix();
		glTranslatef(x, y, 0);
		ofFill();
		//ofSetColor(config->focusColor.r, config->focusColor.g, config->focusColor.b, 200);
		ofRect(0, 0, 10, 10);
	glPopMatrix();
}


void ofxArgosUI::draw() {
	if(!doDraw) return;
	
	glDisableClientState(GL_COLOR_ARRAY);
	
	// Draw the first view (view) 
	headerView->draw();	
	ofSetColor(config->borderColor);
	ofLine(0, headerView->height, headerView->width, headerView->height); 
	views[currentView]->draw(0.0f, headerView->height);
}


void ofxArgosUI::nextView() {
	setView(currentView + 1);
}
void ofxArgosUI::prevView() {
	setView(currentView - 1);
}


void ofxArgosUI::setView(int i) {
	currentView = i;
	if(currentView >= views.size()) currentView = 1;
	else if(currentView < 1) currentView = views.size()-1;
}


void ofxArgosUI::setView(string name) {
	ofxArgosUI_View *view;
	for(int i=1; i < views.size(); i++) {
		if(name.compare(views[i]->name) == 0) {
			setView(i);
			break;
		}
	}
}

ofxArgosUI_View *ofxArgosUI::view(int i) {
	return views.at(i);
}

ofxArgosUI_View *ofxArgosUI::view(string name) {
	ofxArgosUI_View *view;
	for(int i=1; i<views.size(); i++) if(name.compare(views[i]->name) == 0) return views[i];
	return NULL;
}


ofxArgosUI_View *ofxArgosUI::addView(string name) {

	ofxArgosUI_View *newView = new ofxArgosUI_View(name);
	views.push_back(newView);
	if(name == "") newView->setName("View " + ofToString(views.size()-1, 0));
	static bool b;

	// HEADER BUTTON
	//if(views.size() > 1) newView->addTitle(newView->name, &changeView);		// if this isn't the first view, add to header
	setView(views.size() - 1);
	return newView;
}

ofxArgosUI_Control *ofxArgosUI::addControl(ofxArgosUI_Control* control) {
	return views[currentView]->addControl(control);
}

ofxArgosUI_Panel *ofxArgosUI::addPanel(string name, int x, int y, int width, int height) {
	return views[currentView]->addPanel(name, x, y, width, height);
}

ofxArgosUI_Button *ofxArgosUI::addButton(string name, int x, int y, int width, int height, bool *value) {
	return views[currentView]->addButton(name, x, y, width, height, value);
}

ofxArgosUI_Toggle *ofxArgosUI::addToggle(string name, int x, int y, int width, int height, bool *value) {
	return views[currentView]->addToggle(name, x, y, width, height, value);
}

ofxArgosUI_SliderInt *ofxArgosUI::addSlider(string name, int x, int y, int width, int height, int *value, int min, int max) {
	return views[currentView]->addSlider(name, x, y, width, height, value, min, max);
}

ofxArgosUI_SliderFloat *ofxArgosUI::addSlider(string name,int x, int y, int width, int height, float *value, float min, float max, float smoothing) {
	return views[currentView]->addSlider(name, x, y, width, height, value, min, max, smoothing);
}

ofxArgosUI_XYPad *ofxArgosUI::addXYPad(string name, ofPoint* value, float xmin, float xmax, float ymin, float ymax) {
	return views[currentView]->addXYPad(name, value, xmin, xmax, ymin, ymax);
}

ofxArgosUI_Title *ofxArgosUI::addTitle(string name, bool *value) {
	return views[currentView]->addTitle(name, value);
}

ofxArgosUI_Content *ofxArgosUI::addContent(string name, ofBaseDraws *content, float fixwidth) {
	return views[currentView]->addContent(name, content, fixwidth);
}

ofxArgosUI_FPSCounter *ofxArgosUI::addFPSCounter(int x, int y, int width, int height) {
	return views[currentView]->addFPSCounter(x, y, width, height);
}

ofxArgosUI_Knob	*ofxArgosUI::addKnob(string name, int x, int y, int radius, float *value, float min, float max, float smoothing){
	return views[currentView]->addKnob(name, x, y, radius, value, min, max, smoothing);
}

void ofxArgosUI::update(ofEventArgs &e) {

	if(changeView) {
		nextView();	
		changeView = false;
	}
	
	headerView->update(e);
	views[currentView]->height = ofGetHeight();
	views[currentView]->update(e);
	
	
	if(doSaveBackup) doSave = true;
	
	if(doSave) saveToXML(xmlFile);
}

void ofxArgosUI::mouseMoved(ofMouseEventArgs &e) {
	headerView->mouseMoved(e);
	views[currentView]->mouseMoved(e);
}

void ofxArgosUI::mousePressed(ofMouseEventArgs &e) {
	headerView->mousePressed(e);
	views[currentView]->mousePressed(e);
}

void ofxArgosUI::mouseDragged(ofMouseEventArgs &e) {
	headerView->mouseDragged(e);
	views[currentView]->mouseDragged(e);
}

void ofxArgosUI::mouseReleased(ofMouseEventArgs &e) {
	headerView->mouseReleased(e);
	views[currentView]->mouseReleased(e);
	if(doAutoSave) saveToXML(xmlFile);
}

void ofxArgosUI::keyPressed(ofKeyEventArgs &e) {
	headerView->keyPressed(e);
	views[currentView]->keyPressed(e);
	if(doAutoSave) saveToXML(xmlFile);
}

void ofxArgosUI::keyReleased(ofKeyEventArgs &e) {
	headerView->keyReleased(e);
	views[currentView]->keyReleased(e);
}