#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class CommaFreeSeq {
public:
    CommaFreeSeq();

private:
    vector<string> wordList;

    bool arePermutation(string word, string comparison);
    bool checkIfPermutation(string word);
    bool checkIfPeriodic(string word);
    bool checkIfCommaFree(string word);

    void initWordList();
    void start();
};

