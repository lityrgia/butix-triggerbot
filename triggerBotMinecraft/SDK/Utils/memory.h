#pragma once
#include <Windows.h>
#include <psapi.h>
#include <vector>
#include <string>

class Memory {
public:
    template <typename T>
    static T GetAbsoluteAddress(uintptr_t address, int offset);

    static uintptr_t FindPattern(const char* moduleName, const char* pattern);

    static bool findStringInProcessMemory(const std::string& target);
};

template <typename T>
T Memory::GetAbsoluteAddress(uintptr_t address, int offset) {
    if (!address) {
        return nullptr;
    }

    // Получаем относительное смещение
    int32_t relativeOffset = *reinterpret_cast<int32_t*>(address + offset);

    // Вычисляем абсолютный адрес
    uintptr_t absoluteAddress = address + offset + sizeof(int32_t) + relativeOffset;

    return reinterpret_cast<T>(absoluteAddress);
}
