#pragma once

#include <iostream>
#include <string>
#include <set>
#include <tbb/mutex.h>
#include <tbb/task.h>
#include <tbb/task_group.h>
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
    CommaFreeTask(con_set wordList, string code, string wordToAppend, const int& maximumCodeWords, const int& k, int solutions, task_group_context* group);
    task* execute();

private:
    bool codeContains(const string& code, const string& word);
    bool checkIfCyclical(const string& code, string word);
    bool checkIfAppendingIsAllowed(const string& code, string word);
    void filterCyclicalWords(con_set& list, string word);

    int solutions;
    const int& maximumCodeWords;
    int k = 0;
    string code = "";
    string wordToAppend = "";
    con_set wordList;
    task_group_context* group;
    mutex locker;
};