#include "PlayerEnt.h"

#include "Memory.h"
#include "Offsets.h"

#include <algorithm>
#include <array>
#include <cstdint>
#include <string>
#include <string_view>

PlayerEnt::PlayerEnt(std::uintptr_t baseAddress) noexcept
	: m_baseAddress { baseAddress }
{
}

Vector3<float> PlayerEnt::getHead() const noexcept
{
	return Vector3<float> {
		  Memory::read<float>(m_baseAddress + Offsets::g_head + 0x0)
		, Memory::read<float>(m_baseAddress + Offsets::g_head + 0x4)
		, Memory::read<float>(m_baseAddress + Offsets::g_head + 0x8) };
}

Vector3<float> PlayerEnt::getBody() const noexcept
{
	return Vector3<float> {
		  Memory::read<float>(m_baseAddress + Offsets::g_body + 0x0)
		, Memory::read<float>(m_baseAddress + Offsets::g_body + 0x4)
		, Memory::read<float>(m_baseAddress + Offsets::g_body + 0x8) };
}

void PlayerEnt::setBody(const Vector3<float>& buffer) const noexcept
{
	Memory::write(m_baseAddress + Offsets::g_body + 0x0, buffer.getX());
	Memory::write(m_baseAddress + Offsets::g_body + 0x4, buffer.getY());
	Memory::write(m_baseAddress + Offsets::g_body + 0x8, buffer.getZ());
}

Vector3<float> PlayerEnt::getView() const noexcept
{
	return Vector3<float> {
		  Memory::read<float>(m_baseAddress + Offsets::g_view + 0x0)
		, Memory::read<float>(m_baseAddress + Offsets::g_view + 0x4)
		, Memory::read<float>(m_baseAddress + Offsets::g_view + 0x8) };
}

void PlayerEnt::setView(const Vector3<float>& buffer) const noexcept
{
	Memory::write(m_baseAddress + Offsets::g_view + 0x0, buffer.getX());
	Memory::write(m_baseAddress + Offsets::g_view + 0x4, buffer.getY());
	Memory::write(m_baseAddress + Offsets::g_view + 0x8, buffer.getZ());
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

std::uint8_t PlayerEnt::getAmmo() const noexcept
{
	return Memory::read<std::uint8_t>(Memory::resolveAddress(m_baseAddress, Offsets::g_ammo));
}

void PlayerEnt::setAmmo(std::uint8_t buffer) const noexcept
{
	Memory::write(Memory::resolveAddress(m_baseAddress, Offsets::g_ammo), buffer);
}