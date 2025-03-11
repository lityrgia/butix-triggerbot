#include "CPlayer.h"
#include "../SDK/Utils/xorstr.hpp"
#include "CEntity.h"

bool player::CPlayer::getLastOnGround() {

	jfieldID field = butix::instance->getEnv()->GetFieldID(getClass(), xorstr_("ca"), xorstr_("Z"));

	return butix::instance->getEnv()->GetBooleanField(getObj(), field);
}

vec3 player::CPlayer::getPosition() {

	jfieldID x_field = butix::instance->getEnv()->GetFieldID(getClass(), xorstr_("bV"), xorstr_("D"));
	jfieldID y_field = butix::instance->getEnv()->GetFieldID(getClass(), xorstr_("bW"), xorstr_("D"));
	jfieldID z_field = butix::instance->getEnv()->GetFieldID(getClass(), xorstr_("bX"), xorstr_("D"));

	vec3 res{ butix::instance->getEnv()->GetDoubleField(getObj(), x_field)
		, butix::instance->getEnv()->GetDoubleField(getObj(), y_field)
		, butix::instance->getEnv()->GetDoubleField(getObj(), z_field) };

	return res;
}