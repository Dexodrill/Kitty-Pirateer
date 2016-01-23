//Editor: Keenan Longair.
//Last Update: Jan23, 2016 @ 2:30pm.
//Purpose: The main workings of the Game class.
#include "Game.h"
#include "Jukebox.h"
#include <cstdio>

//#include <GL/glut.h>    /* glut.h includes gl.h and glu.h */
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <GL/freeglut.h>

#include "GameObject.h"


// We do not use this function yet, but you might want it.
GLfloat Game::frand() {
    return random()/(GLfloat)RAND_MAX;
}

// Called by Game::idle this function sends a signal to update the screen
void Game::timer(int id)
{
   if(id == 513)
   {
      // Redisplay frame
      glutPostRedisplay();
   }
}

// Tis function 
void Game::idle() {
   glutTimerFunc(Game::c_interval, // in this many miliseconds
     Game::timer,      // call the funtion timer
     513               // with this parameter
   );
}

void Game::run() {


    Game::getInstance().update();   
    // flush the graphics pipele and display the objects we have specified
    //Since we are using double buffering this means we swap the buffer be just drew
    //on to the screen.
    glutSwapBuffers();
    Game::idle();
}


void Game::key(unsigned char key, int x, int y)
{
 
 
    //glutPostRedisplay();
}

void Game::RenderString(float x, float y, void *font, const char* string)
//Renders the string at the desired position in red text.
{  
  char *c;

  const unsigned char* string2 = (const unsigned char*)string;

  glColor3f(1.0, 0.0, 0.0); 
  glRasterPos2f(x, y);

  glutBitmapString(font, string2);
}

void Game::update()
//Function which calls the collide and update functions of the various objects ingame.
{
   m_myBall.update();
   for(int i=0; i<m_gameObjects; i++)
      m_myGameObjects[i]->collide(&m_myBall);

   for(int i=0; i<m_gameObjects; i++)
      m_myGameObjects[i]->update();

    //clear the screen
    glClearColor(1.0, 1.0, 1.0, 0.0); // Set the clear color to white
    glClear(GL_COLOR_BUFFER_BIT);     // clear the screen

    //Display the current score
    char string[40];
    sprintf(string, "Score:\n%d", m_score);
    RenderString(0, m_height-20, GLUT_BITMAP_TIMES_ROMAN_24, string);

    for(int i=0; i<m_gameObjects; i++)
      m_myGameObjects[i]->display();
}

void Game::init() {
    //Set up all the objects in the game that can collide with in an array
    //called m_myGameObjects. m_gameObjects tells how many are defined.
    m_gameObjects = 0;

    //Set the seed for the random variable generator just in case we need it.
    srandom(time(NULL));

    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB); // Use double buffering for smoother images
    glutInitWindowSize(m_width, m_height);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("");

    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, m_width+m_margine, 0, m_height+m_margine);

   //In event-driven programming, like you have in interactive OpenGL 
   //applications, the main application loop generally does three things:
   //  1. check the current event queues, and process any events (e.g., 
   //     mouse movement, key presses, etc.) that have occurred since the last check
   //  2.update the application state - things like player and object positions, 
   //    game physics, etc. - in preparation of the next rendering frame
   //  3.render the current frame.
   // GLUT does these steps implicitly in its glutMainLoop()

   // Set up the callbacks that will be taken care of in step 1:
    glutKeyboardFunc(Game::key); // Keyboard input
    glutDisplayFunc(Game::run);  // Display frames
    //glutIdleFunc(Game::run);    // Wait time between frames.

    glutMainLoop(); // glutMainLoop enters the GLUT event processing loop. 
                    //This routine should be called at most once in a GLUT program. 
                    //Once called, this routine will never return. 
                    //It will call as necessary any callbacks that have been registered.
}


int main(int argc, char **argv) {
    if(!Jukebox::init())
      exit;
    glutInit(&argc, argv);
    Game::getInstance().init();
    SDL_CloseAudio();
}