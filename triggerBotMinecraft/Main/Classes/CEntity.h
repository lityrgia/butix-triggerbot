#pragma once
#include <jni.h>
#include "../Main/Modules/Butix.h"
#include "CMinecraft.h"
#include "../SDK/types.h"

namespace entity {
	class CEntity
	{
	public:
		CEntity(jobject _obj) : obj(_obj){

		}

		bool isDead();
		int getEntityType();
		vec3 getPosition();
		jclass getClass() {
			if (cls == nullptr) {
				cls = butix::instance->getEnv()->GetObjectClass(obj);
			}

			return cls;
		}
		jobject getObj() { return obj; }
		bool isInvisible();

	private:
		jclass cls = nullptr;
		jobject obj;
	};
}