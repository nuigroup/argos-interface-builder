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

#include "Browser.h"

Argos_browser::Argos_browser(ofxArgosUI &gui) {

		browser = gui.addPanel("Element Browser", 280, 670, 570, 90); 

		// Pay close attention to the syntax here. Not adding
		// specific controls (button, toggle) etc to the panel,
		// but rather adding a derived icon type to the panel,
		// using a generic addControl method
		button	= new Draggable_Button	(gui, 10, 10, 70, 70); 
			browser->addControl(button); 

		toggle	= new Draggable_Toggle	(gui,  90, 10, 70, 70); 
			browser->addControl(toggle); 

		slider  = new Draggable_Slider	(gui, 170, 10, 70, 70);
			browser->addControl(slider);

		knob	= new Draggable_Knob	(gui, 250, 10, 70, 70);
			browser->addControl(knob); 

		xypad	= new Draggable_XYPad	(gui, 330, 10, 70, 70);
			browser->addControl(xypad); 

		label	= new Draggable_Label	(gui, 410, 10, 70, 70); 
			browser->addControl(label);

		panel	= new Draggable_Panel	(gui, 490, 10, 70, 70); 
			browser->addControl(panel); 

}