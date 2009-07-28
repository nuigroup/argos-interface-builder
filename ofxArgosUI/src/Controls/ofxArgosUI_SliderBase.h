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

#include "ofxArgosUI_Control.h"

template <typename Type> class ofxArgosUI_SliderBase : public ofxArgosUI_Control {
public:

	Type		*value;
	Type		min, max;
	
	float		barwidth;
	float		pct;		
	
	float		lerpSpeed;
	Type		targetValue;
	Type		oldValue;
	
	ofxArgosUI_SliderBase(string name, Type *value, Type min, Type max, float smoothing = 0) : ofxArgosUI_Control(name) {
		this->value = value;
		this->min	= min;
		this->max	= max;
		
		lerpSpeed	= 1.0f - smoothing * 0.99;		// so smoothing :1 still results in some motion!
		targetValue	= *value;
		oldValue	= targetValue;
		controlType = "SliderBase";
		setup();
	}
	
	void setup() {
		setSize(config->gridSize.x - config->padding.x, config->sliderHeight + config->sliderTextHeight);
		pct		 = ofMap((*value), min, max, 0.0, width);
		barwidth = pct;
	}

	void loadFromXML(ofxXmlSettings &XML) {
		set(XML.getValue("controls:" + controlType + "_" + key + ":value", 0.0f));
	}
	
	void saveToXML(ofxXmlSettings &XML) {
		XML.addTag(controlType + "_" + key);
		XML.pushTag(controlType + "_" + key);
		XML.addValue("name", name);
		XML.addValue("value", getValue());
		XML.popTag();
	}
	
	
	
	Type getValue() {
		return (*value);
	}
	
	
	void set(Type f) {
		(*value) = f;
	}
	
	void add() {
		pct += .05f;
		float temp = ofMap(pct, 0.0, width, min, max);
		
		//VALUE CLAMP
		if(temp >= max)			temp = max;
		else if(temp <= min)	temp = min;
		
		targetValue = temp;	
		oldValue = *value;		// save oldValue (so the draw doesn't update target but uses it)
	}
	
	void sub() {
		pct -= .05f;
		float temp = ofMap(pct, 0.0, width, min, max);
		
		//VALUE CLAMP
		if(temp >= max)			temp = max;
		else if(temp <= min)	temp = min;
		
		targetValue = temp;	
		oldValue = *value;		// save oldValue (so the draw doesn't update target but uses it)
	}
	
	
	void updateSlider() {
		if(!enabled) return;
		
		if(pct > width) {
			pct = width;
		}
		else {
			pct = getMouseX() - x;
			float temp = ofMap(pct, 0.0, (float)width, min, max);
			
			//VALUE CLAMP
			if(temp >= max)			temp = max;
			else if(temp <= min)	temp = min;
			
			targetValue = temp;	
			oldValue = *value;		// save oldValue (so the draw doesn't update target but uses it)
		}
	}
	
	void onPress(int x, int y, int button) {
		updateSlider();
	}
	
	void onDragOver(int x, int y, int button) {
		updateSlider();
	}
	
	void onDragOutside(int x, int y, int button) {
		updateSlider();
	}
	
	
	
	void onKeyRight() {
		add();
	}

	void onKeyLeft() {
		sub();
	}
	
	
	void update() {
		if(!enabled) return;
		
		if(lock) {
			updateSlider();
		}
		
		enabled = false;
		
	}
	
	void draw(float x, float y) {
		
		enabled = true;
		
		if(oldValue != *value) {							// if value has changed programmatically by something else
			oldValue = targetValue = *value;				// save the value in target and oldvalue
		} else {											// otherwise lerp
			*value += (targetValue - *value) * lerpSpeed;
			oldValue = *value;								// and save oldvalue
		}
		
		setPos(x, y);
		
		barwidth = ofMap((*value), min, max, 0.0, (float)width);
		
		if(barwidth >= width)	barwidth = width;
		else if(barwidth <= 0)		barwidth = 0;
		
		ofEnableAlphaBlending();
		glPushMatrix();
		glTranslatef(x, y, 0);
		ofFill();
		
		setEmptyColor();
		ofRect(0, 0, width, config->sliderHeight);
		

		setFullColor();
		ofRect(0, 0, barwidth, config->sliderHeight);
		
		setTextBGColor();
		ofRect(0, config->sliderHeight, width, config->sliderTextHeight);

		setTextColor();
		ofDrawBitmapString(name+":"+ofToString((*value), 6.0), 3, height - 4);
		ofDisableAlphaBlending();
		glPopMatrix();
	}
	
	
	
};