#include "../inc/Sorting.h"
#include "../inc/Movie.h"
#include <algorithm>
#include <random>
#include <time.h>
#include <vector>

void swap(Movie *a, Movie *b)
{
    Movie tmp = *a;
    *a = *b;
    *b = tmp;
}

int partition(std::vector<Movie> &arr, int low, int high)
{
    int pivot = arr[high].getRating();
    int i = low - 1;
    for (int j = low; j < high; ++j)
    {
        if (arr[j].getRating() < pivot)
        {
            ++i;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

void quickSort(std::vector<Movie> &arr, int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void merge(std::vector<Movie> &arr, int low, int mid, int high)
{
    // size of arrays to merge
    int sizeLeft = mid - low + 1;
    int sizeRight = high - mid;

    // temporary arrays
    std::vector<Movie> left;
    std::vector<Movie> right;

    // copying data
    for (int i = 0; i < sizeLeft; ++i)
    {
        left.push_back(arr[low + i]);
    }
    for (int j = 0; j < sizeRight; ++j)
    {
        right.push_back(arr[mid + 1 + j]);
    }

	// merging arrays
    // Initial indexes of first and second subarrays
    int i = 0, j = 0;

    // Initial index of merged subarray array
    int k = low;
    while (i < sizeLeft && j < sizeRight)
    {
        if (left[i].getRating() <= right[j].getRating())
        {
            arr[k] = left[i];
            ++i;
        }
        else
        {
            arr[k] = right[j];
            ++j;
        }
        ++k;
    }

    // Copy remaining elements of left if any
    while (i < sizeLeft)
    {
        arr[k] = left[i];
        ++i;
        ++k;
    }

    /* Copy remaining elements of right if any */
    while (j < sizeRight)
    {
        arr[k] = right[j];
        ++j;
        ++k;
    }
}

void mergeSort(std::vector<Movie> &arr, int low, int high)
{
    if (low < high)
    {
        int mid = low + (high - low) / 2;
        mergeSort(arr, low, mid);
        mergeSort(arr, mid + 1, high);
        merge(arr, low, mid, high);
    }
}