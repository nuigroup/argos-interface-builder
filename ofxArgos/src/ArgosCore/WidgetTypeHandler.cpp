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

#include "WidgetTypeHandler.h"

WidgetTypeHandler::WidgetTypeHandler(ofxArgosUI_Panel &panel) {
	this->editor  = &panel; 
}

WidgetTypeHandler::~WidgetTypeHandler(){
	editor->resetPanel("No Focus", 210, 30);
}

void WidgetTypeHandler::editBaseProperties (ofxArgosUI_Control *control) {
	editor->addTextField("Label:", 10, 30, 190, 20, control->getPropertyRef("name"));
	editor->addTextField("X:", 10, 70, 40, 20, control->getPropertyRef("x"));
	editor->addTextField("Y:", 60, 70, 40, 20, control->getPropertyRef("y"));
	editor->addTextField("W:", 110, 70, 40, 20, control->getPropertyRef("w"));
	editor->addTextField("H:", 160, 70, 40, 20, control->getPropertyRef("h"));
	editor->addTextField("OSC Address:", 10, 110, 190, 20, control->getPropertyRef("osc"));
}