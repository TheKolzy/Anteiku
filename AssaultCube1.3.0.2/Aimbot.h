#pragma once

#include "PlayerEnt.h"

#include <vector>

class Aimbot
{
public:
	Aimbot(const PlayerEnt& playerEnt, const std::vector<PlayerEnt>& botEnt) noexcept;

	              void  aimAtHead  () const noexcept;
	[[nodiscard]] float getDistance() const noexcept;

private:
	const PlayerEnt&              m_playerEnt;
	const std::vector<PlayerEnt>& m_botEnt;
};