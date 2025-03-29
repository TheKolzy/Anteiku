#ifndef MEMORY_H
#define MEMORY_H

#define NOCOMM
#define WIN32_LEAN_AND_MEAN

#include <cstdint>
#include <print>
#include <stdexcept>

#include <Windows.h>

class Memory
{
public:
	explicit Memory(std::uint32_t processIdentifier);
	~Memory() noexcept { CloseHandle(s_process); }

	template <typename T>
	[[nodiscard]] static T read(std::uintptr_t address)     noexcept;
	template <typename T>
	static bool write(std::uintptr_t address, T value)      noexcept;
	template <std::size_t N>
	[[nodiscard]] static std::uintptr_t resolveAddress(std::uintptr_t address
		, const std::array<std::ptrdiff_t, N>& offsets) noexcept;

protected:
	Memory(const Memory& memory)            = delete;
	Memory& operator=(const Memory& memory) = delete;

	Memory(Memory&& memory)                 = delete;
	Memory& operator=(Memory&& memory)      = delete;

private:
	static inline HANDLE s_process {};
};

template <typename T>
T Memory::read(std::uintptr_t address) noexcept
{
	T buffer {};
	if (!ReadProcessMemory(s_process, reinterpret_cast<LPCVOID>(address), &buffer, sizeof(T)
		, nullptr))
	{
		std::println("The address could not be read.");
		return T {};
	}

	return buffer;
}

template <typename T>
bool Memory::write(std::uintptr_t address, T value) noexcept
{
	if (!WriteProcessMemory(s_process, reinterpret_cast<LPVOID>(address), &value, sizeof(T)
		, nullptr))
	{
		std::println("The address could not be written.");
		return false;
	}	

	return true;
}

template <std::size_t N>
static std::uintptr_t Memory::resolveAddress(std::uintptr_t address
	, const std::array<std::ptrdiff_t, N>& offsets) noexcept
{
	for (std::size_t i {}; i < offsets.size() - 1; ++i)	
		address = Memory::read<std::uintptr_t>(address + offsets[i]);

	return address;
}

#endif