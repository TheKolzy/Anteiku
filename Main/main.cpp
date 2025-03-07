#include "../Shared/Process.h"

int main()
{
	try
	{
		Process process { L"Ac_ClIeNt.ExE" };
	}
	catch (const std::runtime_error& error)
	{
		std::println("{}", error.what());
	}
	
	return 0;
}