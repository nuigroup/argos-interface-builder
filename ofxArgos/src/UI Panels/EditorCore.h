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
#pragma once

#include "ofxArgosUI.h"
#include "EditorActions.h"

class EditorPanel {

public:

	EditorPanel();
	
	// Put this in a more appropriate place
	std::ostringstream ostr;

	ofxArgosUI				*gui; 
	ofxArgosUI_Panel		*editor;

	resizeControl			*rControl; 

	ofxArgosUI_Button		*editing; 
	ofxArgosUI_Button		*cancel;
	ofxArgosUI_TextField	*label;
	ofxArgosUI_TextField	*x;
	ofxArgosUI_TextField	*y;
	ofxArgosUI_TextField	*w;
	ofxArgosUI_TextField	*h;
	ofxArgosUI_TextField	*osc;

	bool e_apply;
	bool e_cancel;
	bool e_reset;

	string e_label;
	string e_x;
	string e_y;
	string e_w;
	string e_h; 
	string e_osc; 

	void init(ofxArgosUI &gui); 
	void populate(); 
	void update(); 

	void clearProperties(); 
	void loadProperties();
	void setProperties();
	void updateProperties();

	void removeControl();

	void updateX(int direction);
	void updateY(int direction);

	void updateSize(int width, int height);

	string toStr(float input);

};