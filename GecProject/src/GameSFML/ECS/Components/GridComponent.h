#pragma once
#include <imgui.h>
#include <vector>
#include <string>
#include "Component.h"
#include "../../Vector2.h"
#include "../../Rect.h"
#include "../../Color.h"
#include "../ECSManager.h"

enum class GridType
{
	Normal,
	Isometric
};

// Grid Component.
class GridComponent : public Component
{
	GridType m_Type{ GridType::Normal }; // Grid type.
	Vector2<int> m_CellSize{ 0, 0 }; // Size of each cell.
	Vector2<int> m_GridSize{ 0, 0 }; // Size of the grid.
	std::string m_TextureName{ "" }; // Name of the texture.
	float m_OutlineThickness{ 1.0f }; // Grid outline thickness.
	Color m_OutlineColor{ 1.0f, 1.0f, 1.0f, 0.0f }; // Grid outline color.
	Color m_FillColor{ 0.0f, 0.0f, 0.0f, 0.0f }; // Grid fill color.

public:
	std::vector<EntityID> m_Cells{}; // Vector of cells. TODO: Change from Rect, to an actual cell class.

    // ImGui elements for the GridComponent.
    void OnGui() override
    {
		ImGui::Combo("Grid Type", (int*)&m_Type, "Normal\0Isometric\0"); // Combo box for Grid Type.
		ImGui::DragInt2("Cell Size", &m_CellSize.x, 1);
		ImGui::DragInt2("Grid Size", &m_GridSize.x, 1);
		ImGui::DragFloat("Outline Thickness", &m_OutlineThickness, 0.1f, 0.6f, 3.0f, "%.3f", ImGuiSliderFlags_AlwaysClamp);
		ImGui::ColorEdit4("Outline Colour##Grid", m_OutlineColor, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaPreviewHalf); // Colour picker. No inputs.
		ImGui::ColorEdit4("Fill Colour##Grid", m_FillColor, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaPreviewHalf); // Colour picker. No inputs.
    }

	// Get grid type.
	GridType GetType() { return m_Type; }
	// Get cell size.
	Vector2<int>& GetCellSize() { return m_CellSize; }
	// Get grid size.
	Vector2<int>& GetGridSize() { return m_GridSize; }
	// Get texture name.
	std::string GetTextureName() { return m_TextureName; }
	// Get outline thickness.
	float GetOutlineThickness() { return m_OutlineThickness; }
	// Get outline color.
	Color& GetOutlineColor() { return m_OutlineColor; }
	// Get fill color.
	Color& GetFillColor() { return m_FillColor; }
	// Set grid type.
	void SetType(GridType type) { m_Type = type; }
	// Set cell size.
	void SetCellSize(Vector2<int> cellSize) { m_CellSize = cellSize; }
	// Set grid size.
	void SetGridSize(Vector2<int> gridSize) { m_GridSize = gridSize; }
	// Set texture name.
	void SetTextureName(std::string textureName) { m_TextureName = textureName; }
	// Set outline thickness.
	void SetOutlineThickness(float outlineThickness) { m_OutlineThickness = outlineThickness; }
	// Set outline color.
	void SetOutlineColor(Color outlineColor) { m_OutlineColor = outlineColor; }
	// Set fill color.
	void SetFillColor(Color fillColor) { m_FillColor = fillColor; }

	GridComponent() {}
	GridComponent(Vector2<int> cellSize, Vector2<int> gridSize, std::string defaultTexture = "Backup.png") : m_CellSize(cellSize), m_GridSize(gridSize), m_TextureName(defaultTexture) {}
	GridComponent(Vector2<int> cellSize, Vector2<int> gridSize, GridType gridType, std::string defaultTexture = "Backup.png") : m_CellSize(cellSize), m_GridSize(gridSize), 
		m_Type(gridType), m_TextureName(defaultTexture) {}
};