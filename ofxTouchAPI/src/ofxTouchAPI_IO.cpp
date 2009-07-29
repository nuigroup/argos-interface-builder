/***********************************************************************
 
 Copyright (c) 2009 Dimitri Diakopoulos, http://www.dimitridiakopoulos.com/
 === Google Summer of Code 2009 - NUI Group === 

 Portions Copyright (c) 2008, 2009 Memo Atkens, http://www.memo.tv/
 -> Based on ofxMSAInteractiveObject

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

#include "ofMain.h"
#include "ofxTouchAPI_IO.h"

// ================================================================= CTor
ofxTouchAPI_IO::ofxTouchAPI_IO() {

	_mouseOver	= false;
	_mouseDown	= false;

	enabled		= true;
	verbose		= false;
	
	enableAllEvents(); 
}

// ================================================================= DTor
ofxTouchAPI_IO::~ofxTouchAPI_IO() {
	disableAllEvents();
}

void ofxTouchAPI_IO::killMe() {
	delete this;
}


// ================================================================= Events Enablers/Disablers
void ofxTouchAPI_IO::enableAllEvents() {
	enableMouseEvents();
	enableKeyEvents();
	enableAppEvents();
	enableTouchEvents(); 
}

void ofxTouchAPI_IO::disableAllEvents() {
	disableMouseEvents();
	disableKeyEvents();
	disableAppEvents();
	disableTouchEvents(); 
}


void ofxTouchAPI_IO::enableMouseEvents() {
	ofAddListener(ofEvents.mousePressed, this, &ofxTouchAPI_IO::_mousePressed);
	ofAddListener(ofEvents.mouseMoved, this, &ofxTouchAPI_IO::_mouseMoved);
	ofAddListener(ofEvents.mouseDragged, this, &ofxTouchAPI_IO::_mouseDragged);
	ofAddListener(ofEvents.mouseReleased, this, &ofxTouchAPI_IO::_mouseReleased);
}

void ofxTouchAPI_IO::disableMouseEvents() {
	ofRemoveListener(ofEvents.mousePressed, this, &ofxTouchAPI_IO::_mousePressed);
	ofRemoveListener(ofEvents.mouseMoved, this, &ofxTouchAPI_IO::_mouseMoved);
	ofRemoveListener(ofEvents.mouseDragged, this, &ofxTouchAPI_IO::_mouseDragged);
	ofRemoveListener(ofEvents.mouseReleased, this, &ofxTouchAPI_IO::_mouseReleased);
}

void ofxTouchAPI_IO::enableKeyEvents() {
	ofAddListener(ofEvents.keyPressed, this, &ofxTouchAPI_IO::_keyPressed);
	ofAddListener(ofEvents.keyReleased, this, &ofxTouchAPI_IO::_keyReleased);
}

void ofxTouchAPI_IO::disableKeyEvents() {
	ofRemoveListener(ofEvents.keyPressed, this, &ofxTouchAPI_IO::_keyPressed);
	ofRemoveListener(ofEvents.keyReleased, this, &ofxTouchAPI_IO::_keyReleased);
}

void ofxTouchAPI_IO::enableAppEvents() {
	ofAddListener(ofEvents.setup, this, &ofxTouchAPI_IO::_setup);
	ofAddListener(ofEvents.update, this, &ofxTouchAPI_IO::_update);
	ofAddListener(ofEvents.draw, this, &ofxTouchAPI_IO::_draw);
	ofAddListener(ofEvents.exit, this, &ofxTouchAPI_IO::_exit);
}

void ofxTouchAPI_IO::disableAppEvents() {
	ofRemoveListener(ofEvents.setup, this, &ofxTouchAPI_IO::_setup);
	ofRemoveListener(ofEvents.update, this, &ofxTouchAPI_IO::_update);
	ofRemoveListener(ofEvents.draw, this, &ofxTouchAPI_IO::_draw);
	ofRemoveListener(ofEvents.exit, this, &ofxTouchAPI_IO::_exit);
}

void ofxTouchAPI_IO::enableTouchEvents(){
	ofAddListener(tuio.cursorAdded,this,&ofxTouchAPI_IO::_tuioAdded);
	ofAddListener(tuio.cursorRemoved,this,&ofxTouchAPI_IO::_tuioRemoved);
	ofAddListener(tuio.cursorUpdated,this,&ofxTouchAPI_IO::_tuioUpdated);
}

void ofxTouchAPI_IO::disableTouchEvents(){
	ofRemoveListener(tuio.cursorAdded,this,&ofxTouchAPI_IO::_tuioAdded);
	ofRemoveListener(tuio.cursorRemoved,this,&ofxTouchAPI_IO::_tuioRemoved);
	ofRemoveListener(tuio.cursorUpdated,this,&ofxTouchAPI_IO::_tuioUpdated);
}


// ================================================================= IO Functions
void ofxTouchAPI_IO::setPos(float _x, float _y) {
	x = _x;
	y = _y;
}

void ofxTouchAPI_IO::setSize(float _w, float _h) {
	width = _w;
	height = _h;
}

void ofxTouchAPI_IO::setPosAndSize(float _x, float _y, float _w, float _h) {
	setPos(_x, _y);
	setSize(_w, _h);
}

bool ofxTouchAPI_IO::isMouseOver() {
	return _mouseOver;
}

bool ofxTouchAPI_IO::isMouseDown() {
	return _mouseDown;
}

int ofxTouchAPI_IO::getMouseX() {
	return _mouseX;
}

int ofxTouchAPI_IO::getMouseY() {
	return _mouseY;
}

int ofxTouchAPI_IO::getTouches(){
	return touchList.size(); 
}

bool ofxTouchAPI_IO::isBeingTouched(){
	if (touchList.size() >= 1)
		return true; 
}


int ofxTouchAPI_IO::getLastMouseButton() {
	return _mouseButton;
}

void ofxTouchAPI_IO::_setup(ofEventArgs &e) {
	if(!enabled) return;

	setup();
}

void ofxTouchAPI_IO::_update(ofEventArgs &e) {
	if(!enabled) return;
	
	// check to see if object has moved, and if so update mouse events
	if(oldRect.x != this->x || oldRect.y != this->y || oldRect.width != this->width ||oldRect.height != this->height) {
		ofMouseEventArgs e;
		e.button = _mouseButton;
		e.x = _mouseX;
		e.y = _mouseY;
		if(_mouseDown) _mouseDragged(e);	
		else _mouseMoved(e);
		
		oldRect =  (ofRectangle) (*this);
	}

	update();
}

void ofxTouchAPI_IO::_draw(ofEventArgs &e) {
	if(!enabled) return;

	draw();
}

void ofxTouchAPI_IO::_exit(ofEventArgs &e) {
	if(!enabled) return;

	exit();
}

// ================================================================= Events
void ofxTouchAPI_IO::_mouseMoved(ofMouseEventArgs &e) {
	int x = e.x;
	int y = e.y;
	int button = e.button;
	if(verbose) printf("ofxTouchAPI_IO::_mouseMoved(x: %i, y: %i)\n", x, y);
	if(!enabled) return;
	
	_mouseX = x;
	_mouseY = y;
	
	// If the mouse is over the object
	if(HitTest::rectangle(x, y, this->width, this->height, this->x, this->y)) {
		if (!_mouseOver) {				// if wasn't over previous frame
			onRollOver(x, y);			// call onRollOver
			_mouseOver = true;			// update flag
		}
		onMouseMove(x, y);				// and trigger onMouseMove
	} 

	// If the mouse is not over the object (but the flag is still true from previous frame)
	else if (_mouseOver) {			
		onRollOut();					// call onRollOut
		_mouseOver = false;				// update flag
	}
}


void ofxTouchAPI_IO::_mousePressed(ofMouseEventArgs &e) {
	int x = e.x;
	int y = e.y;
	int button = e.button;
	
	if(verbose) printf("ofxTouchAPI_IO::_mousePressed(x: %i, y: %i, button: %i)\n", x, y, button);
	if(!enabled) return;

	_mouseX = x;
	_mouseY = y;
	_mouseButton = button;
	
	// If the mouse is over the object
	if(HitTest::rectangle(x, y, this->width, this->height, this->x, this->y)) {

		if(!_mouseDown) {					// if wasn't down previous frame
			onPress(x, y, button);			// call onPress
			_mouseDown = true;				// update flag
		}
	} 
	
	// If the mouse is not over the object... do nothing. 
	else {}
}

void ofxTouchAPI_IO::_mouseDragged(ofMouseEventArgs &e) {
	int x = e.x;
	int y = e.y;
	int button = e.button;
	
	if(verbose) printf("ofxTouchAPI_IO::_mouseDragged(x: %i, y: %i, button: %i)\n", x, y, button);
	if(!enabled) return;

	_mouseX = x;
	_mouseY = y;
	_mouseButton = button;

	// If the mouse is over the object
	if(HitTest::rectangle(x, y, this->width, this->height, this->x, this->y)) {
		if(!_mouseOver) {						// if wasn't over previous frame
			//onPress(x, y);					// call onPress - alternate behavior
			_mouseOver = true;					// update flag
		}
		onDragOver(x, y, button);				// and trigger onDragOver
	} 
	
	else {
		if(_mouseOver) {						// if mouse is not over the object, but the flag is true (From previous frame)
			onRollOut();						// call onRollOut
			_mouseOver = false;					// update flag
		}
		if(_mouseDown) {
			onDragOutside(x, y, button);
		}
	}
}

void ofxTouchAPI_IO::_mouseReleased(ofMouseEventArgs &e) {
	int x = e.x;
	int y = e.y;
	int button = e.button;
	
	if(verbose) printf("ofxTouchAPI_IO::_mouseReleased(x: %i, y: %i, button: %i)\n", x, y, button);
	if(!enabled) return;

	_mouseX = x;
	_mouseY = y;
	_mouseButton = button;
	
	// If the mouse is over the object
	if(HitTest::rectangle(x, y, this->width, this->height, this->x, this->y)) {
		onRelease(x, y, button);
	} 

	else {
		if(_mouseDown) onReleaseOutside(x, y, button);
	}

	_mouseDown = false;
}


void ofxTouchAPI_IO::_keyPressed(ofKeyEventArgs &e) {

	int key = e.key;

	if(verbose) printf("ofxTouchAPI_IO::_keyPressed(key: %i)\n", key);

	if(!enabled) return;
	keyPressed(key);
}

void ofxTouchAPI_IO::_keyReleased(ofKeyEventArgs &e) {

	int key = e.key;	

	if(verbose) printf("ofxTouchAPI_IO::_keyReleased(key: %i)\n", key);

	if(!enabled) return;
	keyReleased(key);
}

void ofxTouchAPI_IO::_tuioAdded(ofxTuioCursor &tuioCursor){

	int x = tuioCursor.getX() * ofGetWidth();
	int y = tuioCursor.getY() * ofGetHeight(); 
	int ID = tuioCursor.getFingerId();

	if(verbose) printf("ofxTouchAPI_IO::_tuioAdded(x: %i, y: %i)\n", x, y);

	if(!enabled) return;

	if(HitTest::rectangle(x, y, this->width, this->height, this->x, this->y)) {
	    onTouchDown(x, y, ID);	
		touchList.push_back(ID);
	}

}

void ofxTouchAPI_IO::_tuioRemoved(ofxTuioCursor &tuioCursor){
	
	int x = tuioCursor.getX() * ofGetWidth();
	int y = tuioCursor.getY() * ofGetHeight(); 
	int ID = tuioCursor.getFingerId();

	if(verbose) printf("ofxTouchAPI_IO::_tuioRemoved(x: %i, y: %i)\n", x, y);

	if(!enabled) return;

	// If touch is inside object when it's removed
	if(HitTest::rectangle(x, y, this->width, this->height, this->x, this->y)) {
		if(touchList.size() > 0){
			onTouchUp(x, y, ID);
		}
	} 
	
	// If touch is outside the object when it's removed
	else {

		onTouchUpOutside(x, y, ID); 

		std::list<int>::iterator touchid;
		touchid = find(touchList.begin(), touchList.end(), ID);
		if(touchid != touchList.end()) touchList.remove(ID);
	}

}

void ofxTouchAPI_IO::_tuioUpdated(ofxTuioCursor &tuioCursor){
	
	int x = tuioCursor.getX() * ofGetWidth();
	int y = tuioCursor.getY() * ofGetHeight(); 
	int ID = tuioCursor.getFingerId();

	if(verbose) printf("Number of Touches: %i \n", getTouches());  
	if(verbose) printf("ofxTouchAPI_IO::_tuioUpdated(x: %i, y: %i, ID: %i)\n", x, y, ID);

	if(!enabled) return;

	// If touch is moving inside an object
	if(HitTest::rectangle(x, y, this->width, this->height, this->x, this->y)) {

		if(touchList.size()){
			std::list<int>::iterator touchid;
			touchid = find(touchList.begin(), touchList.end(), ID);
			if(touchid==touchList.end()) touchList.push_back(ID);
			
			onTouchMove(x, y, ID);		
		} else {
			onTouchMoveOver(x, y, ID);
			touchList.push_back(ID);
		}
	} 
	
	// If the touch moves outside an object
	else {
		if(touchList.size()){
			if(touchList.size() <= 1){
				std::list<int>::iterator touchid;
				touchid = find(touchList.begin(), touchList.end(), ID);
				if(touchid!=touchList.end()){
					onTouchMoveOutside(x, y, ID);
					touchList.remove(ID);
				}
			} else {
				std::list<int>::iterator touchid;
				touchid = find(touchList.begin(), touchList.end(), ID);
				if(touchid!=touchList.end()) touchList.remove(ID);
			}
		}
	}
}
