#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

class writer {
public:
    static void writeToFile(string stream);
    static void setDictionary(string dictionary);
    static string getDictionary();

private:
    static string dictionary;
};
