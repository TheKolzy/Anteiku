#include "Memory.h"

Memory::Memory(const Process& process) noexcept
{
	if (process.isFound())
	{
		m_open = OpenProcess(PROCESS_ALL_ACCESS, 0, process.getIdentifier());
		std::cout << "\n[Info]: Access to the process secured.\n";
	}
}