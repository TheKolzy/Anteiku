#include "PlayerEnt.h"

PlayerEnt::PlayerEnt(std::uintptr_t address) noexcept
{
	m_playerEnt    = Process::read<std::uintptr_t>(address);

	m_headVector   = m_playerEnt + Offsets::g_headVector;
	m_bodyVector   = m_playerEnt + Offsets::g_bodyVector;
	m_cameraVector = m_playerEnt + Offsets::g_cameraVector;
	m_health       = m_playerEnt + Offsets::g_health;
	m_armor        = m_playerEnt + Offsets::g_armor;
	m_isShooting   = m_playerEnt + Offsets::g_isShooting;
	m_name         = m_playerEnt + Offsets::g_name;
	m_team         = m_playerEnt + Offsets::g_team;
	m_isDead       = m_playerEnt + Offsets::g_isDead;
	m_reload       = Process::resolveAddress(m_playerEnt, Offsets::g_reload);
	m_ammo         = Process::resolveAddress(m_playerEnt, Offsets::g_ammo);
}

Vector3<float> PlayerEnt::getHeadVector() const noexcept
{
	return Vector3<float> { Process::read<float>(m_headVector)
		, Process::read<float>(m_headVector + 0x4)
		, Process::read<float>(m_headVector + 0x8) };
}

Vector3<float> PlayerEnt::getBodyVector() const noexcept
{
	return Vector3<float> { Process::read<float>(m_bodyVector)
		, Process::read<float>(m_bodyVector + 0x4)
		, Process::read<float>(m_bodyVector + 0x8) };
}

void PlayerEnt::setBodyVector(const Vector3<float>& vector) const noexcept
{
	Process::write<float>(m_bodyVector,       vector.getX());
	Process::write<float>(m_bodyVector + 0x4, vector.getY());
	Process::write<float>(m_bodyVector + 0x8, vector.getZ());
}

Vector3<float> PlayerEnt::getCameraVector() const noexcept
{
	return Vector3<float> { Process::read<float>(m_cameraVector)
		, Process::read<float>(m_cameraVector + 0x4)
		, Process::read<float>(m_cameraVector + 0x8) };
}

void PlayerEnt::setCameraVector(const Vector3<float>& vector) const noexcept
{
	Process::write<float>(m_cameraVector,       vector.getX());
	Process::write<float>(m_cameraVector + 0x4, vector.getY());
	Process::write<float>(m_cameraVector + 0x8, vector.getZ());
}

std::uint8_t PlayerEnt::getHealth() const noexcept
{
	return Process::read<std::uint8_t>(m_health);
}

void PlayerEnt::setHealth(std::uint8_t value) const noexcept
{
	Process::write(m_health, value);
}

std::uint8_t PlayerEnt::getArmor() const noexcept
{
	return Process::read<std::uint8_t>(m_armor);
}

void PlayerEnt::setArmor(std::uint8_t value) const noexcept
{
	Process::write(m_armor, value);
}

bool PlayerEnt::getIsShooting() const noexcept
{
	return Process::read<bool>(m_isShooting);
}

void PlayerEnt::setIsShooting(bool value) const noexcept
{
	Process::write(m_isShooting, value);
}

std::string PlayerEnt::getName() const noexcept
{
	return Process::read<std::array<char, 16>>(m_name).data();
}

void PlayerEnt::setName(std::string_view value) const noexcept
{
	std::array<char, 16> name {};
	// The name has a maximum of 15 characters
	std::copy_n(value.begin(), 15, name.data());
	Process::write(m_name, name);
}

std::uint8_t PlayerEnt::getTeam() const noexcept
{
	return Process::read<std::uint8_t>(m_team);
}

void PlayerEnt::setTeam(std::uint8_t value) const noexcept
{
	Process::write(m_team, value);
}

std::uint8_t PlayerEnt::getIsDead() const noexcept
{
	return Process::read<std::uint8_t>(m_isDead);
}

std::uint8_t PlayerEnt::getReload() const noexcept
{
	return Process::read<std::uint8_t>(m_reload);
}

void PlayerEnt::setReload(std::uint8_t value) const noexcept
{
	Process::write(m_reload, value);
}

std::uint8_t PlayerEnt::getAmmo() const noexcept
{
	return Process::read<std::uint8_t>(m_ammo);
}

void PlayerEnt::setAmmo(std::uint8_t value) const noexcept
{
	Process::write(m_ammo, value);
}