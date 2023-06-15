#pragma once
#include "Game.h"
#include <filesystem>
#include <iostream>
#include <unistd.h>

class TextureManager
{
  private:
    static SDL_Texture *menu;
    static SDL_Texture *grid_3;
    static SDL_Texture *grid_4;
    static SDL_Texture *grid_5;
    static SDL_Texture *grid_6;
    static SDL_Texture *textureX;
    static SDL_Texture *textureO;
    static SDL_Texture *X_wins;
    static SDL_Texture *O_wins;
    static SDL_Texture *tie;

  public:
    static SDL_Texture *loadTexture(const char *fileName, SDL_Renderer *renderer)
    {
        char dirBuff[256];
        getcwd(dirBuff, 256);
        std::string tmp = dirBuff;
        std::string dir;
        if (tmp.substr(tmp.size() - 5, tmp.size() - 1) == "build")
            dir = tmp.substr(0, tmp.size() - 6);
        else
            dir = tmp;
        dir += "/img/";
        dir += fileName;
        std::cout << dir << std::endl;
        SDL_Surface *surface = IMG_Load(dir.c_str());
        SDL_Texture *tex = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
        return tex;
    }
    static void setGrid(SDL_Texture *texture, int size)
    {
        if (size == 3)
            grid_3 = texture;
        if (size == 4)
            grid_4 = texture;
        if (size == 5)
            grid_5 = texture;
        if (size == 6)
            grid_6 = texture;
    }
    static SDL_Texture *getGrid(int size)
    {
        if (size == 3)
            return grid_3;
        if (size == 4)
            return grid_4;
        if (size == 5)
            return grid_5;
        if (size == 6)
            return grid_6;
        return nullptr;
    }
    static void setX(SDL_Texture *texture)
    {
        textureX = texture;
    }
    static SDL_Texture *getX()
    {
        return textureX;
    }
    static void setO(SDL_Texture *texture)
    {
        textureO = texture;
    }
    static SDL_Texture *getO()
    {
        return textureO;
    }
    static void setX_wins(SDL_Texture *texture)
    {
        X_wins = texture;
    }
    static SDL_Texture *getX_wins()
    {
        return X_wins;
    }
    static void setO_wins(SDL_Texture *texture)
    {
        O_wins = texture;
    }
    static SDL_Texture *getO_wins()
    {
        return O_wins;
    }
    static void setTie(SDL_Texture *texture)
    {
        tie = texture;
    }
    static SDL_Texture *getTie()
    {
        return tie;
    }
    static void setMenu(SDL_Texture *texture)
    {
        menu = texture;
    }
    static SDL_Texture *getMenu()
    {
        return menu;
    }
};

SDL_Texture *TextureManager::menu = nullptr;
SDL_Texture *TextureManager::grid_3 = nullptr;
SDL_Texture *TextureManager::grid_4 = nullptr;
SDL_Texture *TextureManager::grid_5 = nullptr;
SDL_Texture *TextureManager::grid_6 = nullptr;
SDL_Texture *TextureManager::textureX = nullptr;
SDL_Texture *TextureManager::textureO = nullptr;
SDL_Texture *TextureManager::X_wins = nullptr;
SDL_Texture *TextureManager::O_wins = nullptr;
SDL_Texture *TextureManager::tie = nullptr;
