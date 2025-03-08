#include "Player.h"

Player::Player(std::uintptr_t processAddress) noexcept
{
	m_Player = Process::read<std::uintptr_t>(processAddress + Offsets::g_Player);

	m_head   = m_Player + Offsets::g_head;
	m_body   = m_Player + Offsets::g_body;
	m_view   = m_Player + Offsets::g_view;
	m_health = m_Player + Offsets::g_health;
	m_armor  = m_Player + Offsets::g_armor;
	m_shoot  = m_Player + Offsets::g_shoot;
	m_name   = m_Player + Offsets::g_name;
	m_team   = m_Player + Offsets::g_team;
	m_dead   = m_Player + Offsets::g_dead;
	m_reload = Process::calculateAddress(m_Player, Offsets::g_reload);
	m_ammo   = Process::calculateAddress(m_Player, Offsets::g_ammo);
}

Vector3<float> Player::getHead() const noexcept
{
	return Vector3<float> { Process::read<float>(m_head)
		, Process::read<float>(m_head + 0x4)
		, Process::read<float>(m_head + 0x8) };
}

Vector3<float> Player::getBody() const noexcept
{
	return Vector3<float> { Process::read<float>(m_body)
		, Process::read<float>(m_body + 0x4)
		, Process::read<float>(m_body + 0x8) };
}

void Player::setBody(Vector3<float> body) const noexcept
{
	Process::write(m_body + 0x0, body.getX());
	Process::write(m_body + 0x4, body.getY());
	Process::write(m_body + 0x8, body.getZ());
}

Vector3<float> Player::getView() const noexcept
{
	return Vector3<float> { Process::read<float>(m_view)
		, Process::read<float>(m_view + 0x4)
		, Process::read<float>(m_view + 0x8) };
}

void Player::setView(Vector3<float> view) const noexcept
{
	Process::write(m_view + 0x0, view.getX());
	Process::write(m_view + 0x4, view.getY());
	Process::write(m_view + 0x8, view.getZ());
}

std::uint8_t Player::getHealth() const noexcept
{
	return Process::read<std::uint8_t>(m_health);
}

void Player::setHealth(std::uint8_t value) const noexcept
{
	Process::write(m_health, value);
}

std::uint8_t Player::getArmor() const noexcept
{
	return Process::read<std::uint8_t>(m_armor);
}

void Player::setArmor(std::uint8_t value) const noexcept
{
	Process::write(m_armor, value);
}

bool Player::getShoot() const noexcept
{
	return Process::read<std::uint8_t>(m_shoot);
}

void Player::setShoot(bool value) const noexcept
{
	Process::write(m_shoot, value);
}

std::string Player::getName() const noexcept
{
	return Process::read<std::array<char, 16>>(m_name).data();
}

void Player::setName(std::string_view value) const noexcept
{
	std::array<char, 16> valueArray {};
	std::copy_n(value.begin(), min(value.size(), valueArray.size() - 1), valueArray.begin());
	Process::write(m_name, valueArray);
}

std::uint8_t Player::getTeam() const noexcept
{
	return Process::read<std::uint8_t>(m_team);
}

void Player::setTeam(std::uint8_t value) const noexcept
{
	Process::write(m_team, value);
}

bool Player::getDead() const noexcept
{
	return Process::read<bool>(m_dead);
}

std::uint8_t Player::getReload() const noexcept
{
	return Process::read<std::uint8_t>(m_reload);
}

void Player::setReload(std::uint8_t value) const noexcept
{
	Process::write(m_reload, value);
}

std::uint8_t Player::getAmmo() const noexcept
{
	return Process::read<std::uint8_t>(m_ammo);
}

void Player::setAmmo(std::uint8_t value) const noexcept
{
	Process::write(m_ammo, value);
}