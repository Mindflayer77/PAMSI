#pragma once
#include <string>
#include <cstring>

class Movie{
    std::string title;
    int rating;
public:
    Movie(): title(""), rating(-1){}
    Movie(const std::string& newName, const int& newRating): title(newName), rating(newRating) {}
    const std::string& getTitle() const {return title;}
    int getRating() const {return rating;}
    ~Movie(){}
    Movie& operator = (const Movie& assignMovie){
        this->title = assignMovie.getTitle();
        this->rating = assignMovie.getRating();
        return *this;
    }
    void setRating(const int& newRating){
        rating = newRating;
    }
    void setTitle(const std::string& newTitle){
        title = newTitle;
    }
};


