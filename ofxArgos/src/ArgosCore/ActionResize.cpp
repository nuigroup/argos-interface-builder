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

#include "ActionResize.h"
#include "EditorCore.h"

actionResize::actionResize(EditorPanel *ed) : ofxArgosUI_Control("actionResize") {
	controlType = "actionResize";
	editor = ed;
	dragging = false; 
	canfocus = false; 
	drawCorner = false; 
}

void actionResize::setControl() {
	if (focus.focused != NULL){
		setPos(focus.focused->getPropertyInt("x", 0) + focus.focused->getPropertyInt("w", 0) + 5, focus.focused->getPropertyInt("y", 0) + focus.focused->getPropertyInt("h", 0) + 5); 
		setSize(15,15);
	}
}

void actionResize::onRollOver(int x, int y) {
	glutSetCursor(GLUT_CURSOR_BOTTOM_RIGHT_CORNER);
	drawCorner = true; 
}

void actionResize::onRollOut() {
	glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
	drawCorner = false; 
}

void actionResize::onDragOutside(int x, int y, int button) {
	
	glutSetCursor(GLUT_CURSOR_BOTTOM_RIGHT_CORNER); 
	dragging = true; 

	dragX = (floor(((float) x / 10)) * 10);
	dragY = (floor(((float) y / 10)) * 10);

	drawCorner = true;

}

void actionResize::onRelease(int x, int y, int button) {
	glutSetCursor(GLUT_CURSOR_LEFT_ARROW);

	dragging = false; 

	drawCorner = false; 

}

void actionResize::onReleaseOutside(int x, int y, int button) {
	glutSetCursor(GLUT_CURSOR_LEFT_ARROW);

	dragging = false; 

	if (focus.focused != NULL){

		//Bounds checking
		if ( (newWidth >= 20) && (newHeight >= 20) )
			editor->newSize(newWidth, newHeight);
		else
			editor->newSize(20, 20);
	}

	drawCorner = false; 

}

void actionResize::update() {}

void actionResize::draw() {

	setControl(); 
	
	editor->isResizing = false; 

	if (dragging && !editor->isMoving) {

		editor->isResizing = true; 

		if (focus.focused !=  NULL){

			ofNoFill(); 

			ofSetColor(255, 255, 255); 

			newWidth = focus.focused->getPropertyInt("w", 0) + (dragX - (focus.focused->getPropertyInt("x", 0) + focus.focused->getPropertyInt("w", 0))); 
			newHeight = focus.focused->getPropertyInt("h", 0) + (dragY - (focus.focused->getPropertyInt("y", 0) + focus.focused->getPropertyInt("h", 0))); 

			ofRect(focus.focused->getPropertyInt("x", 0), focus.focused->getPropertyInt("y", 0), newWidth, newHeight); 

		}
	}

	if (drawCorner){
		glPushMatrix();
			ofFill(); 
				ofSetColor(255, 255, 255); 
				ofRect(this->x, this->y, 5, 5); 
			ofNoFill(); 
		glPopMatrix();
	}


}