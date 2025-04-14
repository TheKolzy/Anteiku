#pragma once

#include "Memory.h"
#include "PlayerEnt.h"
#include "Process.h"

#include <string_view>

class Hack
{
public:
	explicit Hack(std::wstring_view processName) noexcept;

private:
	const Process m_process;
	const Memory  m_memory;

	PlayerEnt     m_playerEnt {};
};