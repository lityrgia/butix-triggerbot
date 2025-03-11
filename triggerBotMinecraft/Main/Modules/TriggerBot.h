#pragma once
#include "../Main/Classes/CEntity.h"

class TriggerBot
{
public:
	static void run();
	static bool checkEntity(std::unique_ptr<entity::CEntity> entity);
};

