#include "../inc/ReadData.h"
#include "../inc/Movie.h"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>

bool readData(std::istream &istrm, std::vector<Movie>& data)
{
    std::string tmp = "", line, word, name;
    std::vector<std::string> row;
    try
    {
    std::getline(istrm,tmp,'\n');
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return false;
    }
       while (getline(istrm, line)) {
        
        row.clear();
        name.clear();
        // read an entire row and
        // store it in a string variable 'line'
        
  
        // used for breaking words
        std::stringstream s(line);
  
        // read every column data of a row and
        // store it in a string variable, 'word'
        while (getline(s, word, ',')) {
  
            // add all the column data
            // of a row to a vector
            row.push_back(word);
        }
        tmp = row[row.size()-1];
        if(row.size() < 3 || !isdigit(tmp[tmp.size()-1]))
            continue;
        else{
            for(int it = 1; it < row.size() - 1; ++it){
                name += row[it];
            }
            data.push_back(Movie(name,std::stoi(row[row.size()-1])));
        }

    }
    return true;
}