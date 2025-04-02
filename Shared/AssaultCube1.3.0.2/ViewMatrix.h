#ifndef VIEWMATRIX_H
#define VIEWMATRIX_H

#include "Memory.h"
#include "Vector3.h"

#include <imgui.h>

#include <cstdint>

class ViewMatrix
{
public:
	explicit ViewMatrix(std::uintptr_t address)                  noexcept;

	[[nodiscard]] float getElement   (int row, int column) const noexcept;
	[[nodiscard]] bool  worldToScreen(const Vector3<float>& world
		, Vector3<float>& screen)                      const noexcept;

private:
	const std::uintptr_t m_address {};
};

#endif