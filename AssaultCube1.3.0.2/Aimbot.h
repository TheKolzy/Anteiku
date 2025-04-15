#pragma once

#include "PlayerEnt.h"

#include <print>
#include <vector>

class Aimbot
{
public:
	Aimbot(const PlayerEnt& playerEnt, const std::vector<PlayerEnt>& botEnt) noexcept;
	Aimbot() noexcept = default;

	void aimAtHead() const noexcept;

private:
	const PlayerEnt*              m_playerEnt {};
	const std::vector<PlayerEnt>* m_botEnt    {};
};