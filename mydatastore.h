#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <deque>
#include "datastore.h"

class MyDataStore : public DataStore {
    public:
        MyDataStore();
        ~MyDataStore();

    /**
     *  Adds a product to the data store
     */
        void addProduct(Product* p);

    /**
     *  Adds a user to the data store
     */
        void addUser(User* u);

    /**
     *  Performs a search of products whose keywords match the given "terms"
     *  type 0 = AND search (intersection of results for each term) while
     *  type 1 = OR search (union of results for each term)
     */
        std::vector<Product*> search(std::vector<std::string>& terms, int type);

    /**
     *  Reproduce the database file from the current Products and User values
     */
        void dump(std::ostream& ofile);

        std::map<std::string, User*> getUsers();

        std::set<Product*> getProds();

        void addCart(std::string username, int index);

        void viewCart(std::string username);

        void buyCart(std::string);

    private:
        std::set<Product*> prods;   // stores all products
        std::map<std::string, User*> users;     // matches username to user
        std::map<std::string, std::set<Product*>> info;     // matches keywords to Products
        std::map<std::string, std::deque<Product*>> cart;   // matches username to Products in cart
};  