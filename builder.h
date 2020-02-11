#pragma once

#include <iostream>
#include <string>
#include <set>
#include <tbb/task.h>
#include <tbb/parallel_invoke.h>
#include <tbb/concurrent_vector.h>
#include <tbb/concurrent_queue.h>
#include <tbb/concurrent_unordered_set.h>

#include "comma-free-task.h"

using namespace tbb;
using namespace std;

typedef concurrent_unordered_set<string> con_set;

class Builder {
public:
    ~Builder();
    con_set buildPeriodicFreeUnorderedSet(concurrent_vector<string>* wordList, const int& k);
    concurrent_vector<bool> buildPeriodicFreeVector(concurrent_vector<string>* wordList, const int& k);

private:
    //con_set insertWordsEvenK(const concurrent_vector<string>& wordList);
    //con_set insertWordsOddK(const concurrent_vector<string>& wordList);
    //bool checkIfPeriodOddK(const string& word);
    //bool checkIfPeriodEvenK(const string& word);
    bool checkIfPeriod(const string& word);

    int k = 0;
    concurrent_vector<string> resultList;
    task_group_context* context;
};