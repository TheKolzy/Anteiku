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
	static inline HANDLE m_processHandle  {};
};

template <typename T>
T Process::read(std::uintptr_t address) noexcept
{
	T value {};
	ReadProcessMemory(m_processHandle, reinterpret_cast<LPCVOID>(address), &value
		, sizeof(T), nullptr);
	return value;
}

template <typename T>
void Process::write(std::uintptr_t address, T value) noexcept
{
	WriteProcessMemory(m_processHandle, reinterpret_cast<LPVOID>(address), &value
		, sizeof(T), nullptr);
}

#endif