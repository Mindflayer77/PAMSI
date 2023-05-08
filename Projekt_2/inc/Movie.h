#pragma once
#include <string>

class Movie{
    std::string name;
    int rating;
public:
    Movie(): name(""), rating(-1){}
    Movie(const std::string& newName, const int& newRating): name(newName), rating(newRating) {}
    const std::string& getName() const {return name;}
    int getRating() const {return rating;}
    ~Movie(){}
    // Movie& operator = (const Movie& assign){
    //     this->name = assign.getName();
    //     this->rating = assign.getRating();
    // }
    // Movie& operator * (){
    //     return *this;
    // }
};


