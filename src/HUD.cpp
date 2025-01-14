/*

File: src/HUD.cpp
Author: Benjamin Smith
Purpose: 
	This superclass for the HUD function allows for the implementation of an overlain
	view window to the main window that encompasses the characters current health
	and weapon information. 

*/

#include "../hdr/HUD.h"

    HUD::HUD()  {
			m_width = Game::getInstance().getWidth();
			m_height = Game::getInstance().getHeight();
			// Create an overlay view over the main game as not to disrupt the primary functions of the game
			// Can be later implepented to be turned off through settings
			if (glutLayerGet(GLUT_OVERLAY_POSSIBLE)) {
				void glutEstablishOverlay();
			}
		}  
	// Prints a text string to the screen. 
	void HUD::RenderString(float x, float y, void *font, const char* string)
	{  
	  //char *c;

	  const unsigned char* string2 = (const unsigned char*)string;

	  glColor3f(0.0, 0.0, 0.0); // black
	  glRasterPos2f(x, y);
	  glutBitmapString(font, string2);
	} 

	// Display the main sections for the HUD 
	void HUD::displayHUD() {
	}

	// Future implementation: create and display a minimap for the player.
	void minimap() {

	}

