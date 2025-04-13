#include "Memory.h"
#include "Offsets.h"
#include "PlayerEnt.h"
#include "Process.h"

#include <cstdint>
#include <print>
#include <stdexcept>

int main()
{
	try
	{
		const Process   process   { L"Ac_ClIeNt.ExE" };
		const Memory    memory    { process.getIdentifier() };
		const PlayerEnt playerEnt { Memory::read<std::uintptr_t>
			(process.getBaseAddress() + Offsets::g_playerEnt) };
	}
	catch (const std::runtime_error& error)
	{
		std::println("{}", error.what());
	}

	return 0;
}