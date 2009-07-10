/***********************************************************************
 
 Copyright (c) 2009 Dimitri Diakopoulos, http://www.dimitridiakopoulos.com/
 === Google Summer of Code 2009 - NUI Group === 

 [BSD License Here]

*************************************************************************/ 

#pragma once

class HitTest {

public: 

	// Static function for rectangle hit testing
	// Call HT::rectangle() to use. 
	static bool rectangle(int tX, int tY, int width, int height, int posX, int posY){

		return ((tX > posX) && (tX < posX + width) && (tY > posY) && (tY < posY + height));
	}

	// Static function for ellipse hit testing. 
	// ToDo: Use mutltiple types of interactive objects (they extend different primatives)
	static bool ellipse(){}

};





