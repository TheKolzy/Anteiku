#ifndef PROCESS_H
#define PROCESS_H

#include <cstdint>
#include <cwchar>
#include <print>
#include <string_view>

#include <Windows.h>

#include <TlHelp32.h>
#include <basetsd.h>
#include <memoryapi.h>
#include <processthreadsapi.h>
#include <wchar.h>
#include <windef.h>
#include <winnt.h>

class Process
{
public:
	explicit Process(std::wstring_view name) noexcept;

	template <typename T>
	T read(std::uintptr_t address) const noexcept;
	template <typename T>
	void write(T value, std::uintptr_t address) const noexcept;

	[[nodiscard]] std::wstring_view getName() const { return m_name; }
	[[nodiscard]] std::uint32_t getProcessID() const { return m_processID; }
	[[nodiscard]] std::uintptr_t getModuleBase() const { return m_moduleBase; }
	[[nodiscard]] bool isFound() const { return m_found; }
	
protected:
	Process(const Process& other) = delete;
	Process(Process&& other) = delete;

	Process& operator=(const Process& other) = delete;
	Process& operator=(Process&& other) = delete;

private:
	bool setNameAndIdentifier(std::wstring_view name) noexcept;
	bool getModuleBase(std::uint32_t processID) noexcept;

	std::wstring m_name {};
	std::uint32_t m_processID {};
	std::uintptr_t m_moduleBase {};
	bool m_found {};
	HANDLE m_open {};
};

template <typename T>
T Process::read(std::uintptr_t address) const noexcept
{
	T value {};
	ReadProcessMemory(m_open, reinterpret_cast<LPCVOID>(address)
		, &value, sizeof(value), nullptr);
	return value;
}

template <typename T>
void Process::write(T value, std::uintptr_t address) const noexcept
{
	WriteProcessMemory(m_open, reinterpret_cast<LPVOID>(address)
		, &value, sizeof(value), nullptr);
}

#endif