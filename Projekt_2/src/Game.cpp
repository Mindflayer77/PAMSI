#include "../inc/Game.h"
#include "../inc/TextureManager.h"
#include "../inc/Visualization.h"
#include "../inc/Performance.h"
#include <iostream>

int SCREEN_WIDTH = 910;
int SCREEN_HEIGHT = 750;
int rectSize = 7;
bool complete = false;
SDL_Texture *backgroundImg;
SDL_Texture *visualizationMenu;
int state = 0;

void Game::init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen)
{
    int flags = 0;
    if (fullscreen)
    {
        flags = SDL_WINDOW_FULLSCREEN;
    }
    if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) == 0)
    {
        std::cout << "Image not initialized" << std::endl;
        std::cout << IMG_GetError() << std::endl;
    }
    else
    {
        std::cout << "Image initialized" << std::endl;
    }
    if (SDL_Init(SDL_INIT_VIDEO) == 0)
    {
        std::cout << "Everything initialized properly" << std::endl;

        window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
        if (window)
        {
            std::cout << "Window created successfully" << std::endl;
        }
        renderer = SDL_CreateRenderer(window, -1, 0);
        if (renderer)
        {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            std::cout << "Renderer created successfully" << std::endl;
        }
        isRunning = true;
        backgroundImg = TextureManager::loadTexture("back.png", renderer);
        visualizationMenu = TextureManager::loadTexture("2.png", renderer);
        state = 0;
    }
    else
    {
        std::cout << SDL_GetError() << std::endl;
        isRunning = false;
    }
}

void Game::handleEvents()
{
    bool end = false;
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type)
    {
    case SDL_QUIT:
        isRunning = false;
        break;
    case SDL_KEYDOWN:
        if (event.key.keysym.sym == SDLK_1)
        {
            state = 1;
            visualizationQuickSort(renderer);
            while (end == false)
            {
                SDL_PollEvent(&event);
                if (event.type == SDL_KEYDOWN)
                {
                    end = true;
                }
                else if (event.type == SDL_QUIT)
                {
                    break;
                    isRunning = false;
                }
            }
        }
        else if (event.key.keysym.sym == SDLK_2)
        {
            state = 1;
            visualizationMergeSort(renderer);
            while (end == false)
            {
                SDL_PollEvent(&event);
                if (event.type == SDL_KEYDOWN)
                {
                    end = true;
                }
                else if (event.type == SDL_QUIT)
                {
                    break;
                    isRunning = false;
                }
            }
        }
        else if (event.key.keysym.sym == SDLK_3)
        {
            state = 1;
            visualizationIntroSort(renderer);
            while (end == false)
            {
                SDL_PollEvent(&event);
                if (event.type == SDL_KEYDOWN)
                {
                    end = true;
                }
                else if (event.type == SDL_QUIT)
                {
                    break;
                    isRunning = false;
                }
            }
        }
        else if(event.key.keysym.sym == SDLK_4)
        {
            state = 1;
            Error err = performanceTest();
            if(err == READ)
                std::cerr << "Error while reading data" << std::endl;
            else if(err == WRITE)
                std::cerr << "Error while writing data" << std::endl;
            else if(err == FILE_NOT_OPENED)
                std::cerr << "Error while trying to open a file" << std::endl;
        }
        else if(event.key.keysym.sym == SDLK_ESCAPE)
            isRunning = false;
        break;
    default:
        break;
    }
}

void Game::render()
{
    SDL_RenderClear(renderer);
    if (state == 0)
    {
        SDL_RenderCopy(renderer, backgroundImg, NULL, NULL);
    }
    if (state == 1)
    {
        SDL_RenderCopy(renderer, backgroundImg, NULL, NULL);
        //SDL_RenderCopy(renderer, visualizationMenu, NULL, NULL);
    }
    SDL_RenderPresent(renderer);
}

void Game::cleanUp()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "Game cleaned" << std::endl;
}

bool Game::running()
{
    return isRunning;
}

void Game::update()
{
}