#include "Errors.h"


extern void fatalError(std::string errorString)
{
	std::cout << "A fatal error has occured, details below:\n";
	std::cout << errorString << std::endl;
	std::cout << "Press any key to continue...\n";
	int tmp;
	std::cin >> tmp;
	SDL_Quit();
	exit(1);
}