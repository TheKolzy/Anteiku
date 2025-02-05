#pragma once

#include <cstddef>

namespace Offsets
{
	inline constexpr std::ptrdiff_t g_playerEnt  { 0x18AC00 };

	inline constexpr std::ptrdiff_t g_health { 0xEC  };
	inline constexpr std::ptrdiff_t g_armor  { 0xF0  };
	inline constexpr std::ptrdiff_t g_shoot  { 0x204 };
}