#pragma once

#include <Windows.h>

#include <cstdint>

class Memory
{
public:
	Memory(std::uint64_t pid);
	~Memory();

	template <typename T>
	static T read(std::uintptr_t address);
	template <typename T>
	static void write(std::uintptr_t address, T value);

private:
	inline static HANDLE m_process {};
};

template <typename T>
T Memory::read(std::uintptr_t address)
{
	T value {};
	ReadProcessMemory(m_process, reinterpret_cast<LPCVOID>(address), &value
		, sizeof(T), nullptr);
	return value;
}

template <typename T>
void Memory::write(std::uintptr_t address, T value)
{
	WriteProcessMemory(m_process, reinterpret_cast<LPVOID>(address), &value
		, sizeof(value), nullptr);
}