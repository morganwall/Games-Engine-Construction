#include "GameSFML/GameSFML.h"

int main()
{
	// Enable Memory Leak Detection when in Debug Mode.
#ifdef _DEBUG // Check if we're in Debug mode.
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);
#endif // _DEBUG

	// Create Game Instance.
	GameSFML* game = new GameSFML(); // Create a new game object.
	
	// Initialise Game and Check that it Succeeded
	assert(game->Init() && "Failed to Initialise the Game!"); // Check the game initialised successfully.
	
	// Run the Game.
	game->Run(); // Run the game.
	
	// Cleanup the Game Instance
	delete game; // Cleanup game object.
	
	return 0;
}

// TODO:
// Fix the linker error that sometimes happens on building.
// Rewrite the MovementSystem, and Use WASD Movement
// Add a World Class.
// Improve Performance of the Grid System.
// Add a Render Order.
// Add Entity Selection.
// Add a Camera System.
// Add a Scrolling Camera.
// Add a Map Editor.
// Add a Menu for Spawning Entities and Giving them Components.
// Add an Ability System.
// Add a HUD to the GUI class.
// Add Health and Mana, and a way of dying.
// Fix Rendering at Different Resolutions.
// Expand on the Physics System if Needed.
// Fix Left Click Doing OnLeftClick Twice in the GridSystem.