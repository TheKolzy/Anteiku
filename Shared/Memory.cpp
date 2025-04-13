#include "Memory.h"

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#ifndef NOMINMAX
#define NOMINMAX
#endif

#include <cstdint>
#include <print>
#include <stdexcept>

#include <Windows.h>

Memory::Memory(std::uint32_t processIdentifier)
{
	s_process = OpenProcess(PROCESS_VM_OPERATION | PROCESS_VM_READ | PROCESS_VM_WRITE
		, 0, processIdentifier);
	if (s_process == nullptr)
	{
		std::println("[Error]: Memory OpenProcess");
		throw std::runtime_error("[Error]: The memory could not be initialized.");
	}
}

Memory::~Memory() noexcept
{
	CloseHandle(s_process);
}