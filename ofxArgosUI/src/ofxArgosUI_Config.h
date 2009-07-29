/***********************************************************************
 
 Copyright (c) 2009 Dimitri Diakopoulos, http://www.dimitridiakopoulos.com/
 === Google Summer of Code 2009 - NUI Group === 

 Portions Copyright (c) 2008, 2009 Memo Atkens, http://www.memo.tv/
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

class ofxArgosUI_Config {
public:	

	ofPoint	gridSize;

	float	buttonHeight;
	float	toggleHeight;
	float	sliderHeight;
	float	sliderTextHeight;
	float	slider2DTextHeight;
	float	titleHeight;
	
	ofPoint padding;
	ofPoint offset;
	ofPoint	slider2DSize;
	
	int	textColor;
	int textOverColor;
	int textBGColor;
	int textBGOverColor;
	
	int fullColor;
	int	fullOverColor;
	int fullActiveColor;
	int emptyColor;
	int borderColor;
	
	ofxArgosUI_Config() {

		sliderHeight		= 12;
		sliderTextHeight	= 18;
		titleHeight			= sliderHeight + sliderTextHeight;
		toggleHeight		= titleHeight;
		buttonHeight		= titleHeight;
		slider2DTextHeight	= titleHeight * 1.5;

		padding.set			(titleHeight/2, titleHeight/2);
		offset.set			(titleHeight/2, titleHeight/2);
		slider2DSize.set	(titleHeight * 4, titleHeight * 4);
		
		gridSize.x			= titleHeight * 8 + padding.x;		
		gridSize.y			= toggleHeight + padding.y;
		
		// Text:
		textColor			= 0xf1f1f1;
		// Text Hover: 
		textOverColor		= 0xf1f1f1;

		// BG Color
		textBGColor			= 0x3a3950;
		// Background Hover
		textBGOverColor		= 0x585778;
		
		// These aren't working? Test.
		fullColor			= 0xCCCCCC;
		fullOverColor		= 0xCCCCCC;
		fullActiveColor		= 0xCCCCCC;
		emptyColor			= 0xCCCCCC;		
		
		borderColor			= 0xCCCCCC;
	}
};

extern ofxArgosUI_Config defaultSimpleGuiConfig;