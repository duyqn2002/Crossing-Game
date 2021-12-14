#ifndef CENEMY_FACTORY_H
#define CENEMY_FACTORY_H

#include "CCAR.h"
#include "CTRUCK.h"
#include "CDOG.h"
#include "CBIRD.h"

class CEnemyFactory
{
public:
	static Movable* createEneny(const ENEMY& enemyType) {
		switch (enemyType)
		{
		case ENEMY::CCAR:
			return new CCAR();
		case ENEMY::CTRUCK:
			return new CTRUCK();
		case ENEMY::CBIRD:
			return new CBIRD();
		case ENEMY::CDOG:
			return new CDOG();
		default:
			return nullptr;
		}
	}
};

#endif // CENEMY_FACTORY_H
