#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN

#define GLX_GLXEXT_LEGACY //Must be declared so that our local glxext.h is picked up, rather than the system one


//#include "GameConstants.h"
#include "windowOGL.h"
#include "cWNDManager.h"
//#include "cColours.h"
//#include "cShapes.h"
//#include "cPyramid.h"
//#include "cCube.h"
//#include "cSphere.h"
//#include "cMaterial.h"
//#include "cLight.h"
//#include "cStarfield.h"
#include "cFontManager.h"


int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR cmdLine,
	int cmdShow)
{

	//Set our window settings
	const int windowWidth = 1024;
	const int windowHeight = 768;
	const int windowBPP = 16;



	//This is our window
	static cWNDManager* pgmWNDMgr = cWNDManager::getInstance();

	// This is the Font manager
	static cFontManager* theFontMgr = cFontManager::getInstance();

	//The example OpenGL code
	windowOGL theOGLWnd;

	//Attach our example to our window
	pgmWNDMgr->attachOGLWnd(&theOGLWnd);

	// Sphere
	//cSphere theSun(4, 40, 40);
	//cSphere theEarth(3, 30, 30);
	//cSphere theMoon(1, 20, 20);

	//Attempt to create the window
	if (!pgmWNDMgr->createWND(windowWidth, windowHeight, windowBPP))
	{
		//If it fails

		MessageBox(NULL, "Unable to create the OpenGL Window", "An error occurred", MB_ICONERROR | MB_OK);
		pgmWNDMgr->destroyWND(); //Reset the display and exit
		return 1;
	}

	if (!theOGLWnd.initOGL(windowWidth, windowHeight)) //Initialize our example
	{
		MessageBox(NULL, "Could not initialize the application", "An error occurred", MB_ICONERROR | MB_OK);
		pgmWNDMgr->destroyWND(); //Reset the display and exit
		return 1;
	}

	// Create Texture map
	//cTexture earthTexture;
	//earthTexture.createTexture("Images/Earth.png");
	//cTexture moonTexture;
	//moonTexture.createTexture("Images/Moon.png");
	//cTexture sunTexture;
	//sunTexture.createTexture("Images/Sun.png");
	//cTexture starTexture;
	//starTexture.createTexture("Images/star.png");

	// the starfield
	//cStarfield theStarField(starTexture.getTexture(), glm::vec3(50.0f, 50.0f, 50.0f));

	//theSun.initialise(sunTexture.getTexture(), glm::vec3(0, 0, 40), glm::vec3(0, 0, 0));

	//theEarth.initialise(earthTexture.getTexture(), glm::vec3(10, 0, 20), glm::vec3(0, 0, 0));
	//float earthRotSpeed = 3.0f;
	//GLfloat earthOrbit = 0.0f;

	//theMoon.initialise(moonTexture.getTexture(), glm::vec3(10, 5, 8), glm::vec3(0, 0, 0));
	//float moonRotSpeed = 5.0f;
	//GLfloat moonOrbit = 0.0f;

	// Create Materials for lights
	//cMaterial sunMaterial(lightColour4(0.0f, 0.0f, 0.0f, 1.0f), lightColour4(1.0f, 1.0f, 1.0f, 1.0f), lightColour4(1.0f, 1.0f, 1.0f, 1.0f), lightColour4(0, 0, 0, 1.0f), 5.0f);
	//cMaterial earthMaterial(lightColour4(0.2f, 0.2f, 0.2f, 1.0f), lightColour4(1.0f, 1.0f, 1.0f, 1.0f), lightColour4(1.0f, 1.0f, 1.0f, 1.0f), lightColour4(0, 0, 0, 1.0f), 50.0f);
	//cMaterial moonMaterial(lightColour4(0.1f, 0.1f, 0.1f, 1.0f), lightColour4(1.0f, 1.0f, 1.0f, 1.0f), lightColour4(0.2f, 0.2f, 0.2f, 1.0f), lightColour4(0, 0, 0, 1.0f), 10.0f);
	//// Create Light
	//cLight sunLight(GL_LIGHT0, lightColour4(0, 0, 0, 1), lightColour4(1, 1, 1, 1), lightColour4(1, 1, 1, 1), glm::vec4(0, 0, 20, 1),
	//	glm::vec3(0.0, 0.0, 1.0), 0.0f, 180.0f, 1.0f, 0.0f, 0.0f);
	////Define Ambient light for scene
	//GLfloat g_Ambient[] = { 0.2, 0.2, 0.2, 1.0 };
	//glLightModelfv(GL_LIGHT_MODEL_AMBIENT, g_Ambient);

	// load game fonts
	// Load Fonts
	LPCSTR gameFonts[2] = { "Fonts/digital-7.ttf", "Fonts/space age.ttf" };

	theFontMgr->addFont("SevenSeg", gameFonts[0], 24);
	theFontMgr->addFont("Space", gameFonts[1], 24);

	//This is the mainloop, we render frames until isRunning returns false
	while (pgmWNDMgr->isWNDRunning())
	{
		pgmWNDMgr->processWNDEvents(); //Process any window events

									   //We get the time that passed since the last frame
		float elapsedTime = pgmWNDMgr->getElapsedSeconds();

		// Lab code goes here
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		theOGLWnd.initOGL(windowWidth, windowHeight);

		//glMatrixMode(GL_MODELVIEW);
		//glLoadIdentity();
		//glTranslatef(0.0f, 0.0f, -80.0f);

		//glPushMatrix();
		//theStarField.render(0.0f);

		//theSun.prepare(0.0f);
		//sunMaterial.useMaterial();
		//sunLight.lightOn();
		//theSun.render(theSun.getRotAngle());

		//// Earth's orbit
		//glPushMatrix();
		//theEarth.setRotAngle(theEarth.getRotAngle() + (earthRotSpeed*elapsedTime));
		//theEarth.prepare(theEarth.getRotAngle()); //Do any pre-rendering logic
		//earthMaterial.useMaterial();				// Set the material for use
		//theEarth.render(theEarth.getRotAngle()); //Render the scene
		//										 // Moon's orbit
		//glPushMatrix();
		//theMoon.setRotAngle(theMoon.getRotAngle() + (moonRotSpeed*elapsedTime));
		//theMoon.prepare(rotationAngle);
		//moonMaterial.useMaterial();
		//theMoon.render(theMoon.getRotAngle());
		//glPopMatrix();
		//glPopMatrix();
		//glPopMatrix();



		glPushMatrix();
		theOGLWnd.setOrtho2D(windowWidth, windowHeight);
		theFontMgr->getFont("Space")->printText("Sun, Earth and Moon ggg", FTPoint(15, 15, 0.0f));
		glPopMatrix();

		pgmWNDMgr->swapBuffers();

	}

	theOGLWnd.shutdown(); //Free any resources
	pgmWNDMgr->destroyWND(); //Destroy the program window

	return 0; //Return success
}
