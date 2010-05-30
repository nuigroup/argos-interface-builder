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

#include "LayoutHandler.h"
#include "utils.h"

void LayoutHandler::saveToXML(string file) {

	// Find someway of clearing the GUI. 

	// Which file are we saving to?
	printf("ofxArgosUI::saveToXML( %s )\n", file.c_str());

	// Clear the file. 
	XML.clear();
	
	// Access all the controls in the primary view, ask them to save. 
	for(int i = 3; i < gui->views[1]->controls.size(); i++) {
		gui->views[1]->controls[i]->saveToXML(XML); 
	}

	// Commit to file. 
	XML.saveFile(file);

}

void LayoutHandler::loadFromXML(string file) {

	for (int i = 2; i < gui->views[1]->controls.size(); i++) {
			gui->views[1]->controls[i]->killMe(); 
			gui->views[1]->controls.erase(gui->views[1]->controls.begin()+i);
	}

	// Which file are we loading from? 
	printf("ofxArgosUI::loadFromXML( %s )\n", file.c_str());
	
	// Some kind of error
	if(XML.loadFile(file) == false) {
		if(verbose) printf("Error loading XMLFile: %s\n", file.c_str());
		return;	
	}

	int numControls = XML.getNumTags("Button");

	//cout << "NUM CONTROLS: " << numControls << "\n"; 

	for(int i=0; i < numControls; i++) {
		button = gui->addButton(
			XML.getValue("Button:name", "No Name", i),
			XML.getValue("Button:x", 0, i),
			XML.getValue("Button:y", 0, i),
			XML.getValue("Button:width", 0, i),
			XML.getValue("Button:height", 0, i),
			&b[bi++]
		);
		button->setPropertyString("osc", XML.getValue("Button:osc", "", i));
	}

	numControls = XML.getNumTags("Slider");

	for(int i=0; i < numControls; i++) {
		slider = gui->addSlider(
			XML.getValue("Slider:name", "No Name", i),
			XML.getValue("Slider:x", 0, i),
			XML.getValue("Slider:y", 0, i),
			XML.getValue("Slider:width", 0, i),
			XML.getValue("Slider:height", 0, i),
			&f[fi++], 
			XML.getValue("Slider:min", 0, i),
			XML.getValue("Slider:max", 0, i),
			0.85
		);
		slider->setPropertyString("osc", XML.getValue("Slider:osc", "", i));
	}


	numControls = XML.getNumTags("Toggle");

	for(int i=0; i < numControls; i++) {
		toggle = gui->addToggle(
			XML.getValue("Toggle:name", "No Name", i),
			XML.getValue("Toggle:x", 0, i),
			XML.getValue("Toggle:y", 0, i),
			XML.getValue("Toggle:width", 0, i),
			XML.getValue("Toggle:height", 0, i),
			&b[bi++]
		);
		toggle->setPropertyString("osc", XML.getValue("Toggle:osc", "", i));
	}

	numControls = XML.getNumTags("Knob");

	for(int i=0; i < numControls; i++) {
		knob = gui->addKnob(
			XML.getValue("Knob:name", "No Name", i),
			XML.getValue("Knob:x", 0, i),
			XML.getValue("Knob:y", 0, i),
			XML.getValue("Knob:width", 0, i),
			&f[fi++], 
			XML.getValue("Knob:min", 0, i),
			XML.getValue("Knob:max", 0, i),
			0.85
		);
		knob->setPropertyString("osc", XML.getValue("Knob:osc", "", i));
	}

	numControls = XML.getNumTags("XYPad");

	for(int i=0; i < numControls; i++) {
		xypad = gui->addXYPad(
			XML.getValue("XYPad:name", "No Name", i),
			XML.getValue("XYPad:x", 0, i),
			XML.getValue("XYPad:y", 0, i),
			XML.getValue("XYPad:width", 0, i),
			XML.getValue("XYPad:height", 0, i),
			&v[vi++],
			XML.getValue("XYPad:minX", 0, i),
			XML.getValue("XYPad:maxX", 0, i),
			XML.getValue("XYPad:minY", 0, i),
			XML.getValue("XYPad:maxY", 0, i)
		);
		xypad->setPropertyString("osc", XML.getValue("XYPad:osc", "", i));
	}


}

void LayoutHandler::init(ofxArgosUI &gui){
	this->gui = &gui; 
}


