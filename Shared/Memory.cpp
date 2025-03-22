#include "Memory.h"

Memory::Memory(std::uint32_t processIdentifier)
{
	if (s_process = OpenProcess(PROCESS_VM_READ | PROCESS_VM_WRITE | PROCESS_VM_OPERATION
		, 0, processIdentifier); s_process == NULL)
		throw std::runtime_error("Read and write permissions could not be obtained.");
}