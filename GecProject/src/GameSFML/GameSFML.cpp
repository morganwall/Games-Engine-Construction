#include "GameSFML.h"

void GameSFML::Run()
{
    while (!m_Quit) // Main game loop. Loop while we don't want to quit.
    {
        m_Quit = m_EventHandler.Process(); // Set quit to the EventHandler return, as it will return true on a quit event.

        Draw();
        Update();
    }

    Cleanup(); // Cleanup the game.
}

void GameSFML::Draw()
{
    // Draw the GUI.
    m_GUI.Draw();

    // Clear the SFML Window.
    m_Window.Clear();

    // Any System Draw Calls.
    m_ECS.GetSystem<RenderSystem>().Draw();
	m_ECS.GetSystem<CollisionSystem>().Draw();
	m_ECS.GetSystem<GridSystem>().Draw();

    // Render the GUI.
    m_GUI.Render();

    // Display to the Window.
    m_Window.Display();
}

void GameSFML::Update()
{
    // Update deltaTime.
    m_Window.Update();

    // Update Game Metrics.
    m_Metrics.Update(m_Window);

	// Update ECS Systems. Not All Systems Will Have an Update Function.
    m_ECS.GetSystem<RenderSystem>().Update(m_Window.GetDeltaTime());
    m_ECS.GetSystem<MovementSystem>().Update(m_Window.GetDeltaTime());
	m_ECS.GetSystem<CollisionSystem>().Update(m_Window.GetDeltaTime());
	m_ECS.GetSystem<AnimationSystem>().Update(m_Window.GetDeltaTime());
	m_ECS.GetSystem<GridSystem>().Update(m_Window.GetDeltaTime());
}

bool GameSFML::Init()
{
    // Create the Window.
    m_Window.Init();
    assert(m_Window.IsOpen() && "Failed to Create SFML Window!"); // Check that the window was created successfully.

    // Create Textures.
    m_TextureManager.LoadTexture("images/Block.png", {32, 32});
	m_TextureManager.LoadTexture("images/PlayerWalk1.png", { 24, 24 });
	m_TextureManager.LoadTexture("images/PlayerWalk2.png", { 24, 24 });
    m_TextureManager.LoadTexture("images/GrassBlockFull.png", { 32, 32 });

    // Create Entities. Try to keep the player entity as the first entity created.
    m_Entities.push_back(m_ECS.NewEntity());
	m_Entities.push_back(m_ECS.NewEntity());
	m_Entities.push_back(m_ECS.NewEntity());

    // Create Components.
    m_ECS.NewComponent<TransformComponent>();
    m_ECS.NewComponent<SpriteComponent>();
    m_ECS.NewComponent<PhysicsComponent>();
	m_ECS.NewComponent<MovementComponent>();
    m_ECS.NewComponent<BoundingBoxComponent>();
	m_ECS.NewComponent<AnimationComponent>();
	m_ECS.NewComponent<GridComponent>();
    m_ECS.NewComponent<InputComponent>();

    // Create Systems.
    m_ECS.NewSystem<RenderSystem>(m_Window, m_ECS);
    m_ECS.NewSystem<MovementSystem>(m_ECS);
    m_ECS.NewSystem<InputSystem>(m_Window, m_ECS);
	m_ECS.NewSystem<CollisionSystem>(m_ECS, m_Window);
	m_ECS.NewSystem<AnimationSystem>(m_ECS);
	m_ECS.NewSystem<GridSystem>(m_Window, m_ECS, m_TextureManager);

    // Set System Signatures.
    m_ECS.GetSystem<RenderSystem>().SetSignature(m_ECS.GetComponentSignature<TransformComponent>() | m_ECS.GetComponentSignature<SpriteComponent>()); // Use OR bitwise operator, to create the sinature from 
                                                                                                                                                      // several component IDs.
    m_ECS.GetSystem<MovementSystem>().SetSignature(m_ECS.GetComponentSignature<TransformComponent>() | m_ECS.GetComponentSignature<PhysicsComponent>() 
        | m_ECS.GetComponentSignature<MovementComponent>());
	m_ECS.GetSystem<InputSystem>().SetSignature(m_ECS.GetComponentSignature<InputComponent>());
    m_ECS.GetSystem<CollisionSystem>().SetSignature(m_ECS.GetComponentSignature<TransformComponent>() | m_ECS.GetComponentSignature<BoundingBoxComponent>());
	m_ECS.GetSystem<AnimationSystem>().SetSignature(m_ECS.GetComponentSignature<AnimationComponent>() | m_ECS.GetComponentSignature<SpriteComponent>());
	m_ECS.GetSystem<GridSystem>().SetSignature(m_ECS.GetComponentSignature<GridComponent>() | m_ECS.GetComponentSignature<TransformComponent>());

    // Assign Components to Entities.
    m_ECS.AddComponent<TransformComponent>(m_Entities[m_ECS.GetPlayerEntity()], TransformComponent()); // Add TransformComponent to the player entity.
    m_ECS.AddComponent<SpriteComponent>(m_Entities[m_ECS.GetPlayerEntity()], SpriteComponent(m_TextureManager.GetTexture2D("Block.png"))); // Add SpriteComponent to the player entity.
    m_ECS.AddComponent<PhysicsComponent>(m_Entities[m_ECS.GetPlayerEntity()], PhysicsComponent({ 0.0f, 0.0f })); // Add PhysicsComponent to the player entity.
    m_ECS.AddComponent<MovementComponent>(m_Entities[m_ECS.GetPlayerEntity()], MovementComponent()); // Add MovementComponent to the player entity.
	m_ECS.AddComponent<BoundingBoxComponent>(m_Entities[m_ECS.GetPlayerEntity()], BoundingBoxComponent({ 0.0f, 0.0f }, { 32.0f, 32.0f })); // Add BoundingBoxComponent to the player entity.
    m_ECS.AddComponent<AnimationComponent>(m_Entities[m_ECS.GetPlayerEntity()], AnimationComponent({&m_TextureManager.GetTexture2D("PlayerWalk1.png"),
        &m_TextureManager.GetTexture2D("PlayerWalk2.png")}, true)); // Add AnimationComponent to the player entity.
	m_ECS.AddComponent<InputComponent>(m_Entities[m_ECS.GetPlayerEntity()], InputComponent()); // Add InputComponent to the player entity.

	m_ECS.AddComponent<TransformComponent>(m_Entities[1], TransformComponent({ 100.0f, 100.0f }, 0.0f, {1.0f, 1.0f})); // Add TransformComponent to the entity.
    m_ECS.AddComponent<BoundingBoxComponent>(m_Entities[1], BoundingBoxComponent({ 100.0f, 100.0f }, { 32.0f, 32.0f })); // Add BoundingBoxComponent to the entity.
    m_ECS.AddComponent<SpriteComponent>(m_Entities[1], SpriteComponent(m_TextureManager.GetTexture2D("Block.png"))); // Add SpriteComponent to the entity.

    m_ECS.AddComponent<TransformComponent>(m_Entities[2], TransformComponent({ 200.0f, 200.0f }, 0.0f, { 1.0f, 1.0f }));
    m_ECS.AddComponent<GridComponent>(m_Entities[2], GridComponent({ 32, 16 }, { 10, 10 }, GridType::Isometric));
	m_ECS.AddComponent<InputComponent>(m_Entities[2], InputComponent());

    // Initialise EventHandler.
    assert(m_EventHandler.Init(&m_Window, &m_ECS.GetSystem<InputSystem>()) && "Failed to Initialise Event Handler!"); // Check that the Event Handler was initialised successfully.

    // Initialise GUI.
    assert(m_GUI.Init(&m_Window, &m_Metrics, &m_ECS, &m_TextureManager) && "Failed to Initialise GUI!"); // Check that the GUI was initialise successfully.

    return true;
}

void GameSFML::Cleanup()
{
    // Cleanup the Window.
    m_Window.Close();

    // Cleanup the GUI.
    m_GUI.Cleanup();
}