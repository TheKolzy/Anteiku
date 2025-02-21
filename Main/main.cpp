#include "../Shared/Process.h"

int main()
{
	try
	{
		Process process { L"NoTePaD.eXe" };
	}
	catch (const std::exception& exception)
	{
		std::println(stderr, "{}", exception.what());
	}
	
	return 0;
}