#include "Enemy.h"
#include "PlayerInfo.h"
#include "Music.h"

Enemy::Enemy()
{
	f_movSpeed = 5.f;
	f_maxHealth = 10.f;
	f_health = f_maxHealth;
	i_defence = 0;
	i_damage = 0;
	f_slow = 0;
	i_currency = 0;
	this->rotation.Set(0, 0, 0);
	this->scale.Set(1, 1, 1);
	this->pos.Set(0, 0, 0);
	this->player = nullptr;

	hp.meshID = GEO_HP;
	hp.b_lightEnabled = false;
	hp.b_Render = false;
	f_showHealthTimer = 0.f;
	f_poisonTimer = 0.f;
	f_slowTimer = 0.f;
	f_poisonDps = 0.f;
}

Enemy::Enemy(Vector3 pos, Node* root)
{
	f_movSpeed = 5.f;
	f_maxHealth = 10;
	f_health = f_maxHealth;
	i_defence = 0;
	i_damage = 0;
	f_slow = 0;
	i_currency = 0;
	this->rotation.Set(0, 0, 0);
	this->scale.Set(1, 1, 1);
	this->pos = pos;
	this->nxtTile = root;
	this->player = nullptr;

	hp.meshID = GEO_HP;
	hp.pos.z = 1.f;
	hp.b_shadows = false;
	hp.b_lightEnabled = false;
	hp.b_Render = false;
	f_showHealthTimer = 0.f;
	
	f_poisonTimer = 0.f;
	f_slowTimer = 0.f;
	f_poisonDps = 0.f;
}

Enemy::~Enemy()
{
}

void Enemy::MoveTo(Vector2 dest, double dt)
{
	float rotationSpeed = 360.f;
	Vector3 view = Vector3(dest.x,dest.y,0)- Vector3(pos.x, pos.y,0) ;
	if (view.Length() == Math::EPSILON)
	{
		return;
	}
	view.Normalize();
	float rotationZToBe = Math::RadianToDegree(atan2(view.y,view.x)); // the rotation that we want it to be at;
	
	rotationZToBe = round(rotationZToBe);
	
	if (this->rotation.z != rotationZToBe)// to rotate the model if the enemy is turning
	{
		if (rotationZToBe < 0) // making sure rotationZToBe is withiin 0 and 360
		{
			rotationZToBe += 360;
		}
		else if (rotationZToBe == -0)
		{
			rotationZToBe = 0;
		}
		
		if (abs(rotationZToBe - rotation.z) <180)
		{
			if (rotationZToBe > rotation.z)
			{

				rotation.z += rotationSpeed * dt;
				if (rotationZToBe < rotation.z)
				{
					rotation.z = rotationZToBe;
				}


			}
			else if (rotationZToBe < rotation.z)
			{
				rotation.z -= rotationSpeed * dt;
				if (rotationZToBe > rotation.z)
				{
					rotation.z = rotationZToBe;
				}
			}
		}
		else
		{
			if (rotationZToBe > rotation.z)
			{

				rotation.z -= rotationSpeed * dt;
				if (rotation.z < 0.f) // wind around if negative numbers
				{
					rotation.z += 360;
				}
				else if (rotation.z == -0.f) // negate negative 0;
				{
					rotation.z = 0;
				}

			}
			else if (rotationZToBe < rotation.z)
			{
				rotation.z += rotationSpeed * dt;
				if (rotation.z >360.f)
				{
					rotation.z -= 360;
				}
			}
		}
	}

	if (this->f_showHealthTimer > 0.f)
	{
		//hp.pos.Set(0, 0, 1);
		hp.b_Render = true;
		hp.pos.x = this->pos.x;
		hp.pos.y = this->pos.y;
		hp.pos.z = this->pos.z + 1.f;
		hp.rotation.z = this->rotation.z;
		hp.scale = Vector3(0.2f, f_health / f_maxHealth, 0.1f);
	}
	view = view * f_movSpeed *((float)(100.f - f_slow) / 100.f) * dt;
	//view = view * f_movSpeed *dt;
	this->pos.x += view.x ;
	this->pos.y += view.y;
}

void Enemy::Update(double dt)
{
	//std::cout << "Updating" << std::endl;

	if (nxtTile != nullptr)
	{
		if ((Vector3(nxtTile->coords.x, nxtTile->coords.y, 0) - Vector3(this->pos.x, this->pos.y, 0)).LengthSquared() < 0.2f*0.2f)
		{
			nxtTile = nxtTile->next;
			if (nxtTile == nullptr)
			{
				return;
			}
		}
		if (f_poisonTimer > 0.f)
		{
			ReceivePoisonDamage(f_poisonDps*dt);
			f_poisonTimer -= dt;
			if (f_poisonTimer <= 0.f)
			{
				f_poisonTimer = 0.f;
			}
		}
		if (f_slowTimer > 0.f)
		{
			f_slowTimer -= dt;
			if (f_slowTimer <= 0.f)
			{
				f_slow = 0.f;
				f_slowTimer = 0.f;
			}
		}
		if (this->f_showHealthTimer > 0.f)
		{
			f_showHealthTimer -= dt;
		}
		else if (this->f_showHealthTimer < 0.f)
		{
			f_showHealthTimer = 0.f;
			hp.b_Render = false;
		}

		MoveTo(nxtTile->coords, dt);
		UpdateAnim(dt);
		UpdateMesh();
	}
	else
	{
		if (player)
		{
			player->i_health -= this->i_damage;
			this->hp.b_isActive = false;
			this->b_isActive = false;
			Music::GetInstance()->PlayMusic(7, false, 0.5);
		}
		
	}
	
}

void Enemy::UpdateAnim(double dt)
{
}

void Enemy::ReceiveDamage(float damage)
{
	float dmg = damage * ((100.f - (float)i_defence) / 100.f);
	this->f_health -= dmg;
	if (f_health <= 0)
	{
		this->GiveCurrency();
		this->hp.b_isActive = false;
		this->b_isActive = false;
	}
	else
	{
		f_showHealthTimer = 1.5f;
	}
}

void Enemy::ReceivePoisonDamage(float damage)
{

	this->f_health -= damage;
	if (f_health <= 0)
	{
		this->GiveCurrency();
		this->hp.b_isActive = false;
		
		this->b_isActive = false;
	}
	else
	{
		f_showHealthTimer = 1.5f;
	}
}

void Enemy::ReceiveSlowStatus(float slowAmount, float duration)
{
	if (slowAmount > this->f_slow)
	{
		this->f_slow = slowAmount;
	}
	if (this->f_slowTimer < duration)
	{
		this->f_slowTimer = duration;
	}
}

void Enemy::ReceivePoisonStatus(float poisonDPS,float slowAmount,float duration)
{
	this->ReceiveSlowStatus(slowAmount,duration);
	if (this->f_poisonDps < poisonDPS)
	{
		this->f_poisonDps = poisonDPS;
	}
	if (this->f_poisonTimer < duration)
	{
		this->f_poisonTimer = duration;
	}
}

void Enemy::GiveCurrency()
{
	player->i_currency += this->i_currency;
	GiveEssence();
}

void Enemy::GiveEssence()
{
}

void Enemy::UpdateMesh()
{

}