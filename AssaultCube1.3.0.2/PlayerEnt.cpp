#include "Memory.h"
#include "Offsets.h"
#include "PlayerEnt.h"

PlayerEnt::PlayerEnt(std::uintptr_t address) noexcept
	: m_baseAddress { address }
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