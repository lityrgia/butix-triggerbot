#include "../Main/Classes/CEntity.h"
#include "../Main/options.h"
#include "CPlayer.h"

int entity::CEntity::getEntityType(){

	jfieldID field = butix::instance->getEnv()->GetFieldID(getClass(), xorstr_("f"), xorstr_("I"));

	jint res = butix::instance->getEnv()->GetIntField(getObj(), field);

	return butix::instance->getEnv()->GetIntField(getObj(), field);
}

bool entity::CEntity::isDead() {

	jfieldID field = butix::instance->getEnv()->GetFieldID(getClass(), xorstr_("y"), xorstr_("Z"));

	jint res = butix::instance->getEnv()->GetBooleanField(getObj(), field);

	return butix::instance->getEnv()->GetBooleanField(getObj(), field);
}

bool entity::CEntity::isInvisible() {

	jmethodID field = butix::instance->getEnv()->GetMethodID(getClass(), xorstr_("bF"), xorstr_("()Z"));

	jint res = butix::instance->getEnv()->CallBooleanMethod(getObj(), field);

	return res;
}

vec3 entity::CEntity::getPosition() {
	jfieldID x_field = butix::instance->getEnv()->GetFieldID(getClass(), xorstr_("D"), xorstr_("D"));
	jfieldID y_field = butix::instance->getEnv()->GetFieldID(getClass(), xorstr_("E"), xorstr_("D"));
	jfieldID z_field = butix::instance->getEnv()->GetFieldID(getClass(), xorstr_("F"), xorstr_("D"));

	vec3 res{ butix::instance->getEnv()->GetDoubleField(getObj(), x_field)
		, butix::instance->getEnv()->GetDoubleField(getObj(), y_field)
		, butix::instance->getEnv()->GetDoubleField(getObj(), z_field) };

	return res;
}