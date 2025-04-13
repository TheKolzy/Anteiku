template <std::floating_point T>
constexpr Vector3<T> Vector3<T>::operator+(const Vector3<T>& vector3) const noexcept
{
	return Vector3<T> { m_x + vector3.m_x, m_y + vector3.m_y, m_z + vector3.m_z };
}

template <std::floating_point T>
constexpr Vector3<T> Vector3<T>::operator-(const Vector3<T>& vector3) const noexcept
{
	return Vector3<T> { m_x - vector3.m_x, m_y - vector3.m_y, m_z - vector3.m_z };
}

template <std::floating_point T>
constexpr Vector3<T> Vector3<T>::operator*(const Vector3<T>& vector3) const noexcept
{
	return Vector3<T> { m_x * vector3.m_x, m_y * vector3.m_y, m_z * vector3.m_z };
}

template <std::floating_point T>
constexpr Vector3<T> Vector3<T>::operator/(const Vector3<T>& vector3) const noexcept
{
	return Vector3<T> { m_x / vector3.m_x, m_y / vector3.m_y, m_z / vector3.m_z };
}