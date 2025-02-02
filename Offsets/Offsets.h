#pragma once

#include <cstddef>

namespace Offsets
{
	inline constexpr std::ptrdiff_t g_playerEnt  { 0x18AC00 };

	inline constexpr std::ptrdiff_t g_headX      { 0x4   };
	inline constexpr std::ptrdiff_t g_headY      { 0x8   };
	inline constexpr std::ptrdiff_t g_headZ      { 0xC   };
	inline constexpr std::ptrdiff_t g_bodyX      { 0x28  };
	inline constexpr std::ptrdiff_t g_bodyY      { 0x2C  };
	inline constexpr std::ptrdiff_t g_bodyZ      { 0x30  };
	inline constexpr std::ptrdiff_t g_viewX      { 0x34  };
	inline constexpr std::ptrdiff_t g_viewY      { 0x38  };
	inline constexpr std::ptrdiff_t g_viewZ      { 0x3C  };
	inline constexpr std::ptrdiff_t g_health     { 0xEC  };
	inline constexpr std::ptrdiff_t g_armor      { 0xF0  };
	inline constexpr std::ptrdiff_t g_shoot      { 0x204 };
	inline constexpr std::ptrdiff_t g_name       { 0x205 }; // 16 chars
	inline constexpr std::ptrdiff_t g_weaponPtr  { 0x364 }; // 0x14 + 0x0

	inline constexpr std::ptrdiff_t g_botEntList { 0x18AC04 };
}