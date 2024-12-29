#pragma once
typedef  unsigned int uint;
typedef  unsigned short ushort;

namespace options {
	namespace menu {
		inline bool isMenuVisible{ true };
		inline ushort toggleButton{ 0x2d };
	}

	namespace triggerbot {
		inline ushort toggleButton{ 0x0 };
		inline bool isEnabled{ false };
		inline int delay{ 600 };
		inline int randomFactorMs{10};
		inline float hitChance{ 100.f };
		inline float distance{ 4.f };
		inline bool attackMobs{ false };
		inline bool attackPlayers{ false };
		inline bool attackMirnich{ false };
		inline bool attackInvisibles{ false };
		inline bool onlyCrits{ false };
	}
}