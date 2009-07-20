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

	THIS SOFTWARE IS PROVIDED BY THE ARGOS PROJECT "AS IS" AND ANY EXPRESS OR IMPLIED 
	WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF 
	MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
	EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
	SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
	PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
	PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
	LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
	NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
	EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. 

*************************************************************************/ 

#pragma once

#include "ofMain.h"
#include "ofxTouchAPI.h"

class ofxTouchAPI_IO : public ofRectangle {

public:

	bool		enabled;		// set to false to disable all events (temporarily) 
	bool		verbose;
	
	ofxTouchAPI_IO();			// constructor
	virtual ~ofxTouchAPI_IO();	// destructor
	
	// ================================================================= Event Enable/Disable
	void enableAllEvents();				// enable all event callbacks (default) 
	void disableAllEvents();			// disable all event callbacks
	
	void enableMouseEvents();			// call this if object should receive mouse events
	void disableMouseEvents();			// call this if object doesn't need to receive mouse events
	
	void enableKeyEvents();				// call this if object should receive key events
	void disableKeyEvents();			// call this if object doesn't need to receive key events 

	void enableTouchEvents();			// call this if object should recieve TUIO
	void disableTouchEvents();			// call this if object doesn't need to receive TUIO
	
	void enableAppEvents();				// call this if object should update/draw automatically	(default)
	void disableAppEvents();			// call this if object doesn't need to update/draw automatically


	// ================================================================= Setters
	void setPos(float _x, float _y);								// set position of object
	void setSize(float _w, float _h);								// set size of object
	void setPosAndSize(float _x, float _y, float _w, float _h);		// set pos and size in one


	// ================================================================= Getters
	bool isMouseOver();					// returns true if mouse is over object (based on position and size)
	bool isMouseDown();					// returns true if mouse button is down and over object (based on position and size)
	int	 getMouseX();					// returns mouse X (in screen coordinates)
	int  getMouseY();					// returns mouse Y (in screen coordinates)
	int  getLastMouseButton();			// returns last mouse button to have activity

	bool isTouchActive(int ID);			// Asks if the current finger ID is touching the object
	int  getTouches();					// returns the number of current fingers on an object

	// ================================================================= Updater Methods
	virtual void setup()	{}	// called when app starts
	virtual void update()	{}	// called every frame to update object
    virtual void draw()		{}	// called every frame to draw object
	virtual void exit()		{}	// called when app quits
	void killMe();				// if your object is a pointer, and you are done with it, explicitly call this


	// ================================================================= Mouse States
	virtual void onRollOver(int x, int y)					{}		// called when mouse enters object x, y, width, height
	virtual void onRollOut()								{}		// called when mouse leaves object x, y, width, height
	virtual void onMouseMove(int x, int y)					{}		// called when mouse moves while over object x, y, width, height
	virtual void onDragOver(int x, int y, int button)		{}		// called when mouse moves while over object and button is down
	virtual void onDragOutside(int x, int y, int button)	{}		// called when mouse moves while outside the object after being clicked on it
	virtual void onPress(int x, int y, int button)			{}		// called when mouse presses while over object
	virtual void onRelease(int x, int y, int button)		{}		// called when mouse releases while over object
	virtual void onReleaseOutside(int x, int y, int button)	{}		// called when mouse releases outside of object after being pressed on object

	// ================================================================= Key States
	virtual void keyPressed(int key)	{}
	virtual void keyReleased(int key)	{}


	// ================================================================= Touch States
	virtual void onTouchDown(float x, float y, int ID)			{}		// called when a touch down occurs on an object
	virtual void onTouchUp(float x, float y, int ID)			{}		// called when a touch up occurs on an object
	virtual void onTouchUpOutside(float x, float y, int ID)		{}		// called when a touch up occurs after having pressed on an object
	virtual void onTouchMove(float x, float y, int ID)			{}		// called when touch moves inside an object
	virtual void onTouchMoveOver(float x, float y, int ID)		{}		// called when touch moves outside to inside an object
	virtual void onTouchMoveOutside(float x, float y, int ID)	{}		// called when touch moves from inside to outside an object

	// ================================================================= Incoming Events
	void _setup(ofEventArgs &e);
	void _update(ofEventArgs &e);
    void _draw(ofEventArgs &e);
	void _exit(ofEventArgs &e);

	void _mouseMoved(ofMouseEventArgs &e);
	void _mousePressed(ofMouseEventArgs &e);	
	void _mouseDragged(ofMouseEventArgs &e);	
	void _mouseReleased(ofMouseEventArgs &e);

	void _keyPressed(ofKeyEventArgs &e);
	void _keyReleased(ofKeyEventArgs &e);

	void _tuioAdded(ofxTuioCursor &tuioCursor);    
	void _tuioRemoved(ofxTuioCursor &tuioCursor); 
	void _tuioUpdated(ofxTuioCursor &tuioCursor); 
	
protected:

	int			_mouseX, _mouseY, _mouseButton;
	bool		_mouseOver;
	bool		_mouseDown;

	std::list<int> touchList;

	ofRectangle	oldRect;
};