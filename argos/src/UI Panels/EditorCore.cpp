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

#include "EditorCore.h"

const float gridsize = 20.00; 

EditorPanel::EditorPanel() {}

void EditorPanel::init(ofxArgosUI &gui){

		// Give the editor access to the GUI
		this->gui  = &gui; 

		// Give actions access to the edtior
		rControl = new resizeControl(this); 

		// Add a panel to the GUI for the editor 
		editor = gui.addPanel("Widget Editor", 10, 20, 210, 180); 
		
		// Populate the editor panel with controls for editing
		populate(); 

		// Prevent the editor from being able to focus itself
		editor->lockPanel();
	
		// But, Reset text inputs so they _can_ focus;
		label->canfocus = true; 
		x->canfocus		= true; 
		y->canfocus		= true; 
		w->canfocus		= true; 
		h->canfocus		= true;
		osc->canfocus	= true;

}

void EditorPanel::update(){
	if (stateManager::editing) {
		if (focus.focused != NULL){
			if (focus.loaded == false){
				loadProperties();
				setProperties();
			}
			updateProperties(); 
			rControl->enableAppEvents(); 
			rControl->draw(); 
		}	
	}

	else {
		// Find out why resizeControl is being drawn elsewhere... 
		rControl->disableAppEvents();
		clearProperties();
	}
}

void EditorPanel::populate(){

		label = editor->addTextField("Label:", 10, 30, 190, 20, &e_label); 

		x = (editor->addTextField("X:", 10, 70, 40, 20, &e_x)); 
		y = (editor->addTextField("Y:", 60, 70, 40, 20, &e_y)); 
		w = (editor->addTextField("W:", 110, 70, 40, 20, &e_w)); 
		h = (editor->addTextField("H:", 160, 70, 40, 20, &e_h));

		osc = (editor->addTextField("OSC Address", 10, 110, 190, 20, &e_osc));

		editing = (editor->addButton("Editing", 20, (editor->height - 35), 80, 20, &stateManager::editing)); 
			editing->setToggleMode(true);
		cancel = (editor->addButton("Cancel", 110,(editor->height - 35), 80, 20, &e_cancel));
}


// Loads the editor's internal strings
void EditorPanel::loadProperties(){

	focus.loaded = true;

	e_label = focus.focused->name;
	e_x = toStr(focus.focused->x);
	e_y = toStr(focus.focused->y);
	e_w = toStr(focus.focused->width);
	e_h = toStr(focus.focused->height);
	e_osc = focus.focused->OSCaddress;

}
// Sets the editors internal strings to the textboxes'
void EditorPanel::setProperties(){
	
	label->setInput(e_label); 
	x->setInput(e_x); 
	y->setInput(e_y); 
	w->setInput(e_w); 
	h->setInput(e_h); 
	osc->setInput(e_osc); 

}

// Updates control with value of local text boxes. 
void EditorPanel::updateProperties(){

	// Input range checking? 
	focus.focused->name = e_label; 
	focus.focused->x = atof(e_x.c_str()); 
	focus.focused->y = atof(e_y.c_str());
	focus.focused->width = atof(e_w.c_str());
	focus.focused->height = atof(e_h.c_str());
	focus.focused->OSCaddress = e_osc; 

}

void EditorPanel::clearProperties(){
	
	e_label = "";
	e_x = "";
	e_y = "";
	e_w = "";
	e_h = "";
	e_osc = "";

	label->setInput("No Focus"); 
	x->setInput("0"); 
	y->setInput("0"); 
	w->setInput("0"); 
	h->setInput("0"); 
	osc->setInput(""); 

}

void EditorPanel::removeControl() {
	for (int i = 0; i <= gui->views[1]->controls.size() - 1; i++) {
		if ( gui->views[1]->controls.at(i) == focus.focused){
			if (gui->views[1]->controls.size() >= 1){
				gui->views[1]->controls.erase(gui->views[1]->controls.begin()+i);
				clearProperties(); 
				focus.clear();
			}
		}
	}
}

// TODO: Put this in a utility class: 
// Takes a number and outputs to string. 
string EditorPanel::toStr(float input){
	
	// Clear the stream & reset. 
	ostr.clear(); 
	ostr.str("");  

	// Put data to stream
	ostr << input; 

	// Output as a string
	return ostr.str(); 
}


// update INTERNAL numbers... 
void EditorPanel::updateX(int direction){
	if (stateManager::editing) {
		e_x = (direction == 1) ? toStr(atof(e_x.c_str()) - gridsize) : toStr(atof(e_x.c_str()) + gridsize);
		setProperties();
	}
}

void EditorPanel::updateY(int direction){
	if (stateManager::editing) {
		e_y = (direction == 1) ? toStr(atof(e_y.c_str()) - gridsize) : toStr(atof(e_y.c_str()) + gridsize);
		setProperties();
	}
}

void EditorPanel::updateSize(int width, int height){
	if (stateManager::editing) {
		e_w = toStr(atof(e_w.c_str()) + width);
		e_h = toStr(atof(e_h.c_str()) + height);
		setProperties();
	}
}