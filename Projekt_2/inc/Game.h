#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Sorting.h"

extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;
extern int rectSize;
extern bool complete;

class Game 
{
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	bool isRunning;
public:
	Game(){}
	~Game(){}
	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	void handleEvents();
	void cleanUp();
	bool running();
	void render();
	void update();
	void display();
};