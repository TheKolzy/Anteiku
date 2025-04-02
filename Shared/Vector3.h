#ifndef VECTOR3_H
#define VECTOR3_H

#include <concepts>
#include <print>

template <std::floating_point T>
class Vector3
{
public:
	constexpr Vector3(T x, T y, T z) noexcept : m_x { x }, m_y { y }, m_z { z } {};
	constexpr Vector3()              noexcept = default;
	~Vector3()                       noexcept = default;

	[[nodiscard]] constexpr Vector3 operator+(const Vector3& vector) const noexcept;
	[[nodiscard]] constexpr Vector3 operator-(const Vector3& vector) const noexcept;
	[[nodiscard]] constexpr Vector3 operator*(const Vector3& vector) const noexcept;
	[[nodiscard]] constexpr Vector3 operator/(const Vector3& vector) const noexcept;

	[[nodiscard]] constexpr T getX() const noexcept { return m_x;  }
	[[nodiscard]] constexpr T getY() const noexcept { return m_y;  }
	[[nodiscard]] constexpr T getZ() const noexcept { return m_z;  }

	constexpr void setX(T value)           noexcept { m_x = value; }
	constexpr void setY(T value)           noexcept { m_y = value; }
	constexpr void setZ(T value)           noexcept { m_z = value; }

	void print()                     const noexcept { std::println("{} {} {}", m_x, m_y, m_z); }

private:
	T m_x {};
	T m_y {};
	T m_z {};
};

template <std::floating_point T>
constexpr Vector3<T> Vector3<T>::operator+(const Vector3& vector) const noexcept
{
	return Vector3 { m_x + vector.m_x, m_y + vector.m_y, m_z + vector.m_z };
}

template <std::floating_point T>
constexpr Vector3<T> Vector3<T>::operator-(const Vector3& vector) const noexcept
{
	return Vector3 { m_x - vector.m_x, m_y - vector.m_y, m_z - vector.m_z };
}

template <std::floating_point T>
constexpr Vector3<T> Vector3<T>::operator*(const Vector3& vector) const noexcept
{
	return Vector3 { m_x * vector.m_x, m_y * vector.m_y, m_z * vector.m_z };
}

template <std::floating_point T>
constexpr Vector3<T> Vector3<T>::operator/(const Vector3& vector) const noexcept
{
	return Vector3 { m_x / vector.m_x, m_y / vector.m_y, m_z / vector.m_z };
}

#endif