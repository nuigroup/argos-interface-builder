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
string e_osc; 

Argos_editor::Argos_editor() {}

void Argos_editor::init(ofxArgosUI &gui){

		// Give the editor access to the GUI
		this->gui  = &gui; 

		// Add a panel to the GUI for the editor 
		editor = gui.addPanel("Element Editor", 10, 20, 210, 180); 
		
		// Populate the editor panel with controls for editing
		populate(); 

		// Prevent the editor from editing itself! 
		editor->lockPanel();
	
		// Reset text inputs so they can focus;
		label->canfocus = true; 
		x->canfocus = true; 
		y->canfocus = true; 
		w->canfocus = true; 
		h->canfocus = true;
		osc->canfocus = true;

}

void Argos_editor::update(){

	if (focus.focused != NULL){

		if (focus.loaded == false){
			loadProperties(); 
			setProperties(); 
		}

		updateProperties(); 
	}
	
}

void Argos_editor::populate(){

		label = editor->addTextField("Label:", 10, 30, 190, 20, &e_label); 

		x = (editor->addTextField("X:", 10, 70, 40, 20, &e_x)); 
		y = (editor->addTextField("Y:", 60, 70, 40, 20, &e_y)); 
		w = (editor->addTextField("W:", 110, 70, 40, 20, &e_w)); 
		h = (editor->addTextField("H:", 160, 70, 40, 20, &e_h));

		osc = (editor->addTextField("OSC Address", 10, 110, 190, 20, &e_osc));

		//apply = (editor->addButton("Apply", 10,(editor->height - 35), 70, 25, &e_apply));
		cancel = (editor->addButton("Cancel", 70,(editor->height - 35), 70, 25, &e_cancel));
		//reset = (editor->addButton("Reset", 160,(editor->height - 35), 70, 25, &e_reset));
}


void Argos_editor::loadProperties(){

	focus.loaded = true;

	//cout << focus.focused->getType(); 

	e_label = focus.focused->name;
	e_x = toStr(focus.focused->x);
	e_y = toStr(focus.focused->y);
	e_w = toStr(focus.focused->width);
	e_h = toStr(focus.focused->height);
	e_osc = focus.focused->OSCaddress;

}

void Argos_editor::setProperties(){
	
	label->setInput(e_label); 
	x->setInput(e_x); 
	y->setInput(e_y); 
	w->setInput(e_w); 
	h->setInput(e_h); 
	osc->setInput(e_osc); 

}

void Argos_editor::updateProperties(){

	focus.focused->name = e_label; 
	focus.focused->x = atof(e_x.c_str()); 
	focus.focused->y = atof(e_y.c_str());
	focus.focused->width = atof(e_w.c_str());
	focus.focused->height = atof(e_h.c_str());
	focus.focused->OSCaddress = e_osc; 

}



// TODO: Put this in a utility class: 
// Takes a number and outputs to string. 
string Argos_editor::toStr(float input){
	
	// Clear the stream & reset. 
	ostr.clear(); 
	ostr.str("");  

	// Put data to stream
	ostr << input; 

	// Output as a string
	return ostr.str(); 
}