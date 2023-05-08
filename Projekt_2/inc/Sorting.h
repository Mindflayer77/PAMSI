#pragma once
#include <vector>
#include "Movie.h"

void swap(Movie* a, Movie* b);
int partition(std::vector<Movie>& arr, int low, int high);
void quickSort(std::vector<Movie>& arr, int low, int high);
int median(const std::vector<int> &tab);