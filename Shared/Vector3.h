#pragma once

template <std::floating_point T>
class Vector3
{
public:
	Vector3(T x, T y, T z) noexcept : m_x { x }, m_y { y }, m_z { z } {};

	Vector3 operator+(const Vector3& vector3) const noexcept;
	Vector3 operator-(const Vector3& vector3) const noexcept;
	Vector3 operator*(const Vector3& vector3) const noexcept;
	Vector3 operator/(const Vector3& vector3) const noexcept;

	[[nodiscard]] T getX() const noexcept { return m_x; }
	void setX(T value)           noexcept { m_x = value; }
	[[nodiscard]] T getY() const noexcept { return m_y; }
	void setY(T value)           noexcept { m_y = value; }
	[[nodiscard]] T getZ() const noexcept { return m_z; }
	void setZ(T value)           noexcept { m_z = value; }
	void printData()       const noexcept { std::println("{} {} {}", m_x, m_y, m_z); }

private:
	T m_x {};
	T m_y {};
	T m_z {};
};

template <std::floating_point T>
Vector3<T> Vector3<T>::operator+(const Vector3& vector3) const noexcept
{
	return Vector3 { m_x + vector3.m_x, m_y + vector3.m_y, m_z + vector3.m_z };
}

template <std::floating_point T>
Vector3<T> Vector3<T>::operator-(const Vector3& vector3) const noexcept
{
	return Vector3 { m_x - vector3.m_x, m_y - vector3.m_y, m_z - vector3.m_z };
}

template <std::floating_point T>
Vector3<T> Vector3<T>::operator*(const Vector3& vector3) const noexcept
{
	return Vector3 { m_x * vector3.m_x, m_y * vector3.m_y, m_z * vector3.m_z };
}

template <std::floating_point T>
Vector3<T> Vector3<T>::operator/(const Vector3& vector3) const noexcept
{
	return Vector3 { m_x / vector3.m_x, m_y / vector3.m_y, m_z / vector3.m_z };
}