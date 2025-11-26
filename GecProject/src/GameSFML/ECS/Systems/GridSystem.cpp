#include "GridSystem.h"
#include "../ECSManager.h"

void GridSystem::Update(float deltaTime)
{
	for (EntityID curEntity : m_Entities) // Loop through all the system's entities.
	{
		GridComponent& grid{ m_ECS.GetComponent<GridComponent>(curEntity) }; // Get the GridComponent of the current entity.
		TransformComponent& transform{ m_ECS.GetComponent<TransformComponent>(curEntity) }; // Get the TransformComponent of the current entity.

		if ((grid.GetGridSize().x * grid.GetGridSize().y) == grid.m_Cells.size()) // Check if all the cells are already created.
		{
			for (int y = 0; y < grid.GetGridSize().y; y++)
			{
				for (int x = 0; x < grid.GetGridSize().x; x++)
				{
					EntityID cell{ grid.m_Cells[(y * grid.GetGridSize().x) + x] }; // Get the current cell.
					TransformComponent& cellTransform{ m_ECS.GetComponent<TransformComponent>(cell) }; // Get the TransformComponent of the cell.

					if (grid.GetType() == GridType::Normal) // Check if grid is normal.
					{
						cellTransform.SetPosition({ float(grid.GetCellSize().x * x + transform.GetPosition().x), float(grid.GetCellSize().y * y + transform.GetPosition().y) }); // Set the cell position.
					}
					else if (grid.GetType() == GridType::Isometric) // Check if grid is isometric.
					{
						Vector2<float> isoPos
						{
							(x - y) * (grid.GetCellSize().x / 2.0f) + transform.GetPosition().x,
							(x + y) * (grid.GetCellSize().y / 2.0f) + transform.GetPosition().y
						};

						cellTransform.SetPosition(isoPos); // Set the cell position.
					}
				}
			}
		}
		else // Create cells.
		{
			for (EntityID cell : grid.m_Cells) // Loop through all the cells.
			{
				m_ECS.RemoveEntity(cell); // Destroy the cell.
			}
			grid.m_Cells.clear(); // Clear the cells. This is needed when resizing an already existing grid.

			for (int y = 0; y < grid.GetGridSize().y; y++)
			{
				for (int x = 0; x < grid.GetGridSize().x; x++)
				{
					EntityID cell{ m_ECS.NewEntity() }; // Create a new cell.
					m_ECS.AddComponent<TransformComponent>(cell, TransformComponent()); // Add a TransformComponent to the cell.
					m_ECS.AddComponent<SpriteComponent>(cell, SpriteComponent()); // Add a SpriteComponent to the cell.
					TransformComponent& cellTransform{ m_ECS.GetComponent<TransformComponent>(cell) }; // Get the TransformComponent of the cell.
					SpriteComponent& cellSprite{ m_ECS.GetComponent<SpriteComponent>(cell) }; // Get the SpriteComponent of the cell.

					cellSprite.SetTexture(m_TextureManager.GetTexture2D(grid.GetTextureName())); // Set the cell sprite texture.

					if (grid.GetType() == GridType::Normal) // Check if grid is normal.
					{
						cellTransform.SetPosition({ float(grid.GetCellSize().x * x + transform.GetPosition().x), float(grid.GetCellSize().y * y + transform.GetPosition().y) }); // Set the cell position.
					}
					else if (grid.GetType() == GridType::Isometric) // Check if grid is isometric.
					{
						Vector2<float> isoPos
						{
							(x - y) * (grid.GetCellSize().x / 2.0f) + transform.GetPosition().x,
							(x + y) * (grid.GetCellSize().y / 2.0f) + transform.GetPosition().y
						};

						cellTransform.SetPosition(isoPos); // Set the cell position.
					}

					grid.m_Cells.push_back(cell); // Add the cell to the grid.
				}
			}
		}
	}
}

void GridSystem::Draw()
{
	for (EntityID curEntity : m_Entities) // Loop through all the system's entities.
	{
		GridComponent& grid{ m_ECS.GetComponent<GridComponent>(curEntity) }; // Get the GridComponent of the current entity.

		for (EntityID curCell : grid.m_Cells)
		{
			TransformComponent& cellTransform{ m_ECS.GetComponent<TransformComponent>(curCell) }; // Get the TransformComponent of the cell entity.

			sf::RectangleShape rect; // TODO: Remove all of this when Creating the Cell class, and handle rendering in there.
			rect.setPosition(cellTransform.GetPosition().x, cellTransform.GetPosition().y); // Set the rect position.
			rect.setSize({float(grid.GetCellSize().x), float(grid.GetCellSize().y)}); // Set the rect size.
			rect.setOutlineColor(grid.GetOutlineColor()); // Set the rect outline color.
			rect.setOutlineThickness(grid.GetOutlineThickness()); // Set the rect outline thickness.
			rect.setFillColor(grid.GetFillColor()); // Set the rect fill color.
			m_Window.GetSFWindow().draw(rect); // Draw the rect.
		}
	}
}

void GridSystem::OnLeftClick(const Vector2<int>& mousePos)
{
	for (EntityID curEntity : m_Entities) // Loop through all the system's entities.
	{
		GridComponent& grid{ m_ECS.GetComponent<GridComponent>(curEntity) }; // Get the GridComponent of the current entity.
		TransformComponent& transform{ m_ECS.GetComponent<TransformComponent>(curEntity) }; // Get the TransformComponent of the current entity.

		if (curEntity == m_ECS.GetPlayerEntity()) // Check if the current entity is the player.
			continue; // Skip the player entity.

		if (grid.GetType() == GridType::Normal) // Check if the grid is normal.
		{
			if (mousePos.x >= transform.GetPosition().x && mousePos.x <= transform.GetPosition().x + (grid.GetGridSize().x * grid.GetCellSize().x) &&
				mousePos.y >= transform.GetPosition().y && mousePos.y <= transform.GetPosition().y + (grid.GetGridSize().y * grid.GetCellSize().y)) // Make sure the mouse click was within the grid.
			{
				// Get cell pos.
				Vector2<int> cellPos
				{
					int((mousePos.x - transform.GetPosition().x)) / grid.GetCellSize().x,
					int((mousePos.y - transform.GetPosition().y)) / grid.GetCellSize().y
				};

				// Check that cell pos is valid.
				if (cellPos.x >= 0 && cellPos.x < grid.GetGridSize().x && cellPos.y >= 0 && cellPos.y < grid.GetGridSize().y)
				{
					// Get the cell entity, and sprite.
					EntityID cell{ grid.m_Cells[(cellPos.y * grid.GetGridSize().x) + cellPos.x] }; // Get the cell entity.
					SpriteComponent& cellSprite{ m_ECS.GetComponent<SpriteComponent>(cell) }; // Get the SpriteComponent of the cell entity.

					// Change the texture. TODO: Make this change dynamically, or with a selected texture.
					cellSprite.SetTexture(m_TextureManager.GetTexture2D("GrassBlockFull.png")); // Set the cell sprite texture.
				}
			}
		}
		else if (grid.GetType() == GridType::Isometric) // Check if the grid is isometric.
		{
			// Convert mouse position to isometric grid coordinates
			Vector2<float> relativePos
			{
				mousePos.x - transform.GetPosition().x,
				mousePos.y - transform.GetPosition().y
			};

			Vector2<int> cellPos
			{
				int((relativePos.x / (grid.GetCellSize().x / 2.0f) + relativePos.y / (grid.GetCellSize().y / 2.0f)) / 2),
				int((relativePos.y / (grid.GetCellSize().y / 2.0f) - (relativePos.x / (grid.GetCellSize().x / 2.0f))) / 2)
			};

			// Check that cell pos is valid.
			if (cellPos.x >= 0 && cellPos.x < grid.GetGridSize().x && cellPos.y >= 0 && cellPos.y < grid.GetGridSize().y)
			{
				// Get the cell entity, and sprite.
				EntityID cell{ grid.m_Cells[(cellPos.y * grid.GetGridSize().x) + cellPos.x] }; // Get the cell entity.
				SpriteComponent& cellSprite{ m_ECS.GetComponent<SpriteComponent>(cell) }; // Get the SpriteComponent of the cell entity.

				// Change the texture. TODO: Make this change dynamically, or with a selected texture.
				cellSprite.SetTexture(m_TextureManager.GetTexture2D("GrassBlockFull.png")); // Set the cell sprite texture.
			}
		}
	}
}