#include "Hack.h"

Hack::Hack(std::wstring_view processName)
try
	: m_process { processName }, m_memory { m_process.getIdentifier() }
	, m_player { m_process.getAddress() + static_cast<std::uintptr_t>(Offsets::g_player) }
{
}
catch (const std::exception& exception) {
    std::println("{}", exception.what());
    std::exit(EXIT_FAILURE);
}