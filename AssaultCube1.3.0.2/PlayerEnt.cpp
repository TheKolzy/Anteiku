#include "Memory.h"
#include "Offsets.h"
#include "PlayerEnt.h"

#include <algorithm>
#include <array>
#include <cstdint>
#include <string>
#include <string_view>

PlayerEnt::PlayerEnt(std::uintptr_t baseAddress) noexcept
	: m_baseAddress { baseAddress }
{
}

std::int8_t PlayerEnt::getHealth() const noexcept
{
	return Memory::read<std::int8_t>(m_baseAddress + Offsets::g_health);
}

void PlayerEnt::setHealth(std::int8_t buffer) const noexcept
{
	Memory::write(m_baseAddress + Offsets::g_health, buffer);
}

std::uint8_t PlayerEnt::getArmor() const noexcept
{
	return Memory::read<std::uint8_t>(m_baseAddress + Offsets::g_armor);
}

void PlayerEnt::setArmor(std::uint8_t buffer) const noexcept
{
	Memory::write(m_baseAddress + Offsets::g_armor, buffer);
}

bool PlayerEnt::isShooting() const noexcept
{
	return Memory::read<bool>(m_baseAddress + Offsets::g_isShooting);
}

void PlayerEnt::setShooting(bool buffer) const noexcept
{
	Memory::write(m_baseAddress + Offsets::g_isShooting, buffer);
}

std::string PlayerEnt::getName() const noexcept
{
	return Memory::read<std::array<char, 16>>(m_baseAddress + Offsets::g_name).data();
}

void PlayerEnt::setName(std::string_view buffer) const noexcept
{
	std::array<char, 16> name {};
	const std::size_t length { std::min(name.size() - 1, buffer.size()) };
	std::copy_n(buffer.begin(), length, name.begin());
	name[length] = '\0';

	Memory::write(m_baseAddress + Offsets::g_name, name);
}

std::uint8_t PlayerEnt::getTeam() const noexcept
{
	return Memory::read<std::uint8_t>(m_baseAddress + Offsets::g_team);
}

void PlayerEnt::setTeam(std::uint8_t buffer) const noexcept
{
	Memory::write(m_baseAddress + Offsets::g_team, buffer);
}

bool PlayerEnt::isDead() const noexcept
{
	return Memory::read<bool>(m_baseAddress + Offsets::g_isDead);
}