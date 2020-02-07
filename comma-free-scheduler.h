#pragma once

#include <string>
#include <iostream>

#include <tbb/task_scheduler_init.h>
#include <tbb/task.h>
#include <tbb/tick_count.h>
#include <tbb/parallel_for.h>
#include <tbb/concurrent_vector.h>

#include "comma-free-checker.h"
#include "comma-free-parallel.h"
#include "builder.h"

using namespace std;
using namespace tbb;

class CommaFreeScheduler {
public:
    CommaFreeScheduler(int n, int k);
    CommaFreeScheduler(int n, int k, int threadAmount);
    virtual ~CommaFreeScheduler();
    void startCommaFreeParallel();
    void startCommaFreeChecker();

private:
    string initWord();
    void evaluate(task_list& list);

    concurrent_vector<string>* wordList = new concurrent_vector<string>();
    int n = 0;
    int k = 0;
};
