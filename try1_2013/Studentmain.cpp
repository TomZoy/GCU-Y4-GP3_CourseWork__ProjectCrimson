#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN

#define GLX_GLXEXT_LEGACY //Must be declared so that our local glxext.h is picked up, rather than the system one


//#include <windows.h>
#include "GameConstants.h"
#include "windowOGL.h"
#include "cWNDManager.h"
#include "cColours.h"
#include "cShapes.h"
#include "cPyramid.h"
#include "cCube.h"
#include "cSphere.h"
#include "cMaterial.h"
#include "cLight.h"
#include "cStarfield.h"
#include "cFontMgr.h"
#include "cCamera.h"
#include "cInputMgr.h"
#include "cSoundMgr.h"
#include "cModelLoader.h"
#include "cModel.h"
#include "cPlayer.h"
#include "cEnemy.h"
#include "cLaser.h"


#include "cBackground.h"
#include "cCameraMgr.h"
#include "cBullet.h"
#include "shootingRangeGame.h"


cCamera *activeCamera;


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

	// This is the input manager
	static cInputMgr* theInputMgr = cInputMgr::getInstance();

	// This is the Font manager
	static cFontMgr* theFontMgr = cFontMgr::getInstance();

	// This is the sound manager
	static cSoundMgr* theSoundMgr = cSoundMgr::getInstance();

	// Camera manager
	static cCameraMgr* theCameraMgr = cCameraMgr::getInstance();
	
	//The example OpenGL code
	windowOGL theOGLWnd;

	//Attach our example to our window
	pgmWNDMgr->attachOGLWnd(&theOGLWnd);

	// Attach the keyboard manager
	pgmWNDMgr->attachInputMgr(theInputMgr);

	// Attach the keyboard manager
	theCameraMgr->attachInputMgr(theInputMgr);



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
	cTexture tardisTexture;
	tardisTexture.createTexture("Models/tardis.png");
	cTexture spaceShipTexture;
	spaceShipTexture.createTexture("Models/SpaceShip/sh3.jpg");


	cTexture laserTexture;
	laserTexture.createTexture("Models/laser.tga");

	cTexture bulletTexture;
	bulletTexture.createTexture("Models/Crimson/bullet_rife/Brass.jpg");

	cTexture starTexture;
	starTexture.createTexture("Images/star.png");



	cTexture backgroundTexture;
	backgroundTexture.createTexture("Images/gun-range.jpg");

	cTexture targetTexture;
	targetTexture.createTexture("Models/Crimson/target/textures/texture.jpg");

	cTexture rifleTexture;
	rifleTexture.createTexture("Models/Crimson/rifle/texture/steel.jpg");
	cTexture pistolTexture;
	pistolTexture.createTexture("Models/Crimson/pistol/textures/handgun_C.jpg");



	// the starfield
	cStarfield theStarField(backgroundTexture.getTexture(), glm::vec3(5.0f, 5.0f, 5.0f));

	// Create Materials for lights
	cMaterial sunMaterial(lightColour4(0.0f, 0.0f, 0.0f, 1.0f), lightColour4(1.0f, 1.0f, 1.0f, 1.0f), lightColour4(1.0f, 1.0f, 1.0f, 1.0f), lightColour4(0, 0, 0, 1.0f), 5.0f);

	// Create Light
	cLight sunLight(GL_LIGHT0, lightColour4(0, 0, 0, 1), lightColour4(1, 1, 1, 1), lightColour4(1, 1, 1, 1), glm::vec4(0, 0, 20, 1),
		glm::vec3(0.0, 0.0, 1.0), 0.0f, 180.0f, 1.0f, 0.0f, 0.0f);
	cLight lfLight(GL_LIGHT1, lightColour4(0, 0, 0, 1), lightColour4(1, 1, 1, 1), lightColour4(1, 1, 1, 1), glm::vec4(30, 0, 100, 1),
		glm::vec3(0.0, 0.0, 1.0), 0.0f, 180.0f, 1.0f, 0.0f, 0.0f);
	cLight rfLight(GL_LIGHT2, lightColour4(0, 0, 0, 1), lightColour4(1, 1, 1, 1), lightColour4(1, 1, 1, 1), glm::vec4(-30, 0, 100, 1),
		glm::vec3(0.0, 0.0, 1.0), 0.0f, 180.0f, 1.0f, 0.0f, 0.0f);
	cLight cbLight(GL_LIGHT3, lightColour4(0, 0, 0, 1), lightColour4(1, 1, 1, 1), lightColour4(1, 1, 1, 1), glm::vec4(0, 0, -100, 1),
		glm::vec3(0.0, 0.0, 1.0), 0.0f, 180.0f, 1.0f, 0.0f, 0.0f);
	//Define Ambient light for scene
	GLfloat g_Ambient[] = { 0.2, 0.2, 0.2, 1.0 };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, g_Ambient);

	// load game fonts
	LPCSTR gameFonts[3] = { "Fonts/digital-7.ttf", "Fonts/gunplay-rg.ttf","Fonts/doctor_who.ttf" };

	theFontMgr->addFont("SevenSeg", gameFonts[0], 55);
	theFontMgr->addFont("Text", gameFonts[1], 50);
	theFontMgr->addFont("TextSmall", gameFonts[1], 25);
	theFontMgr->addFont("drWho", gameFonts[2], 50);


	// load game sounds
	LPCSTR gameSounds[3] = { "Audio/who10Edit.wav", "Audio/shot007.wav", "Audio/explosion2.wav" };
	LPCSTR BGM[5] = { "Audio/BGM/wav/radio1-_01_A_Night_Of_Dizzy_Spells.wav","Audio/BGM/wav/radio2_-01_The_Misadventure_Begins.wav","Audio/BGM/wav/radio3_-04_Cold_as_Steel.wav","Audio/BGM/wav/radio4_-.wav","Audio/BGM/wav/radio5_-09_The_Day_Time_Ran_Away.wav" };
	LPCSTR SFX[7] = { "Audio/SFX/wav/fireGun.wav", "Audio/SFX/wav/reload.wav", "Audio/SFX/wav/ricochet1.wav", "Audio/SFX/wav/ricochet2.wav", "Audio/SFX/wav/ricochet3.wav", "Audio/SFX/wav/targetHit.wav", "Audio/SFX/wav/gunEmpty.wav" };

	//theSoundMgr->add("Theme", gameSounds[0]);
	//theSoundMgr->add("Shot", gameSounds[1]);
	//theSoundMgr->add("Explosion", gameSounds[2]);

	theSoundMgr->add("BGM1", BGM[0]);
	theSoundMgr->add("BGM2", BGM[1]);
	theSoundMgr->add("BGM3", BGM[2]);
	theSoundMgr->add("BGM4", BGM[3]);
	theSoundMgr->add("BGM5", BGM[4]);


	theSoundMgr->add("fireGunSFX", SFX[0]);
	theSoundMgr->add("reloadSFX", SFX[1]);
	theSoundMgr->add("ricochet1SFX", SFX[2]);
	theSoundMgr->add("ricochet2SFX", SFX[3]);
	theSoundMgr->add("ricochet3SFX", SFX[4]);
	theSoundMgr->add("targetHitSFX", SFX[5]);
	theSoundMgr->add("emptyGunSFX", SFX[6]);



	theSoundMgr->add("Shot", gameSounds[1]);
	theSoundMgr->add("Explosion", gameSounds[2]);

	// Create a camera
	cCamera camera1;
	camera1.setTheCameraPos(glm::vec3(0.0f, 0.0f, 8.0f));
	camera1.setTheCameraLookAt(glm::vec3(0.0f, 0.0f, 0.0f));
	camera1.setTheCameraUpVector(glm::vec3(0.0f, 1.0f, 0.0f)); // pointing upwards in world space
	camera1.setTheCameraAspectRatio(windowWidth, windowHeight);
	camera1.setTheProjectionMatrix(0.0f, camera1.getTheCameraAspectRatio(), 0.1f, 500.0f);
	camera1.update();
	theCameraMgr->add("camera1", &camera1);

	// Create another camera
	cCamera camera2(windowWidth,windowHeight);
	camera2.setTheCameraPos(glm::vec3(0.0f, 0.0f, 75.0f));
	camera2.setTheCameraLookAt(glm::vec3(0.0f, 0.0f, 0.0f));
	camera2.setTheCameraUpVector(glm::vec3(0.0f, 1.0f, 0.0f)); // pointing upwards in world space
	camera2.setTheCameraAspectRatio(windowWidth, windowHeight);
	camera2.setTheProjectionMatrix(25.0f, camera2.getTheCameraAspectRatio(), 0.0f, 300.0f);
	camera2.update();
	theCameraMgr->add("camera2", &camera2);

	//Clear key buffers
	theInputMgr->clearBuffers(theInputMgr->KEYS_DOWN_BUFFER | theInputMgr->KEYS_PRESSED_BUFFER);

	// Model
	//cModelLoader tardisMdl;
	//tardisMdl.loadModel("Models/tardis1314.obj", tardisTexture); // Player

	//// riffle
	//cModelLoader rifleMdl;
	//rifleMdl.loadModel("Models/Crimson/rifle/hunting_rifle.obj", rifleTexture); // Player

	//// pistol
	cModelLoader pistolMdl;
	pistolMdl.loadModel("Models/Crimson/pistol/Handgun_obj.obj", rifleTexture); // Player


	//cModelLoader spaceShipMdl;
	//spaceShipMdl.loadModel("Models/SpaceShip/Sample_Ship.obj", spaceShipTexture); // Enemy
	
	cModelLoader theLaser;
	theLaser.loadModel("Models/laser.obj", laserTexture);

	cModelLoader theBullet;
	theBullet.loadModel("Models/Crimson/bullet_rife/50_Barrett.obj", bulletTexture);

	cModelLoader targetMdl;
	targetMdl.loadModel("Models/Crimson/target/target2.obj", targetTexture);


	for (int loop = 0; loop < 5; loop++)
	{
		theEnemy.push_back(new cEnemy);
		//theEnemy[loop]->randomise();
		theEnemy[loop]->setMdlDimensions(targetMdl.getModelDimensions());
		theEnemy[loop]->setScale(glm::vec3(5, 5, 5));
	}


	cPlayer thePlayer;
	thePlayer.initialise(glm::vec3(0, 0, 0), 90.0f, glm::vec3(1, 1, 1), glm::vec3(0, 0, 0), 5.0f, true);
	thePlayer.setMdlDimensions(pistolMdl.getModelDimensions());
	thePlayer.attachInputMgr(theInputMgr);
	thePlayer.attachSoundMgr(theSoundMgr);
	thePlayer.attachCameraMgr(theCameraMgr);
	theSoundMgr->attachInputMgr(theInputMgr);

	float tCount = 0.0f;

	
	string outputMsg;
	string autoFollowBulletText;
	colour3f textColor = (0.99f, 0.99f, 0.99f);
	//std::vector<cLaser*> laserList;
	//std::vector<cLaser*>::iterator index;

	std::vector<cBullet*> bulletList;
	std::vector<cBullet*>::iterator index2;




   //This is the mainloop, we render frames until isRunning returns false
	while (pgmWNDMgr->isWNDRunning())
	{
		pgmWNDMgr->processWNDEvents(); //Process any window events

		//We get the time that passed since the last frame
		float elapsedTime = pgmWNDMgr->getElapsedSeconds();
		
		theSoundMgr->updateSound();


		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		theOGLWnd.initOGL(windowWidth,windowHeight);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		theCameraMgr->updateCamera();
		//glLoadMatrixf((GLfloat*)&activeCamera->getTheViewMatrix());//.getTheViewMatrix());
		glLoadMatrixf((GLfloat*)&(theCameraMgr->getCurrentCamera())->getTheViewMatrix());//.getTheViewMatrix());


		//theStarField.renderFull(windowWidth, windowHeight);


		sunMaterial.useMaterial();

		
		sunLight.lightOn();
		lfLight.lightOn();
		rfLight.lightOn();
		cbLight.lightOn();
		
		for (vector<cEnemy*>::iterator enemyIterator = theEnemy.begin(); enemyIterator != theEnemy.end(); ++enemyIterator)
		{
			if ((*enemyIterator)->isActive())
			{
				targetMdl.renderMdl((*enemyIterator)->getPosition(), (*enemyIterator)->getRotation(), (*enemyIterator)->getScale());
				(*enemyIterator)->update(elapsedTime);
			}
		}

		pistolMdl.renderMdl(thePlayer.getPosition(), thePlayer.getRotation(), thePlayer.getScale());
		
		// target Y should be between 5.0f - 30.0f
		//targetMdl.renderMdl(glm::vec3(0.0f, 0.5f, 5.0f), 0.0f, glm::vec3(1.0f, 1.0f, 1.0f));


		thePlayer.update(elapsedTime);
		
		/*
		for (vector<cLaser*>::iterator laserIterartor = theTardisLasers.begin(); laserIterartor != theTardisLasers.end(); ++laserIterartor)
		{
			if ((*laserIterartor)->isActive())
			{
				theLaser.renderMdl((*laserIterartor)->getPosition(), (*laserIterartor)->getRotation(), (*laserIterartor)->getScale());
				(*laserIterartor)->update(elapsedTime);
			}
		}
		*/
		for (vector<cBullet*>::iterator bulletIterartor = theBullets.begin(); bulletIterartor != theBullets.end(); ++bulletIterartor)
		{
			if ((*bulletIterartor)->isActive())
			{
				theBullet.renderMdl((*bulletIterartor)->getPosition(),(*bulletIterartor)->getRotation(), (*bulletIterartor)->getScale());
				(*bulletIterartor)->update(elapsedTime);
			}
		}
		


		outputMsg = to_string(bulletsLeft) + "/" + to_string(magazineSize);//to_string(theEnemy.size()); // convert float to string
		if (autoFollowBullet)
		{
			autoFollowBulletText = "Follow bullet ENABLED";
		}
		else
		{
			autoFollowBulletText = "Follow bullet DISABLED";
		}


		glDisable(GL_LIGHTING);
		glPushMatrix();
		theOGLWnd.setOrtho2D(windowWidth, windowHeight);

		theFontMgr->getFont("Text")->printText("Crimson shooting", FTPoint(10, 50, 0.0f), textColor);
		theFontMgr->getFont("Text")->printText("Bullets: ", FTPoint(690, 50, 0.0f), textColor); // uses c_str to convert string to LPCSTR
		theFontMgr->getFont("SevenSeg")->printText(outputMsg.c_str(), FTPoint(900, 50, 0.0f), textColor); // uses c_str to convert string to LPCSTR
		theFontMgr->getFont("TextSmall")->printText(autoFollowBulletText.c_str(), FTPoint(750, 130, 0.0f), textColor); // uses c_str to convert string to LPCSTR
		glPopMatrix();

		//glEnable(GL_LIGHTING);
		pgmWNDMgr->swapBuffers();

		tCount += elapsedTime;

		//Clear key buffers
		theInputMgr->clearBuffers(theInputMgr->KEYS_DOWN_BUFFER | theInputMgr->KEYS_PRESSED_BUFFER);

	}

	theOGLWnd.shutdown(); //Free any resources
	pgmWNDMgr->destroyWND(); //Destroy the program window

	return 0; //Return success
}
