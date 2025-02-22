#ifndef OFFSETS_H
#define OFFSETS_H

#include <array>

namespace Offsets
{
	inline constexpr std::ptrdiff_t g_playerEnt             { 0x18AC00 };

	inline constexpr std::ptrdiff_t g_headVector            { 0x4      };
	inline constexpr std::ptrdiff_t g_bodyVector            { 0x28     };
	inline constexpr std::ptrdiff_t g_cameraVector          { 0x34     };
	inline constexpr std::ptrdiff_t g_health                { 0xEC     };
	inline constexpr std::ptrdiff_t g_armor                 { 0xF0     };
	inline constexpr std::ptrdiff_t g_isShooting            { 0x204    };
	inline constexpr std::ptrdiff_t g_name                  { 0x205    };
	// 0 = CLA (RED), 1 = RVSF (BLUE)
	inline constexpr std::ptrdiff_t g_team                  { 0x30C    };
	inline constexpr std::ptrdiff_t g_isDead                { 0x318    };
	inline constexpr std::array<std::ptrdiff_t, 3> g_reload { 0x364, 0x10, 0x0 };
	inline constexpr std::array<std::ptrdiff_t, 3> g_ammo   { 0x364, 0x14, 0x0 };

	inline constexpr std::ptrdiff_t g_botEntList            { 0x18AC04 };
	inline constexpr std::ptrdiff_t g_playerCount           { 0x18AC0C };	
}

#endif