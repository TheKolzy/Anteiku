#include "ViewMatrix.h"

ViewMatrix::ViewMatrix(std::uintptr_t address) noexcept
	: m_address { address }
{
}

float ViewMatrix::getElement(int row, int column) const noexcept
{
	const int indexOpenGL { (row * 4) + (column * 16) };     // Column Major = (column, row)
	// const int indexDirectX { (row * 16) + (column * 4) }; // Row Major    = (row, column)

	return Memory::read<float>(m_address + indexOpenGL);
}

bool ViewMatrix::worldToScreen(const Vector3<float>& world, Vector3<float>& screen) const noexcept
{
    const float w { getElement(3, 0) * world.getX() + getElement(3, 1) * world.getY()
                  + getElement(3, 2) * world.getZ() + getElement(3, 3) };
    if (w <= 0.001f)
        return false;

    const float x { getElement(0, 0) * world.getX() + getElement(0, 1) * world.getY()
                  + getElement(0, 2) * world.getZ() + getElement(0, 3) };
    const float y { getElement(1, 0) * world.getX() + getElement(1, 1) * world.getY()
                  + getElement(1, 2) * world.getZ() + getElement(1, 3) };

    const float nx = x / w;
    const float ny = y / w;

    const ImVec2 size = ImGui::GetIO().DisplaySize;
    screen.setX( (size.x * 0.5f * nx) + (nx + size.x * 0.5f));
    screen.setY(-(size.y * 0.5f * ny) + (ny + size.y * 0.5f));

	return true;
}