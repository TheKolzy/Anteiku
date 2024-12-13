#include "Memory/Memory.h"
#include "Process/Process.h"

int main()
{
	Process process { L"Ac_ClIeNt.ExE" };
	Memory memory { process };

	memory.write(1337, 0x0351268C);

	return 0;
}