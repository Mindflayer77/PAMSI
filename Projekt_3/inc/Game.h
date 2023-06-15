#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <utility>
#include <vector>
extern int WIN_HEIGHT;
extern int WIN_WIDTH;
extern const char* title;
extern bool fullscreen;
class Game
{
  private:
    std::vector<std::vector<char>> board;
    uint sizeBoard;
    bool finished;
    bool running;
    char currentPlayer;
    char winner;
    uint moves;
    uint maxDepth;

  private:
    SDL_Renderer *renderer;
    SDL_Window *window;
    std::pair<int, int> Xpos;
    std::pair<int, int> Opos;
    bool drawX;
    bool drawO;
    bool drawGrid;
    int state; //0 ---> menu, 1 ---> game

  public:
    Game();
    Game(uint size);
    ~Game();
    void init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen);
    void handleEvents();
    void update();
    std::vector<std::vector<char>> &getBoard();
    std::vector<std::vector<char>> getBoardCopy();
    bool isRunning() const;
    bool getStatus() const;
    void setStatus(bool newStatus);
    void drawBoard() const;
    int evaluate();
    int minimax(int depth, int alpha, int beta, bool maximizer);
    void setXpos(int x, int y);
    void setOpos(int x, int y);
    std::pair<int,int> getOpos() const;
    std::pair<int,int> getXpos() const;
    SDL_Rect playerTextSize() const;
    bool validMove(int x, int y) const;
    void setGame(int size);
    void resetGame();
};