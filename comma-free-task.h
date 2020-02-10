#pragma once

#include <iostream>
#include <string>
#include <set>
#include <tbb/task.h>
#include <tbb/parallel_invoke.h>
#include <tbb/parallel_for.h>
#include <tbb/concurrent_vector.h>
#include <tbb/concurrent_unordered_set.h>

#include "writer.h"

using namespace tbb;
using namespace std;

typedef concurrent_unordered_set<string> con_set;

class CommaFreeTask: public task {
public:
    CommaFreeTask(con_set wordList, string code, string wordToAppend, int maximumCodeWords, int k, int solutions, bool* isFinished);
    task* execute();

private:
    bool checkIfCyclical(string code, string word);
    bool codeContains(string code, string word);
    bool checkIfAppendingIsAllowed(string code, string word);
    con_set filterCyclicalWords(con_set list, string word);

    int solutions;
    int maximumCodeWords = 0;
    int k = 0;
    string code = "";
    string wordToAppend = "";
    bool* isFinished;
    con_set wordList;
};