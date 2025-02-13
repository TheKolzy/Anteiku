#include "Player.h"

Player::Player(std::uintptr_t address)
{
	m_player = Memory::read<std::uintptr_t>(address);

	m_health = m_player + Offsets::g_health;
	m_armor  = m_player + Offsets::g_armor;
	m_shoot  = m_player + Offsets::g_shoot;
	m_name   = m_player + Offsets::g_name;
	m_ammo   = Memory::calculateAddress<Offsets::g_ammo.size()>
		(m_player, Offsets::g_ammo);
}

std::uint8_t Player::getHealth() const
{
	return Memory::read<std::uint8_t>(m_health);
}

void Player::setHealth(std::uint8_t value) const
{
	Memory::write<std::uint8_t>(m_health, value);
}

std::uint8_t Player::getArmor() const
{
	return Memory::read<std::uint8_t>(m_armor);
}

void Player::setArmor(std::uint8_t value) const
{
	Memory::write<std::uint8_t>(m_armor, value);
}

bool Player::getShoot() const
{
	return Memory::read<bool>(m_shoot);
}

void Player::setShoot(bool value) const
{
	Memory::write<bool>(m_shoot, value);
}

std::string Player::getName() const
{
	return Memory::read<std::array<char, 16>>(m_name).data();
}

void Player::setName(std::string_view value) const
{
	std::array<char, 16> lastName {};
	std::memcpy(lastName.data(), value.data(), std::min<std::size_t>
		(value.size(), lastName.size() - 1));
	Memory::write<std::array<char, 16>>(m_name, lastName);
}

std::uint8_t Player::getAmmo() const
{
	return Memory::read<std::uint8_t>(m_ammo);
}

void Player::setAmmo(std::uint8_t value) const
{
	Memory::write<std::uint8_t>(m_ammo, value);
}