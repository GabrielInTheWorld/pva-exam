#pragma once

#include <iostream>
#include <string>
#include <tbb/concurrent_vector.h>

using namespace tbb;
using namespace std;

class Builder {
public:
    concurrent_vector<string> buildCommaFreeList(concurrent_vector<string>* wordList, int k);

private:
    bool checkIfCyclical(string code, string word);
    bool checkIfPeriod(string word);
    bool codeContains(string code, string word);
    bool listContains(string word);
    bool checkIfAppendingIsAllowed(string code, string word);
    string joinString(concurrent_vector<string> list);

    int k = 0;
    concurrent_vector<string> resultList;
};