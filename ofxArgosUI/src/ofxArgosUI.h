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
#ifndef OFX_SIMPLE_GUI_H
#define OFX_SIMPLE_GUI_H

#include "ofMain.h"
#include "ofxXmlSettings.h"
#include "ofxTouchAPI.h"
#include "ofxArgosUI_Includes.h"

#define	OFX_SIMPLEGUITOO_XML_NAME	"ofxArgosUI_Too.xml"

class ofxArgosUI_Too {

	
public:
	int							guiFocus;
	ofxArgosUI_Config			*config;	
	
	ofxArgosUI_Too();

	void					loadFromXML(string file = OFX_SIMPLEGUITOO_XML_NAME);
	void					saveToXML(string file = OFX_SIMPLEGUITOO_XML_NAME);	
	void					setAutoSave(bool b);

	void					setVerbose(bool v);
	
//	int		getValueI(string nameID);
//	float	getValueF(string nameID);
//	bool	getValueB(string nameID);
	
	void					drawFocus(float x, float y);
	void					setDraw(bool b);
	void					toggleDraw();
	void					draw();
	bool					isOn();
	
	void					nextPage();
	void					prevPage();
	void					setPage(int i);				// 1 based index of page
	void					setPage(string name);
	
	ofxArgosUI_View		*page(int i);				// 1 based index of page
	ofxArgosUI_View		*page(string name);
	ofxArgosUI_View		*addView(string name = "");

	ofxArgosUI_Control		*addControl(ofxArgosUI_Control* control);

	ofxArgosUI_Button		*addButton(string name, int x, int y, int width, int height, bool *value);
	ofxArgosUI_Toggle		*addToggle(string name, bool *value);
	ofxArgosUI_SliderInt	*addSlider(string name, int *value, int min, int max);
	ofxArgosUI_SliderFloat	*addSlider(string name, float *value, float min, float max, float smoothing = 0);
	ofxArgosUI_Slider2d		*addSlider2d(string name, ofPoint* value, float xmin, float xmax, float ymin, float ymax);
	ofxArgosUI_Title		*addTitle(string name, bool *value = NULL);
	ofxArgosUI_Content		*addContent(string name, ofBaseDraws *content, float fixwidth = -1);
	ofxArgosUI_FPSCounter	*addFPSCounter();
	
protected:
	bool							doAutoSave;
	bool							doSave, doSaveBackup;
	bool							changePage;
	int								currentPage;			// 1 based index of page (0 is for global controls)
	
	ofxXmlSettings					XML;
	string							xmlFile;
	
	bool							verbose;
	bool							doDraw;
	float							border;

	ofxArgosUI_View				*headerPage;
	vector <ofxArgosUI_View*>		pages;				// 0 is for headerPage
	
	void drawHeader(); 
	void addListeners();
	void removeListeners();
	
//	void setup(ofEventArgs &e);
	void update(ofEventArgs &e);
//  void draw(ofEventArgs &e);
//	void exit(ofEventArgs &e);
	
	void mouseMoved(ofMouseEventArgs &e);
	void mousePressed(ofMouseEventArgs &e);	
	void mouseDragged(ofMouseEventArgs &e);	
	void mouseReleased(ofMouseEventArgs &e);
	
	void keyPressed(ofKeyEventArgs &e);
	void keyReleased(ofKeyEventArgs &e);
};

#endif





