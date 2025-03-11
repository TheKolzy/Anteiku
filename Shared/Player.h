#pragma once

#include "Offsets.h"
#include "Process.h"
#include "Vector3.h"

class Player
{
public:
	Player() = default;
	explicit Player(std::uintptr_t address)        noexcept;

	[[nodiscard]]  Vector3<float> getHead()  const noexcept;
	[[nodiscard]]  Vector3<float> getBody()  const noexcept;
	void setBody  (Vector3<float> body)      const noexcept;
	[[nodiscard]]  Vector3<float> getView()  const noexcept;
	void setView  (Vector3<float> view)      const noexcept;
	[[nodiscard]]  std::uint8_t getHealth()  const noexcept;
	void setHealth(std::uint8_t value)       const noexcept;
	[[nodiscard]]  std::uint8_t getArmor()   const noexcept;
	void setArmor (std::uint8_t value)       const noexcept;
	[[nodiscard]]  bool getShoot()           const noexcept;
	void setShoot (bool value)               const noexcept;
	[[nodiscard]]  std::string getName()     const noexcept;
	void setName  (std::string_view value)   const noexcept;
	[[nodiscard]]  std::uint8_t getTeam()    const noexcept;
	void setTeam  (std::uint8_t value)       const noexcept;
	[[nodiscard]]  bool getDead()            const noexcept;
	[[nodiscard]]  std::uint8_t getReload()  const noexcept;
	void setReload(std::uint8_t value)       const noexcept;
	[[nodiscard]]  std::uint8_t getAmmo()    const noexcept;
	void setAmmo  (std::uint8_t value)       const noexcept;

private:
	std::uintptr_t m_Player {};

	std::uintptr_t m_head   {};
	std::uintptr_t m_body   {};
	std::uintptr_t m_view   {};
	std::uintptr_t m_health {};
	std::uintptr_t m_armor  {};
	std::uintptr_t m_shoot  {};
	std::uintptr_t m_name   {};
	std::uintptr_t m_team   {};
	std::uintptr_t m_dead   {};
	std::uintptr_t m_reload {};
	std::uintptr_t m_ammo   {};
};