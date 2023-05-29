#include "../inc/Sorting.h"
#include "../inc/Graphics.h"
#include "../inc/Movie.h"
#include <SDL2/SDL.h>
#include <algorithm>
#include <cmath>
#include <future>
#include <random>
#include <thread>
#include <time.h>
#include <vector>

void swap(Movie *a, Movie *b)
{
    Movie tmp = *a;
    *a = *b;
    *b = tmp;
}

void quickSort(std::vector<Movie> &arr, int low, int high, SDL_Renderer *renderer)
{
    if (low < high)
    {
        int pivot = arr[high].getRating();
        int i = low - 1;
        int j = high + 1;
        while (1)
        {
            while (pivot > arr[++i].getRating())
                ;
            while (pivot < arr[--j].getRating())
                ;
            if (i <= j)
            {
                swap(&arr[i], &arr[j]);
                if (renderer != nullptr)
                    drawState(arr, renderer, i, j);
            }
            else
                break;
            if (renderer != nullptr)
                drawState(arr, renderer, i, j);
        }
        if (j > low)
            quickSort(arr, low, j, renderer);
        if (j < high)
            quickSort(arr, i, high, renderer);
    }
}

void merge(std::vector<Movie> &arr, int low, int mid, int high, SDL_Renderer *renderer)
{
    int i, j, k;
    int sizeLeft = mid - low + 1;
    int sizeRight = high - mid;
    // temporary array
    Movie *leftArr = new Movie[sizeLeft];
    Movie *rightArr = new Movie[sizeRight];
    for (int i = 0; i < sizeLeft; ++i)
    {
        leftArr[i] = arr[low + i];
    }
    for (int j = 0; j < sizeRight; ++j)
    {
        rightArr[j] = arr[mid + j + 1];
    }
    i = 0;
    j = 0;
    k = low;
    while (i < sizeLeft && j < sizeRight)
    {
        if (leftArr[i].getRating() <= rightArr[j].getRating())
        {
            arr[k] = leftArr[i];
            if (renderer != nullptr)
                drawState(arr, renderer, k, i + low);
            i++;
        }
        else
        {
            arr[k] = rightArr[j];
            if (renderer != nullptr)
                drawState(arr, renderer, k, j + low);
            j++;
        }

        k++;
    }
    while (i < sizeLeft)
    {
        arr[k] = leftArr[i];
        if (renderer != nullptr)
            drawState(arr, renderer, k, i + low);
        i++;
        k++;
    }

    while (j < sizeRight)
    {
        arr[k] = rightArr[j];
        if (renderer != nullptr)
            drawState(arr, renderer, k, j + low);
        j++;
        k++;
    }
    delete[] leftArr;
    delete[] rightArr;
}

void mergeSort(std::vector<Movie> &arr, int low, int high, SDL_Renderer *renderer)
{
    if (low < high)
    {
        int mid = low + (high - low) / 2;
        mergeSort(arr, low, mid, renderer);
        mergeSort(arr, mid + 1, high, renderer);
        merge(arr, low, mid, high, renderer);
    }
}

void insertionSort(std::vector<Movie> &arr, int low, int high, SDL_Renderer *renderer)
{
    // Get the left and the right index of the subarray
    // to be sorted
    int left = low;
    int right = high;
    std::string title;
    int key = -1;

    for (int i = left; i <= right; i++)
    {
        key = arr[i].getRating();
        title = arr[i].getTitle();
        int j = i;

        /* Move elements of arr[0..i-1], that are
                greater than key, to one position ahead
                of their current position */
        while (j > left && arr[j - 1].getRating() > key)
        {
            arr[j] = arr[j - 1];
            if (renderer != nullptr)
                drawState(arr, renderer, j, j - 1);
            j--;
        }
        arr[j].setRating(key);
        arr[j].setTitle(title);
    }

    return;
}

void heapify(std::vector<Movie> &arr, int low, int high, int i, SDL_Renderer *renderer)
{
    int idx = low + i - 1;
    Movie tmp = arr[low + i - 1];
    int child = -1;
    while (i <= high / 2)
    {
        child = 2 * i;
        if (child < high && arr[low + child - 1].getRating() < arr[low + child].getRating())
            child++;
        if (tmp.getRating() >= arr[low + child - 1].getRating())
            break;
        arr[low + i - 1] = arr[low + child - 1];
        if (renderer != nullptr)
            drawState(arr, renderer, low + i - 1, low + child - 1);
        i = child;
    }
    arr[low + i - 1] = tmp;
    if (renderer != nullptr)
        drawState(arr, renderer, low + i - 1, idx);
}

// Main function to do heap sort
void heapSort(std::vector<Movie> &arr, int low, int high, int size, SDL_Renderer *renderer)
{
    size = high - low;
    // Build heap (rearrange array)
    for (int i = size / 2; i >= 1; i--)
        heapify(arr, low, size, i, renderer);

    // One by one extract an element
    // from heap
    for (int i = size; i >= 1; i--)
    {

        // Move current root to end
        swap(&arr[low], &arr[low + i]);
        if (renderer != nullptr)
            drawState(arr, renderer, low, low + i);

        // call max heapify on the reduced heap
        heapify(arr, low, i, 1, renderer);
    }
}

void introSort(std::vector<Movie> &arr, int low, int high, SDL_Renderer *renderer)
{
    int maxDepth = 2 * log(high - low);
    introSortBody(arr, low, high, maxDepth, renderer);
}

// int partition(std::vector<Movie> &arr, int low, int high)
// {
//     int pivot = arr[high].getRating();
//     int i = low - 1;
//     for (int j = low; j <= high - 1; ++j)
//     {
//         if (arr[j].getRating() <= pivot)
//         {
//             ++i;
//             swap(&arr[i], &arr[j]);
//         }
//     }
//     swap(&arr[i + 1], &arr[high]);
//     return (i + 1);
// }

int findPivot(std::vector<Movie> &arr, int low, int mid, int high)
{
    std::vector<Movie> tmp;
    tmp.push_back(arr[low]);
    tmp.push_back(arr[mid]);
    tmp.push_back(arr[high]);
    insertionSort(tmp, 0, tmp.size() - 1, nullptr);
    if (tmp[1].getRating() == arr[low].getRating())
        return low;
    if (tmp[1].getRating() == arr[mid].getRating())
        return mid;
    if (tmp[1].getRating() == arr[high].getRating())
        return high;
    return high;
}

void introSortBody(std::vector<Movie> &arr, int low, int high, int maxDepth, SDL_Renderer *renderer)
{
    int size = high - low;
    if (size > 20 && high > low)
    {
        if (maxDepth == 0)
        {
            heapSort(arr, low, high, size, renderer);
            return;
        }
        int pivot = findPivot(arr, low, low + ((high - low) / 2) + 1, high);
        swap(&arr[pivot], &arr[high]);
        if (renderer != nullptr)
            drawState(arr, renderer, pivot, high);
        // int p = partition(arr, low, high);
        // introSortBody(arr, low, p, maxDepth - 1, renderer);
        // introSortBody(arr, p + 1, high, maxDepth - 1, renderer);
        int pivotValue = arr[high].getRating();
        int i = low - 1;
        int j = high + 1;
        while (1)
        {
            while (pivotValue > arr[++i].getRating())
                ;
            while (pivotValue < arr[--j].getRating())
                ;
            if (i <= j)
            {
                swap(&arr[i], &arr[j]);
            }
            else
                break;
            if (renderer != nullptr)
                drawState(arr, renderer, i, j);
        }
        if (j > low)
            introSortBody(arr, low, j, maxDepth - 1, renderer);
        if (j < high)
            introSortBody(arr, i, high, maxDepth - 1, renderer);
    }
    else
    {
        insertionSort(arr, low, high, renderer);
    }
}