#ifndef BOOK_RECOMMENDER_H
#define BOOK_RECOMMENDER_H

#include <iostream> 
#include <iomanip>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <set>
#include <algorithm>



#define BOOK_LIST std::vector<std::string>
#define USER_LIST std::vector<std::string>
#define USER_RATINGS_MAP std::map <std::string, std::vector<double> >
#define BOOK_AVG_MAP std::map<std::string, double >
#define BOOK_AVG_LIST std::vector<std::pair<double, std::string> >

class BookRecommender {
    private:
        BOOK_LIST books;
        USER_RATINGS_MAP ratedBooks;
        BOOK_AVG_MAP averages;
    public:
        USER_LIST users;
        BookRecommender();   
        BookRecommender(std::string fileName); 
        void printRecommend(std::string userName);
        void printAverages();
        double getAverage(std::string bookTitle);
        double getSimilarity(std::string userName1, std::string userName2);
        int getBookCount();
        int getUserCount();
        double getUserBookRating(std::string userName, std:: string bookTitle); 
        std::string fixString(std::string line);
};

#endif