#ifndef TANK_MONSTER_H
#define TANK_MONSTER_H

#include "Enemy.h"

class TankMonster :public Enemy
{
public:
	TankMonster();
	TankMonster(Vector3 pos, Node* root);
	~TankMonster();

	virtual void UpdateAnim(double dt);

private:

protected:
	float f_rotateSpeed;

};

#endif