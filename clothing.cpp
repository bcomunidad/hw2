#include <iostream>
#include <string>
#include <set>
#include <iomanip>
#include <sstream>
#include "clothing.h"
#include "product.h"
#include "util.h"

Clothing::Clothing(const std::string category_, const std::string name_, double price_, int qty_, std::string size, std::string brand) :
    Product(category_, name_, price_, qty_)
{
    size_ = size;
    brand_ = brand;
    std::string temp = name_ + " ";
    temp.append(brand_); 
    keys_ = parseStringToWords(temp);
}

Clothing::~Clothing() {

}

std::string Clothing::getSize() {
    return size_;
}

std::string Clothing::getBrand() {
    return brand_;
}

std::set<std::string> Clothing::keywords() const {
    return keys_;
}

std::string Clothing::displayString() const {
    std::string s;
    std::stringstream ss;
    ss << price_;
    ss >> s;
    std::string output = name_ + "Size: " + size_ + " Brand: " + brand_ + "\n" + s + " " + std::to_string(qty_) + " left.";
    return output;
}

void Clothing::dump(std::ostream& os) const {
    os << category_ << std::endl;
    os << name_ << std::endl;
    os << price_ << std::endl;
    os << qty_ << std::endl;
    os << size_ << std::endl;
    os << brand_ << std::endl;
}