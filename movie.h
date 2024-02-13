#include <iostream>
#include <string>
#include <set>
#include "product.h"

class Movie : public Product {
    public:
        Movie(const std::string category_, const std::string name_, double price_, int qty_, std::string genre, std::string rating);
        ~Movie();
        std::string getGenre();
        std::string getRating();
        std::set<std::string> keywords() const;
        std::string displayString() const;
        void dump(std::ostream& os) const;



    private:
        std::string genre_;
        std::string rating_;
        std::set<std::string> keys_;
};