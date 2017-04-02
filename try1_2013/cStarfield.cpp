/*
==================================================================================
cStarfield.cpp
==================================================================================
*/

#include "cStarfield.h"

/*
cStarfield::cStarfield()
{
	srand((unsigned)time(NULL));
	setRotAngle(0.0f);
	glGetFloatv(GL_ALIASED_POINT_SIZE_RANGE, m_AliasedPointSizes);
	m_NumStars = 1;
	m_TextureID = 0;
	m_FieldVolume = glm::vec3(1.0f,1.0f,1.0f);
	m_StarPos = glm::vec3(0.0f, 0.0f, 5.0f);

	generateStarField();
}

*/

cStarfield::cStarfield(GLint theTextureID, glm::vec3 theFieldVolume)
{
	srand((unsigned)time(NULL));
	setRotAngle(0.0f);
	glGetFloatv(GL_ALIASED_POINT_SIZE_RANGE, m_AliasedPointSizes);
	m_NumStars = 1;
	m_TextureID = theTextureID;
	m_FieldVolume = theFieldVolume;
	m_StarPos = glm::vec3(0.0f, 0.0f, 0.0f);
	generateStarField();
}

void cStarfield::render(float rotation)
{
}

void cStarfield::renderFull(int windowWidth, int windowHeight)
{
	glMatrixMode(GL_MODELVIEW);


	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, m_TextureID);
	glPushMatrix();
	glLoadIdentity();
	
	glEnable(GL_POINT_SPRITE);
	glTexEnvi(GL_POINT_SPRITE, GL_COORD_REPLACE, GL_TRUE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glDepthMask(GL_FALSE);
	glEnable(GL_POINT_SIZE);
	glPointSize(10000.0f);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);


	glm::vec3 pointInSpace;
	glBegin(GL_POINTS);

	for (int loop = 0; loop < m_StarField.size(); loop++)
	{ 	
		pointInSpace = m_StarField.at(loop);
		glVertex3f(pointInSpace.x, pointInSpace.y, pointInSpace.z);
	}
	glEnd();
	
	glDisable(GL_POINT_SIZE);
	glDisable(GL_POINT_SPRITE);
	



	glDisable(GL_TEXTURE_2D);
	glDepthMask(GL_TRUE);
	glPopMatrix();
}

void cStarfield::initialise(cTexture theTexture)
{
	srand((unsigned)time(NULL));
	glBindTexture(GL_TEXTURE_2D, theTexture.getTexture());
}

void cStarfield::initialise(GLint theTextureID, glm::vec3 theFieldVolume)
{
	srand((unsigned)time(NULL));
	m_TextureID = theTextureID;
	m_FieldVolume = theFieldVolume;

	glBindTexture(GL_TEXTURE_2D, m_TextureID);

}

//generate the PlayerHit effect
void cStarfield::generateStarField()
{
	float rowHeight = 0.0f;

	//middle ROW
	m_StarPos.x = 0.0f;
	m_StarPos.y = rowHeight;
	m_StarField.push_back(glm::vec3(m_StarPos.x, m_StarPos.y, -1.0f));

	m_StarPos.x = -0.275f;
	m_StarPos.y = rowHeight;
	m_StarField.push_back(glm::vec3(m_StarPos.x, m_StarPos.y, -1.0f));

	m_StarPos.x = -0.55f;
	m_StarPos.y = rowHeight;
	m_StarField.push_back(glm::vec3(m_StarPos.x, m_StarPos.y, -1.0f));

	m_StarPos.x = 0.276f;
	m_StarPos.y = rowHeight;
	m_StarField.push_back(glm::vec3(m_StarPos.x, m_StarPos.y, -1.0f));

	m_StarPos.x = 0.551f;
	m_StarPos.y = rowHeight;
	m_StarField.push_back(glm::vec3(m_StarPos.x, m_StarPos.y, -1.0f));

	//top ROW

	rowHeight = 0.276f;

	m_StarPos.x = 0.0f;
	m_StarPos.y = rowHeight;
	m_StarField.push_back(glm::vec3(m_StarPos.x, m_StarPos.y, -1.0f));

	m_StarPos.x = -0.275f;
	m_StarPos.y = rowHeight;
	m_StarField.push_back(glm::vec3(m_StarPos.x, m_StarPos.y, -1.0f));

	m_StarPos.x = -0.55f;
	m_StarPos.y = rowHeight;
	m_StarField.push_back(glm::vec3(m_StarPos.x, m_StarPos.y, -1.0f));

	m_StarPos.x = 0.276f;
	m_StarPos.y = rowHeight;
	m_StarField.push_back(glm::vec3(m_StarPos.x, m_StarPos.y, -1.0f));

	m_StarPos.x = 0.551f;
	m_StarPos.y = rowHeight;
	m_StarField.push_back(glm::vec3(m_StarPos.x, m_StarPos.y, -1.0f));

	//bottom ROW

	rowHeight = -0.275f;

	m_StarPos.x = 0.0f;
	m_StarPos.y = rowHeight;
	m_StarField.push_back(glm::vec3(m_StarPos.x, m_StarPos.y, -1.0f));

	m_StarPos.x = -0.275f;
	m_StarPos.y = rowHeight;
	m_StarField.push_back(glm::vec3(m_StarPos.x, m_StarPos.y, -1.0f));

	m_StarPos.x = -0.55f;
	m_StarPos.y = rowHeight;
	m_StarField.push_back(glm::vec3(m_StarPos.x, m_StarPos.y, -1.0f));

	m_StarPos.x = 0.276f;
	m_StarPos.y = rowHeight;
	m_StarField.push_back(glm::vec3(m_StarPos.x, m_StarPos.y, -1.0f));

	m_StarPos.x = 0.551f;
	m_StarPos.y = rowHeight;
	m_StarField.push_back(glm::vec3(m_StarPos.x, m_StarPos.y, -1.0f));

}