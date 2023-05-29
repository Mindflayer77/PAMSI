#pragma once
#include <vector>
#include <SDL2/SDL.h>
#include "Movie.h"

void swap(Movie* a, Movie* b);
void quickSort(std::vector<Movie>& arr, int low, int high, SDL_Renderer* renderer);

void mergeSort(std::vector<Movie>& arr, int low, int high, SDL_Renderer* renderer);
void merge(std::vector<Movie>& arr, int low, int mid, int high, SDL_Renderer* renderer);

void insertionSort(std::vector<Movie>& arr, int low, int high, SDL_Renderer* renderer);

void heapify(std::vector<Movie>& arr, int low, int high, int i, SDL_Renderer* renderer);
void heapSort(std::vector<Movie>& arr, int low, int high, int size, SDL_Renderer* renderer);

int partition(std::vector<Movie>& arr, int low, int high);
int findPivot(std::vector<Movie>& arr, int low, int mid, int high);
void introSortBody(std::vector<Movie>& arr, int low, int high, int maxDepth, SDL_Renderer* renderer);
void introSort(std::vector<Movie>& arr, int low, int high, SDL_Renderer* renderer);