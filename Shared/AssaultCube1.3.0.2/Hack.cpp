#include "Hack.h"

Hack::Hack(std::wstring_view processName)
try
	: m_process    { processName }, m_memory { m_process.getIdentifier() }
	, m_player     { m_process.getAddress() + static_cast<std::uintptr_t>(Offsets::g_player) }
	, m_aimbot     { m_player, m_playerList }
	, m_viewMatrix { m_process.getAddress() + Offsets::g_viewMatrix }
	, m_esp        { m_viewMatrix , m_playerList }
{
	initializePlayerList();
}
catch (const std::exception& exception) {
    std::println("{}", exception.what());
    std::exit(EXIT_FAILURE);
}

void Hack::run() noexcept // Not Const
{
	while (true)
	{
		m_esp.run();
	}
}

void Hack::initializePlayerList() noexcept
{
	const int playerCount { Memory::read<int>(m_process.getAddress() + Offsets::g_playerCount) };
	std::uintptr_t addressPlayerList { Memory::read<std::uintptr_t>
		(m_process.getAddress() + Offsets::g_playerList) };
	addressPlayerList += 0x4;

	for (int i {}; i < playerCount - 1; ++i)
	{
		m_playerList.push_back(Player { addressPlayerList });
		addressPlayerList += 0x4;
	}
}