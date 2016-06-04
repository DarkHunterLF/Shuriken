#pragma once

#include <SDL\SDL.h>
#include <GL\glew.h>
#include <string>
#include <iostream>

#include "Sprite.h"
#include "Errors.h"
#include "GLSLProgram.h"
#include "GLTexture.h"
#include "ImageLoader.h"

enum class GAME_STATE {PLAY, EXIT};

class ShurikenEngine
{
public:
	ShurikenEngine(std::string name, int width, int height);
	~ShurikenEngine();

	void run();


private:
	void initSystems();
	void initShaders();
	void gameLoop();
	void processInput();
	void drawGame();

	SDL_Window* _window;
	int _screenWidth;
	int _screenHeight;
	std::string _name;

	GAME_STATE _gameState;
	Sprite _sprite;

	GLSLProgram _colorProgram;
	GLTexture _playerTexture;
	
};

