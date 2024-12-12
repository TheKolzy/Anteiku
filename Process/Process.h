#ifndef PROCESS_H
#define PROCESS_H

#include <cstdint>
#include <cwchar>
#include <ios>
#include <iostream>
#include <string_view>

#include <Windows.h>

#include <TlHelp32.h>
#include <basetsd.h>
#include <windef.h>
#include <winnt.h>

class Process
{
public:
	explicit Process(std::wstring_view name) noexcept;

	std::wstring_view getName() const noexcept { return m_name; }
	DWORD getIdentifier() const noexcept { return m_identifier; }
	std::uintptr_t getAddress() const noexcept { return m_address; }
	
private:
	void setNameAndIdentifier(std::wstring_view name) noexcept;
	void setAddress(DWORD identifier) noexcept;

	std::wstring m_name {};
	DWORD m_identifier {};
	std::uintptr_t m_address {};
};

#endif