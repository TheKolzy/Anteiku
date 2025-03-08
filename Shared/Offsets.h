#pragma once

#include <array>

namespace Offsets
{
	inline constexpr std::ptrdiff_t g_Player                { 0x18AC00 };
	
	inline constexpr std::ptrdiff_t g_head                  { 0x004 };
	inline constexpr std::ptrdiff_t g_body                  { 0x028 };
	inline constexpr std::ptrdiff_t g_view                  { 0x034 };
	inline constexpr std::ptrdiff_t g_health                { 0x0EC };
	inline constexpr std::ptrdiff_t g_armor                 { 0x0F0 };
	inline constexpr std::ptrdiff_t g_shoot                 { 0x204 };
	inline constexpr std::ptrdiff_t g_name                  { 0x205 };
	inline constexpr std::ptrdiff_t g_team                  { 0x30C };
	inline constexpr std::ptrdiff_t g_dead                  { 0x318 };
	inline constexpr std::array<std::ptrdiff_t, 3> g_reload { 0x364, 0x10, 0x0 };
	inline constexpr std::array<std::ptrdiff_t, 3> g_ammo   { 0x364, 0x14, 0x0 };

	inline constexpr std::ptrdiff_t g_EntityList            { 0x18AC04 };
	inline constexpr std::ptrdiff_t g_playerCount           { 0x18AC0C };
}