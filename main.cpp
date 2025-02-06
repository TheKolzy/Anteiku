#include "Memory/Memory.h"
#include "Offsets/Offsets.h"
#include "Player/Player.h"
#include "Process/Process.h"

int main()
{
	const Process process { L"Ac_ClIeNt.ExE" };
	const Memory  memory  { process.getPID() };

	Player player { Offsets::g_playerEnt + process.getAddress() };
	std::println("{}", player.getHealth());

	return 0;
}