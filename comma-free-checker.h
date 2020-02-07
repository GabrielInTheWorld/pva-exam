#pragma once
#include <iostream>
#include <vector>
#include <iterator>

#include <tbb/task.h>
#include <tbb/parallel_for.h>
#include <tbb/concurrent_vector.h>
#include <tbb/mutex.h>

#include <string>

using namespace tbb;
using namespace std;

class CommaFreeChecker: public task {
public:
    CommaFreeChecker(concurrent_vector<string>* wordList, string word, int index, int raise, int n, int k);
    //CommaFreeChecker(string* words, vector<string>& wordList, string word, int index, int raise, int n, int k);
    virtual ~CommaFreeChecker();

    virtual task* execute();
private:
    bool checkIfPeriodic(string word);
    bool checkIfCyclical(string word);
    void checkContaining(string word);
    bool contains(string word);
    string joinString(concurrent_vector<string> list);
    string join(concurrent_vector<string>* list);
    string shiftWord(string word);

    string* words;
    //string words = "";
    string code = "";
    concurrent_vector<string>* tmpList;
    concurrent_vector<string>* holdList;
    //vector<string>& wordList;
    string word;
    int index;
    int tmpIndex;
    int raise;
    int n;
    int k;
};
