/***********************************************************************
 
 Copyright (c) 2009 Dimitri Diakopoulos, http://argos.dimitridiakopoulos.com/
 === Google Summer of Code 2009 - NUI Group === 

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

#include "Editor.h"

bool e_apply;
bool e_cancel;
bool e_reset;

string e_label;
string e_x;
string e_y;
string e_w;
string e_h; 

Argos_editor::Argos_editor() {}

void Argos_editor::init(ofxArgosUI &gui){

		this->gui  = &gui; 

		editor = gui.addPanel("Element Editor", 10, 20, 240, ofGetHeight()-30); 
		
		// +++ Basic Properties 
		editor->addTextField("Label:", 10, 30, 190, 20, &e_label); 
		editor->addTextField("X:", 10, 70, 40, 20, &e_x); 
		editor->addTextField("Y:", 60, 70, 40, 20, &e_y); 
		editor->addTextField("W:", 110, 70, 40, 20, &e_w); 
		editor->addTextField("H:", 160, 70, 40, 20, &e_h); 

		editor->addTextField("OSC Address", 10, 110, 100, 20, &e_h); 

		// +++ Apply/Cancel/Reset Buttons
		editor->addButton("Apply", 10,(editor->height - 35), 70, 25, &e_apply);
		editor->addButton("Cancel", 85,(editor->height - 35), 70, 25, &e_cancel);
		editor->addButton("Reset", 160,(editor->height - 35), 70, 25, &e_reset);
}

void Argos_editor::update(){

	if (focus.focused != NULL){
		e_x = focus.focused->x ; 
	}

}