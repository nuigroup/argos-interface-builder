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

#include "ActionMove.h"
#include "EditorCore.h"

actionMove::actionMove(EditorPanel *ed) : ofxArgosUI_Control("actionMove") {
	controlType = "actionMove";
	editor = ed;
	dragging = false; 
}

void actionMove::setControl() {
	if (focus.focused != NULL){
		setPos(focus.focused->getPropertyInt("x", 0), focus.focused->getPropertyInt("y", 0)); 
		setSize(focus.focused->getPropertyInt("w", 0), focus.focused->getPropertyInt("h", 0));
	}
}

void actionMove::onRollOver(int x, int y) {
	glutSetCursor(GLUT_CURSOR_INFO); 	
}

void actionMove::onRollOut() {
	glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
}

void actionMove::onDragOver(int x, int y, int button) {
	
	glutSetCursor(GLUT_CURSOR_INFO); 

	dragging = true; 

	dragX = (floor(((float) x / 20)) * 20);
	dragY = (floor(((float) y / 20)) * 20);
}

void actionMove::onDragOutside(int x, int y, int button) {
	
	glutSetCursor(GLUT_CURSOR_INFO); 

	dragging = true; 

	dragX = (floor(((float) x / 20)) * 20);
	dragY = (floor(((float) y / 20)) * 20);
}

void actionMove::onRelease(int x, int y, int button) {

	glutSetCursor(GLUT_CURSOR_LEFT_ARROW);

	if (focus.focused != NULL && dragging == true){
		if ( (newX >= 0) && (newY >= 0))
			editor->newPosition(newX, newY); 
	}

	dragging = false; 
}

void actionMove::onReleaseOutside(int x, int y, int button) {

	glutSetCursor(GLUT_CURSOR_LEFT_ARROW);

	dragging = false; 

	if (focus.focused != NULL){
		if ( (newX >= 0) && (newY >= 0))
			editor->newPosition(newX, newY); 
	}
}

void actionMove::update() {}

void actionMove::draw() {

	setControl(); 

	editor->isMoving = false; 

	if (dragging && !editor->isResizing) {

		editor->isMoving = true; 

		if (focus.focused != NULL){
			ofNoFill(); 
			ofSetColor(255, 255, 255); ;

			newX = dragX;
			newY = dragY; 

			ofRect(newX, newY, width, height); 

		}
	}
}