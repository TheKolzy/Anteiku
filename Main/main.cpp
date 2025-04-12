#include "Process.h"

#include <print>
#include <stdexcept>

int main()
{
	try
	{
		const Process process { L"NoTePaD.eXe" };
	}
	catch (const std::runtime_error& error)
	{
		std::println("{}", error.what());
	}

	return 0;
}