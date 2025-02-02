#include "Memory/Memory.h"
#include "Process/Process.h"

int main()
{
	const Process process { L"Ac_ClIeNt.ExE" };
	const Memory  memory  { process.getPID() };

	return 0;
}