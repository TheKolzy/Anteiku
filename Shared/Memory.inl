#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#ifndef NOMINMAX
#define NOMINMAX
#endif

#include <cstddef>
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

template <std::size_t N>
std::uintptr_t Memory::resolveAddress(std::uintptr_t address
	, const std::array<std::ptrdiff_t, N>& offsets) noexcept
{
	for (std::size_t i {}; i < offsets.size() - 1; ++i)
		address = read<std::uintptr_t>(address + offsets[i]);

	return address;
}