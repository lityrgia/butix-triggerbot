#define IMGUI_DISABLE_METRICS_WINDOW
#define IMGUI_DISABLE_DEBUG_LOG
#define IMGUI_DISABLE_DEBUG_TOOLS
#include "SDK/includes.h"

#pragma comment(lib, "libMinHook.x64.lib")

#include <GL/gl.h>
#pragma comment(lib, "OpenGL32.lib")

void initCheat(HMODULE hModule){

    butix::instance = std::make_unique<butix::Butix>();
    butix::instance->attach();

    if (butix::instance->isOptifine()) {
        butix::instance->getLaunchwrapper();
    }

    ImGuiHook::Load(renderGui);

    minecraft::instance = std::make_unique<minecraft::CMinecraft>();
    minecraft::instance->getMinecraft();
    
    while (!butix::instance->isUnload()) {
        auto localPlayer = minecraft::instance->getLocalPlayer();
        if (localPlayer == nullptr) {
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            continue;
        }
        else if (localPlayer != (void*)player::instance.get()) player::instance = std::make_unique<player::CPlayer>(localPlayer);

        if(options::triggerbot::isEnabled) TriggerBot::run();

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    ImGuiHook::Unload();
    butix::instance->getJvm()->DetachCurrentThread();
    FreeLibraryAndExitThread(hModule, EXIT_SUCCESS);
}

bool __stdcall DllMain(HMODULE hModule, DWORD reasonCall, LPVOID lpReserved) {
    static std::thread mainThread;

    if (reasonCall == DLL_PROCESS_ATTACH) {

        mainThread = std::thread([hModule] {initCheat(hModule); });
        if (mainThread.joinable()) {
            mainThread.detach();
        }
    }
    else if (reasonCall == DLL_PROCESS_DETACH) {

    }

    return true;
}