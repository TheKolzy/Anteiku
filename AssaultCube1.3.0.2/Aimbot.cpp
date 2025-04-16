#include "Aimbot.h"

#include "Vector3.h"

#include <cmath>
#include <numbers>

Aimbot::Aimbot(const PlayerEnt& playerEnt, const std::vector<PlayerEnt>& botEnt) noexcept
	: m_playerEnt { playerEnt }, m_botEnt { botEnt }
{
}

void Aimbot::aimAtHead() const noexcept
{
	const Vector3<float> relativeDistance { m_botEnt[0].getHead() - m_playerEnt.getHead() };

	const float opposite   { relativeDistance.getZ() };
	const float hypotenuse { std::sqrt(
		  std::pow(relativeDistance.getX(), 2.0f)
		+ std::pow(relativeDistance.getY(), 2.0f)
		+ std::pow(relativeDistance.getZ(), 2.0f)) };
	const float pitch      { std::asin(opposite / hypotenuse)
		* (180.0f / static_cast<float>(std::numbers::pi)) };

	float yaw { std::atan2(relativeDistance.getY(), relativeDistance.getX())
		* (180.0f / static_cast<float>(std::numbers::pi)) + 90.0f };
	if (yaw < 0.0f)
		yaw += 360.0f;

	if (!m_botEnt[0].isDead())
		m_playerEnt.setView({ yaw, pitch, 0 });
}