#pragma once
#include <iostream>
#include <string>
#include <tbb/parallel_for.h>
#include <tbb/concurrent_vector.h>
#include <tbb/task.h>

using namespace std;
using namespace tbb;

class CommaFreeParallel : public task {
public:
    CommaFreeParallel(concurrent_vector<string>* wordList, string word, int index, int raise, int n, int k);
    //void start();
    task* execute();

private:
    bool checkIfCommaFree();
    bool checkIfCyclical(string word);
    bool contains(string word);
    bool checkIfPeriodic();
    //string shiftWord(string word);
    void addWord();
    //void addToWordList();

    string word = "";
    int n = 0;
    int k = 0;
    int index = 0; 
    int raise = 0;
    concurrent_vector<string>* wordList;
};

