#include "cEnemy.h"

cEnemy::cEnemy() : cModel()
{
	
}


//void cEnemy::setModel(cModelLoader model)
//{
//	model = model;
//	this->setMdlDimensions(model.getModelDimensions());
//	//theEnemy[loop]->setMdlDimensions(targetModelList.front()->getModelDimensions());
//}
//
//void cEnemy::render()
//{
//	this->model.renderMdl(this->getPosition(), this->getRotation(), this->getScale());
//	//renderMdl((*enemyIterator)->getPosition(), (*enemyIterator)->getRotation(), (*enemyIterator)->getScale());
//}




void cEnemy::randomise()
{
	//target should spawn -4f - 4f on both x and y

	int targetX = (rand() % 7) - 6;
	cModel::m_mdlPosition.x = targetX;

	//int targetY = (rand() % 3) - 2;
	//cModel::m_mdlPosition.y = targetY;

	int targetZ = (rand() % 6) - 5;
	cModel::m_mdlPosition.z = 50 + targetZ;

	//	cModel::m_mdlSpeed = m_EnemyMinSpeed + rand() / (float)RAND_MAX * m_EnemyMaxSpeed;


	/*
	if (rand() % 2 == 0)
	{
		cModel::m_mdlPosition.x = -PLAYFIELDX;
	}
	else
	{
		cModel::m_mdlPosition.x = PLAYFIELDX;
	}
	cModel::m_mdlPosition.y = 0.0f;
	cModel::m_mdlPosition.z = (rand() / (float)RAND_MAX) * 300.0f;   // random number as a float between 0 & 1
	//cModel::m_mdlRotation = (rand() / (float)RAND_MAX) * 2 * 3.14f;
	cModel::m_mdlDirection.x = -(float)glm::sin(cModel::m_mdlRotation);
	//cModel::m_mdlDirection.z = (float)glm::cos(cModel::m_mdlRotation);
	cModel::m_mdlSpeed = m_EnemyMinSpeed + rand() / (float)RAND_MAX * m_EnemyMaxSpeed;
	cModel::m_IsActive = true;
	*/
}

void cEnemy::update(float elapsedTime)
{
	/*
	cModel::m_mdlPosition += cModel::m_mdlDirection * cModel::m_mdlSpeed * elapsedTime;
	if (cModel::m_mdlPosition.x > PLAYFIELDX)
		cModel::m_mdlPosition.x -= 2 * PLAYFIELDX;
	if (cModel::m_mdlPosition.x < -PLAYFIELDX)
		cModel::m_mdlPosition.x += 2 * PLAYFIELDX;
	if (cModel::m_mdlPosition.z > PLAYFIELDZ)
		cModel::m_mdlPosition.z -= 2 * PLAYFIELDZ;
	if (cModel::m_mdlPosition.z < -PLAYFIELDZ)
		cModel::m_mdlPosition.z += 2 * PLAYFIELDZ;
		*/
}

cEnemy::~cEnemy()
{

}

