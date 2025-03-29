#ifndef AIMBOT_H
#define AIMBOT_H

#include "Player.h"
#include "Vector3.h"

#include <cmath>
#include <numbers>
#include <vector>

class Aimbot
{
public:
	Aimbot(const Player& player, const std::vector<Player>& playerList) noexcept;

	void aimAtHead() const noexcept;

private:
	const Player&              m_player;
	const std::vector<Player>& m_playerList;
};

#endif