#include "Process.h"

Process::Process(std::wstring_view name) noexcept
{
	setNameAndIdentifier(name);

	if (m_found)
	{
		setAddress(m_identifier);

		std::wcout << "[Process Name      ]: " << m_name << '\n';
		std::cout << "[Process Identifier]: " << m_identifier << '\n';
		std::cout << "[Process Address   ]: 0x" << std::hex << std::uppercase
			<< m_address << std::dec << '\n';
	}
	else
		std::cout << "[Error]: Process could not be found.\n";
}

void Process::setNameAndIdentifier(std::wstring_view name) noexcept
{
	const HANDLE processesSnapshot { CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0) };

	if (processesSnapshot == INVALID_HANDLE_VALUE)
	{
		std::cout << "[Error 1]: Processes snapshot could not be taken.\n";
		return;
	}

	PROCESSENTRY32 processesList { .dwSize { sizeof(PROCESSENTRY32) } };

	if (!Process32First(processesSnapshot, &processesList))
	{
		std::cout << "[Error 2]: Processes list could not be found.\n";
		return;
	}

	while (Process32Next(processesSnapshot, &processesList))
	{
		if (!_wcsnicmp(name.data(), processesList.szExeFile, std::wcslen(name.data())))
		{
			m_name = processesList.szExeFile;
			m_identifier = processesList.th32ProcessID;
			m_found = true;
			break;
		}
	}
}

void Process::setAddress(DWORD identifier) noexcept
{
	const HANDLE modulesSnapshot { CreateToolhelp32Snapshot(TH32CS_SNAPMODULE
		| TH32CS_SNAPMODULE32, identifier) };

	if (modulesSnapshot == INVALID_HANDLE_VALUE)
	{
		std::cout << "[Error 1]: Modules snapshot could not be taken.\n";
		return;
	}

	MODULEENTRY32 modulesList { .dwSize { sizeof(MODULEENTRY32) } };

	if (!Module32First(modulesSnapshot, &modulesList))
	{
		std::cout << "[Error 2]: Modules list could not be found.\n";
		return;
	}

	while (Module32Next(modulesSnapshot, &modulesList))
	{
		if (identifier == modulesList.th32ProcessID)
		{
			m_address = reinterpret_cast<std::uintptr_t>(modulesList.modBaseAddr);
			break;
		}
	}
}