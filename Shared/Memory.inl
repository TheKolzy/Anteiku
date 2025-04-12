#include <cstdint>
#include <print>

#include <Windows.h>

template <typename T>
T Memory::read(std::uintptr_t address) noexcept
{
	T buffer {};
	if (!ReadProcessMemory(s_process, reinterpret_cast<LPCVOID>(address), &buffer
		, sizeof(T), nullptr))
		std::println("[Error]: Memory ReadProcessMemory");

	return buffer;
}

template <typename T>
bool Memory::write(std::uintptr_t address, const T& buffer) noexcept
{
	if (!WriteProcessMemory(s_process, reinterpret_cast<LPVOID>(address), &buffer
		, sizeof(T), nullptr))
	{
		std::println("[Error]: Memory WriteProcessMemory");
		return false;
	}

	return true;
}