#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

class CommaFreeSeq {
public:
    CommaFreeSeq();

private:
    vector<string> wordList;
    string commaFreeCode = "";

    bool codeContains(string code, string word);
    bool checkIfAppendingIsAllowed(string code, string word);
    bool checkIfPeriodic(string word);
    bool checkIfCyclical(string code, string word);
    bool checkIfCommaFree(string word);

    void initWordList();
    void start();

    int k = 4;
};

