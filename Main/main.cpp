#include "Memory.h"
#include "Offsets.h"
#include "Player.h"
#include "Process.h"

#include <print>

int main()
{
	try
	{
		const Process process { L"Ac_ClIeNt.ExE" };
		const Memory  memory  { process.getIdentifier() };
		const Player  player  { process.getAddress()
			+ static_cast<std::uintptr_t>(Offsets::g_player) };
	}
	catch (const std::exception& exception)
	{
		std::println("{}", exception.what());
	}

	return 0;
}