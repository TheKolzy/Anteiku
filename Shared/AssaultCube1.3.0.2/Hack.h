#ifndef HACK_H
#define HACK_H

#include "Memory.h"
#include "Offsets.h"
#include "Player.h"
#include "Process.h"

#include <print>
#include <string_view>

class Hack
{
public:
	explicit Hack(std::wstring_view processName);

private:
	const Process m_process;
	const Memory  m_memory;

	const Player  m_player;
};

#endif