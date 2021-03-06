#include "FixedProjectile.h"

FixedProjectile::FixedProjectile(GEOMETRY_TYPE ID) : SplashTarget(ID)
{
	this->meshID = GEO_CANNON;
}

FixedProjectile::~FixedProjectile()
{
}

void FixedProjectile::Update(double dt)
{
	Vector3 d;
	//if (this->b_isActive)
	//{

	//if (enemy->b_isActive == false)
	//{
	//	//iceparticle->ClearParticles();
	//	//this->iceparticle.isActive = false;
	//	this->b_isActive = false;
	//	return;
	//}
	
	d = enemyLastPos - this->pos;
	//this->vel = (this->vel + d *( p_speed / 4.f)).Normalize() * p_speed;
	if (d.IsZero())
	{
		return;
	}
	this->vel = d.Normalized() * p_speed;
	rotation.z = Math::RadianToDegree(atan2(this->vel.y, this->vel.x));
	this->pos += vel * dt;
	float distanceToCheck = 0.04f * p_speed;
	if (d.LengthSquared() <= distanceToCheck * distanceToCheck)
	{
		if (meshID == GEO_CANNON)
		{

			f_particleSpawnTimer = 0.f;

			iceparticle->pos = this->pos;
			iceparticle->pos.z = 2.f;
			iceparticle->SpawnParticle();
		}
		//this->iceparticle.isActive = false;
		this->b_isActive = false;
		if (enemyVec != nullptr)
		{
			for (vector<Enemy*>::iterator it = (*enemyVec).begin(); it != (*enemyVec).end(); ++it)
			{
				if ((*it)->b_isActive == true)
				{
					if (((*it)->pos - this->pos).LengthSquared() < f_range*f_range)
					(*it)->ReceiveDamage(i_damage);
				}
			}
		}
		//std::cout << d.LengthSquared() << std::endl;
	}

}