#include <Windows.h>
#include <psapi.h>
#include <vector>
#include <iostream>
#include "memory.h"
#include <string>

bool Memory::findStringInProcessMemory(const std::string& target) {
    MEMORY_BASIC_INFORMATION mbi;
    char buffer[4096];  // ����� ��� ������ ������ �� ������
    SIZE_T bytesRead;
    SYSTEM_INFO sysInfo;
    GetSystemInfo(&sysInfo);

    // �������� ���������� � ������
    unsigned char* startAddress = (unsigned char*)sysInfo.lpMinimumApplicationAddress;
    unsigned char* endAddress = (unsigned char*)sysInfo.lpMaximumApplicationAddress;

    // �������� ����� ��� �������� ������
    for (unsigned char* addr = startAddress; addr < endAddress; addr += mbi.RegionSize) {
        if (VirtualQuery(addr, &mbi, sizeof(mbi)) == 0)
            continue;

        // ���� ��� ������� ������, ��������� ��� ������
        if (mbi.State == MEM_COMMIT && (mbi.Protect == PAGE_READWRITE || mbi.Protect == PAGE_READONLY)) {
            // �������� �� ������� ����� � ������� ������
            for (unsigned char* ptr = addr; ptr < addr + mbi.RegionSize; ++ptr) {
                if (memcmp(ptr, target.c_str(), target.length()) == 0) {
                    std::cout << "Found string at address: " << (void*)ptr << std::endl;
                    return true;  // ������ �������
                }
            }
        }
    }
    return false;  // ������ �� �������
}

uintptr_t Memory::FindPattern(const char* moduleName, const char* pattern) {
    // �������� ���������� ������
    HMODULE hModule = GetModuleHandleA(moduleName);
    if (!hModule) {
        return 0;
    }

    // �������� ���������� � ������
    MODULEINFO moduleInfo;
    if (!GetModuleInformation(GetCurrentProcess(), hModule, &moduleInfo, sizeof(MODULEINFO))) {
        return 0;
    }

    // ����������� ������� �� ������ � ������ ������ � �������
    auto patternToByte = [](const char* pattern) {
        std::vector<int> bytes;
        const char* current = pattern;

        while (*current) {
            // ��������� ������� ������ ��������

            if (*current == '?') {
                ++current;
                if (*current == '?') ++current;  // ��������� '??'
                bytes.push_back(-1); // Wildcard
            }
            else if (isxdigit(*current)) { // ��������, �������� �� ������ ����������������� ������
                char* end;
                long value = strtoul(current, &end, 16);

                // ���������, ��� �� ���������� ������ �����
                if (end == current) {
                    break;  // ��������� ���������� ��� ������
                }

                bytes.push_back(static_cast<int>(value));

                current = end; // ��������� � ���������� �������
            }
            else {
                ++current;  // ���������� ������������ ������
            }
        }
        return bytes;
    };

    std::vector<int> patternBytes = patternToByte(pattern);
    if (patternBytes.empty()) {
        return 0;
    }

    BYTE* scanStart = reinterpret_cast<BYTE*>(moduleInfo.lpBaseOfDll);
    size_t size = moduleInfo.SizeOfImage;

    // ����� �������� � ������ ������
    size_t patternSize = patternBytes.size();
    int* patternData = patternBytes.data();

    for (size_t i = 0; i < size - patternSize; ++i) {
        bool found = true;
        for (size_t j = 0; j < patternSize; ++j) {
            if (scanStart[i + j] != patternData[j] && patternData[j] != -1) {
                found = false;
                break;
            }
        }
        if (found) {
            //std::cout << "Found pattern with address: " << std::hex << reinterpret_cast<uintptr_t>(&scanStart[i]) << std::endl;
            return reinterpret_cast<uintptr_t>(&scanStart[i]);
        }
    }

    return 0;
}