#ifndef PLAYER_H
#define PLAYER_H

#define NOMINMAX

#include "Memory.h"
#include "Offsets.h"
#include "Vector3.h"

#include <array>
#include <algorithm>
#include <cstdint>
#include <string>
#include <string_view>

class Player
{
public:
	explicit Player (std::uintptr_t address)           noexcept;

	[[nodiscard]]    Vector3<float> getHead()    const noexcept;
	[[nodiscard]]    Vector3<float> getBody()    const noexcept;
	[[nodiscard]]    Vector3<float> getView()    const noexcept;
	[[nodiscard]]    std::int8_t    getHealth()  const noexcept;	
	[[nodiscard]]    std::uint8_t   getArmor()   const noexcept;
	[[nodiscard]]    bool           isShooting() const noexcept;	
	[[nodiscard]]    std::string    getName()    const noexcept;
	[[nodiscard]]    std::uint8_t   getTeam()    const noexcept;
	[[nodiscard]]    bool           isAlive()    const noexcept;
	[[nodiscard]]    std::uint8_t   getAmmo()    const noexcept;

	void setBody    (Vector3<float>   value)     const noexcept;
	void setView    (Vector3<float>   value)     const noexcept;
	void setHealth  (std::int8_t      value)     const noexcept;
	void setArmor   (std::uint8_t     value)     const noexcept;
	void setShooting(bool             value)     const noexcept;
	void setName    (std::string_view value)     const noexcept;
	void setTeam    (std::uint8_t     value)     const noexcept;
	void setAmmo    (std::uint8_t     value)     const noexcept;

private:
	const std::uintptr_t m_player {};
};

#endif