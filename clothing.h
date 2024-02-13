#include <iostream>
#include <string>
#include <set>
#include "product.h"

class Clothing : public Product {
    public:
        Clothing(const std::string category_, const std::string name_, double price_, int qty_, std::string size, std::string brand);
        ~Clothing();
        std::string getSize();
        std::string getBrand();
        std::set<std::string> keywords() const;
        std::string displayString() const;
        void dump(std::ostream& os) const;


    private:
        std::string size_;
        std::string brand_;
        std::set<std::string> keys_;
};