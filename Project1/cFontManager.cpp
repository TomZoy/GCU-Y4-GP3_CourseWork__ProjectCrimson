/*
== == == == == == == == =
cFontManager.h
- Header file for class definition - SPECIFICATION
- Header file for the cFontManager class
== == == == == == == == =
*/

#include "cFontManager.h"

cFontManager* cFontManager::pInstance = NULL;

/*
=================================================================================
Singleton Design Pattern
=================================================================================
*/
cFontManager* cFontManager::getInstance()
{
	if (pInstance == NULL)
	{
		pInstance = new cFontManager();
	}
	return cFontManager::pInstance;
}

/*
=================================================================================
Constructor
=================================================================================
*/
cFontManager::cFontManager()
{

}

cFontManager::~cFontManager()							// Destructor.
{
	deleteFont();
}
void cFontManager::addFont(LPCSTR fontName, LPCSTR fileName, int fontSize)  // add font to the Font collection
{
	if (!getFont(fontName))
	{
		cFont * newFont = new cFont(fileName, fontSize);
		gameFonts.insert(make_pair(fontName, newFont));
	}
}

cFont* cFontManager::getFont(LPCSTR fontName)				// return the font for use
{
	map<LPCSTR, cFont*>::iterator theFont = gameFonts.find(fontName);
	if (theFont != gameFonts.end())
	{
		return theFont->second;
	}
	else
	{
		return NULL;
	}
}

void cFontManager::deleteFont()								// delete font.
{
	for (map<LPCSTR, cFont*>::const_iterator theFont = gameFonts.begin(); theFont != gameFonts.end(); theFont++)
	{
		delete theFont->second;
	}
}
