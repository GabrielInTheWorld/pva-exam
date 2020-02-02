#pragma once
#include <string>
#include <tbb/parallel_for.h>
#include <tbb/task.h>

using namespace std;
using namespace tbb;

class CommaFreeParallel {
public:
    CommaFreeParallel(int n, int k);
    void start();

private:
    bool checkIfCommaFree();
    bool checkIfCyclical(string word);
    bool isCyclical(string word);
    bool checkIfPeriodic();
    string shiftWord(string word);
    void addWord();
    void addToWordList();

    string words = "";
    int n = 0;
    int k = 0;
};

