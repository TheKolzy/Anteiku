#include "../Shared/Offsets.h"
#include "../Shared/PlayerEnt.h"
#include "../Shared/Process.h"
#include "../Shared/Vector3.h"

int main()
{
	try
	{
		Process   process { L"Ac_ClIeNt.ExE" };
		PlayerEnt player  { process.getProcessAddress() + Offsets::g_playerEnt };
	}
	catch (const std::exception& exception)
	{
		std::println(stderr, "{}", exception.what());
	}
	
	return 0;
}