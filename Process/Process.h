#ifndef PROCESS_H
#define PROCESS_H

#include <cstdint>
#include <cwchar>
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
	
private:
	std::wstring getName(std::wstring_view name) const noexcept;

	const std::wstring m_name {};
	const DWORD m_identifier {};
	const std::uintptr_t m_address {};
};

#endif