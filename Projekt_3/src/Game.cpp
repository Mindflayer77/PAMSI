#include "../inc/Game.h"
#include "../inc/TextureManager.h"
#include <algorithm>
#include <string>
#include <utility>

int WIN_HEIGHT = 700;
int WIN_WIDTH = 700;
const char *title = "Tic-Tac-Toe";
bool fullscreen = false;

Game::Game()
{
    sizeBoard = 3;
    finished = false;
    moves = 0;
    maxDepth = sizeBoard;
    std::vector<char> row;
    drawX = false;
    drawO = false;
    drawGrid = false;
    winner = '\0';
    for (uint j = 0; j < sizeBoard; ++j)
    {
        for (uint i = 0; i < sizeBoard; ++i)
        {
            row.emplace_back('_');
        }
        board.push_back(row);
        row.clear();
    }
}

Game::Game(uint size)
{
    sizeBoard = size;
    finished = false;
    moves = 0;
    maxDepth = sizeBoard;
    std::vector<char> row;
    drawX = false;
    drawO = false;
    drawGrid = false;
    winner = '\0';
    for (uint j = 0; j < size; ++j)
    {
        for (uint i = 0; i < size; ++i)
        {
            row.emplace_back('_');
        }
        board.push_back(row);
        row.clear();
    }
}

Game::~Game()
{
}

std::vector<std::vector<char>> &Game::getBoard()
{
    return board;
}

std::vector<std::vector<char>> Game::getBoardCopy()
{
    return board;
}

void Game::setStatus(bool newStatus)
{
    finished = newStatus;
}

bool Game::getStatus() const
{
    return finished;
}

void Game::setXpos(int x, int y)
{
    Xpos.first = x;
    Xpos.second = y;
}

void Game::setOpos(int x, int y)
{
    Opos.first = x;
    Opos.second = y;
}

std::pair<int, int> Game::getXpos() const
{
    return Xpos;
}

std::pair<int, int> Game::getOpos() const
{
    return Opos;
}
bool Game::isRunning() const
{
    return running;
}

void Game::drawBoard() const
{
    for (auto row : board)
    {
        for (auto elem : row)
        {
            std::cout << elem << "|";
        }
        std::cout << std::endl;
    }
}

SDL_Rect Game::playerTextSize() const
{
    SDL_Rect rect;
    rect.h = WIN_HEIGHT / sizeBoard - 60 / sizeBoard;
    rect.w = WIN_WIDTH / sizeBoard - 60 / sizeBoard;
    return rect;
}

bool Game::validMove(int x, int y) const
{
    if (board[x][y] == '_' && x < sizeBoard && y < sizeBoard)
    {
        return true;
    }
    return false;
}

void Game::init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen)
{
    currentPlayer = 'O';
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
        running = true;
        TextureManager::setGrid(TextureManager::loadTexture("grid_3.png", renderer), 3);
        TextureManager::setGrid(TextureManager::loadTexture("grid_4.png", renderer), 4);
        TextureManager::setGrid(TextureManager::loadTexture("grid_5.png", renderer), 5);
        TextureManager::setGrid(TextureManager::loadTexture("grid_6.png", renderer), 6);
        TextureManager::setX(TextureManager::loadTexture("X.png", renderer));
        TextureManager::setO(TextureManager::loadTexture("O.png", renderer));
        TextureManager::setX_wins(TextureManager::loadTexture("X_wins.png", renderer));
        TextureManager::setO_wins(TextureManager::loadTexture("O_wins.png", renderer));
        TextureManager::setTie(TextureManager::loadTexture("Tie.png", renderer));
        drawGrid = true;
    }
    else
    {
        std::cout << SDL_GetError() << std::endl;
        running = false;
    }
}

void Game::handleEvents()
{
    if (currentPlayer == 'X' && finished!= true)
    {
        SDL_Event event;
        SDL_PollEvent(&event);
        switch (event.type)
        {
        case SDL_QUIT:
            running = false;
            break;
        case SDL_MOUSEBUTTONDOWN:
            std::cout << "Click" << std::endl;
            int x, y;
            SDL_GetMouseState(&x, &y);
            x = x / (WIN_WIDTH / sizeBoard);
            y = y / (WIN_HEIGHT / sizeBoard);
            if (validMove(x, y) && finished != true)
            {
                board[x][y] = 'X';
                Xpos = {x, y};
                ++moves;
                int result = -5;
                result = evaluate();
                currentPlayer = 'O';
                if (result == 1 || result == -1)
                {
                    finished = true;
                    winner = 'X';
                }
                if (moves == sizeBoard * sizeBoard)
                {
                    finished = true;
                }
                drawX = true;
            }
            break;
        default:
            break;
        }
    }
    else if (finished != true)
    {
        int result = 0;
        int bestResult = -2;
        std::pair<int, int> best;
        for (int i = 0; i < sizeBoard; ++i)
        {
            for (int j = 0; j < sizeBoard; ++j)
            {
                if (board[i][j] == '_')
                {
                    board[i][j] = 'O';
                    result = minimax(maxDepth, -10000, 10000, false);
                    board[i][j] = '_';
                    if (result > bestResult)
                    {
                        bestResult = result;
                        best.first = i;
                        best.second = j;
                    }
                }
            }
        }
        if (validMove(best.first, best.second) && finished != true)
        {
            board[best.first][best.second] = 'O';
            Opos = {best.first, best.second};
            ++moves;
            int eval = -5;
            eval = evaluate();
            currentPlayer = 'X';
            if (eval == 1 || eval == -1)
            {
                finished = true;
                winner = 'O';
            }
            if (moves == sizeBoard * sizeBoard)
            {
                finished = true;
            }
            drawO = true;
        }
    }
}

void Game::update()
{
    if (drawGrid)
    {
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, TextureManager::getGrid(4), NULL, NULL);
        SDL_RenderPresent(renderer);
        drawGrid = false;
    }
    if (drawX)
    {
        SDL_Rect rec = playerTextSize();
        rec.x = Xpos.first * (WIN_WIDTH / sizeBoard) + 30 / sizeBoard;
        rec.y = Xpos.second * (WIN_HEIGHT / sizeBoard) + 30 / sizeBoard;
        SDL_RenderCopy(renderer, TextureManager::getX(), NULL, &rec);
        SDL_RenderPresent(renderer);
        drawX = false;
    }
    if (drawO)
    {
        SDL_Rect rec = playerTextSize();
        rec.x = Opos.first * (WIN_WIDTH / sizeBoard) + 30 / sizeBoard;
        rec.y = Opos.second * (WIN_HEIGHT / sizeBoard) + 30 / sizeBoard;
        SDL_RenderCopy(renderer, TextureManager::getO(), NULL, &rec);
        SDL_RenderPresent(renderer);
        drawO = false;
    }
    if (finished)
    {
        SDL_Rect rec;
        rec.h = WIN_HEIGHT;
        rec.w = WIN_WIDTH * 2;
        rec.x = -WIN_WIDTH / 2;
        rec.y = WIN_HEIGHT - 650;
        if (winner == 'X')
        {
            SDL_RenderCopy(renderer, TextureManager::getX_wins(), NULL, &rec);
        }
        else if (winner == 'O')
        {
            SDL_RenderCopy(renderer, TextureManager::getO_wins(), NULL, &rec);
        }
        else
        {
            SDL_RenderCopy(renderer, TextureManager::getTie(), NULL, &rec);
        }
        SDL_RenderPresent(renderer);
    }
    // std::cout << std::endl;
    // drawBoard();
    // std::cout << std::endl;
    // if (finished)
    // {
    //     running = false;
    // }
}

int Game::evaluate()
{
    for (int i = 0; i < sizeBoard; ++i)
    {
        for (int j = 1; j < sizeBoard; ++j)
        {
            if (board[i][j] != board[i][j - 1] || board[i][j] == '_' || board[i][j - 1] == '_')
            {
                break;
            }
            if (j == sizeBoard - 1)
            {
                if (board[i][j] == 'X')
                    return -1;
                else if (board[i][j] == 'O')
                    return 1;
            }
        }
    }

    for (int i = 0; i < sizeBoard; ++i)
    {
        for (int j = 1; j < sizeBoard; ++j)
        {
            if (board[j][i] != board[j - 1][i] || board[j][i] == '_' || board[j - 1][i] == '_')
            {
                break;
            }
            if (j == sizeBoard - 1)
            {
                if (board[j][i] == 'X')
                    return -1;
                else if (board[j][i] == 'O')
                    return 1;
            }
        }
    }

    bool diagonal = true;
    int countPlayer = 0;
    int countAI = 0;
    for (int i = 0; i < sizeBoard; ++i)
    {
        if (diagonal == false)
            break;
        for (int j = 0; j < sizeBoard; ++j)
        {
            if (i == j)
            {
                if (board[i][j] == '_')
                {
                    diagonal = false;
                    break;
                }
                else if (board[0][0] == 'X')
                {
                    if (board[i][j] == 'O')
                    {
                        diagonal = false;
                        break;
                    }
                    else if (i == sizeBoard - 1 && j == sizeBoard - 1)
                        return -1;
                }
                else if (board[0][0] == 'O')
                {
                    if (board[i][j] == 'X')
                    {
                        diagonal = false;
                        break;
                    }
                    else if (i == sizeBoard - 1 && j == sizeBoard - 1)
                        return 1;
                }
            }
        }
    }

    diagonal = true;
    countPlayer = 0;
    countAI = 0;
    for (int i = sizeBoard - 1; i >= 0; --i)
    {
        if (diagonal == false)
            break;
        for (int j = 0; j < sizeBoard; ++j)
        {
            if (j == sizeBoard - 1 - i)
            {
                if (board[i][j] == '_')
                {
                    diagonal = false;
                    break;
                }
                else if (board[sizeBoard - 1][0] == 'X')
                {
                    if (board[i][j] == 'O')
                    {
                        diagonal = false;
                        break;
                    }
                    else if (i == 0 && j == sizeBoard - 1)
                        return -1;
                }
                else if (board[sizeBoard - 1][0] == 'O')
                {
                    if (board[i][j] == 'X')
                    {
                        diagonal = false;
                        break;
                    }
                    else if (i == 0 && j == sizeBoard - 1)
                        return 1;
                }
            }
        }
    }
    return 0;
}
int Game::minimax(int depth, int alpha, int beta, bool maximizer)
{
    int result = evaluate();
    bool przerwanie = false;
    if (result != 0 || depth == 0)
    {
        return result;
    }
    if (maximizer)
    {
        for (int i = 0; i < sizeBoard; ++i)
        {
            for (int j = 0; j < sizeBoard; ++j)
            {
                if (board[i][j] == '_')
                {
                    board[i][j] = 'O';
                    alpha = std::max(alpha, minimax(depth - 1, alpha, beta, false));
                    board[i][j] = '_';
                    if (alpha >= beta)
                    {
                        przerwanie = true;
                        break;
                    }
                }
            }
            if (przerwanie == true)
                break;
        }
        return alpha;
    }
    else
    {
        for (int i = 0; i < sizeBoard; ++i)
        {
            for (int j = 0; j < sizeBoard; ++j)
            {
                if (board[i][j] == '_')
                {
                    board[i][j] = 'X';
                    beta = std::min(beta, minimax(depth - 1, alpha, beta, true));
                    board[i][j] = '_';
                    if (alpha >= beta)
                    {
                        przerwanie = true;
                        break;
                    }
                }
            }
            if (przerwanie == true)
            {
                break;
            }
        }
        return beta;
    }
}