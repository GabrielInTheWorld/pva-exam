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
    con_set buildPeriodicFreeUnorderedSet(concurrent_vector<string>* wordList, const int& k);

private:
    bool checkIfPeriod(const string& word);

    int k = 0;
    concurrent_vector<string> resultList;
};