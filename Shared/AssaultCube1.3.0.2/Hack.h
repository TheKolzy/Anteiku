#ifndef HACK_H
#define HACK_H

#include "Aimbot.h"
#include "ESP.h"
#include "Memory.h"
#include "Offsets.h"
#include "Player.h"
#include "Process.h"
#include "ViewMatrix.h"

#include <cstdint>
#include <print>
#include <string_view>
#include <vector>

class Hack // Not Const
{
public:
	explicit Hack(std::wstring_view processName);
	~Hack() noexcept = default;

	void run() noexcept; // Not Const

private:
	void initializePlayerList() noexcept;

	std::vector<Player> m_playerList {};

	// --- //

	const Process       m_process;
	const Memory        m_memory;

	const Player        m_player;
	const Aimbot        m_aimbot;
	const ViewMatrix    m_viewMatrix;
	ESP                 m_esp;
};

#endif