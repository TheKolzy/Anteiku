#include "Hack.h"

Hack::Hack(std::wstring_view processName)
	: m_Process { processName }
{
	m_Player = { Player { Process::read<std::uintptr_t>(m_Process.getAddress()
		+ Offsets::g_Player) } };
}

void Hack::start() const noexcept
{
	Aimbot aimbot { m_Player, m_Process.getAddress() };

	while (true)
	{
		aimbot.aimAtHead();
	}
}