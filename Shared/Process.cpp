#include "Process.h"

Process::Process(std::wstring_view name)
{
	if (!initializeNameAndIdentifier(name) || !initializeAddress())
		throw std::runtime_error("[Exception]: Failed to Find the Process");

	showData();
	s_process = OpenProcess(PROCESS_ALL_ACCESS, 0, m_identifier);
}

bool Process::initializeNameAndIdentifier(std::wstring_view name) noexcept
{
	const HANDLE processSnapshots { CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0) };
	if (processSnapshots == INVALID_HANDLE_VALUE)
	{	
		std::println("[Process Error]: CreateToolhelp32Snapshot");
		return false;
	}

	PROCESSENTRY32 processLists { .dwSize { sizeof(PROCESSENTRY32) } };
	if (!Process32First(processSnapshots, &processLists))
	{
		std::println("[Process Error]: Process32First");
		CloseHandle(processSnapshots);
		return false;
	}
	
	do
	{
		if (!_wcsnicmp(name.data(), processLists.szExeFile, name.size()))
		{
			m_name       = processLists.szExeFile;
			m_identifier = processLists.th32ProcessID;
			CloseHandle(processSnapshots);
			return true;
		}
	} while (Process32Next(processSnapshots, &processLists));

	CloseHandle(processSnapshots);
	return false;
}

bool Process::initializeAddress() noexcept
{
	const HANDLE moduleSnapshots { CreateToolhelp32Snapshot(TH32CS_SNAPMODULE32
		| TH32CS_SNAPMODULE, m_identifier) };
	if (moduleSnapshots == INVALID_HANDLE_VALUE)
	{
		std::println("[Module Error]: CreateToolhelp32Snapshot, Check the Architecture");
		return false;
	}

	MODULEENTRY32 moduleLists { .dwSize { sizeof(MODULEENTRY32) } };
	if (!Module32First(moduleSnapshots, &moduleLists))
	{
		std::println("[Module Error]: Module32First");
		CloseHandle(moduleSnapshots);
		return false;
	}

	do
	{
		if (moduleLists.th32ProcessID == m_identifier)
		{
			m_address = reinterpret_cast<std::uintptr_t>(moduleLists.modBaseAddr);
			CloseHandle(moduleSnapshots);
			return true;
		}
	} while (Module32Next(moduleSnapshots, &moduleLists));

	CloseHandle(moduleSnapshots);
	return false;
}

void Process::showData() const noexcept
{
	std::printf ("[Process Name      ]: %ls\n", m_name.c_str());
	std::println("[Process Identifier]: {} (0x{:08X})", m_identifier, m_identifier);
	std::println("[Process Address   ]: 0x{:012X}\n", m_address);
}