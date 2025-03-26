#include "Player.h"

Player::Player(std::uintptr_t address) noexcept
	: m_player { Memory::read<std::uintptr_t>(address) }
{
}

Vector3<float> Player::getHead() const noexcept
{
	return Vector3<float> { Memory::read<float>(m_player + Offsets::g_head)
		, Memory::read<float>(m_player + Offsets::g_head + 0x4)
		, Memory::read<float>(m_player + Offsets::g_head + 0x8) };
}

Vector3<float> Player::getBody() const noexcept
{
	return Vector3<float> { Memory::read<float>(m_player + Offsets::g_body)
		, Memory::read<float>(m_player + Offsets::g_body + 0x4)
		, Memory::read<float>(m_player + Offsets::g_body + 0x8) };
}

Vector3<float> Player::getView() const noexcept
{
	return Vector3<float> { Memory::read<float>(m_player + Offsets::g_view)
		, Memory::read<float>(m_player + Offsets::g_view + 0x4)
		, Memory::read<float>(m_player + Offsets::g_view + 0x8) };
}

std::int8_t Player::getHealth() const noexcept
{
	return Memory::read<std::int8_t>(m_player + Offsets::g_health);
}

std::uint8_t Player::getArmor() const noexcept
{
	return Memory::read<std::uint8_t>(m_player + Offsets::g_armor);
}

bool Player::isShooting() const noexcept
{
	return Memory::read<bool>(m_player + Offsets::g_isShooting);
}

std::string Player::getName() const noexcept
{
	return Memory::read<std::array<char, 16>>(m_player + Offsets::g_name).data();
}

std::uint8_t Player::getTeam() const noexcept
{
	return Memory::read<std::uint8_t>(m_player + Offsets::g_team);
}

bool Player::isAlive() const noexcept
{
	return !Memory::read<bool>(m_player + Offsets::g_isAlive);
}

std::uint8_t Player::getAmmo() const noexcept
{
	return Memory::read<std::uint8_t>(Memory::resolveAddress(m_player, Offsets::g_ammo));
}

void Player::setBody(Vector3<float> value) const noexcept
{
	Memory::write(m_player + Offsets::g_body      , value.getX());
	Memory::write(m_player + Offsets::g_body + 0x4, value.getY());
	Memory::write(m_player + Offsets::g_body + 0x8, value.getZ());
}

void Player::setView(Vector3<float> value) const noexcept
{
	Memory::write(m_player + Offsets::g_view      , value.getX());
	Memory::write(m_player + Offsets::g_view + 0x4, value.getY());
	Memory::write(m_player + Offsets::g_view + 0x8, value.getZ());
}

void Player::setHealth(std::int8_t value) const noexcept
{
	Memory::write(m_player + Offsets::g_health, value);
}

void Player::setArmor(std::uint8_t value) const noexcept
{
	Memory::write(m_player + Offsets::g_armor, value);
}

void Player::setShooting(bool value) const noexcept
{
	Memory::write(m_player + Offsets::g_isShooting, value);
}

void Player::setName(std::string_view value) const noexcept
{
	std::array<char, 16> name {};
	std::size_t size { std::min(value.size(), name.size() - 1) };
	std::copy_n(value.begin(), size, name.begin());
	name[size] = '\0';
	
	Memory::write(m_player + Offsets::g_name, name);
}

void Player::setTeam(std::uint8_t value) const noexcept
{
	Memory::write(m_player + Offsets::g_team, value);
}

void Player::setAmmo(std::uint8_t value) const noexcept
{
	Memory::write(Memory::resolveAddress(m_player, Offsets::g_ammo), value);
}