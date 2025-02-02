#include "Memory.h"

Memory::Memory(std::uint64_t pid)
{
	m_process = OpenProcess(PROCESS_ALL_ACCESS, 0, static_cast<DWORD>(pid));
}

Memory::~Memory()
{
	CloseHandle(m_process);
}