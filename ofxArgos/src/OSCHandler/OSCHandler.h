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

#pragma once

#include "ofxOsc.h"
#include "ofTypes.h"

class OSCHandler {

public:

	bool verbose; 

	void start(int port){
		sender.setup("127.0.0.1", port); 
		printf("OSCHandler initalised at localhost on port %i \n", port);
		verbose = false; 
	}

	void setVerbose(bool x){
		verbose = x; 
	}

	void sendOSC(const int &value, string address){
		if (verbose) printf("OSCHandler::sendOSC:int\n");

		ofxOscMessage message;
		message.setAddress(address);
		message.addIntArg(value);
		sender.sendMessage(message); 
	}

	void sendOSC(const float &value, string address){
		if (verbose) printf("OSCHandler::sendOSC:float\n");

		ofxOscMessage message;
		message.setAddress(address);
		message.addFloatArg(value);
		sender.sendMessage(message); 
	}

	void sendOSC(const bool &value, string address){
		if (verbose) printf("OSCHandler::sendOSC:bool\n");

		ofxOscMessage message;
		message.setAddress(address);
		message.addIntArg(value);
		sender.sendMessage(message); 
	}

	void sendOSC(const ofPoint &value, string address){
		if (verbose) printf("OSCHandler::sendOSC:ofPoint\n");

		ofxOscMessage message;
		message.setAddress(address);
		message.addFloatArg(value.x);
		message.addFloatArg(value.y);
		sender.sendMessage(message); 
	}
	
private:
	ofxOscSender sender;

};

extern OSCHandler oschandler;