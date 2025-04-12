#pragma once

#include <cstdint>
#include <string>
#include <string_view>

class Process
{
public:
	explicit Process(std::wstring_view name);

	[[nodiscard]] std::wstring_view getName       () const noexcept { return m_name;        }
	[[nodiscard]] std::uint32_t     getIdentifier () const noexcept { return m_identifier;  }
	[[nodiscard]] std::uintptr_t    getBaseAddress() const noexcept { return m_baseAddress; }

private:
	[[nodiscard]] bool initializeNameAndIdentifier(std::wstring_view name) noexcept;
	[[nodiscard]] bool initializeBaseAddress      ()                       noexcept;

	std::wstring   m_name        {};
	std::uint32_t  m_identifier  {};
	std::uintptr_t m_baseAddress {};
};