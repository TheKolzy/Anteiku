#include "Memory.h"
#include "Process.h"

#include <print>

int main()
{
	try
	{
		const Process process { L"Ac_ClIeNt.ExE" };
		const Memory  memory  { process.getIdentifier() };
	}
	catch (const std::exception& exception)
	{
		std::println("{}", exception.what());
	}

	return 0;
}