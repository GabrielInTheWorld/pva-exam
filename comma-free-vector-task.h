#pragma once

#include <iostream>
#include <string>
#include <tbb/task.h>
#include <tbb/concurrent_unordered_set.h>
#include <tbb/concurrent_vector.h>
#include <tbb/parallel_for.h>
#include <tbb/parallel_invoke.h>

#include "writer.h"

using namespace std;
using namespace tbb;

typedef concurrent_vector<string> con_vec;

class CommaFreeVectorTask: public task {

public: 
    CommaFreeVectorTask(const con_vec* wordList, const concurrent_vector<bool> wordListIndices, concurrent_vector<unsigned int> indices, unsigned int nextIndex, const int& maximumCodeWords, const int& k, int solutions, task_group_context* group, CommaFreeVectorTask* parent);
    task* execute();
    CommaFreeVectorTask* getParent();
    string getWord();

private:
    bool checkIfCyclical(const string& code, string word);
    bool codeContains(const string& code, const string& word);
    bool checkIfAppendingIsAllowed(const string& code, const string& word);
    void filterCyclicalWords(concurrent_vector<bool> list, const string& word);
    void rotateLeft(string& word, int range);
    string& dereferencingCode();

    CommaFreeVectorTask* parent;
    const con_vec* wordList;
    const concurrent_vector<bool> wordListIndices;
    concurrent_vector<unsigned int> indices;
    unsigned int nextIndex;
    const int& maximumCodeWords;
    const int& k;
    int solutions;
    task_group_context* group;
};

