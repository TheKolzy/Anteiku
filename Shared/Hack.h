#pragma once

#include "Aimbot.h "
#include "Offsets.h"
#include "Player.h "
#include "Process.h"

class Hack
{
public:
	explicit Hack(std::wstring_view processName);

	void start() const noexcept;
private:
	Process m_Process;

	Player  m_Player {};
};