#pragma once

#include "Vector3.h"

#include <cstdint>
#include <string>
#include <string_view>

class PlayerEnt
{
public:
	explicit PlayerEnt(std::uintptr_t baseAddress) noexcept;

	[[nodiscard]] Vector3<float> getHead    ()                             const noexcept;
	[[nodiscard]] Vector3<float> getBody    ()                             const noexcept;
	              void           setBody    (const Vector3<float>& buffer) const noexcept;
	[[nodiscard]] Vector3<float> getView    ()                             const noexcept;
				  void           setView    (const Vector3<float>& buffer) const noexcept;
	[[nodiscard]] std::int8_t    getHealth  ()                             const noexcept;
	              void           setHealth  (std::int8_t buffer)           const noexcept;
	[[nodiscard]] std::uint8_t   getArmor   ()                             const noexcept;
	              void           setArmor   (std::uint8_t buffer)          const noexcept;
	[[nodiscard]] bool           isShooting ()                             const noexcept;
	              void           setShooting(bool buffer)                  const noexcept;
	[[nodiscard]] std::string    getName    ()                             const noexcept;
	              void           setName    (std::string_view buffer)      const noexcept;
	[[nodiscard]] std::uint8_t   getTeam    ()                             const noexcept;
	              void           setTeam    (std::uint8_t buffer)          const noexcept;
	[[nodiscard]] bool           isDead     ()                             const noexcept;
	[[nodiscard]] std::uint8_t   getAmmo    ()                             const noexcept;

private:
	const std::uintptr_t m_baseAddress {};
};