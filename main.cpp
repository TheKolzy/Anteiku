#include "Memory/Memory.h"
#include "Process/Process.h"

int main()
{
	Process myProcess { L"NoTePaD.eXe" };
	Memory myMemory { myProcess };
	return 0;
}