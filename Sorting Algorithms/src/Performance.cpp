#include "../inc/Performance.h"
#include "../inc/ReadData.h"
#include <chrono>
#include <fstream>
#include <iostream>
#include <time.h>

Error performanceTest()
{
    std::vector<Movie> data;
    std::vector<Movie> dataUtil;
    std::ifstream istrm("../Data.csv", std::ios::in);
    std::ofstream ostrm("../out.txt", std::ios::out | std::ios::app);
      srand(unsigned(time(NULL)));
    // for (int i = 0; i < 1000000; ++i)
    // {
    //     data.push_back(Movie("name", rand() % 1000 + 1));
    // }
    if (istrm.is_open())
    {
        if (!readData(istrm, data))
            return READ;
    }
    else
        return FILE_NOT_OPENED;
    dataUtil = data;
    auto start = std::chrono::high_resolution_clock::now();
    quickSort(dataUtil, 0, dataUtil.size() - 1, nullptr);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    // for (int i = 0; i < data.size(); ++i)
    // {
    //     ostrm << dataUtil[i].getTitle() << " -----> " << dataUtil[i].getRating() << std::endl;
    // }
    std::cout << "Quicksort algorithm" << std::endl;
    std::cout << "Elements sorted: " << data.size() << std::endl;
    std::cout << "Sorting time: " << duration.count() << " miliseconds" << std::endl;
    dataUtil = data;
    start = std::chrono::high_resolution_clock::now();
    mergeSort(data, 0, data.size() - 1, nullptr);
    stop = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    // for (int i = 0; i < data.size(); ++i)
    // {
    //     ostrm << data[i].getTitle() << " -----> " << data[i].getRating() << std::endl;
    // }
    std::cout << "Mergesort algorithm" << std::endl;
    std::cout << "Elements sorted: " << dataUtil.size() << std::endl;
    std::cout << "Sorting time: " << duration.count() << " miliseconds" << std::endl;
    dataUtil = data;
    start = std::chrono::high_resolution_clock::now();
    introSort(data, 0, data.size() - 1, nullptr);
    stop = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

    std::cout << "Introsort algorithm" << std::endl;
    std::cout << "Elements sorted: " << dataUtil.size() << std::endl;
    std::cout << "Sorting time: " << duration.count() << " miliseconds" << std::endl;
    istrm.close();
    ostrm.close();
    remove("../out.txt");
    return NONE;
}