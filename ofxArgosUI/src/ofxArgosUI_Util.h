/***********************************************************************
 
 Copyright (c) 2009, 2010 Dimitri Diakopoulos, http://www.dimitridiakopoulos.com/


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

inline void drawrRectangle(int x, int y, int w, int h, int radius){

    glBegin(GL_POLYGON);

    glVertex2f (x + radius, y);
    glVertex2f (x + w - radius, y);
		for(float t  = PI * 1.5f; t < TWO_PI; t += 0.1f){
			float sx = x + w - radius + cos(t) * radius;
			float sy = y + radius + sin(t) * radius;
			glVertex2f (sx, sy);
		}

    glVertex2f (x + w, y + radius);
    glVertex2f (x + w, y + h - radius);
		for(float t  = 0; t < PI * 0.5f; t += 0.1f){
			float sx = x + w - radius + cos(t) * radius;
			float sy = y + h - radius + sin(t) * radius;
			glVertex2f (sx, sy);
		}
        
    glVertex2f (x + w -radius, y + h);
    glVertex2f (x + radius, y + h);
		for(float t  = PI * 0.5f; t < PI; t += 0.1f){
			float sx = x + radius + cos(t) * radius;
			float sy = y + h - radius + sin(t) * radius;
			glVertex2f (sx, sy);
		}
    
    glVertex2f (x, y + h - radius);
    glVertex2f (x, y + radius);
		for(float t  = PI; t < PI * 1.5f; t += 0.1f){
			float sx = x + radius + cos(t) * radius;
			float sy = y + radius + sin(t) * radius;
			glVertex2f (sx, sy);
		}
    
    glEnd();  

}

// Draw a rounded rectangle with corners rounded around a specific radius. 
inline void rRectangle(int x, int y, int w, int h, int radius){
	
    glDisable(GL_TEXTURE_2D);

		glEnable( GL_POLYGON_OFFSET_FILL );
			glPolygonOffset( 2.5, 2.5 );
			drawrRectangle(x, y, w, h, radius);
		glDisable( GL_POLYGON_OFFSET_FILL );

		glEnable( GL_BLEND );
			glEnable( GL_LINE_SMOOTH );
				glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
				glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
					drawrRectangle(x, y, w, h, radius); 
				glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
			glDisable( GL_LINE_SMOOTH );
		glDisable( GL_BLEND );

    glEnable(GL_TEXTURE_2D);

}