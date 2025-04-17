#include "Aimbot.h"

#include "Offsets.h"
#include "Vector3.h"

#include <cmath>

Aimbot::Aimbot(const PlayerEnt& playerEnt, const std::vector<PlayerEnt>& botEnt) noexcept
	: m_playerEnt { playerEnt }, m_botEnt { botEnt }
{
}

void Aimbot::aimAtHead() const noexcept
{
	if (m_botEnt[0].isDead())
		return;

	const Vector3<float> relativeDistance { m_botEnt[0].getHead() - m_playerEnt.getHead() };

	const float opposite   { relativeDistance.getZ() };
	const float hypotenuse { std::hypot(
		  relativeDistance.getX()
		, relativeDistance.getY()
		, relativeDistance.getZ()) };
	const float pitch      { std::asin(opposite / hypotenuse) * Offsets::g_radianToDegree };

	float yaw { std::atan2(relativeDistance.getY(), relativeDistance.getX())
		* Offsets::g_radianToDegree + 90.0f };
	if (yaw < 0.0f)	yaw += 360.0f;

	m_playerEnt.setView({ yaw, pitch, 0 });
}

float Aimbot::getDistance() const noexcept
{
	if (m_botEnt[0].isDead())
		return 0.0f;

	const Vector3<float> relativeDistance { m_botEnt[0].getHead() - m_playerEnt.getHead() };
	const float hypotenuse { std::hypot(
		  relativeDistance.getX()
		, relativeDistance.getY()
		, relativeDistance.getZ()) };

	return hypotenuse;
}