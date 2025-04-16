#include "Aimbot.h"

Aimbot::Aimbot(const PlayerEnt& playerEnt, const std::vector<PlayerEnt>& botEnt) noexcept
	: m_playerEnt { playerEnt }, m_botEnt { botEnt }
{
}

void Aimbot::aimAtHead() const noexcept
{
}