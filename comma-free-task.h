#pragma once

#include <iostream>
#include <string>
#include <set>
#include <tbb/task.h>
#include <tbb/parallel_for.h>
#include <tbb/concurrent_vector.h>

using namespace tbb;
using namespace std;

class CommaFreeTask: public task {
public:
    CommaFreeTask(set<string> wordList, string code, string wordToAppend, int maximumCodeWords, int k, int solutions, bool* isFinished);
    task* execute();

private:
    bool checkIfCyclical(string code, string word);
    bool checkIfPeriod(string word);
    bool codeContains(string code, string word);
    bool checkIfAppendingIsAllowed(string code, string word);
    set<string> filterCyclicalWords(set<string> list, string word);

    int solutions;
    int maximumCodeWords = 0;
    int k = 0;
    string code = "";
    string wordToAppend = "";
    bool* isFinished;
    set<string> wordList;
};