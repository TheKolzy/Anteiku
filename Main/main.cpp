#include "Process.h"

#include <print>

int main()
{
	try
	{
		Process process { L"NoTePaD.eXe" };
	}
	catch (const std::exception& exception)
	{
		std::println("{}", exception.what());
	}

	return 0;
}