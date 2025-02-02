#pragma once

#include <Windows.h>

#include <TlHelp32.h>

#include <iostream>
#include <print>
#include <string>

class Process
{
public:
	Process(std::wstring_view name);

	std::wstring_view getName()    const { return m_name;    }
	std::uint64_t     getPID()     const { return m_pid;     }
	std::uintptr_t    getAddress() const { return m_address; }

private:
	void initializeNameAndPID(std::wstring_view name);
	void initializeAddress();

	std::wstring   m_name    { L"0" };
	std::uint64_t  m_pid     {};
	std::uintptr_t m_address {};
};