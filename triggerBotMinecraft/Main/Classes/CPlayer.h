#pragma once
#include <jni.h>
#include "../Main/Modules/Butix.h"
#include "CMinecraft.h"
#include "../SDK/types.h"

namespace player {
	class CPlayer
	{
	public:
		CPlayer(jobject obj) : obj(obj) {}

		bool getLastOnGround();
		vec3 getPosition();

		jclass getClass() {
			if (cls == nullptr) {
				cls = butix::instance->getEnv()->GetObjectClass(obj);
			}

			return cls;
		}
		jobject getObj() { return obj; }

	private:
		jclass cls = nullptr;
		jobject obj;
	};

	inline std::unique_ptr<CPlayer> instance = nullptr;
}