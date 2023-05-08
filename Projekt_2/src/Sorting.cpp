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

int median(const std::vector<int> &tab)
{
    int sIdx, bIdx;
    int min = tab[0];
    int max = tab[0];
	int med = 0;
    for (int i = 0; i < tab.size(); ++i)
    {
        if (tab[i] < min)
        {
            min = tab[i];
            sIdx = i;
        }
        if (tab[i] > max)
        {
            max = tab[i];
            bIdx = i;
        }
    }
	for(int j = 0; j < tab.size(); ++j){
		if(j != sIdx && j != bIdx){
			med = tab[j];
		}
	}
	return med;
}

int partition(std::vector<Movie> &arr, int low, int high)
{
    //int pivot = median({arr[low].getRating(),arr[(high-low)/2].getRating(), arr[high].getRating()});
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