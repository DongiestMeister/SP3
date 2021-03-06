#ifndef ICETOWER_H
#define ICETOWER_H

#include "Tower.h"
#include "ParticleGenerator.h"
#include "IceProjectile.h"

class IceTower : public Tower
{
public:
	IceTower();
	~IceTower();

	ParticleGenerator particleGenerator;

	virtual IceProjectile* GetProjectile();
	virtual void Update(double dt);
	virtual bool LevelUp();
	virtual void Fire(double dt);
	virtual void UpdateMesh();


	static ESSENCE_TYPE type;
	static int cost;
	static int ecost;
	float f_SlowDura;
	float f_SlowAmount;

private:
};

#endif