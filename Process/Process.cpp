#include "Process.h"

Process::Process(std::wstring_view name) noexcept
	: m_name { getName(name) }
{
	if (m_name != L"")
		std::wcout << "[Process Name]: " << m_name << '\n';
	else
		std::cout << "[Error]: Process could not be found.\n";
}

std::wstring Process::getName(std::wstring_view name) const noexcept
{
	const HANDLE processesSnapshot { CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0) };

	if (processesSnapshot == INVALID_HANDLE_VALUE)
	{
		std::cout << "[Error 1]: Processes snapshot could not be taken.\n";
		return L"";
	}

	PROCESSENTRY32 processesList { .dwSize { sizeof(PROCESSENTRY32) } };

	if (!Process32First(processesSnapshot, &processesList))
	{
		std::cout << "[Error 2]: Processes list could not be found.\n";
		return L"";
	}

	std::wstring processName {};
	while (Process32Next(processesSnapshot, &processesList))
	{
		if (!_wcsnicmp(name.data(), processesList.szExeFile, std::wcslen(name.data())))
		{
			processName = processesList.szExeFile;
			break;
		}
	}

	return processName;
}