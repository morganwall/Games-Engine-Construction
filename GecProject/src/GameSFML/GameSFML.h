#pragma once
#include <iostream>
#include <string>
#include "Vector2.h"
#include "ECS/ECSManager.h"
#include "GUI.h"
#include "EventHandler.h"
#include "TextureManager.h"
#include "Window.h"

class GameSFML
{
    bool m_Quit{ false }; // Should be game quit.

    ECSManager m_ECS; // The entity component system.
    GUI m_GUI; // The GUI.
    EventHandler m_EventHandler; // The SFML and ImGui event handler.
    GameMetrics m_Metrics; // Game metrics class.
    TextureManager m_TextureManager; // The texture manager.
    Window m_Window; // The window.

    std::vector<EntityID> m_Entities{}; // Vector of the entityIDs.

public:
    // Runs the game. Contains the main game loop.
    void Run();
    // Contains all of the drawing code. Should be called within the Run function.
    void Draw();
    // Game update function.
    void Update();
    // Initialises the game.
    bool Init();
    // Cleanup the game.
    void Cleanup();

    // Constructor.
    GameSFML() {};
    // Destructor.
    ~GameSFML() {};
};