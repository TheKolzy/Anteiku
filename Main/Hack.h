#pragma once

#include "Aimbot.h"
#include "Memory.h"
#include "PlayerEnt.h"
#include "Process.h"

#include <string_view>
#include <vector>

class Hack
{
public:
	explicit Hack(std::wstring_view processName) noexcept;
	void run() const noexcept;

private:
	const Process m_process;
	const Memory  m_memory;

	void initializeBotEnt() noexcept;

	PlayerEnt              m_playerEnt {};
	std::vector<PlayerEnt> m_botEnt    {};
	Aimbot                 m_aimbot    {};
};