#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

#include <tbb/parallel_for.h>
#include <tbb/concurrent_vector.h>

using namespace std;
using namespace tbb;

class writer {
public:
    static void writeToFile(string stream);
    static void setDictionary(string dictionary);
    static string getDictionary();

private:
    static string dictionary;
    static concurrent_vector<string> solutionList;
};
