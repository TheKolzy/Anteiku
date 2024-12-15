#include "..\Shared\Process.h"

Process::Process(std::wstring_view name) noexcept
{
	if (setNameAndIdentifier(name) && getModuleBase(m_processID))
	{
		std::wprintf(L"[Process Name      ]: %ls\n", m_name.data());
		std::print("[Process Identifier]: {}\n", m_processID);
		std::print("[Process Address   ]: {:#X}\n", m_moduleBase);

		m_open = OpenProcess(PROCESS_ALL_ACCESS, 0, m_processID);
		std::print("\n[Info]: Access to the process granted.\n");
	}
	else
		std::print("[Error]: Process could not be found.\n");
}

bool Process::setNameAndIdentifier(std::wstring_view name) noexcept
{
	const HANDLE processesSnapshot { CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0) };

	if (processesSnapshot == INVALID_HANDLE_VALUE)
	{
		std::print("[Error 1]: Processes snapshot could not be taken.\n");
		return false;
	}

	PROCESSENTRY32 processesList { .dwSize { sizeof(PROCESSENTRY32) } };

	if (!Process32First(processesSnapshot, &processesList))
	{
		std::print("[Error 2]: Processes list could not be found.\n");
		return false;
	}

	while (Process32Next(processesSnapshot, &processesList))
	{
		if (!_wcsnicmp(name.data(), processesList.szExeFile, std::wcslen(name.data())))
		{
			m_name = processesList.szExeFile;
			m_processID = processesList.th32ProcessID;
			m_found = true;
			return true;
		}
	}

	return false;
}

bool Process::getModuleBase(std::uint32_t processID) noexcept
{
	const HANDLE modulesSnapshot { CreateToolhelp32Snapshot(TH32CS_SNAPMODULE
		| TH32CS_SNAPMODULE32, processID) };

	if (modulesSnapshot == INVALID_HANDLE_VALUE)
	{
		std::print("[Error 1]: Modules snapshot could not be taken.\n");
		return false;
	}

	MODULEENTRY32 modulesList { .dwSize { sizeof(MODULEENTRY32) } };

	if (!Module32First(modulesSnapshot, &modulesList))
	{
		std::print("[Error 2]: Modules list could not be found.\n");
		return false;
	}

	while (Module32Next(modulesSnapshot, &modulesList))
	{
		if (processID == modulesList.th32ProcessID)
		{
			m_moduleBase = reinterpret_cast<std::uintptr_t>(modulesList.modBaseAddr);
			return true;
		}
	}

	return false;
}