#include <iostream>
#include <string>
#include <set>
#include <iomanip>
#include <sstream>
#include "movie.h"
#include "product.h"
#include "util.h"


Movie::Movie(const std::string category_, const std::string name_, double price_, int qty_, std::string genre, std::string rating) : 
    Product(category_, name_, price_, qty_)
{
    genre_ = genre;
    rating_ = rating;
    keys_ = parseStringToWords(name_);
    keys_.insert(genre_);
}

Movie::~Movie() {

}

std::string Movie::getGenre() {
    return genre_;
}

std::string Movie::getRating() {
    return rating_;
}

std::set<std::string> Movie::keywords() const {
    return keys_;
}

std::string Movie::displayString() const {
    std::string s;
    std::stringstream ss;
    ss << price_;
    ss >> s;
    std::string output = name_ + "\n" + "Genre: " + genre_ + " Rating: " + rating_ + "\n" + s + " " + std::to_string(qty_) + " left.";
    return output;
}

void Movie::dump(std::ostream& os) const {
    os << category_ << std::endl;
    os << name_ << std::endl;
    os << price_ << std::endl;
    os << qty_ << std::endl;
    os << genre_ << std::endl;
    os << rating_ << std::endl;
}