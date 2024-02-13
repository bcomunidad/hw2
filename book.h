#include <iostream>
#include <string>
#include <set>
#include "product.h"

class Book : public Product {
    public:
        Book(std::string ISBN, std::string author, const std::string category_, std::string name_, double price_, int qty_);
        ~Book();
        std::string get_ISBN();
        std::string get_author();
        std::set<std::string> keywords() const;
        std::string displayString() const;
        void dump(std::ostream& os) const;

    private:
        std::string ISBN_;
        std::string author_;
        std::set<std::string> keys_;
};