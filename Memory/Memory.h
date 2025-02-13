#pragma once

#include <Windows.h>

#include <array>
#include <cstddef>
#include <cstdint>

class Memory
{
public:
	Memory (std::uint64_t pid);
	~Memory();

	template <typename T>
	static T    read (std::uintptr_t address);
	template <typename T>
	static void write(std::uintptr_t address, T value);
	template <std::size_t N>
	static std::uintptr_t calculateAddress(std::uintptr_t address
		, const std::array<std::ptrdiff_t, N>& offsets);

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

template <std::size_t N>
std::uintptr_t Memory::calculateAddress(std::uintptr_t address
	, const std::array<std::ptrdiff_t, N>& offsets)
{
	std::uintptr_t lastAddress { address };
	for (std::size_t i = 0; i < offsets.size() - 1; i++)
	{
		lastAddress += offsets[i];
		lastAddress = read<std::uintptr_t>(lastAddress);
	}
	lastAddress += offsets[offsets.size() - 1];

	return lastAddress;
}