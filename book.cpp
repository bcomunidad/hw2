#include <iostream>
#include <string>
#include <set>
#include <iomanip>
#include <sstream>
#include "book.h"
#include "product.h"
#include "util.h"

using namespace std;

Book::Book(std::string ISBN, std::string author, const std::string category_, std::string name_, double price_, int qty_) :
    Product(category_, name_, price_, qty_)
{
    // fill set with keywords (ISBN, author name, product name)
    ISBN_ = ISBN;
    author_ = author;
    std::string temp = name_ + " ";
    temp.append(author_);
    keys_ = parseStringToWords(temp);
    keys_.insert(ISBN_);
}

Book::~Book() {


}

std::string Book::get_ISBN() {
    return ISBN_;
}

std::string Book::get_author() {
    return author_;
}

std::set<std::string> Book::keywords() const {
    return keys_;
}

std::string Book::displayString() const {
    std::string s;
    std::stringstream ss;
    ss << price_;
    ss >> s;
    std::string output = name_ + "\n" + "Author: " + author_ + " ISBN: " + ISBN_ + "\n" + s + " " + std::to_string(qty_) + " left.";
    return output;
}

void Book::dump(std::ostream& os) const {
    os << category_ << std::endl;
    os << name_ << std::endl;
    os << price_ << std::endl;
    os << qty_ << std::endl;
    os << ISBN_ << std::endl;
    os << author_ << std::endl;
}

