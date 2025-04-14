#include "Hack.h"
#include "Memory.h"
#include "Offsets.h"
#include "PlayerEnt.h"
#include "Process.h"

#include <cstdint>
#include <print>
#include <stdexcept>
#include <string_view>

Hack::Hack(std::wstring_view processName) noexcept
try
	: m_process { processName }, m_memory { m_process.getIdentifier() }
{
	m_playerEnt = PlayerEnt { Memory::read<std::uintptr_t>
		(m_process.getBaseAddress() + Offsets::g_playerEnt) };
	initializeBotEnt();
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
		(m_process.getBaseAddress() + Offsets::g_botEnt) };
	botEntAddress += 0x4;
	const int botEntCount { Memory::read<int>
		(m_process.getBaseAddress() + Offsets::g_botEntCount) };
	for (int i {}; i < botEntCount - 1; ++i)
	{
		m_botEnt.push_back(PlayerEnt { Memory::read<std::uintptr_t>(botEntAddress) });
		botEntAddress += 0x4;
	}	
}