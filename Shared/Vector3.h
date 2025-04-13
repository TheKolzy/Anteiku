#pragma once

#include <concepts>
#include <print>

template <std::floating_point T>
class Vector3
{
public:
	constexpr Vector3(T x, T y, T z) noexcept : m_x { x }, m_y { y }, m_z { z } {};
	constexpr Vector3() noexcept = default;

	[[nodiscard]] constexpr Vector3<T> operator+(const Vector3<T>& vector3) const noexcept;
	[[nodiscard]] constexpr Vector3<T> operator-(const Vector3<T>& vector3) const noexcept;
	[[nodiscard]] constexpr Vector3<T> operator*(const Vector3<T>& vector3) const noexcept;
	[[nodiscard]] constexpr Vector3<T> operator/(const Vector3<T>& vector3) const noexcept;

	[[nodiscard]] constexpr T    getX()         const noexcept { return m_x;   }
	              constexpr void setX(T buffer)       noexcept { m_x = buffer; }
	[[nodiscard]] constexpr T    getY()         const noexcept { return m_y;   }
	              constexpr void setY(T buffer)       noexcept { m_y = buffer; }
	[[nodiscard]] constexpr T    getZ()         const noexcept { return m_z;   }
	              constexpr void setZ(T buffer)       noexcept { m_z = buffer; }

	void print() const noexcept { std::println("{} {} {}", m_x, m_y, m_z); }

private:
	T m_x {};
	T m_y {};
	T m_z {};
};

#include "Vector3.inl"