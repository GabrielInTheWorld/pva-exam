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
    //static writer* getInstance();
    static void writeToFile(string stream);
    static void setDictionary(string dictionary);
    static string getDictionary();

private:
    /*writer();
    writer(const writer&);
    ~writer();

    string dictionary;
    static writer* _instance;

    class CGuard {
    public:
        ~CGuard();
    };*/
    static string dictionary;
};
