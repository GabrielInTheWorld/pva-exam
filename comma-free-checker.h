#pragma once
#include <iostream>
#include <vector>
#include <tbb/task.h>
#include <tbb/parallel_for.h>

#include <string>

using namespace tbb;
using namespace std;

class CommaFreeChecker: public task {
public:
    CommaFreeChecker(string* words, string word, int index, int raise, int n, int k);
    virtual ~CommaFreeChecker();

    task* execute();
private:
    bool checkIfPeriodic(string word);
    bool checkIfCyclical(string word);
    void checkContaining(string word);
    bool contains(string word);
    string shiftWord(string word);

    string* words = 0;
    string word;
    int index;
    int raise;
    int n;
    int k;
};
