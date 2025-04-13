#pragma once

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

private:
	static inline HANDLE s_process {};
};

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#ifndef NOMINMAX
#define NOMINMAX
#endif

#include "Memory.inl"