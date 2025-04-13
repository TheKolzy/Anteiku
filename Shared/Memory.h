#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

using HANDLE  = void*;
using LPCVOID = const void*;
using LPVOID  = void*;

class Memory
{
public:
	explicit Memory(std::uint32_t processIdentifier);
	~Memory() noexcept;

	template <typename T>
	[[nodiscard]] static T    read (std::uintptr_t address)                  noexcept;
	template <typename T>
	              static bool write(std::uintptr_t address, const T& buffer) noexcept;

	template <std::size_t N>
	[[nodiscard]] static std::uintptr_t resolveAddress(std::uintptr_t address
		, const std::array<std::ptrdiff_t, N>& offsets)                  noexcept;

private:
	static inline HANDLE s_process {};
};

#include "Memory.inl"