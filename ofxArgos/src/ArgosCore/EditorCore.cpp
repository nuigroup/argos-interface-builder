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

const float gridsize = 5.00; 

EditorPanel::EditorPanel() {}

void EditorPanel::init(ofxArgosUI &gui){

		this->gui  = &gui; 

		editor = gui.addPanel("No Focus", 10, 20, 210, 30); 

		// Prevent the editor from being able to focus itself
		editor->lockPanel();
	
}

void EditorPanel::update(){

	if (stateManager::editing) {

		if (focus.focused != NULL){

			if (focus.loaded == false){
				
				cout << focus.focused->controlType << "\n"; 

				reset(); 

				focus.loaded = true;

				rControl = new actionResize(this); 
				mControl = new actionMove(this); 

				if (focus.focused->controlType == "Button"){
					bhandler = new ButtonHandler(*editor); 
					bhandler->editProperties(focus.focused); 
				}

				else if (focus.focused->controlType == "Slider"){
					shandler = new SliderHandler(*editor); 
					shandler->editProperties(focus.focused); 
				}

				else if (focus.focused->controlType == "Knob"){
					khandler = new KnobHandler(*editor); 
					khandler->editProperties(focus.focused); 
				}

				else if (focus.focused->controlType == "XYPad"){
					xyhandler = new XYHandler(*editor); 
					xyhandler->editProperties(focus.focused); 
				}

				else if (focus.focused->controlType == "Toggle"){
					thandler = new ToggleHandler(*editor); 
					thandler->editProperties(focus.focused); 
				}

			}
		}
	}
	
	else {
		editor->resetPanel("No Focus", 210, 30); 
	}
}
	
// Avoid memory leaks... 
void EditorPanel::reset(){

	editor->resetPanel("No Focus", 210, 30); 

	rControl->disableAllEvents();
	mControl->disableAllEvents(); 

}

void EditorPanel::moveXY_Arrows(string axis, string dir){
	if (stateManager::editing) {
		if (axis == "x"){
			if (dir == "left" ){
				focus.focused->setPropertyInt("x", focus.focused->getPropertyInt("x", 0) - gridsize); 
			}
			else if (dir == "right") {
				focus.focused->setPropertyInt("x", focus.focused->getPropertyInt("x", 0) + gridsize); 
			}
		}
		else if (axis == "y"){
			if (dir == "up" ){
				focus.focused->setPropertyInt("y", focus.focused->getPropertyInt("y", 0) - gridsize);
			}
			else if (dir == "down") {
				focus.focused->setPropertyInt("y", focus.focused->getPropertyInt("y", 0) + gridsize); 
			}
		}
	}
}

void EditorPanel::deleteControl() {
	if (stateManager::editing) {
		for (int i = 0; i <= gui->views[1]->controls.size() - 1; i++) {
			if ( gui->views[1]->controls.at(i) == focus.focused){
				if (gui->views[1]->controls.size() >= 1){
					gui->views[1]->controls[i]->killMe(); 
					gui->views[1]->controls.erase(gui->views[1]->controls.begin()+i);
					focus.clear();
					reset();  
				}
			}
		}
	}
}

void EditorPanel::newSize(int newWidth, int newHeight){
	if (stateManager::editing) {
		focus.focused->setPropertyInt("w", newWidth);
		focus.focused->setPropertyInt("h", newHeight); 
	}
}

void EditorPanel::newPosition(int newX, int newY){
	if (stateManager::editing) {
		focus.focused->setPropertyInt("x", newX);
		focus.focused->setPropertyInt("y", newY); 
	}
}