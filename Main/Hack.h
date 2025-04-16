#pragma once

// Essentials

#include "Memory.h"
#include "Process.h"

// Modules

#include "Aimbot.h"
#include "PlayerEnt.h"

#include <string_view>
#include <vector>

class Hack
{
public:
	explicit Hack(std::wstring_view processName) noexcept;

	void run() const noexcept;

private:
	// Essentials

	const std::unique_ptr<const Process> m_process {};
	const std::unique_ptr<const Memory>  m_memory  {};

	// Modules

	void initializeBotEnt() noexcept;

	std::unique_ptr<const PlayerEnt>        m_playerEnt {};
	std::unique_ptr<std::vector<PlayerEnt>> m_botEnt    {};
	std::unique_ptr<const Aimbot>           m_aimbot    {};
};