#pragma once

#include <string>
#include <iostream>

#include <tbb/task_scheduler_init.h>
#include <tbb/task.h>
#include <tbb/tick_count.h>
#include <tbb/parallel_for.h>
#include <tbb/concurrent_vector.h>

#include "comma-free-parallel.h"
#include "comma-free-vector-task.h"
#include "builder.h"
#include "writer.h"

using namespace std;
using namespace tbb;

class CommaFreeScheduler {
public:
    CommaFreeScheduler(int n, int k, int numberCores);
    virtual ~CommaFreeScheduler();
    void startCommaFreeParallel();
    void startCommaFreeVector();

private:
    string initWord();
    tick_count initParallelWork();
    void createWordList(string startWord);
    void writeSolution(string solutionCode, int numberCores, double seconds);

    concurrent_vector<string>* wordList = new concurrent_vector<string>();
    int n = 0;
    int k = 0;
    int numberCores = 0;
    task_group_context* context;
    Builder builder;
};
