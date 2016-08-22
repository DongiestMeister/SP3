#include "PoisonTower.h"
#include "SingleTarget.h"

PoisonTower::PoisonTower()
:Tower()
{
	this->i_level = 1;
	this->meshID = GEO_POISONTOWER;
	SetAtkDmg(10);
	SetRange(5);
	SetSpdRate(0.5f);
	this->p_speed = 10.f;
	this->projectile_meshID = GEO_ARROW;
	this->heightOffset.Set(0, 0, 2);
	this->strategy = FIRST_ENEMY;
	s_name = "Arrow Tower";
}

PoisonTower::~PoisonTower()
{

}


Projectile* PoisonTower::GetProjectile()
{
	for (std::vector<Projectile*>::iterator it = projectileList.begin(); it != projectileList.end(); ++it)
	{
		Projectile* projectile = (Projectile*)(*it);
		if (!(projectile->b_isActive))
		{
			projectile->b_isActive = true;
			projectile->meshID = projectile_meshID;
			return projectile;

		}
	}
	for (unsigned i = 0; i <= 10; ++i)
	{

		Projectile* projectile = new SingleTarget(projectile_meshID);
		projectile->b_isActive = false;
		projectileList.push_back(projectile);
	}
	projectileList.back()->b_isActive = true;
	return projectileList.back();
}

void PoisonTower::Update(double dt)
{
	Tower::Update(dt);
}

void PoisonTower::LevelUp()
{
	if (this->i_level >= 2)
	{
		i_level = 2;
	}
	this->i_level++;
	this->atkDamage += 5;
	this->atkRange += 1;
	if (atkRange > 7)
	{
		atkRange = 7;
	}
}