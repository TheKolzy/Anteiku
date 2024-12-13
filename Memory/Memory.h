#ifndef MEMORY_H
#define MEMORY_H

#include "../Process/Process.h"

#include <cstdint>
#include <iostream>

#include <Windows.h>

#include <basetsd.h>
#include <memoryapi.h>
#include <processthreadsapi.h>
#include <windef.h>
#include <winnt.h>

class Memory
{
public:
	explicit Memory(const Process& process) noexcept;

	template <typename T>
	T read(std::uintptr_t address) const noexcept;
	template <typename T>
	void write(T value, std::uintptr_t address) const noexcept;
private:
	HANDLE m_open {};
};

template <typename T>
T Memory::read(std::uintptr_t address) const noexcept
{
	T value {};
	ReadProcessMemory(m_open, address, &value, sizeof(value), nullptr);
	return value;
}

template <typename T>
void Memory::write(T value, std::uintptr_t address) const noexcept
{
	WriteProcessMemory(m_open, address, &value, sizeof(value), nullptr);
}

#endif