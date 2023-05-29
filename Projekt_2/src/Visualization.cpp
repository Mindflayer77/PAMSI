#include "../inc/Visualization.h"
#include "../inc/Graphics.h"
#include "../inc/Movie.h"
#include "../inc/Sorting.h"
#include <random>
#include <time.h>

void visualizationQuickSort(SDL_Renderer *renderer)
{
    std::vector<Movie> data;
    srand(unsigned(time(NULL)));
    for (int i = 0; i < 130; ++i)
    {
        data.push_back(Movie("name", rand() % 100 + 1));
    }
    quickSort(data, 0, data.size() - 1, renderer);
    complete = true;
    drawState(data, renderer,-1,-1);
    complete = false;
}

void visualizationMergeSort(SDL_Renderer *renderer)
{
    std::vector<Movie> data;
    srand(unsigned(time(NULL)));
    for (int i = 0; i < 130; ++i)
    {
        data.push_back(Movie("name", rand() % 100 + 1));
    }
    mergeSort(data, 0, data.size() - 1, renderer);
    complete = true;
    drawState(data, renderer,-1,-1);
    complete = false;
}

void visualizationIntroSort(SDL_Renderer *renderer)
{
    std::vector<Movie> data;
    srand(unsigned(time(NULL)));
    for (int i = 0; i < 130; ++i)
    {
        data.push_back(Movie("name", rand() % 100 + 1));
    }
    introSort(data, 0, data.size() - 1, renderer);
    complete = true;
    drawState(data, renderer,-1,-1);
    complete = false;
}
