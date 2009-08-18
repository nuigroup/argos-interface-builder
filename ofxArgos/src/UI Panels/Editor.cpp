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

bool	ba[20]; 
float	fa[20];
int		fib;

bool minimized; 

Argos_editor::Argos_editor(ofxArgosUI &gui) {

		// Reference the Argos GUI into this object
		egui   = &gui; 

		editor = egui->addPanel("Element Editor", 10, 20, 240, ofGetHeight()-30); 

		// +++ Apply/Cancel/Reset Buttons
		editor->addButton("Apply", 10,(editor->height - 35), 70, 25, &ba[fib++]);
		editor->addButton("Cancel", 85,(editor->height - 35), 70, 25, &ba[fib++]);
		editor->addButton("Reset", 160,(editor->height - 35), 70, 25, &ba[fib++]);

		// +++ Minimize/Maximize 
		//editor->addButton("", editor->width - 35, 15 , 18, 18, &minimized);
}