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

ofxArgosUI_Too::ofxArgosUI_Too() {

	config			= &defaultSimpleGuiConfig;
	
//	guiFocus		= 0;
	
	verbose			= true;
	
	xmlFile			= OFX_SIMPLEGUITOO_XML_NAME;

	doSave			= false;
	doSaveBackup	= false;
	changePage		= false;
	
	drawHeader(); 

}

void ofxArgosUI_Too::drawHeader(){

	headerPage	= addView("Header");
	//headerPage->height = config->buttonHeight * 2;
	//headerPage->width = 0;

	//headerPage->addToggle("Auto Save", &doAutoSave);
	//headerPage->addButton("Save Settings", &doSave);
	//headerPage->addButton("Backup XML", &doSaveBackup);

	addView();
	setAutoSave(false);
	setDraw(true);
	setPage(1);
}


void ofxArgosUI_Too::addListeners() {
	//ofAddListener(ofEvents.setup, this, &ofxArgosUI_Too::setup);
	ofAddListener(ofEvents.update, this, &ofxArgosUI_Too::update);
	//ofAddListener(ofEvents.draw, this, &ofxArgosUI_Too::draw);
	//ofAddListener(ofEvents.exit, this, &ofxArgosUI_Too::exit);

	ofAddListener(ofEvents.mousePressed, this, &ofxArgosUI_Too::mousePressed);
	ofAddListener(ofEvents.mouseMoved, this, &ofxArgosUI_Too::mouseMoved);
	ofAddListener(ofEvents.mouseDragged, this, &ofxArgosUI_Too::mouseDragged);
	ofAddListener(ofEvents.mouseReleased, this, &ofxArgosUI_Too::mouseReleased);
	
	ofAddListener(ofEvents.keyPressed, this, &ofxArgosUI_Too::keyPressed);
	ofAddListener(ofEvents.keyReleased, this, &ofxArgosUI_Too::keyReleased);

}


void ofxArgosUI_Too::removeListeners() {
	//ofRemoveListener(ofEvents.setup, this, &ofxArgosUI_Too::setup);
	ofRemoveListener(ofEvents.update, this, &ofxArgosUI_Too::update);
	//ofRemoveListener(ofEvents.draw, this, &ofxArgosUI_Too::draw);
	//ofRemoveListener(ofEvents.exit, this, &ofxArgosUI_Too::exit);
	
	ofRemoveListener(ofEvents.mousePressed, this, &ofxArgosUI_Too::mousePressed);
	ofRemoveListener(ofEvents.mouseMoved, this, &ofxArgosUI_Too::mouseMoved);
	ofRemoveListener(ofEvents.mouseDragged, this, &ofxArgosUI_Too::mouseDragged);
	ofRemoveListener(ofEvents.mouseReleased, this, &ofxArgosUI_Too::mouseReleased);
	
	ofRemoveListener(ofEvents.keyPressed, this, &ofxArgosUI_Too::keyPressed);
	ofRemoveListener(ofEvents.keyReleased, this, &ofxArgosUI_Too::keyReleased);
}

void ofxArgosUI_Too::setDraw(bool b) {
	doDraw = b;
	if(doDraw) addListeners();
	else removeListeners();	
	if(doAutoSave) saveToXML(xmlFile);
}

void ofxArgosUI_Too::toggleDraw() {
	setDraw(!doDraw);
}

bool ofxArgosUI_Too::isOn() {
	return doDraw;
}


void ofxArgosUI_Too::setAutoSave(bool b) {
	doAutoSave = b;
}


void ofxArgosUI_Too::loadFromXML(string file) {
	if(verbose) printf("ofxArgosUI_Too::loadFromXML( %s )\n", file.c_str());
	
	if(file.compare("NULL") != 0) xmlFile = file;
	else {
		xmlFile = OFX_SIMPLEGUITOO_XML_NAME;
	}
	
	if(XML.loadFile(xmlFile) == false) {
		if(verbose) printf("Error loading XMLFile: %s\n", xmlFile.c_str());
		return;	
	}
	
	doDraw		= XML.getValue("options:doDraw", true);
	doAutoSave	= XML.getValue("options:doAutoSave", false);
	currentPage	= XML.getValue("options:currentPage", 1);
	
	for(int i=1; i < pages.size(); i++) {
		pages[i]->loadFromXML(XML);
	}
	
	setPage(currentPage);
	setDraw(doDraw);
}


void ofxArgosUI_Too::saveToXML(string file) {
	doSave = false;
	
	XML.clear();	// clear cause we are building a new xml file
	
	XML.addTag("options");
	XML.pushTag("options");
	XML.addValue("doDraw", doDraw);
	XML.addValue("doAutoSave", doAutoSave);
	XML.addValue("currentPage", currentPage);
	XML.popTag();
	
	XML.addTag("controls");
	XML.pushTag("controls");
	for(int i=1; i < pages.size(); i++) {
		pages[i]->saveToXML(XML);
	}
	XML.popTag();
	
	XML.saveFile(file);
	if(doSaveBackup) XML.saveFile(file+".bak");
	printf("ofxArgosUI_Too::saveToXML( %s )\n", file.c_str());
}


void ofxArgosUI_Too::setVerbose(bool v) {
	verbose = v;
}

//
//int ofxArgosUI_Too::getValueI(string nameID) {
//	for(int i=0; i<controls.size(); i++) {
//		if(nameID.compare(controls[i]->name) == 0) {
//			ofxArgosUI_SliderInt *c = dynamic_cast<ofxArgosUI_SliderInt *> (controls[i]);
//			if(c) return c->getValue();
//		}
//	}
//	return NULL;	
//}
//
//float ofxArgosUI_Too::getValueF(string nameID) {
//	for(int i=0; i<controls.size(); i++) {
//		if(nameID.compare(controls[i]->name) == 0) {
//			ofxArgosUI_SliderFloat *c = dynamic_cast<ofxArgosUI_SliderFloat *> (controls[i]);
//			if(c) return c->getValue();
//		}
//	}	
//	return NULL;
//}
//
//bool ofxArgosUI_Too::getValueB(string nameID) {
//	for(int i=0; i<controls.size(); i++) {
//		if(nameID.compare(controls[i]->name) == 0) {
//			ofxArgosUI_Toggle *c = dynamic_cast<ofxArgosUI_Toggle *> (controls[i]);
//			if(c) return c->getValue();
//		}
//	}	
//	return NULL;
//}


void ofxArgosUI_Too::drawFocus(float x, float y) {
	glPushMatrix();
	glTranslatef(x, y, 0);
	ofFill();
//	ofSetColor(config->focusColor.r, config->focusColor.g, config->focusColor.b, 200);
	ofRect(0, 0, 10, 10);
	glPopMatrix();
}


void ofxArgosUI_Too::draw() {
	if(!doDraw) return;
	
	glDisableClientState(GL_COLOR_ARRAY);
	
	headerPage->draw();		// this is the header
	ofSetColor(config->borderColor);
	ofLine(0, headerPage->height, headerPage->width, headerPage->height); 
	pages[currentPage]->draw(0.0f, headerPage->height);
}


void ofxArgosUI_Too::nextPage() {
	setPage(currentPage + 1);
}
void ofxArgosUI_Too::prevPage() {
	setPage(currentPage - 1);
}


void ofxArgosUI_Too::setPage(int i) {
	currentPage = i;
	if(currentPage >= pages.size()) currentPage = 1;
	else if(currentPage < 1) currentPage = pages.size()-1;
}


void ofxArgosUI_Too::setPage(string name) {
	ofxArgosUI_View *page;
	for(int i=1; i < pages.size(); i++) {
		if(name.compare(pages[i]->name) == 0) {
			setPage(i);
			break;
		}
	}
}


ofxArgosUI_View *ofxArgosUI_Too::page(int i) {
	return pages.at(i);
}

ofxArgosUI_View *ofxArgosUI_Too::page(string name) {
	ofxArgosUI_View *page;
	for(int i=1; i<pages.size(); i++) if(name.compare(pages[i]->name) == 0) return pages[i];
	return NULL;
}


ofxArgosUI_View *ofxArgosUI_Too::addView(string name) {

	ofxArgosUI_View *newPage = new ofxArgosUI_View(name);
	pages.push_back(newPage);
	if(name == "") newPage->setName("Page " + ofToString(pages.size()-1, 0));
	static bool b;
//	if(pages.size() > 1) headerPage->addTitle(newPage->name);				// if this isn't the first page, add to header
	if(pages.size() > 1) newPage->addTitle(newPage->name, &changePage);		// if this isn't the first page, add to header
	setPage(pages.size() - 1);
	return newPage;
}


ofxArgosUI_Control *ofxArgosUI_Too::addControl(ofxArgosUI_Control* control) {
	return pages[currentPage]->addControl(control);
}

ofxArgosUI_Button *ofxArgosUI_Too::addButton(string name, int x, int y, int width, int height, bool *value) {
	return pages[currentPage]->addButton(name, x, y, width, height, value);
}

ofxArgosUI_Toggle *ofxArgosUI_Too::addToggle(string name, bool *value) {
	return pages[currentPage]->addToggle(name, value);
}

ofxArgosUI_SliderInt *ofxArgosUI_Too::addSlider(string name, int *value, int min, int max) {
	return pages[currentPage]->addSlider(name, value, min, max);
}

ofxArgosUI_SliderFloat *ofxArgosUI_Too::addSlider(string name, float *value, float min, float max, float smoothing) {
	return pages[currentPage]->addSlider(name, value, min, max, smoothing);
}

ofxArgosUI_Slider2d *ofxArgosUI_Too::addSlider2d(string name, ofPoint* value, float xmin, float xmax, float ymin, float ymax) {
	return pages[currentPage]->addSlider2d(name, value, xmin, xmax, ymin, ymax);
}

ofxArgosUI_Title *ofxArgosUI_Too::addTitle(string name, bool *value) {
	return pages[currentPage]->addTitle(name, value);
}

ofxArgosUI_Content *ofxArgosUI_Too::addContent(string name, ofBaseDraws *content, float fixwidth) {
	return pages[currentPage]->addContent(name, content, fixwidth);
}

ofxArgosUI_FPSCounter *ofxArgosUI_Too::addFPSCounter() {
	return pages[currentPage]->addFPSCounter();
}



void ofxArgosUI_Too::update(ofEventArgs &e) {
	if(changePage) {
		nextPage();	
		changePage = false;
	}
	
	headerPage->update(e);
	pages[currentPage]->height = ofGetHeight();
	pages[currentPage]->update(e);
	
	
	if(doSaveBackup) doSave = true;
	
	if(doSave) saveToXML(xmlFile);
}

void ofxArgosUI_Too::mouseMoved(ofMouseEventArgs &e) {
	headerPage->mouseMoved(e);
	pages[currentPage]->mouseMoved(e);
}

void ofxArgosUI_Too::mousePressed(ofMouseEventArgs &e) {
	headerPage->mousePressed(e);
	pages[currentPage]->mousePressed(e);
}

void ofxArgosUI_Too::mouseDragged(ofMouseEventArgs &e) {
	headerPage->mouseDragged(e);
	pages[currentPage]->mouseDragged(e);
}

void ofxArgosUI_Too::mouseReleased(ofMouseEventArgs &e) {
	headerPage->mouseReleased(e);
	pages[currentPage]->mouseReleased(e);
	if(doAutoSave) saveToXML(xmlFile);
}

void ofxArgosUI_Too::keyPressed(ofKeyEventArgs &e) {
	headerPage->keyPressed(e);
	pages[currentPage]->keyPressed(e);
	if(doAutoSave) saveToXML(xmlFile);
}

void ofxArgosUI_Too::keyReleased(ofKeyEventArgs &e) {
	headerPage->keyReleased(e);
	pages[currentPage]->keyReleased(e);
}