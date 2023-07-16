/*  Malia Fairbanks
    CPSC 1020
    Prof. Dan Wooster
    Project 4
    04/19/2023
    main.cpp
*/
#include "BookRecommender.h"
using namespace std; 


int main (int argc, char *argv[]){


    BookRecommender book_recommend(argv[1]);

    string input;

   do {


        cin >> input;
        if (input == "averages"){
            book_recommend.printAverages();
        }
        else if (input == "recommend"){
            cin >> input;
            book_recommend.printRecommend(input);
        }

   } while (input != "quit");

    return 0;
}