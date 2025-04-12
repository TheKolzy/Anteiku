#include "Memory.h"
#include "Process.h"

#include <print>
#include <stdexcept>

int main()
{
	try
	{
		const Process process { L"Ac_ClIeNt.ExE" };
		const Memory  memory  { process.getIdentifier() };
	}
	catch (const std::runtime_error& error)
	{
		std::println("{}", error.what());
	}

	return 0;
}