#pragma once

#include <print>

#include <Windows.h>

#include <TlHelp32.h>

class Process
{
public:
	explicit Process(std::wstring_view name);
	~Process() noexcept { CloseHandle(s_process); }

	template <typename T>
	static T read(std::uintptr_t address);
	template <typename T>
	static void write(std::uintptr_t address, T value);
	template <std::size_t N>
	static std::uintptr_t calculateAddress(std::uintptr_t address
		, const std::array<std::ptrdiff_t, N>& array);

	[[nodiscard]] std::wstring_view getName()       const noexcept { return m_name;       }
	[[nodiscard]] std::uint32_t     getIdentifier() const noexcept { return m_identifier; }
	[[nodiscard]] std::uintptr_t    getAddress()    const noexcept { return m_address;    }

protected:
	Process(const Process& process)            = delete;
	Process(Process&& process)                 = delete;
	Process& operator=(const Process& process) = delete;
	Process& operator=(Process&& process)      = delete;

private:
	bool initializeNameAndIdentifier(std::wstring_view name) noexcept;
	bool initializeAddress()                                 noexcept;
	void printData()                                   const noexcept;

	std::wstring         m_name       {};
	std::uint32_t        m_identifier {};
	std::uintptr_t       m_address    {};
	static inline HANDLE s_process    {};
};

template <typename T>
T Process::read(std::uintptr_t address)
{
	T value {};
	ReadProcessMemory(s_process, reinterpret_cast<LPCVOID>(address), &value, sizeof(T)
		, nullptr);

	return value;
}

template <typename T>
void Process::write(std::uintptr_t address, T value)
{
	WriteProcessMemory(s_process, reinterpret_cast<LPVOID>(address), &value, sizeof(T)
		, nullptr);
}

template <std::size_t N>
std::uintptr_t Process::calculateAddress(std::uintptr_t address
	, const std::array<std::ptrdiff_t, N>& array)
{
	std::uintptr_t value { address };
	for (std::size_t i { 0 }; i < array.size() - 1; ++i)
	{
		value = Process::read<std::uintptr_t>(value + array[i]);
	}
	value += array[array.size() - 1];

	return value;
}