#pragma once

#include <array>
#include <cstddef>

namespace Offsets
{
	inline constexpr std::ptrdiff_t g_playerEnt  { 0x18AC00 };

	inline constexpr std::ptrdiff_t g_health { 0xEC  };
	inline constexpr std::ptrdiff_t g_armor  { 0xF0  };
	inline constexpr std::ptrdiff_t g_shoot  { 0x204 };
	inline constexpr std::ptrdiff_t g_name   { 0x205 };
	inline constexpr std::array<std::ptrdiff_t, 3> g_ammo { 0x364, 0x14, 0x0 };
}