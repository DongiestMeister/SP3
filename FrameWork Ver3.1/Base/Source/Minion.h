#ifndef MINION_H
#define MINION_H

#include "Enemy.h"

class Minion : public Enemy
{
public:
	Minion();
	Minion(Vector3 pos, Node* node);
	virtual ~Minion();
	virtual void UpdateAnim(double dt);
	virtual void ReceivePoisonStatus(float poisonDamage, float slowAmount, float duration);
	virtual void GiveEssence();
	virtual void UpdateMesh();

private:

protected:
	//variables for animation
	bool b_rotateUp;
	float f_rotateSpeed;
	float f_clampRotate;
};

#endif