#include "../inc/Movie.h"
#include "../inc/ReadData.h"
#include "../inc/RenderWindow.h"
#include "../inc/Sorting.h"
#include <SDL2/SDL.h>
#include <chrono>
#include <fstream>
#include <future>
#include <iostream>
#include <random>
#include <thread>
#include <time.h>
#include <vector>

RenderWindow window("Sorting algorithms", 1000, 700);

SDL_Color white = {255, 255, 255};
SDL_Color black = {0, 0, 0};

int level = 0;

bool appRunning = true;
bool mouseDown = false;
bool mousePressed = false;

bool swingPlayed = false;
bool secondSwingPlayed = false;

SDL_Event event;

int state = 0; // 0 = title screen, 1 = game, 2 = end screen

Uint64 currentTick = SDL_GetPerformanceCounter();
Uint64 lastTick = 0;
double deltaTime = 0;

const char *getLevelText(int side)
{
    int tempLevel = (level + 1) * 2 - 1;
    if (side == 1)
    {
        tempLevel++;
    }
    std::string s = std::to_string(tempLevel);
    s = "HOLE: " + s;
    return s.c_str();
}

void update()
{

    lastTick = currentTick;
    currentTick = SDL_GetPerformanceCounter();
    deltaTime = (double)((currentTick - lastTick) * 1000 / (double)SDL_GetPerformanceFrequency());

    mousePressed = false;
    // Get our controls and events
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            appRunning = false;
            break;
        case SDL_MOUSEBUTTONDOWN:
            if (event.button.button == SDL_BUTTON_LEFT)
            {
                mouseDown = true;
                mousePressed = true;
            }
            break;
        case SDL_MOUSEBUTTONUP:
            if (event.button.button == SDL_BUTTON_LEFT)
            {
                mouseDown = false;
            }
            break;
        }
    }
}

void titleScreen()
{
    if (SDL_GetTicks() < 2000)
    {
        if (!swingPlayed)
        {
            swingPlayed = true;
        }
        // Get our controls and events
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                appRunning = false;
                break;
            }
        }

        window.clear();
        window.display();
    }
    else
    {
        if (!secondSwingPlayed)
        {
            secondSwingPlayed = true;
        }
        lastTick = currentTick;
        currentTick = SDL_GetPerformanceCounter();
        deltaTime = (double)((currentTick - lastTick) * 1000 / (double)SDL_GetPerformanceFrequency());

        // Get our controls and events
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                appRunning = false;
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    state = 1;
                }
                break;
            }
        }
        window.clear();
        window.display();
    }
}
void app()
{
    if (state == 0)
    {
        titleScreen();
    }
    else
    {
        update();
    }
}

void visualizationQuickSort(SDL_Renderer *renderer)
{
    std::vector<Movie> data;
    srand(unsigned(time(NULL)));
    for (int i = 0; i < 1000; ++i)
    {
        data.push_back(Movie("name", rand() % 100 + 1));
    }
    quickSort(data, 0, data.size() - 1, renderer);
}

int main()
{


    std::vector<Movie> data;
    std::ifstream istrm("../Data.csv", std::ios::in);
    std::ofstream ostrm("../out.txt", std::ios::out | std::ios::app);
    // if (istrm.is_open())
    // {
    //     readData(istrm, data);
    // }
    srand(unsigned(time(NULL)));
    for (int i = 0; i < 100000; ++i)
    {
        data.push_back(Movie("name", rand() % 1000 + 1));
    }
    while(appRunning){
        app();
    auto start = std::chrono::high_resolution_clock::now();
    // mergeSort(data, 0, data.size() - 1, nullptr);
    // quickSort(data, 0, data.size() - 1, nullptr);
    // insertionSort(data,0,data.size()-1,nullptr);
    // heapSort(data,0,data.size()-1,data.size());
    introSort(data, 0, data.size() - 1, nullptr);

    // std::cout << findPivot(data,0,(data.size()-1)/2,data.size()-1) << std::endl;
    auto stop = std::chrono::high_resolution_clock::now();
    // visualizationQuickSort(renderer);
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    // for (int  i =data.size()/2 - 1; i >= 0; i--)
    //  heapify(data,0,data.size()-1,i);
    for (int i = 0; i < data.size(); ++i)
    {
        ostrm << data[i].getTitle() << " -----> " << data[i].getRating() << std::endl;
    }
    std::cout << "Elements sorted: " << data.size() << std::endl;
    std::cout << "Sorting time: " << duration.count() << " miliseconds" << std::endl;
    }
    remove("../out.txt");
    window.cleanUp();
    istrm.close();
    ostrm.close();
    return 0;
}