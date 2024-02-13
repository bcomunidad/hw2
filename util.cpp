#include <sstream>
#include <cctype>
#include <algorithm>
#include <string>
#include <iostream>
#include "util.h"
using namespace std;

std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(std::string rawWords)
{
    std::set<std::string> words;
    int len = rawWords.length();
    if(len == 2) {
        bool punc = false;
        for(int i = 0; i < 2; i++) {
            if(int(rawWords[i]) < 65 || int(rawWords[i]) > 122) {     // if string contrains punctuation char
                punc = true;
            }
        }
        if(!punc) {
            words.insert(rawWords);
            return words;
        }
    }
    else if(len > 2){
        int iter = 0;
        for(int i = 0; i < len; i++) {
            if(int(rawWords[i]) >= 65 && int(rawWords[i]) <= 122) {     // if char at idx i is a letter
                iter++;
            }
            else if(iter >= 2) {       // else char is not a letter   
                words.insert(rawWords.substr(i-iter, iter));
                iter = 0;
            }
            if(i+1 == len && iter >= 2) {
                words.insert(rawWords.substr(i+1-iter, iter));
            }

        }
    }
    return words;
}

/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(), 
	    std::find_if(s.begin(), 
			 s.end(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    s.erase(
	    std::find_if(s.rbegin(), 
			 s.rend(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))).base(), 
	    s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}
