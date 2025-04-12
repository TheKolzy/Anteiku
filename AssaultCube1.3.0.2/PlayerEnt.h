#pragma once

#include <cstdint>

class PlayerEnt
{
public:
	explicit PlayerEnt(std::uintptr_t address) noexcept;

	[[nodiscard]] std::uint8_t getHealth()                    const noexcept;
	              void         setHealth(std::uint8_t buffer) const noexcept;

private:
	const std::uintptr_t m_baseAddress {};
};