#include "GUI.h"
#include <typeinfo> // Used for typeid.

bool GUI::Init(Window* window, GameMetrics* metrics, ECSManager* ecs, TextureManager* textureManager)
{
	m_Window = window;
    m_Metrics = metrics;
    m_ECS = ecs;
    m_TextureManager = textureManager;

	// Init ImGui.
	ImGui::SFML::Init(m_Window->GetSFWindow());

    // Init ImGui Styles.
	ImGuiStyle& style{ ImGui::GetStyle() }; // Get the ImGui style.
	style.IndentSpacing = 6.0f; // Set the indent spacing.
	style.ScrollbarSize = 5.0f; // Set the scrollbar size.

    // Init Preview Texture.
    m_TexturePreviewEntity = m_ECS->NewEntity(); // Create new entity.
    m_ECS->AddComponent<TransformComponent>(m_TexturePreviewEntity, TransformComponent({-10000.0f, 0.0f}, 0.0f, {1.0f, 1.0f})); // Assign transform component to entity. Setting the transform pos far
                                                                                                                                // off-screen, as I only want it to show in the menu.
                                                                                                                                // TODO: If possible, add a var to RenderSystem, to hide a sprite.
    m_ECS->AddComponent<SpriteComponent>(m_TexturePreviewEntity, SpriteComponent(m_TextureManager->GetTexture2D("Backup.png"))); // Assign sprite component to entity.

    // Disable ImGui Saving and or Loading Window Settings.
	ImGuiIO& io = ImGui::GetIO(); // Get the ImGui IO.
	io.IniFilename = nullptr; // Set the INI file name to nullptr. This should stop ImGui from creating the file and writing to it.

	return true;
}

void GUI::Draw()
{
	sf::RenderWindow& sfWindow{ m_Window->GetSFWindow() }; // Get the SFML window.

	ImGui::SFML::Update(m_Window->GetSFWindow(), m_UIClock.restart()); // Update ImGui.

    // Draw FPS Window.
    if (m_ShowMetrics)
    {
        ImGui::SetNextWindowPos({ 0, 0 }); // Set the next window to be drawn at 0, 0.
        ImGui::Begin("Metrics", 0, ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize |
            ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_AlwaysAutoResize); // Create the metrics window.
        ImGui::TextColored(m_MetricsColor, "FPS: %.1f", m_Metrics->m_FPS);
        ImGui::TextColored(m_MetricsColor, "Frame Time: %.3f ms", m_Metrics->m_FrameTime);

        ImGui::End();
    }

    // Draw Settings Window.
	ImGui::SetNextWindowSize(ImVec2(sfWindow.getSize().x / 3.0f, sfWindow.getSize().y)); // Set the next window size to be 1/6th of the window size. // TODO: Make this a var.
    ImGui::SetNextWindowPos(ImVec2(sfWindow.getSize().x - (sfWindow.getSize().x / 3.0f), 0.0f)); // Set the position of the next window. // TODO: Make this a var.
    ImGui::Begin("Settings", 0, ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize); // ImGuiWindowFlags_NoSavedSettings tells ImGui to not save settings for this window in imgui.ini.
    if (ImGui::CollapsingHeader("Windows")) // Windows header.
    {
        ImGui::Checkbox("Show Demo Window", &m_ShowDemoWnd);
    }
    if (ImGui::CollapsingHeader("Metrics")) // Metrics header.
    {
        ImGui::Checkbox("Show Metrics", &m_ShowMetrics);
        if (m_ShowMetrics)
        {
            ImGui::SameLine(); // Tell ImGui to draw to the same line as the last menu object.
			ImGui::ColorEdit3("Colour##1", m_MetricsColor, ImGuiColorEditFlags_NoInputs); // Colour picker. No inputs.
            ImGui::SliderFloat("Metrics Update Time (ms)", &m_Metrics->m_UpdateTime, 1.0f, 3000.0f);
        }
        ImGui::Checkbox("Limit FPS", &m_Metrics->m_LimitFPS);
        if (m_Metrics->m_LimitFPS)
            if (ImGui::SliderFloat("FPS Limit", &m_Metrics->m_MaxFPS, 25.0f, 250.0f, "%.0f"))
                m_Metrics->m_UpdateLimit = true;
    }
    if (ImGui::CollapsingHeader("Textures")) // Textures header.
    {
        m_NumTextures = m_TextureManager->GetNumTextures();
        ImGui::Text("Number of Textures: %d", m_NumTextures);
        ImGui::Indent();
        if (ImGui::CollapsingHeader("Preview##1")) // Texture preview header.
        {
			if (ImGui::BeginListBox("##LoadedTextures")) // Loaded textures list. The text after the ## is not displayed.
            {
                for (unsigned int i = 0; i < m_NumTextures; i++) // Loop through all textures in the map.
                {
                    const bool isSelected = (m_TextureSelectedIndex == i); // Check if the current texture is selected in the list.
                    if (ImGui::Selectable(m_TextureManager->GetKeyAtIndex(i).c_str(), isSelected)) // Create a new selectable element.
                        m_TextureSelectedIndex = i;

                    if (isSelected)
                    {
                        ImGui::SetItemDefaultFocus();
                        m_ECS->GetComponent<SpriteComponent>(m_TexturePreviewEntity).SetTexture(m_TextureManager->GetTexture2D(m_TextureManager->GetKeyAtIndex(i))); // Set the sprite of the preview entity,
                                                                                                                                                                     // to the texture at index i.
                    }
                }
                ImGui::EndListBox();
            }

            ImGui::SameLine();
            ImGui::Image(m_ECS->GetComponent<SpriteComponent>(m_TexturePreviewEntity).GetSprite()); // Draw the sprite as an ImGui Image.
        }
        ImGui::Unindent();
    }
    if (ImGui::CollapsingHeader("Entities")) // Entities Header.
    {
		m_NumEntities = m_ECS->GetNumEntities();
		ImGui::Text("Number of Entities: %d", m_NumEntities);
		ImGui::Indent();
        if (ImGui::CollapsingHeader("Preview##2")) // Entity preview header.
        {
            if(ImGui::BeginListBox("##LoadedEntities", 
                ImVec2(ImGui::GetContentRegionAvail().x, 0))) // Loaded entities list. The text after the ## is not displayed.
            {
                for (unsigned int curEntity = 0; curEntity < m_NumEntities; curEntity++) // Loop through all entities in the map.
                {
					const bool isSelected{ m_EntitySelectedIndex == curEntity }; // Check if the current entity is selected in the list.
					if (ImGui::TreeNode(std::to_string(curEntity).c_str())) // Create a new tree node. A ListBox in a ListBox wouldn't work.
					{
                        if (isSelected)
                        {
                            ImGui::SetItemDefaultFocus();
                        }
                        
                        Signature entitySignature{ m_ECS->GetEntity(curEntity).GetComponents() }; // Get the entity's signature.

						if (ImGui::TreeNode("Components")) // Components tree node.
                        {
							for (size_t curComponentID = 0; curComponentID < entitySignature.size(); curComponentID++) // Loop through all components in the entity's signature.
							{
                                if (entitySignature[curComponentID]) // Check if the current component is in the entity's signature.
                                {
									std::type_index componentType{ m_ECS->GetComponentType(curComponentID) }; // Get the component type.

                                    auto getter = m_ECS->m_ComponentGetters.find(componentType); // Get the component getter from the map.
									assert(getter != m_ECS->m_ComponentGetters.end() && "Invalid Getter!"); // Check if the component getter exists by checking that we didn't reach the end of the map.
									Component& curComponent{ getter->second(curEntity) }; // Get the current component.

                                    if (ImGui::TreeNode(m_ECS->GetComponentTypeString(curComponentID).c_str()))
                                    {
										curComponent.OnGui(); // Call the component's OnGui function.

                                        ImGui::TreePop();
                                    }
                                }
							}

                            ImGui::TreePop();
                        }

						ImGui::TreePop();
					}
                }
				ImGui::EndListBox();
            }
        }
        ImGui::Unindent();
    }
    ImGui::End();

	if (m_ShowDemoWnd)
		ImGui::ShowDemoWindow(&m_ShowDemoWnd); // Show the ImGui demo window.
}

void GUI::Render()
{
	ImGui::SFML::Render(m_Window->GetSFWindow()); // Render ImGui.
}

void GUI::Cleanup()
{
	ImGui::SFML::Shutdown();
}