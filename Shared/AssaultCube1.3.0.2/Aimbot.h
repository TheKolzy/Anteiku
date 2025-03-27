#ifndef AIMBOT_H
#define AIMBOT_H

#include "Player.h"
#include "Vector3.h"

#include <cmath>
#include <numbers>
#include <print>
#include <vector>

class Aimbot
{
public:
	Aimbot(const Player& player, std::vector<Player>& playerList) noexcept;

	void aimAtHead() const noexcept;

private:
	const Player&        m_player;
	std::vector<Player>& m_playerList;
};

#endif