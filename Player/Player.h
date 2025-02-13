#pragma once

#include "..\Memory\Memory.h"
#include "..\Offsets\Offsets.h"

#include <string>

class Player
{
public:
	Player(std::uintptr_t address);

	std::uint8_t getHealth() const;
	void setHealth(std::uint8_t value) const;

	std::uint8_t getArmor() const;
	void setArmor(std::uint8_t value) const;

	bool getShoot() const;
	void setShoot(bool value) const;

	std::string getName() const;
	void setName(std::string_view value) const;

	std::uint8_t getAmmo() const;
	void setAmmo(std::uint8_t value) const;

private:
	std::uintptr_t m_player {};

	std::uintptr_t m_health {};
	std::uintptr_t m_armor  {};
	std::uintptr_t m_shoot  {};
	std::uintptr_t m_name   {};
	std::uintptr_t m_ammo   {};
};