#include "PlayerInfo.h"

PlayerInfo::PlayerInfo()
{
	Init();
}

PlayerInfo::~PlayerInfo()
{
}

void PlayerInfo::Init()
{
	i_health = 30;
	i_currency = 50;
	i_essenceBasic = 0;
	i_essenceIce = 0;
	i_essenceSpeed = 0;
	i_essenceTanky = 0;
}