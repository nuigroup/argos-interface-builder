/***********************************************************************
 
 Copyright (c) 2009, 2010 Dimitri Diakopoulos, http://www.dimitridiakopoulos.com/


 Portions Copyright (c) 2008, 2009 Memo Aktens, http://www.memo.tv/
 -> Based on ofxSimpleGuiToo
 
 Portions Copyright (c) 2008 Todd Vanderlin, http://toddvanderlin.com/
 -> Inspired by ofxSimpleGui API

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

#include "ofTypes.h"

class ofxArgosUI_Parameter {

public:	
	
	/*
	typedef map<string, string> properties; 

	properties p; 

	void addProperty(string key, string defValue){
		  p.insert (pair<string,string>(key,defValue) );
	}
	*/

	int		textColor;
	int		textOverColor;

	int		textBGColor;
	int		textBGOverColor;
	
	int		fullColor;
	int		fullOverColor;
	int		fullActiveColor;

	int		emptyColor;

	int		borderColor;

	int		panelColor;
	int		panelBorderColor; 
	
	ofxArgosUI_Parameter() {
		
		textColor			= 0x000000;
		textOverColor		= 0x000000;

		textBGColor			= 0x4d5bc6;
		textBGOverColor		= 0x3647c7;

		fullColor			= 0xefefef;
		fullOverColor		= 0xefefef;
		fullActiveColor		= 0xefefef;

		emptyColor			= 0x2a2f39;		
		
		borderColor			= 0xe3e3e3;

	}

};
