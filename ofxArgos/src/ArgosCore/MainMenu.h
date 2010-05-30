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
#include "StateManager.h"

/***********************************************************************
*	Main Menu... 
*************************************************************************/ 

class MainMenu : public ofxArgosUI_Panel {

public:

	ofxArgosUI			*gui; 
	ofxArgosUI_Panel	*menupanel;

	ofxArgosUI_Button	*hover; 

	bool				show; 

	MainMenu() : ofxArgosUI_Panel("Main Menu", ofGetWidth() - 110, 0, 100, 25)  {}

	void init(ofxArgosUI &gui){

		//enableAllEvents();


		this->gui = &gui; 

		gui.addControl(this); 

		this->setCornerRadius(0);
		this->enableAllInput(); 
	
		hover = this->addButton("Edit", this->x, this->y, 100, 10, &show);

	}

	void onRollover(int x, int y)	{
		cout << "onRollOver \n"; 
	}

	void onMouseMove(int x, int y){
		cout << "onMouseMove \n"; 
	}

};