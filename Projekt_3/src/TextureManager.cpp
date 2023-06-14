// #include "../inc/TextureManager.h"
// #include <filesystem>
// #include <iostream>
// #include <string>
// #include <unistd.h>
// SDL_Texture *TextureManager::loadTexture(const char *fileName, SDL_Renderer *renderer)
// {
//     char dirBuff[256];
//     getcwd(dirBuff, 256);
//     std::string tmp = dirBuff;
//     std::string dir;
//     if (tmp.substr(tmp.size() - 5, tmp.size() - 1) == "build")
//         dir = tmp.substr(0, tmp.size() - 6);
//     else
//         dir = tmp;
//     dir += "/img/";
//     dir += fileName;
//     std::cout << dir << std::endl;
//     SDL_Surface *surface = IMG_Load(dir.c_str());
//     SDL_Texture *tex = SDL_CreateTextureFromSurface(renderer, surface);
//     SDL_FreeSurface(surface);
//     return tex;
// }
