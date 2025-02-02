#include "Process.h"

Process::Process(std::wstring_view name)
{
	initializeNameAndPID(name);
	initializeAddress();

	std::wcout << "[Process Name      ]: " << m_name << '\n';
	std::println("[Process Identifier]: {}", m_pid);
	std::println("[Process Address   ]: 0x{:X}\n", m_address);
}

void Process::initializeNameAndPID(std::wstring_view name)
{
	if (const HANDLE snapshot { CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0) };
		snapshot != INVALID_HANDLE_VALUE)
	{
		PROCESSENTRY32 list {};
		list.dwSize = sizeof(PROCESSENTRY32);

		if (Process32First(snapshot, &list))
		{
			do
			{
				if (!_wcsicmp(name.data(), list.szExeFile))
				{
					m_name = list.szExeFile;
					m_pid = list.th32ProcessID;
					break;
				}
			}
			while (Process32Next(snapshot, &list));
		}
		else
			std::println("[Error]: The process list could not be taken.");

		CloseHandle(snapshot);
	}
	else
		std::println("[Error]: The process snapshot could not be taken.");
}

void Process::initializeAddress()
{
	if (const HANDLE moduleSnapshot { CreateToolhelp32Snapshot(TH32CS_SNAPMODULE32
		| TH32CS_SNAPMODULE, static_cast<DWORD>(m_pid)) };
		moduleSnapshot != INVALID_HANDLE_VALUE)
	{
		MODULEENTRY32 moduleList {};
		moduleList.dwSize = sizeof(MODULEENTRY32);

		if (Module32First(moduleSnapshot, &moduleList))
		{
			do
			{
				if (moduleList.th32ProcessID == m_pid)
				{
					m_address = reinterpret_cast<std::uintptr_t>(moduleList.modBaseAddr);
					break;
				}
			}
			while (Module32Next(moduleSnapshot, &moduleList));
		}
		else
			std::println("[Error]: The module list could not be taken.");

		CloseHandle(moduleSnapshot);
	}
	else
		std::println("[Error]: The module snapshot could not be taken.");
}