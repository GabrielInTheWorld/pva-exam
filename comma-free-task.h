#pragma once

#include <iostream>
#include <string>
#include <tbb/task.h>
#include <tbb/parallel_for.h>
#include <tbb/concurrent_vector.h>

using namespace tbb;
using namespace std;

class CommaFreeTask: public task {
public:
    CommaFreeTask(concurrent_vector<string> wordList, string code, string wordToAppend, int maximumCodeWords, int k);
    task* execute();

private:
    bool checkIfCyclical(string code, string word);
    bool checkIfPeriod(string word);
    bool codeContains(string code, string word);
    bool checkIfAppendingIsAllowed(string code, string word);

    int maximumCodeWords = 0;
    int k = 0;
    string code = "";
    string wordToAppend = "";
    concurrent_vector<string> wordList;
};