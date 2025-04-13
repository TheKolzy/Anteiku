#include "Memory.h"
#include "Offsets.h"
#include "PlayerEnt.h"

#include <cstdint>

PlayerEnt::PlayerEnt(std::uintptr_t baseAddress) noexcept
	: m_baseAddress { baseAddress }
{
}

std::uint8_t PlayerEnt::getHealth() const noexcept
{
	return Memory::read<std::uint8_t>(m_baseAddress + Offsets::g_health);
}

void PlayerEnt::setHealth(std::uint8_t buffer) const noexcept
{
	Memory::write(m_baseAddress + Offsets::g_health, buffer);
}