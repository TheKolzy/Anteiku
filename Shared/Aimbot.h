#pragma once

#include "Offsets.h"
#include "Player.h "
#include "Process.h"
#include "Vector3.h"

#include <numbers>
#include <vector>

class Aimbot
{
public:
	Aimbot(const Player& player, std::uintptr_t processAddress) noexcept;

	[[nodiscard]] std::uint8_t getPlayerCount() const noexcept;
	Vector3<float> calculateAngleHead() const noexcept;
	void aimAtHead() const noexcept;
	
private:
	const Player&       m_Player         {};
	std::uintptr_t      m_processAddress {};

	std::uintptr_t      m_playerCount    {};
	std::uintptr_t      m_EntityList     {};
	std::vector<Player> m_bots           {};
};