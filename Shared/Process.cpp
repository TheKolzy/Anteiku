#include "Process.h"

Process::Process(std::wstring_view processName)
{
	if (!initializeProcessNameAndId(processName) || !initializeProcessAddress())
		throw std::runtime_error("[Exception]: Incorrect Process Initialization");

	s_processHandle = OpenProcess(PROCESS_ALL_ACCESS, 0, m_processId);
}

bool Process::initializeProcessNameAndId(std::wstring_view processName) noexcept
{
	const HANDLE processSnapshots { CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0) };
	if (processSnapshots == INVALID_HANDLE_VALUE)
	{
		std::println("\n[Error]: Process CreateToolhelp32Snapshot");
		return false;
	}

	PROCESSENTRY32 processLists { .dwSize { sizeof(PROCESSENTRY32) } };
	if (!Process32First(processSnapshots, &processLists))
	{
		std::println("\n[Error]: Process Process32First");
		CloseHandle(processSnapshots);
		return false;
	}
	
	do
	{
		if (!_wcsnicmp(processName.data(), processLists.szExeFile, processName.size()))
		{
			m_processName = processLists.szExeFile;
			m_processId   = processLists.th32ProcessID;
			std::wprintf(L"[Process Name   ]: %ls\n", m_processName.c_str());
			std::println( "[Process Id     ]: {} (0x{:X})", m_processId, m_processId);
			CloseHandle(processSnapshots);
			return true;
		}
	}
	while (Process32Next(processSnapshots, &processLists));
	CloseHandle(processSnapshots);

	return false;
}

bool Process::initializeProcessAddress() noexcept
{
	const HANDLE moduleSnapshots { CreateToolhelp32Snapshot(TH32CS_SNAPMODULE32
		| TH32CS_SNAPMODULE, m_processId) };
	if (moduleSnapshots == INVALID_HANDLE_VALUE)
	{
		std::println("\n[Error]: Module CreateToolhelp32Snapshot, Change Architecture");
		return false;
	}

	MODULEENTRY32 moduleLists { .dwSize { sizeof(MODULEENTRY32) } };
	if (!Module32First(moduleSnapshots, &moduleLists))
	{
		std::println("\n[Error]: Module Module32First");
		CloseHandle(moduleSnapshots);
		return false;
	}

	do
	{
		if (m_processId == moduleLists.th32ProcessID)
		{
			m_processAddress = reinterpret_cast<std::uintptr_t>(moduleLists.modBaseAddr);
			std::println("[Process Address]: 0x{:012X}\n", m_processAddress);
			CloseHandle(moduleSnapshots);
			return true;
		}
	}
	while (Module32Next(moduleSnapshots, &moduleLists));
	CloseHandle(moduleSnapshots);

	return false;
}