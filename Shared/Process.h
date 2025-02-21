#ifndef PROCESS_H
#define PROCESS_H

#include <print>

#include <Windows.h>

#include <TlHelp32.h>

class Process
{
public:
	explicit Process(std::wstring_view processName);

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

	std::wstring   m_processName    {};
	std::uint32_t  m_processId      {};
	std::uintptr_t m_processAddress {};
};

#endif