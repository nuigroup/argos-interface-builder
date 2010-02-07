/***********************************************************************
 
 Copyright (c) 2009, 2010 Dimitri Diakopoulos, http://argos.dimitridiakopoulos.com/

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

#include "EditorActions.h"
#include "EditorCore.h"

resizeControl::resizeControl(EditorPanel *ed) : ofxArgosUI_Control("resizeControl") {
	controlType = "resizeControl";
	editor = ed;
	dragging = false; 
}

void resizeControl::setControl() {
	if (focus.focused != NULL){
		setPos(focus.focused->x + focus.focused->width + 5, focus.focused->y + focus.focused->height + 5); 
		setSize(10,10);
	}
}

void resizeControl::onRollOver(int x, int y) {
	glutSetCursor(GLUT_CURSOR_BOTTOM_RIGHT_CORNER); 	
}

void resizeControl::onRollOut() {
	glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
}

void resizeControl::onDragOutside(int x, int y, int button) {
	
	glutSetCursor(GLUT_CURSOR_BOTTOM_RIGHT_CORNER); 
	dragging = true; 

	dragX = (floor(((float) x / 20)) * 20);
	dragY = (floor(((float) y / 20)) * 20);

}

void resizeControl::onRelease(int x, int y, int button) {
	glutSetCursor(GLUT_CURSOR_LEFT_ARROW);

	dragging = false; 

}

void resizeControl::onReleaseOutside(int x, int y, int button) {
	glutSetCursor(GLUT_CURSOR_LEFT_ARROW);

	dragging = false; 

	if (focus.focused != NULL){
		editor->updateSize((newWidth - focus.focused->width), (newHeight - focus.focused->height));
	}

}

void resizeControl::update() {}

void resizeControl::draw() {

	setControl(); 

	if (dragging) {

		if (focus.focused != NULL){
			ofNoFill(); 
			ofSetColor(255, 255, 255); ;

			newWidth = focus.focused->width + (dragX - (focus.focused->x + focus.focused->width));
			newHeight = focus.focused->height + (dragY - (focus.focused->y + focus.focused->height));

			ofRect(focus.focused->x, focus.focused->y, newWidth, newHeight); 

		}
	}

	ofEnableAlphaBlending();

		glPushMatrix();

			ofFill(); 
				ofSetColor(0xe3e3e3); 
				ofRect(x, y, 5, 5); 
			ofNoFill(); 

		glPopMatrix();

	ofDisableAlphaBlending();

}