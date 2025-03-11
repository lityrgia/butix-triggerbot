#pragma once
#include <jni.h>
#include <iostream>
#include "../SDK/Utils/xorstr.hpp"
#include "../Main/Modules/Butix.h"
#include <memory>

namespace minecraft {
	class CMinecraft
	{
	public:

		jobject getMinecraft();
		jobject getLocalPlayer();
		jobject getObjectPosition();
		jclass getClass() {
			if (cls == nullptr) {
				cls = butix::instance->getEnv()->GetObjectClass(obj);
			}

			return cls;
		}
		jobject getObj() { return obj; }

	private:
		jclass cls = nullptr;
		jobject obj = nullptr;
	};

	inline std::unique_ptr<CMinecraft> instance;
}
