#ifndef PROCESS_H
#define PROCESS_H

#include <print>

#include <Windows.h>

#include <TlHelp32.h>

class Process
{
public:
	explicit Process(std::wstring_view processName);

	template <typename T>
	[[nodiscard]] static T read(std::uintptr_t address)       noexcept;
	template <typename T>
	static void write(std::uintptr_t address, T value)        noexcept;
	template <std::size_t N>
	[[nodiscard]] static std::uintptr_t resolveAddress(std::uintptr_t address
		, const std::array<std::ptrdiff_t, N>& offsets)       noexcept;

	[[nodiscard]] std::wstring_view getProcessName()    const noexcept 
		{ return m_processName;    }
	[[nodiscard]] std::uint32_t     getProcessId()      const noexcept 
		{ return m_processId;      }
	[[nodiscard]] std::uintptr_t    getProcessAddress() const noexcept
		{ return m_processAddress; }
	 
protected:
	Process(const Process& process)            = delete;
	Process(Process&& process)                 = delete;
	Process& operator=(const Process& process) = delete;
	Process& operator=(Process&& process)      = delete;

private:
	bool initializeProcessNameAndId(std::wstring_view processName) noexcept;
	bool initializeProcessAddress()                                noexcept;

	std::wstring         m_processName    {};
	std::uint32_t        m_processId      {};
	std::uintptr_t       m_processAddress {};
	static inline HANDLE s_processHandle  {};
};

template <typename T>
T Process::read(std::uintptr_t address) noexcept
{
	T value {};
	ReadProcessMemory(s_processHandle, reinterpret_cast<LPCVOID>(address), &value
		, sizeof(T), nullptr);

	return value;
}

template <typename T>
void Process::write(std::uintptr_t address, T value) noexcept
{
	WriteProcessMemory(s_processHandle, reinterpret_cast<LPVOID>(address), &value
		, sizeof(T), nullptr);
}

template <std::size_t N>
std::uintptr_t Process::resolveAddress(std::uintptr_t address
	, const std::array<std::ptrdiff_t, N>& offsets) noexcept
{
	std::uintptr_t value { address };
	for (std::size_t i { 0 }; i < offsets.size() - 1; ++i)
	{
		value += offsets[i];
		value = read<std::uintptr_t>(value);
	}
	value += offsets[offsets.size() - 1];

	return value;
}

#endif