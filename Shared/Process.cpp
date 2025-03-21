#include "Process.h"

Process::Process(std::wstring_view name)
{
	if (!initializeNameAndIdentifier(name) || !initializeAddress())
		throw std::runtime_error("The specified process could not be found.");
}

bool Process::initializeNameAndIdentifier(std::wstring_view name) noexcept
{
	const HANDLE processSnapshots { CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0) };
	if (processSnapshots == INVALID_HANDLE_VALUE)
		return false;

	PROCESSENTRY32 processLists { .dwSize { sizeof(PROCESSENTRY32) } };
	if (!Process32First(processSnapshots, &processLists))
	{
		CloseHandle(processSnapshots);
		return false;
	}

	do
	{
		if (!_wcsicmp(name.data(), processLists.szExeFile))
		{
			m_name       = processLists.szExeFile;
			m_identifier = processLists.th32ProcessID;
			CloseHandle(processSnapshots);
			return true;
		}
	}
	while (Process32Next(processSnapshots, &processLists));
	CloseHandle(processSnapshots);

	return false;
}

bool Process::initializeAddress() noexcept
{
	const HANDLE moduleSnapshots { CreateToolhelp32Snapshot(TH32CS_SNAPMODULE32
		| TH32CS_SNAPMODULE, m_identifier) };
	if (moduleSnapshots == INVALID_HANDLE_VALUE)
		return false;

	MODULEENTRY32 moduleLists { .dwSize { sizeof(MODULEENTRY32) } };
	if (!Module32First(moduleSnapshots, &moduleLists))
	{
		CloseHandle(moduleSnapshots);
		return false;
	}

	do
	{
		if (m_identifier == moduleLists.th32ProcessID)
		{
			m_address = reinterpret_cast<std::uintptr_t>(moduleLists.modBaseAddr);
			CloseHandle(moduleSnapshots);
			return true;
		}
	}
	while (Module32Next(moduleSnapshots, &moduleLists));
	CloseHandle(moduleSnapshots);

	return false;
}