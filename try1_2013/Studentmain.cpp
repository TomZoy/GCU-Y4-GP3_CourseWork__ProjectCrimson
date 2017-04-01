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


	allowBaloons = false;
	perfectCombo = false;


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

	// Create Texture maps
	//cTexture laserTexture;
	//laserTexture.createTexture("Models/laser.tga");

	cTexture bulletTexture;
	bulletTexture.createTexture("Models/Crimson/bullet_rife/Brass.jpg");

	//cTexture starTexture;
	//starTexture.createTexture("Images/star.png");

	cTexture hitTexture;
	hitTexture.createTexture("Models/Crimson/hitText.jpg");

	cTexture backgroundTexture;
	backgroundTexture.createTexture("Images/gun-range.jpg");

	cTexture pistolTexture;
	pistolTexture.createTexture("Models/Crimson/pistol/textures/simpleGrey.jpg"); //handgun_C.jpg");

	vector<cTexture*> targetTextureList;

	cTexture targetTexture1;
	targetTexture1.createTexture("Models/Crimson/target/textures/texture1.jpg");
	targetTextureList.push_back(&targetTexture1);
	cTexture targetTexture2;
	targetTexture2.createTexture("Models/Crimson/target/textures/texture2.jpg");
	targetTextureList.push_back(&targetTexture2);
	cTexture targetTexture3;
	targetTexture3.createTexture("Models/Crimson/target/textures/texture3.jpg");
	targetTextureList.push_back(&targetTexture3);
	cTexture targetTexture4;
	targetTexture4.createTexture("Models/Crimson/target/textures/texture4.jpg");
	targetTextureList.push_back(&targetTexture4);
	cTexture targetTexture5;
	targetTexture5.createTexture("Models/Crimson/target/textures/texture5.jpg");
	targetTextureList.push_back(&targetTexture5);
	cTexture targetTexture6;
	targetTexture1.createTexture("Models/Crimson/target/textures/texture6.jpg");
	targetTextureList.push_back(&targetTexture6);




	// the starfield
	cStarfield theStarField(backgroundTexture.getTexture(), glm::vec3(5.0f, 5.0f, 5.0f));

	// Create Materials for lights
	cMaterial sunMaterial(lightColour4(0.0f, 0.0f, 0.0f, 1.0f), lightColour4(1.0f, 1.0f, 1.0f, 1.0f), lightColour4(1.0f, 1.0f, 1.0f, 1.0f), lightColour4(0, 0, 0, 1.0f), 5.0f);

	// Create Light
	
	cLight sunLight(GL_LIGHT0, lightColour4(0, 0, 0, 1), lightColour4(1, 1, 1, 1), lightColour4(1, 1, 1, 1), glm::vec4(0, 0, 20, 1),
		glm::vec3(0.0, 0.0, 1.0), 0.0f, 180.0f, 1.0f, 0.0f, 0.0f);
	cLight lfLight(GL_LIGHT1, lightColour4(0, 0, 0, 1), lightColour4(1, 1, 1, 1), lightColour4(1, 1, 1, 1), glm::vec4(30, 0, 50, 1),
		glm::vec3(0.0, 0.0, 1.0), 0.0f, 180.0f, 1.0f, 0.0f, 0.0f);
	cLight rfLight(GL_LIGHT2, lightColour4(0, 0, 0, 1), lightColour4(1, 1, 1, 1), lightColour4(1, 1, 1, 1), glm::vec4(-30, 0, 50, 1),
		glm::vec3(0.0, 0.0, 1.0), 0.0f, 180.0f, 1.0f, 0.0f, 0.0f);
	//cLight cbLight(GL_LIGHT3, lightColour4(0, 0, 0, 1), lightColour4(1, 1, 1, 1), lightColour4(1, 1, 1, 1), glm::vec4(0, 0, -100, 1),
	//		glm::vec3(0.0, 0.0, 1.0), 0.0f, 180.0f, 1.0f, 0.0f, 0.0f);
	//Define Ambient light for scene
	GLfloat g_Ambient[] = { 0.2, 0.2, 0.2, 1.0 };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, g_Ambient);

	// load game fonts
	LPCSTR gameFonts[3] = { "Fonts/digital-7.ttf", "Fonts/gunplay-rg.ttf", "Fonts/doctor_who.ttf" };

	theFontMgr->addFont("SevenSeg", gameFonts[0], 55);
	theFontMgr->addFont("Text", gameFonts[1], 50);
	theFontMgr->addFont("TextSmall", gameFonts[1], 25);
	theFontMgr->addFont("drWho", gameFonts[2], 50);


	// load game sounds
	//LPCSTR gameSounds[3] = { "Audio/who10Edit.wav", "Audio/shot007.wav", "Audio/explosion2.wav" };
	LPCSTR BGM[5] = { "Audio/BGM/wav/radio1-_01_A_Night_Of_Dizzy_Spells.wav", "Audio/BGM/wav/radio2_-01_The_Misadventure_Begins.wav", "Audio/BGM/wav/radio3_-04_Cold_as_Steel.wav", "Audio/BGM/wav/radio4_-.wav", "Audio/BGM/wav/radio5_-09_The_Day_Time_Ran_Away.wav" };
	LPCSTR SFX[9] = { "Audio/SFX/wav/fireGun.wav", "Audio/SFX/wav/reload.wav", "Audio/SFX/wav/ricochet1.wav", "Audio/SFX/wav/ricochet2.wav", "Audio/SFX/wav/ricochet3.wav", "Audio/SFX/wav/targetHit.wav", "Audio/SFX/wav/gunEmpty.wav", "Audio/SFX/wav/bounce.wav", "Audio/SFX/wav/Mario-coin-sound.wav" };

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
	theSoundMgr->hitSoundList.push_back("ricochet1SFX");
	theSoundMgr->add("ricochet2SFX", SFX[3]);
	theSoundMgr->hitSoundList.push_back("ricochet2SFX");
	theSoundMgr->add("ricochet3SFX", SFX[4]);
	theSoundMgr->hitSoundList.push_back("ricochet3SFX");
	theSoundMgr->add("targetHitSFX", SFX[5]);
	theSoundMgr->hitSoundList.push_back("targetHitSFX");
	theSoundMgr->add("emptyGunSFX", SFX[6]);
	theSoundMgr->add("bounce", SFX[7]);
	theSoundMgr->add("marioCoin", SFX[8]);



	// Create a camera
	cCamera camera1;
	camera1.setTheCameraPos(glm::vec3(0.0f, 3.0f, 15.0f));
	camera1.setTheCameraLookAt(glm::vec3(0.0f, 0.0f, 0.0f));
	camera1.setTheCameraUpVector(glm::vec3(0.0f, 1.0f, 0.0f)); // pointing upwards in world space
	camera1.setTheCameraAspectRatio(windowWidth, windowHeight);
	camera1.setTheProjectionMatrix(120.0f, camera1.getTheCameraAspectRatio(), 0.1f, 500.0f);
	camera1.update();
	theCameraMgr->add("camera1", &camera1);

	// Create another camera
	cCamera camera2(windowWidth, windowHeight);
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
	cModelLoader baloonMdl;
	baloonMdl.loadModel("Models/Crimson/baloonZ.obj", hitTexture);

	//// pistol
	cModelLoader pistolMdl;
	pistolMdl.loadModel("Models/Crimson/pistol/Handgun_obj.obj", pistolTexture); // Player


	cModelLoader theBullet;
	theBullet.loadModel("Models/Crimson/bullet_rife/50_Barrett.obj", bulletTexture);

	vector<cModelLoader*> targetModelList;
	for (unsigned i = 0; i < targetTextureList.size(); i++)
	{
		targetModelList.push_back(new cModelLoader);
		targetModelList[i]->loadModel("Models/Crimson/target/target2.obj", *targetTextureList[i]);
	}

	cModelLoader targetMdl;
	targetMdl.loadModel("Models/Crimson/target/target2.obj", *targetTextureList.front());

	//enemy spawn loop
	for (int loop = 0; loop < 6; loop++)
	{
		theEnemy.push_back(new cEnemy);

		theEnemy[loop]->setIsActive(true);
		theEnemy[loop]->setScale(glm::vec3(2, 2, 1));
		theEnemy[loop]->setMdlRadius(2.0f);
		theEnemy[loop]->setPosition(glm::vec3(0.0f, 0.0f, 50.0f));

		theEnemy[loop]->ID = loop;
		theEnemy[loop]->randomise(6, 0, 6); // they will spawn on X -3->+3 Y 0 Z -3->+3
	}

	//baloon spawn loop
	for (int loop = 0; loop < 10; loop++)
	{
		theBaloonList.push_back(new cBaloon);

		theBaloonList[loop]->setIsActive(false);
		theBaloonList[loop]->setScale(glm::vec3(2, 2, 1));
		theBaloonList[loop]->setMdlRadius(2.0f);
		theBaloonList[loop]->setPosition(glm::vec3(0.0f, -15.0f, 10.0f));
		theBaloonList[loop]->setDirection(glm::vec3(0, 1, 0));
		theBaloonList[loop]->ID = loop;
		theBaloonList[loop]->setSpeed(0.01f);
		theBaloonList[loop]->randomise(22, 6, 0);
	}


	cPlayer thePlayer;
	thePlayer.initialise(glm::vec3(0, 0, 0), 90.0f, glm::vec3(1, 1, 1), glm::vec3(0, 0, 0), 5.0f, true);
	thePlayer.setMdlDimensions(pistolMdl.getModelDimensions());
	thePlayer.attachInputMgr(theInputMgr);
	thePlayer.attachSoundMgr(theSoundMgr);
	thePlayer.attachCameraMgr(theCameraMgr);
	theSoundMgr->attachInputMgr(theInputMgr);

	float tCount = 0.0f;
	targetHitCount = 0;


	string outputMsg;
	string targetHitText;
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
		theOGLWnd.initOGL(windowWidth, windowHeight);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		theCameraMgr->updateCamera();
		//glLoadMatrixf((GLfloat*)&activeCamera->getTheViewMatrix());//.getTheViewMatrix());
		glLoadMatrixf((GLfloat*)&(theCameraMgr->getCurrentCamera())->getTheViewMatrix());//.getTheViewMatrix());


		//theStarField.renderFull(windowWidth, windowHeight);


		sunMaterial.useMaterial();


		sunLight.lightOn();
		lfLight.lightOn();
		//rfLight.lightOn();
		//cbLight.lightOn();

		for (vector<cEnemy*>::iterator enemyIterator = theEnemy.begin(); enemyIterator != theEnemy.end(); ++enemyIterator)
		{
			if ((*enemyIterator)->isActive())
			{
				targetModelList.at((*enemyIterator)->ID)->renderMdl((*enemyIterator)->getPosition(), (*enemyIterator)->getRotation(), (*enemyIterator)->getScale());
				(*enemyIterator)->update(elapsedTime);
			}
		}

		pistolMdl.renderMdl(thePlayer.getPosition(), thePlayer.getRotation(), thePlayer.getScale());
		thePlayer.update(elapsedTime);

		//debug model
		baloonMdl.renderMdl(glm::vec3(0.0f, 8.0f, 10.0f), 0.0f, glm::vec3(1.0f, 1.0f, 1.0f));




		//bullet rendering
		for (vector<cBullet*>::iterator bulletIterartor = theBullets.begin(); bulletIterartor != theBullets.end(); ++bulletIterartor)
		{
			if ((*bulletIterartor)->isActive())
			{
				theBullet.renderMdl((*bulletIterartor)->getPosition(), (*bulletIterartor)->getRotation(), (*bulletIterartor)->getScale());
				(*bulletIterartor)->update(elapsedTime);
			}
		}

		//baloon rendering
		if (allowBaloons) //if all the targets are eliminated, triggered by cPlayer check
		{
			int baloonsOutOfGame = 0; //how many baloos are already off the screen
			for (vector<cBaloon*>::iterator baloonIterartor = theBaloonList.begin(); baloonIterartor != theBaloonList.end(); ++baloonIterartor)
			{
				if ((*baloonIterartor)->isActive())
				{
					baloonMdl.renderMdl((*baloonIterartor)->getPosition(), (*baloonIterartor)->getRotation(), (*baloonIterartor)->getScale());
					(*baloonIterartor)->update(elapsedTime);
					
					if ((*baloonIterartor)->getPosition().y > 8.0f)
						baloonsOutOfGame++;
				}
			}

			if (baloonsOutOfGame == theBaloonList.size()) //if all the baloons are out the srceen, is game over
				isGameOver = true;
		}

		outputMsg = to_string(bulletsLeft) + "/" + to_string(magazineSize);
		targetHitText = to_string(targetHitCount);
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
		theFontMgr->getFont("TextSmall")->printText("Targets hit: ", FTPoint(10, 130, 0.0f), textColor);
		theFontMgr->getFont("SevenSeg")->printText(targetHitText.c_str(), FTPoint(160, 130, 0.0f), textColor);
		if (perfectCombo)
			theFontMgr->getFont("SevenSeg")->printText("PERFECT COMBO!", FTPoint(240, 130, 0.0f), textColor);

		glPopMatrix();

		glEnable(GL_LIGHTING);
		pgmWNDMgr->swapBuffers();

		tCount += elapsedTime;

		//Clear key buffers
		theInputMgr->clearBuffers(theInputMgr->KEYS_DOWN_BUFFER | theInputMgr->KEYS_PRESSED_BUFFER);

	}

	theOGLWnd.shutdown(); //Free any resources
	pgmWNDMgr->destroyWND(); //Destroy the program window

	return 0; //Return success
}
