#include "../inc/Movie.h"
#include "../inc/ReadData.h"
#include "../inc/Sorting.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <time.h>

int main()
{
    //Movie *data = new Movie[450000];
    std::vector<Movie> data;
    std::ifstream istrm("../Data.csv", std::ios::in);
    std::ofstream ostrm("../out.txt",std::ios::out | std::ios::app);
    // if (istrm.is_open())
    // {
    //     readData(istrm, data);
    // }
    srand(unsigned(time(NULL)));
    for(int i = 0; i < 1000000; ++i){
        data.push_back(Movie("name", rand() % 1000000 + 1));
    }
    auto start = std::chrono::high_resolution_clock::now();
    quickSort(data,0,data.size()-1);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    for(int i = 0; i< data.size(); ++i){
        ostrm << data[i].getName() << " -----> " << data[i].getRating() << std::endl;
    }
    std::cout << "Elements sorted: " << data.size() << std::endl;
    std::cout << "Sorting time: " << duration.count() << " miliseconds" << std::endl;
    //delete[] data;
    //remove("../out.txt");
    return 0;
}