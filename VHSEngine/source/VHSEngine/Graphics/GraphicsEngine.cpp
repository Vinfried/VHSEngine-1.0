#include "VHSEngine/Graphics/GraphicsEngine.h"
#include "GL/glew.h"
#include "VHSEngine/Graphics/VertexArrayObject.h"
#include "VHSEngine/Graphics/ShaderProgram.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "VHSEngine/Graphics/Texture.h"

GraphicsEngine::GraphicsEngine()
{
	SdlWindow = nullptr;
	SdlGLContext = NULL;
	bWireframeMode = false;
}

GraphicsEngine::~GraphicsEngine()
{
	//remove textures from memory
	TextureStack.clear();

	//this will handle deleting the SDL window from memory
	SDL_DestroyWindow(SdlWindow);

	//destroy the GL context for SDL
	SDL_GL_DeleteContext(SdlGLContext);
	//close the SDL framework
	SDL_Quit();

	cout << "Destroyed Graphics Engine..." << endl;

}

bool GraphicsEngine::InitGE(const char* WTitle, bool bFullScreen, int WWidth, int WHeight)
{
	//make sure SDL initialises
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		cout << "SDL failed: " << SDL_GetError() << endl;
		return false;
	}
	//Use OpenGL 4.6 and set default attributes
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);

	//Set the fullscreen flag
	int FullscreenFlag = 0;

	if (bFullScreen) {
		FullscreenFlag = SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN;
	}
	else {
		FullscreenFlag = SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN;
	}

	//create the SDL2 image

	SdlWindow = SDL_CreateWindow(
		WTitle,
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, //location of the window
		WWidth, WHeight, // width and height of the window
		FullscreenFlag
	);

	if (SdlWindow == nullptr) {
		cout << "SDL window failed: " << SDL_GetError() << endl;
		return false;
	}

	//add all the gl attributes to the window
	SdlGLContext = SDL_GL_CreateContext(SdlWindow);
	if (SdlGLContext == NULL) {
		cout << "SDL GL Context failed: " << SDL_GetError() << endl;

	}

	//to make glew work we need to mark experimental true
	glewExperimental = GL_TRUE;

	const GLenum InitGLEW = glewInit();

	if (InitGLEW != GLEW_OK) {
		cout << "GLEW failed: " << glewGetErrorString(InitGLEW) << endl;
		return false;
	}

	return true;
}

void GraphicsEngine::PresentGraphics()
{
	//present the new graphics using openGL
	SDL_GL_SwapWindow(SdlWindow);
}

void GraphicsEngine::ClearGraphics()
{
	//set the background color
	glClearColor(0.23f, 0.38f, 0.47f, 1.0f);

	//clear the screen
	glClear(GL_COLOR_BUFFER_BIT);
}

void GraphicsEngine::Draw()
{
	ClearGraphics();

	HandleWireFrameMode(false);

	vhsuint index = 0;
	for (VAOPtr VAO : VAOs) {
		
		Shader->RunShader();
		

		//move the object
		glm::mat4 transform = glm::mat4(1.0f);

		if (index == 0) { //Square
			//move in the x, y or z direction based on the amount added
			transform = glm::translate(transform, glm::vec3(0.5f, 0.0, 0.0f));
			//radians is rotating amount
			//vec3 is the direction to rotate in
			transform = glm::rotate(transform, glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f));

		}
		else if (index == 1) { //Triangle
			transform = glm::translate(transform, glm::vec3(-0.5f, 0.0, 0.0f));
			//x and y will work for our 2D shapes
			//z must be larger than 0 or you wont see the object (1 is default)
			transform = glm::scale(transform, glm::vec3(0.75f, 0.75f, 1.0f));
		}

		Shader->SetMat4("transform", transform);
		//draw each VAO
		VAO->Draw();

		index++;
	}

	index = 0;

	PresentGraphics();
}

SDL_Window* GraphicsEngine::GetWindow() const
{
	return SdlWindow;
}

void GraphicsEngine::CreateVAO(GeometricShapes Shape)
{
	// Create a new VAO as a shared pointer
	VAOPtr NewVAO = make_shared<VAO>(Shape);
	//add it to the stack
	VAOs.push_back(NewVAO);
}

void GraphicsEngine::CreateShader(VFShaderParams ShaderFilePaths)
{
	//create a new shader class
	ShaderPtr NewShader = make_shared<ShaderProgram>();

	//initialise the shader into opengl using the file paths
	NewShader->InitVFShader(ShaderFilePaths);
	
	//add the shader to our graphics engine
	Shader = NewShader;

}

TexturePtr GraphicsEngine::CreateTexture(const char* FilePath)
{
	TexturePtr NewTexture = nullptr;

	//Run through all the textures and check if one with the same path exists
	for (TexturePtr TestTexture : TextureStack) {
		if (TestTexture->GetFilePath() == FilePath) {
			NewTexture = TestTexture;
			cout << "Texture found! Assigning current texture." << endl;
			break;
		}
	}

	//if there is no texture already in existence
	if (NewTexture == nullptr) {
		cout << "Creating new texture..." << endl;

		//create a new texture already in existence
		NewTexture = make_shared<Texture>();

		//if the filter was found assign it to the texture stack
		if (NewTexture->CreateTextureFromFilePath(FilePath)) {
			cout << "Texture" << NewTexture->GetID() << "creation success! Adding to Texture Stack." << endl;
			
			//add the texture to the texture stack
			TextureStack.push_back(NewTexture);
		
		}
	}

	return NewTexture;
}

void GraphicsEngine::HandleWireFrameMode(bool bShowWireframeMode)
{
	//if wireframe mode is set, change it, vice versa
	if (bShowWireframeMode != bWireframeMode) {
		bWireframeMode = bShowWireframeMode;

		//change how openGL renders between vertices
		if (bWireframeMode) {
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
		else {
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}

		cout << "Wireframe mode updated..." << endl;
	}
}
