/*  Malia Fairbanks
    CPSC 1020
    Prof. Dan Wooster
    Project 4
    04/19/2023
    BookRecommender.cpp
*/
#include "BookRecommender.h"
using namespace std;

// Constructor to initialize the data members
BookRecommender::BookRecommender(){};

// function that compares pairs in order of rating
bool comparePairs(const pair<double, string> &a, const pair<double, string> &b)
{
    if (a.first != b.first) {
        // Sort by rating from highest to lowest
        return a.first > b.first;
    }
    else {
        // Sort by book title in alphabetical order in case of ties
        return a.second < b.second;
    }
}

// Constructor to read data from a file and initialize the data members
BookRecommender::BookRecommender(string fileName)
{
    ifstream inFile(fileName);
    string line;
    set<string> bookSet;

    int line_number = 1;

    while (getline(inFile, line)) {
        line = fixString(line);
        if (line_number % 3 == 2) {
            bookSet.insert(line);
        }
        line_number++;
    }

    // convert book set into vector
    for (string book : bookSet) {
        books.push_back(book);
    }
    
    inFile.clear();
    inFile.seekg(0, ios::beg);

    string userName, bookTitle, ratingString;
    double rating;
    while (getline(inFile, userName) && getline(inFile, bookTitle) && (getline(inFile, ratingString))) {
        rating = stod(ratingString);
        userName = fixString(userName);
        bookTitle = fixString(bookTitle);

        if (ratedBooks.find(userName) == ratedBooks.end()) {
            // if we haven't, were setting it to a 0 as default with the length of all the books
            ratedBooks[userName] = vector<double>(books.size(), 0);
            users.push_back(userName);
        }
        // figuring out the book index 
        int bookIndex = find(books.begin(), books.end(), bookTitle) - books.begin();

        // setting rating for the user to the right index
        ratedBooks[userName][bookIndex] = rating;
    }

    // looping through all books
    int bookSize = getBookCount();
    for (int i = 0; i < bookSize; i++) {
        string bookName = books[i];
        int count = 0;  // non-zero ratings count
        double sum = 0; // sum of non-zero ratings

        for (pair<string, vector<double>> element : ratedBooks) {
            double rating = element.second[i];
            // consider only non-zero ratings
            if (rating != 0) {
                sum += rating;
                count++;
            }
        }
        averages[bookName] = sum / count; // calculate average rating per book
    }
};

// Method to print book recommendations for a given user
void BookRecommender::printRecommend(string userName) { 
    if (!ratedBooks.count(userName)) {
        printAverages();
    }

    else {
        BOOK_AVG_LIST similarities;
        // make a loop to go through all the users
        int userSize = getUserCount();
        for(int i = 0; i < userSize; i++){
            if(users[i] != userName){
                similarities.push_back(make_pair(getSimilarity(userName, users[i]), users[i]));
            }
        }

        sort(similarities.rbegin(), similarities.rend()); // sort in descending order of similarity

        BOOK_AVG_LIST averageSimilarities;
        string simUser;

        for (int bookIndex = 0; bookIndex < books.size(); bookIndex++) {
            averageSimilarities.push_back(make_pair(0, books[bookIndex])); // list of pair rating 0 and book name
            int count = 0;
            for (int i = 0; i < 3; i++) {
                // top 3 that didn't rate it 0 --> add rating to the list
                if (ratedBooks[similarities[i].second][bookIndex] != 0) {
                    averageSimilarities[bookIndex].first += ratedBooks[similarities[i].second][bookIndex];
                    count++; //increase count for calculating 
                }
            }
            if (count != 0) {
                averageSimilarities[bookIndex].first /= count;
            }
        }
        sort(averageSimilarities.begin(), averageSimilarities.end(), comparePairs);

        for (int i = 0; i < averageSimilarities.size(); i++) {
            if (averageSimilarities[i].first > 0) {
                // print out the book name and rating
                cout << averageSimilarities[i].second << " " << fixed << setprecision(2)
                     << averageSimilarities[i].first << endl;
            }
        }
    }
};

// Method to print book average ratings
void BookRecommender::printAverages() {

    BOOK_AVG_LIST multiBookRating;
    for (pair<string, double> element : averages) {
        multiBookRating.push_back(make_pair(element.second, element.first));
    }
    // sort the vector of pairs
    sort(multiBookRating.begin(), multiBookRating.end(), comparePairs);
    // print averages
    for (pair<double, string> element : multiBookRating) {
        cout << element.second << " " << fixed << setprecision(2) << element.first << endl;
    }
};

// Method to get the average rating for a specified book
double BookRecommender::getAverage(string bookTitle) {
    return averages[bookTitle];
};

// Method to get the similarity value for two users
double BookRecommender::getSimilarity(string userName1, string userName2) {
    double sim = 0;
    int bookSize = getBookCount();
    for (int i = 0; i < bookSize; i++){
        sim += ratedBooks[userName1][i] * ratedBooks[userName2][i];
    }
    return sim;
};


int BookRecommender::getBookCount() {
    return books.size();
};

int BookRecommender::getUserCount() {
    return users.size();
};

double BookRecommender::getUserBookRating(string userName, string bookTitle) {
    int i = find(books.begin(), books.end(), bookTitle) - books.begin();
    return ratedBooks[userName][i];
};

string BookRecommender::fixString(string line) {
    line.pop_back();
    return line;
}