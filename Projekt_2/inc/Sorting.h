#pragma once
#include <vector>
#include "Movie.h"

void swap(Movie* a, Movie* b);
int partition(std::vector<Movie>& arr, int low, int high);
void quickSort(std::vector<Movie>& arr, int low, int high);

void mergeSort(std::vector<Movie>& arr, int low, int high);
void divide(std::vector<Movie>& arr, int low, int high);
void merge(std::vector<Movie>& arr, int low, int mid, int high);