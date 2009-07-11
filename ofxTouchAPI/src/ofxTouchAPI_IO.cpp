/***********************************************************************
 
 Copyright (c) 2009 Dimitri Diakopoulos, http://www.dimitridiakopoulos.com/
 === Google Summer of Code 2009 - NUI Group === 

 Portions Copyright (c) 2008, 2009 Memo Atkens, http://www.memo.tv/ 
 -> Based on ofxMSAInteractiveObject

 [BSD License Here]

*************************************************************************/ 

#include "ofMain.h"
#include "ofxTouchAPI_IO.h"

// ================================================================= CTor
ofxTouchAPI_IO::ofxTouchAPI_IO() {

	_mouseOver	= false;
	_mouseDown	= false;

	enabled		= true;
	verbose		= true;
	
	enableAllEvents(); 
}

// ================================================================= DTor
ofxTouchAPI_IO::~ofxTouchAPI_IO() {
	disableAllEvents();
}

void ofxTouchAPI_IO::killMe() {
	delete this;
}


// ================================================================= Events
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

/* Function to find ID in a list of touches, update x and y
bool ofxTouchAPI_IO::isTouchActive(int ID)
{
	
	vector<i>::iterator result;

	result = find(touchlist.begin(), touchlist.end(), ID); 
		
	if (result == touchlist.end())
		return false; 
	else
		return true; 
}
*/ 

int ofxTouchAPI_IO::getTouches(){
	return touchlist.size(); 
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

	int x = tuioCursor.getX();
	int y = tuioCursor.getY();
	int ID = tuioCursor.getFingerId();

	if(verbose) printf("ofxTouchAPI_IO::_tuioAdded(x: %i, y: %i)\n", x, y);

	// If the touch is over the object
	if(HitTest::rectangle(x, y, this->width, this->height, this->x, this->y)) {
		touchlist.push_back(tuioCursor);
		onTouchDown(touchlist); 
	}

}

void ofxTouchAPI_IO::_tuioRemoved(ofxTuioCursor &tuioCursor){
	
	int x = tuioCursor.getX();
	int y = tuioCursor.getY();
	int ID = tuioCursor.getFingerId();

	if(verbose) printf("ofxTouchAPI_IO::_tuioRemoved(x: %i, y: %i)\n", x, y);

	// If the touch is over the object
	if(HitTest::rectangle(x, y, this->width, this->height, this->x, this->y)) {

		// is the touch in our list of touches? 
		//if (isTouchActive(ID)) {
		//	onTouchUp(touchlist);
		//}
	}

	//else{
	//	// if any touch is that had at one point touched this object, release it
	//	onTouchUpOutside(touchlist);  
	//}

}

void ofxTouchAPI_IO::_tuioUpdated(ofxTuioCursor &tuioCursor){
	
	int x = tuioCursor.getX();
	int y = tuioCursor.getY();
	int ID = tuioCursor.getFingerId();

	printf("Number of Touches: %i \n", getTouches());  

	if(verbose) printf("ofxTouchAPI_IO::_tuioUpdated(x: %i, y: %i, ID: %i)\n", x, y, ID);

	// If the touch is over the object
	if(HitTest::rectangle(x, y, this->width, this->height, this->x, this->y)) {

		// is the touch in our list of touches? 
		//if (isTouchActive(ID)) {
		//	onTouchMove(touchlist); 
		//}
	
		// if finger was not originally down on object, make it so
		// alternate behavior: call onTouchMove right after
		//else {
		//	touchlist.push_back(tuioCursor);
		//	//onTouchMove(touchlist); 
		//}
		
	}

}
