#include "../Shared/Offsets.h"
#include "../Shared/Player.h "
#include "../Shared/Process.h"
#include "../Shared/Vector3.h"

int main()
{
	try
	{
		Process process { L"Ac_ClIeNt.ExE" };
		Player  player  { process.getAddress() };
	}
	catch (const std::runtime_error& error)
	{
		std::println("{}", error.what());
	}
	
	return 0;
}