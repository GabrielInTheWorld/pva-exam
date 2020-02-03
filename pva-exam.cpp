// pva-exam.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <vector>
#include <iostream>
#include <string>
#include <tbb/task.h>

#include "comma-free-seq.h"
#include "comma-free-checker.h"
#include "comma-free-parallel.h"

using namespace std;
using namespace tbb;

int main() {
    int n = 4;
    int k = 4;

    string words = "";
    string startWord = "";
    for ( int i = 0; i < k; ++i ) {
        startWord.append("a");
    }
    string tmpA = startWord;
    CommaFreeChecker* rootA = new (task::allocate_root())CommaFreeChecker(&words, tmpA, 0, 0, n, k);
    tbb::task::spawn_root_and_wait(*rootA);
    for ( int i = n - 1; i > 0; --i ) {
        string tmp = startWord;
        CommaFreeChecker* root = new (task::allocate_root())CommaFreeChecker(&words, tmp, 0, i, n, k);
        tbb::task::spawn_root_and_wait(*root);
    }
    cout << "Finished!" << endl;
    for ( int i = 0; i < words.length() - k; i += k ) {
        cout << words.substr(i, k) << endl;
    }

    //CommaFreeSeq cfs;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
