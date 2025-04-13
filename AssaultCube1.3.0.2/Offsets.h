#pragma once

#include <cstddef>

namespace Offsets
{
	inline constexpr std::ptrdiff_t g_playerEnt  { 0x18AC00 };

	inline constexpr std::ptrdiff_t g_health     { 0xEC  };
	inline constexpr std::ptrdiff_t g_armor      { 0xF0  };
	inline constexpr std::ptrdiff_t g_isShooting { 0x204 };
	inline constexpr std::ptrdiff_t g_name       { 0x205 };
	inline constexpr std::ptrdiff_t g_team       { 0x30C };
	inline constexpr std::ptrdiff_t g_isDead     { 0x318 };
}