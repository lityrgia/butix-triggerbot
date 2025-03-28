#include "../Main/Modules/Butix.h"
#include "../SDK/Utils/memory.h"
#include "../SDK/Utils/xorstr.hpp"
#include "../Main/Gui/imguiHook.h"
#include "../Main/Gui/gui.h"

#include "jni.h"

jclass butix::Butix::findClass(const char* name) {
    jclass cls = nullptr;

    if (isOptifineExisting) {
        jstring jname = butix::instance->getEnv()->NewStringUTF(name);
        if (!jname) {
            return nullptr;
        }

        cls = reinterpret_cast<jclass>(env->CallObjectMethod(launchloader_obj, findclass_md, jname));

        butix::instance->getEnv()->DeleteLocalRef(jname);
    }
    else {
        cls = getEnv()->FindClass(name);
    }

    return cls;
}

void butix::Butix::getLaunchwrapper() {

    jclass launch_cls = env->FindClass(xorstr_("net/minecraft/launchwrapper/Launch"));
    if (!launch_cls) return;

    jclass launchwrapper_cls = env->FindClass(xorstr_("net/minecraft/launchwrapper/LaunchClassLoader"));
    if (!launchwrapper_cls) return;

    auto classloader_fid = env->GetStaticFieldID(launch_cls, xorstr_("classLoader"), xorstr_("Lnet/minecraft/launchwrapper/LaunchClassLoader;"));

    findclass_md = env->GetMethodID(launchwrapper_cls, xorstr_("findClass"), xorstr_("(Ljava/lang/String;)Ljava/lang/Class;"));
    if (!findclass_md) return;

    launchloader_obj = env->NewGlobalRef(env->GetStaticObjectField(launch_cls, classloader_fid));
    if (!launchloader_obj) return;

    env->DeleteLocalRef(launchwrapper_cls);
    env->DeleteLocalRef(launch_cls);
}


void butix::Butix::attach() {
		//jvm = Memory::GetAbsoluteAddress<JavaVM*>(Memory::FindPattern(xorstr_("jvm.dll"), xorstr_("48 8D 0D ?? ?? ?? ?? 45 33 C0 FF D0")), 3);
		JNI_GetCreatedJavaVMs(&jvm, 1, nullptr);
	
		if (jvm == nullptr)
		{
			MessageBoxA(0, "ERROR", "Failed to init jvm", MB_ICONASTERISK);
		}

		jvm->AttachCurrentThread((void**)&env, nullptr);
}

JNIEnv* butix::Butix::getEnv()
{
	return env;
}

JavaVM* butix::Butix::getJvm()
{
	return jvm;
}
