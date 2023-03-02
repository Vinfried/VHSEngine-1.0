#pragma once
#include "VHSEngine/Graphics/GraphicsEngine.h"
#include "CoreMinimal.h"

class Game {
public:
	//Get game instance or create one if it doesn't exist
	static Game& GetGameInstance();

	//Destroy the game running the constructor
	static void DestroyGameInstance();

	//Start the game/app
	void Start(const char* WTitle, bool bFullscreen, int WWidth, int WHeight);
private:
	Game();
	~Game();

	//Run the game loop
	void Run();

	//Handle the game logic
	void Update();

	//Handle the Input/Output
	void ProcessInput();

	//Handle the 3D graphics drawing to the screen
	//Will clear and each frame
	void Draw();

	//Handle anything that needs to be deleted when the game ends
	void CloseGame();

private:
	//boolean that ends the game
	bool bIsGameOver;

	GraphicsEnginePtr Graphics;

};