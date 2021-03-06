#include "SpeedMonster.h"
#include "PlayerInfo.h"

SpeedMonster::SpeedMonster() :Enemy()
{
	this->meshID = GEO_SPEED;
	this->f_movSpeed = 5.f;
	this->f_maxHealth = 55.f;
	this->f_health = f_maxHealth;
	this->i_damage = 1;
	this->i_defence = 0;
	this->f_rotateSpeed = 90.f;
	this->i_currency = 1;
}

SpeedMonster::SpeedMonster(Vector3 pos, Node* root) :Enemy(pos, root)
{
	this->meshID = GEO_SPEED;
	this->f_movSpeed = 5.f;
	this->f_maxHealth = 55.f;
	this->f_health = f_maxHealth;

	this->i_damage = 1;
	this->i_defence = 0;
	this->f_rotateSpeed = 90.f;
	i_currency = 1;
}

SpeedMonster::~SpeedMonster()
{
}

void SpeedMonster::UpdateAnim(double dt)
{
}

void SpeedMonster::GiveEssence()
{
	//Enemy::GiveCurrency();
	player->i_essenceSpeed += 1;
}

void SpeedMonster::UpdateMesh()
{
	if (f_poisonTimer > 0)
	{
		this->meshID = GEO_SPEED_POISON;
	}
	else if (f_slowTimer > 0)
	{
		this->meshID = GEO_SPEED_FROST;
	}
	else
	{
		this->meshID = GEO_SPEED;
	}
}
