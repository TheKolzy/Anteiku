#ifndef VECTOR3_H
#define VECTOR3_H

template <std::floating_point T>
class Vector3
{
public:
	Vector3(T x, T y, T z) noexcept : m_x { x }, m_y { y }, m_z { z } {};

	[[nodiscard]] T getX() const noexcept { return m_x;  }
	void setX(T value)           noexcept { m_x = value; }
	[[nodiscard]] T getY() const noexcept { return m_y;  }
	void setY(T value)           noexcept { m_y = value; }
	[[nodiscard]] T getZ() const noexcept { return m_z;  }
	void setZ(T value)           noexcept { m_z = value; }

	void print() const noexcept { std::println("{}, {}, {}", m_x, m_y, m_z); }

	[[nodiscard]] Vector3 operator+(const Vector3& vector) const noexcept;
	[[nodiscard]] Vector3 operator-(const Vector3& vector) const noexcept;
	[[nodiscard]] Vector3 operator*(const Vector3& vector) const noexcept;
	[[nodiscard]] Vector3 operator/(const Vector3& vector) const noexcept;

private:
	T m_x {};
	T m_y {};
	T m_z {};
};

template <std::floating_point T>
Vector3<T> Vector3<T>::operator+(const Vector3<T>& vector) const noexcept
{
	return Vector3<T>(m_x + vector.m_x, m_y + vector.m_y, m_z + vector.m_z);
}

template <std::floating_point T>
Vector3<T> Vector3<T>::operator-(const Vector3<T>& vector) const noexcept
{
	return Vector3<T>(m_x - vector.m_x, m_y - vector.m_y, m_z - vector.m_z);
}

template <std::floating_point T>
Vector3<T> Vector3<T>::operator*(const Vector3<T>& vector) const noexcept
{
	return Vector3<T>(m_x * vector.m_x, m_y * vector.m_y, m_z * vector.m_z);
}

template <std::floating_point T>
Vector3<T> Vector3<T>::operator/(const Vector3<T>& vector) const noexcept
{
	return Vector3<T>(m_x / vector.m_x, m_y / vector.m_y, m_z / vector.m_z);
}

#endif