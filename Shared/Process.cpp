#include "Process.h"

#define WIN32_LEAN_AND_MEAN

#include <print>
#include <stdexcept>

#include <Windows.h>

#include <TlHelp32.h>

Process::Process(std::wstring_view name)
{
	if (!initializeNameAndIdentifier(name) || !initializeBaseAddress())
		throw std::runtime_error("[Error]: The process could not be initialized.");
}

bool Process::initializeNameAndIdentifier(std::wstring_view name) noexcept
{
	const HANDLE processSnapshot { CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0) };
	if (processSnapshot == INVALID_HANDLE_VALUE)
	{
		std::println("[Error]: Process CreateToolhelp32Snapshot");
		return false;
	}

	PROCESSENTRY32 processEntry {};
	processEntry.dwSize = sizeof(PROCESSENTRY32);
	if (!Process32First(processSnapshot, &processEntry))
	{
		std::println("[Error]: Process32First");
		CloseHandle(processSnapshot);
		return false;
	}

	do
	{
		if (!_wcsicmp(processEntry.szExeFile, name.data()))
		{
			m_name       = processEntry.szExeFile;
			m_identifier = processEntry.th32ProcessID;
			CloseHandle(processSnapshot);
			return true;
		}
	}
	while (Process32Next(processSnapshot, &processEntry));
	std::println("[Warning]: Check the process name or if it's running.");

	CloseHandle(processSnapshot);
	return false;
}

bool Process::initializeBaseAddress() noexcept
{
	const HANDLE moduleSnapshot { CreateToolhelp32Snapshot(TH32CS_SNAPMODULE32
		| TH32CS_SNAPMODULE, m_identifier) };
	if (moduleSnapshot == INVALID_HANDLE_VALUE)
	{
		std::println("[Error]: Module CreateToolhelp32Snapshot");
		std::println("[Warning]: Check the process architecture.");
		return false;
	}

	MODULEENTRY32 moduleEntry {};
	moduleEntry.dwSize = sizeof(MODULEENTRY32);
	if (!Module32First(moduleSnapshot, &moduleEntry))
	{
		std::println("[Error]: Module32First");
		CloseHandle(moduleSnapshot);
		return false;
	}

	do
	{
		if (moduleEntry.th32ProcessID == m_identifier)
		{
			m_baseAddress = reinterpret_cast<std::uintptr_t>(moduleEntry.modBaseAddr);
			CloseHandle(moduleSnapshot);
			return true;
		}
	}
	while (Module32Next(moduleSnapshot, &moduleEntry));

	CloseHandle(moduleSnapshot);
	return false;
}