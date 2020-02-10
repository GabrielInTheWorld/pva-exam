#pragma once

#include <iostream>
#include <string>
#include <set>
#include <tbb/task.h>
#include <tbb/parallel_invoke.h>
#include <tbb/concurrent_vector.h>
#include <tbb/concurrent_unordered_set.h>

#include "comma-free-task.h"

using namespace tbb;
using namespace std;

typedef concurrent_unordered_set<string> con_set;

class Builder {
public:
    ~Builder();
    concurrent_vector<string> buildCommaFreeList(concurrent_vector<string>* wordList, int k);

private:
    con_set insertWordsEvenK(concurrent_vector<string> wordList);
    con_set insertWordsOddK(concurrent_vector<string> wordList);
    bool checkIfPeriodOddK(string word);
    bool checkIfPeriodEvenK(string word);

    int k = 0;
    concurrent_vector<string> resultList;
    task_group_context* context;
};