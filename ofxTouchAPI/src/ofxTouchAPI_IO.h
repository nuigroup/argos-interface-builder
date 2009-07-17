/***********************************************************************
 
 Copyright (c) 2009 Dimitri Diakopoulos, http://www.dimitridiakopoulos.com/
 === Google Summer of Code 2009 - NUI Group === 

 Portions Copyright (c) 2008, 2009 Memo Atkens, http://www.memo.tv/
 -> Based on ofxMSAInteractiveObject

 [BSD License Here]

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

	bool isTouchActive(int ID);						// Asks if the current finger ID is touching the object
	int  getTouches();								// returns the number of current fingers on an object
	void addTouch(ofxTuioCursor &tuioCursor);		// Adds active touch on the object
	void updateTouch(ofxTuioCursor &tuioCursor);	// Updates an active touch on the object
	void removeTouch(ofxTuioCursor &tuioCursor);	// Removes an inactive touch on the object


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
	virtual void onTouchDown(vector<ofxTuioCursor> touchlist)				{}		// called when a touch down occurs on an object
	virtual void onTouchUp(vector<ofxTuioCursor> touchlist)				{}		// called when a touch up occurs on an object
	virtual void onTouchUpOutside(vector<ofxTuioCursor> touchlist)			{}		// called when a touch up occurs after having pressed on an object
	virtual void onTouchMove(vector<ofxTuioCursor> touchlist)				{}		// called when touch moves inside the object
	virtual void onTouchMoveOutside(vector<ofxTuioCursor> touchlist)		{}		// called when touch release outside of an object after being pressed on an object

	// ================================================================= Events
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

	vector<ofxTuioCursor> touchlist; 

	ofRectangle	oldRect;
};


