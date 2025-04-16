#include "Hack.h"

// Essentials

#include "Memory.h"
#include "Process.h"

// Modules

#include "Aimbot.h"
#include "PlayerEnt.h"

#include "Offsets.h"

#include <cstdint>
#include <print>
#include <stdexcept>
#include <string_view>
#include <vector>

Hack::Hack(std::wstring_view processName) noexcept
try
	: m_process { std::make_unique<const Process>(processName) }
	, m_memory  { std::make_unique<const Memory> (m_process->getIdentifier()) }
{
	m_playerEnt = { std::make_unique<const PlayerEnt>(Memory::read<std::uintptr_t>
		(m_process->getBaseAddress() + Offsets::g_playerEnt)) };
	initializeBotEnt();
	m_aimbot = std::make_unique<const Aimbot>(*m_playerEnt, *m_botEnt);
}
catch (const std::runtime_error& error)
{
	std::println("{}", error.what());
	std::exit(EXIT_FAILURE);
}

void Hack::run() const noexcept
{
	while (true)
	{
	}
}

void Hack::initializeBotEnt() noexcept
{
	std::uintptr_t botEntAddress { Memory::read<std::uintptr_t>
		(m_process->getBaseAddress() + Offsets::g_botEnt) };
	botEntAddress += 0x4;
	const int botEntCount { Memory::read<int>
		(m_process->getBaseAddress() + Offsets::g_botEntCount) };

	for (int i {}; i < botEntCount - 1; ++i)
	{
		m_botEnt->push_back(PlayerEnt { Memory::read<std::uintptr_t>(botEntAddress) });
		botEntAddress += 0x4;
	}
}