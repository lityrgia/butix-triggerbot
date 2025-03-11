#pragma once
#include <memory>
#include <iostream>
#include <Windows.h>
#include <jni.h>
#include "../SDK/Utils/xorstr.hpp"

namespace butix {
	class Butix
	{
	public:

		void attach();
		JavaVM* getJvm();
		JNIEnv* getEnv();
		void getLaunchwrapper();
		jclass findClass(const char* name);


		bool isOptifine()
		{
			if (!isCheckedOptifine)
			{
				isCheckedOptifine = true;
				jclass forgeClass = env->FindClass(xorstr_("net/minecraft/launchwrapper/Launch"));
				if (forgeClass != NULL)
				{
					env->DeleteLocalRef(forgeClass);
					isOptifineExisting = true;
				}
			}
			return isOptifineExisting;
		}

		void shouldDetach() { unload = true; }

		bool isUnload() { return unload; }

	private:
		jmethodID findclass_md;
		jobject launchloader_obj;
		JavaVM* jvm;
		JNIEnv* env;
		bool isCheckedOptifine = false;
		bool isOptifineExisting = false;
		bool unload = false;
	};
	
	inline std::unique_ptr<Butix> instance = nullptr;
}