#ifndef HACK_H
#define HACK_H

#include "Memory.h"
#include "Offsets.h"
#include "Player.h"
#include "Process.h"

#include <cstdint>
#include <print>
#include <string_view>
#include <vector>

class Hack
{
public:
	explicit Hack(std::wstring_view processName);
	void run() noexcept;

private:
	void initializePlayerList() noexcept;

	const Process       m_process;
	const Memory        m_memory;

	const Player        m_player;
	std::vector<Player> m_playerList {};
};

#endif