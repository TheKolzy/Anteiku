#include "Aimbot.h"

Aimbot::Aimbot(const Player& player, const std::vector<Player>& playerList) noexcept
	: m_player { player }, m_playerList { playerList }
{
}

void Aimbot::aimAtHead() const noexcept
{
	const Vector3<float> relativeDistance { m_playerList[0].getHead() - m_player.getHead() };
	
	const float hypotenuse { std::sqrt(std::pow(relativeDistance.getX(), 2.0f)
		+ std::pow(relativeDistance.getY(), 2.0f) + std::pow(relativeDistance.getZ(), 2.0f)) };
	const float opposite   { relativeDistance.getZ() };
	const float pitch      { std::asin(opposite / hypotenuse)
		* (180.0f / static_cast<float>(std::numbers::pi)) };

	const float yaw        { std::atan2(relativeDistance.getY(), relativeDistance.getX())
		* (180.0f / static_cast<float>(std::numbers::pi)) + 90.0f };

	if (m_playerList[0].isAlive())
		m_player.setView({ yaw, pitch, 0 });
}