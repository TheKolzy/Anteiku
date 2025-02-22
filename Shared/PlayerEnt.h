#ifndef PLAYERENT_H
#define PLAYERENT_H

#include "../Shared/Offsets.h"
#include "../Shared/Process.h"
#include "../Shared/Vector3.h"

class PlayerEnt
{
public:
	PlayerEnt(std::uintptr_t address) noexcept;

	[[nodiscard]] Vector3<float> getHeadVector()       const noexcept;
	[[nodiscard]] Vector3<float> getBodyVector()       const noexcept;
	void setBodyVector  (const Vector3<float>& vector) const noexcept;
	[[nodiscard]] Vector3<float> getCameraVector()     const noexcept;
	void setCameraVector(const Vector3<float>& vector) const noexcept;
	[[nodiscard]]  std::uint8_t getHealth()            const noexcept;
	void setHealth(std::uint8_t value)                 const noexcept;
	[[nodiscard]]  std::uint8_t getArmor()             const noexcept;
	void setArmor (std::uint8_t value)                 const noexcept;
	[[nodiscard]] bool getIsShooting()                 const noexcept;
	void setIsShooting(bool value)                     const noexcept;
	[[nodiscard]]  std::string getName()               const noexcept;
	void setName  (std::string_view value)             const noexcept;
	[[nodiscard]]  std::uint8_t getReload()            const noexcept;
	void setReload(std::uint8_t value)                 const noexcept;
	[[nodiscard]]  std::uint8_t getAmmo()              const noexcept;
	void setAmmo  (std::uint8_t value)                 const noexcept;

private:
	std::uintptr_t m_playerEnt    {};

	std::uintptr_t m_headVector   {};
	std::uintptr_t m_bodyVector   {};
	std::uintptr_t m_cameraVector {};
	std::uintptr_t m_health       {};
	std::uintptr_t m_armor        {};
	std::uintptr_t m_isShooting   {};
	std::uintptr_t m_name         {};
	std::uintptr_t m_reload       {};
	std::uintptr_t m_ammo         {};
};

#endif