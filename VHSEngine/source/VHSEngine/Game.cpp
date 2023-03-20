#include "VHSEngine/Game.h"
#include "VHSEngine/Graphics/GraphicsEngine.h"
#include "VHSEngine/Graphics/Texture.h"

Game& Game::GetGameInstance()
{
	static Game* GameInstance = new Game();
	return *GameInstance;
}

void Game::DestroyGameInstance()
{
	static Game* GameInstance = &GetGameInstance();
	delete GameInstance;
}

void Game::Start(const char* WTitle, bool bFullscreen, int WWidth, int WHeight)
{
	Graphics = make_shared<GraphicsEngine>();

	if (Graphics->InitGE(WTitle, bFullscreen, WWidth, WHeight)) {
		bIsGameOver = false;
	}

	Run();
}

Game::Game()
{
	cout << "Game Initialised" << endl;

	Graphics = nullptr;
	bIsGameOver = false;
}

Game::~Game()
{
	Graphics = nullptr;
	cout << "Game Over..." << endl;
}

void Game::Run()
{
	if (!bIsGameOver) {

		Graphics->CreateShader({
			L"Game/Shaders/TextureShader/TextureShader.svert",
			L"Game/Shaders/TextureShader/TextureShader.sfrag"
			});

		Graphics->CreateTexture("Game/Textures/GreySquare_S.jpg");
		Graphics->CreateTexture("Game/Textures/seamless-tech-texture.jpg")->BindTexture();

		//create VAOS
		Graphics->CreateVAO(GeometricShapes::Polygon);
		Graphics->CreateVAO(GeometricShapes::Triangle);
	}

	while (!bIsGameOver) {
		//Make sure twe process what the user has done
		ProcessInput();
		
		//Apply the logic base on the inputs and the AI Logic
		Update();

		//Render the screen based on the 2 functions above
		Draw();
	}

	//Clean the game after it ends
	CloseGame();
}

void Game::Update()
{
}

void Game::ProcessInput()
{
	SDL_Event PollEvent;

	//this is waiting for inputs to be pressed
	while (SDL_PollEvent(&PollEvent)) {
		//checking what input was pressed
		switch (PollEvent.type) {
		case SDL_QUIT: //on close button pressed
			bIsGameOver = true;
			break;
		default:
			break;
		}
	}
}

void Game::Draw()
{
	Graphics->Draw();
}

void Game::CloseGame()
{
}
