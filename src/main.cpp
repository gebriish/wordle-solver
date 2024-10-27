#include <core/application.h>

int main()
{
	// Simple entry point (can change the words dataset path) [max size of list defined in 'core/wordleLayer.h']
	Application app("res/FiveLetterWords.txt");
	app.run();
}