#include "Aimbot.h"

Aimbot::Aimbot(const Player& player, std::uintptr_t processAddress) noexcept
	: m_Player { player }, m_processAddress { processAddress }
{
	m_playerCount = { processAddress + Offsets::g_playerCount };
	m_EntityList  = { Process::read<std::uintptr_t>(processAddress + Offsets::g_EntityList) };

	std::println("[Player Count]: {}", getPlayerCount());
	m_EntityList += 0x4;
	for (int i {}; i < getPlayerCount() - 1; ++i)
	{
		std::uintptr_t playerAddress { Process::read<std::uintptr_t>(m_EntityList) };
		m_bots.push_back(Player { playerAddress });
		m_EntityList += 0x4;
	}
}

std::uint8_t Aimbot::getPlayerCount() const noexcept
{
	return Process::read<std::uint8_t>(m_processAddress + Offsets::g_playerCount);
}

Vector3<float> Aimbot::calculateAngleHead() const noexcept
{
	Vector3<float> relativeDistance { m_bots[0].getHead() - m_Player.getHead() };
	float hypotenuse { std::sqrt
		( std::pow(m_bots[0].getHead().getX() - m_Player.getHead().getX(), 2.0f)
		+ std::pow(m_bots[0].getHead().getY() - m_Player.getHead().getY(), 2.0f)
		+ std::pow(m_bots[0].getHead().getZ() - m_Player.getHead().getZ(), 2.0f)) };
	float y { std::asin(relativeDistance.getZ() / hypotenuse)
		* (180 / static_cast<float>(std::numbers::pi)) };

	float x { std::atan2(relativeDistance.getY(), relativeDistance.getX())
		* (180 / static_cast<float>(std::numbers::pi)) + 90.0f };

	return Vector3<float> { x, y, 0 };
}


void Aimbot::aimAtHead() const noexcept
{
	if (!m_bots[0].getDead())
		m_Player.setView(calculateAngleHead());
}