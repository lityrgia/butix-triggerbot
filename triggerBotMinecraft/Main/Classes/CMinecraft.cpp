#include "CMinecraft.h"

jobject minecraft::CMinecraft::getMinecraft() {
	jfieldID field = nullptr;

	cls = butix::instance->findClass(xorstr_("djz"));
	field = butix::instance->getEnv()->GetStaticFieldID(cls, xorstr_("F"), xorstr_("Ldjz;"));

	obj = butix::instance->getEnv()->GetStaticObjectField(cls, field);

	return obj;
}

jobject minecraft::CMinecraft::getLocalPlayer() {

	auto player_fid = butix::instance->getEnv()->GetFieldID(getClass(), "s", xorstr_("Ldzm;"));

	jobject res = butix::instance->getEnv()->GetObjectField(getObj(), player_fid);

	return res;
}

jobject minecraft::CMinecraft::getObjectPosition() {

	auto player_fid = butix::instance->getEnv()->GetFieldID(getClass(), "u", xorstr_("Laqa;"));

	jobject res = butix::instance->getEnv()->GetObjectField(getObj(), player_fid);

	return res;
}