#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <deque>
#include "mydatastore.h"
#include "user.h"
#include "util.h"

using namespace std;

MyDataStore::MyDataStore() {

}

MyDataStore::~MyDataStore() {
    std::map<std::string, User*>::iterator userit = users.begin();
    while(userit != users.end()) {
        delete userit->second;
        ++userit;
    }
    std::set<Product*>::iterator prodit = prods.begin();
    while(prodit != prods.end()) {
        delete *prodit;
        ++prodit;
    }
}

std::map<std::string, User*> MyDataStore::getUsers() {
    return users;
}

std::set<Product*> MyDataStore::getProds() {
    return prods;
}

void MyDataStore::addProduct(Product* P) {
    prods.insert(P);
    std::set<std::string> keywords = P->keywords();

    // depending on keyword, add Product associated with that keyword
    std::set<std::string>::iterator setit = keywords.begin();
    while(setit != keywords.end()) {
        std::map<std::string, std::set<Product*>>::iterator mapit = info.find(*setit);
        if(mapit == info.end()) {            // keyword is not found in Product, thus, need to add empty product list to that keyword    
            std::set<Product*> emptySet;
            info.insert(std::make_pair(*setit, emptySet)); 
        }
        else {                               // keyword is found in map, thus, already associated with a Product
            std::set<Product*> newSet;
            newSet.insert(P);
            info.insert(std::make_pair(*setit, newSet));
        }
        ++setit;
    }
}

void MyDataStore::addUser(User* u) {
    std::map<std::string, User*>::iterator it = users.find(u->getName());
    if(it == users.end()) {     // new user has not been added yet
        users.insert(std::make_pair(u->getName(), u));
        std::deque<Product*> emptyCart;
        cart.insert(std::make_pair(u->getName(), emptyCart));       // new Users don't have anything in their cart
    }
}

std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type) {
    std::vector<Product*> vec;
    std::set<Product*> infocopy;

    if(type == 0 || type == 1) {
        if(type == 0) {     // and (intersection)
            for(unsigned int i = 0; i < terms.size(); i++) {
                infocopy = setIntersection(infocopy, info[terms[i]]);
            }
        }
        else if(type == 1) {    // or (union)
            for(unsigned int i = 0; i < terms.size(); i++) {
                infocopy = setUnion(infocopy, info[terms[i]]);
            }
        }
        std::set<Product*>::iterator setit = infocopy.begin();
        for(setit; setit != infocopy.end(); ++setit) {
            vec.push_back(*setit);
        }
    }
    return vec;
}

void MyDataStore::dump(std::ostream& ofile) {
    ofile << "<products>" << endl;
    std::set<Product*>::iterator it = prods.begin();
    while(it != prods.end()) {
        (*it)->dump(ofile);
        ++it;
    }
    ofile << "</products>" << endl;
    ofile << "<users>" << endl;
    std::map<std::string, User*>::iterator mapit = users.begin();
    while(mapit != users.end()) {
        (*mapit->second).dump(ofile);
        ++mapit;
    }
    ofile << "</users>" << endl;
}

void MyDataStore::addCart(std::string username, int index) {
    std::map<std::string, User*>::iterator mapit = users.find(username);
    if(mapit == users.end()) {       // username not found
        cout << "Invalid Request" << endl;
        return;
    }
    else if(index > prods.size()) {
        cout << "Invalid Request" << endl;
        return;
    }
    std::set<Product*>::iterator setit = prods.begin();
    for(int i = 0; i < index; i++) {        // iterating to product being added to cart
        setit++;        
    }
    std::map<std::string, std::deque<Product*>>::iterator it = cart.begin();
    for(it; it != cart.end(); ++it) {
        if(it->first == username) {     // user found
            it->second.push_back(*setit);
        }
    }
}

void MyDataStore::viewCart(std::string username) {
    std::map<std::string, User*>::iterator mapit = users.find(username);
    if(mapit == users.end()) {       // username not found
        cout << "Invalid username" << endl;
        return;
    }
    std::map<std::string, std::deque<Product*>>::iterator it = cart.begin();
    for(it; it != cart.end(); ++it) {
        if(it->first == username) {     // found user's cart
            std::deque<Product*>::iterator dequeit = it->second.begin();
            for(dequeit; dequeit != it->second.begin(); ++dequeit) {
                cout << (*dequeit)->displayString() << endl;
            }
        }
    }
}

void MyDataStore::buyCart(std::string username) {
    std::map<std::string, User*>::iterator mapit = users.find(username);
    if(mapit == users.end()) {       // username not found
        cout << "Invalid username" << endl;
        return;
    }
    std::map<std::string, std::deque<Product*>>::iterator it1 = cart.begin();
    for(it1; it1 != cart.end(); ++it1) {
        if(it1->first == username) {     // found user's cart
            std::deque<Product*>::iterator it = it1->second.begin();        // going through user's product deque
            for(it; it != it1->second.end(); ++it) {
                if(((*it)->getQty() > 0) && ((mapit->second->getBalance()) - ((*it)->getPrice()) >= 0.00)) {
                    it1->second.pop_front();
                    (*it)->subtractQty(1);
                    mapit->second->deductAmount((*it)->getPrice());
                }
            }
        }
    }
}
