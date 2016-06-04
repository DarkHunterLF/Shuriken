#include "ShurikenEngine.h"



ShurikenEngine::ShurikenEngine(std::string name, int width, int height) : _window(nullptr), _name(name), _screenWidth(width), _screenHeight(height), _gameState(GAME_STATE::PLAY)
{
}

ShurikenEngine::~ShurikenEngine()
{
}

void ShurikenEngine::run()
{
	initSystems();

	_sprite.init(-1, -1, 2, 2);

	_playerTexture = ImageLoader::loadPNG("Textures/ninjaWhite.png");

	gameLoop();
}

void ShurikenEngine::initSystems()
{
	SDL_Init(SDL_INIT_EVERYTHING);

	_window = SDL_CreateWindow(_name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		_screenWidth, _screenHeight, SDL_WINDOW_OPENGL);
	if (_window == nullptr)
	{
		fatalError("SDL window could not be created!");
	}

	SDL_GLContext glcontext = SDL_GL_CreateContext(_window);
	if (_window == nullptr)
	{
		fatalError("GL Context could not be created!");
	}

	GLenum glInit = glewInit();

	if (glInit != GLEW_OK)
	{
		fatalError("Glew could not be initialised!");
	}

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	glClearColor(0.0f, 0.0f, 1.0f, 1.0f); //Sets 'background' colour

	initShaders();
}

void ShurikenEngine::initShaders()
{
	_colorProgram.compileShaders("Shaders/colorShader.vert", "Shaders/colorShader.frag");
	_colorProgram.addAttribute("vertexPosition");
	_colorProgram.addAttribute("vertexColor");
	_colorProgram.addAttribute("vertexUV");
	_colorProgram.linkShaders();
}

void ShurikenEngine::gameLoop()
{
	while (_gameState != GAME_STATE::EXIT)
	{
		processInput();

		//_colorProgram.getUniformLocation("varname");

		drawGame();
	}
}

void ShurikenEngine::processInput()
{
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		switch (e.type)
		{
			case SDL_QUIT:
				_gameState = GAME_STATE::EXIT;
				break;
			
			case SDL_MOUSEMOTION:
				std::cout << "X: " << e.motion.x << "\nY: " << e.motion.y << std::endl;
				break;

		}
	};
}

void ShurikenEngine::drawGame()
{
	glClearDepth(1.0);
	glActiveTexture(GL_TEXTURE0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_colorProgram.use();
	glBindTexture(GL_TEXTURE_2D, _playerTexture.id);
	GLint textureLocation = _colorProgram.getUniformLocation("mySampler");
	glUniform1i(textureLocation, 0);

	_sprite.draw();

	glBindTexture(GL_TEXTURE_2D, 0);
	_colorProgram.unUse();

	SDL_GL_SwapWindow(_window);
}