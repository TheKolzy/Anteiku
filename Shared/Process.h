#ifndef PROCESS_H
#define PROCESS_H

#define NOCOMM
#define WIN32_LEAN_AND_MEAN

#include <cstdint>
#include <stdexcept>
#include <string>
#include <string_view>

#include <Windows.h>

#include <TlHelp32.h>

class Process
{
public:
	explicit Process(std::wstring_view name);
	~Process()                                               noexcept = default;

	[[nodiscard]] std::wstring_view getName()          const noexcept { return m_name;       }
	[[nodiscard]] std::uint32_t     getIdentifier()    const noexcept { return m_identifier; }
	[[nodiscard]] std::uintptr_t    getAddress()       const noexcept { return m_address;    }

protected:
	Process(const Process& process)            = delete;
	Process& operator=(const Process& process) = delete;

	Process(Process&& process)                 = delete;
	Process& operator=(Process&& process)      = delete;

private:
	bool initializeNameAndIdentifier(std::wstring_view name) noexcept;
	bool initializeAddress()                                 noexcept;

	std::wstring   m_name       {};
	std::uint32_t  m_identifier {};
	std::uintptr_t m_address    {};
};

#endif