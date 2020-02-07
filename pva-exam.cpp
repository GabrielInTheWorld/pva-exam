// pva-exam.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <vector>
#include <iostream>
#include <string>
#include <tbb/task.h>
#include <tbb/tick_count.h>
#include <tbb/task_scheduler_init.h>

#include "comma-free-seq.h"
#include "comma-free-checker.h"
#include "comma-free-parallel.h"
#include "comma-free-scheduler.h"

using namespace std;
using namespace tbb;

int main() {

    //task_scheduler_init my_task(4);
    int threadAmount = 4;
    int n = 3;
    int k = 4;
    CommaFreeScheduler scheduler(n, k, threadAmount);
    scheduler.startCommaFreeParallel();

    //string words = "";
    //string startWord = "";
    //for ( int i = 0; i < k; ++i ) {
    //    startWord.append("a");
    //}
    //cout << "Start!" << endl;
    //tick_count t0 = tick_count::now();
    //task_list list;

    //string tmpA = startWord;
    //concurrent_vector<string>* wordList = new concurrent_vector<string>();
    ///*CommaFreeChecker* rootA = new (task::allocate_root())CommaFreeChecker(wordList, tmpA, 0, 0, n, k);
    //list.push_back(*rootA);*/
    ////tbb::task::spawn_root_and_wait(*root);
    //for ( int i = n - 1; i >= 0; --i ) {
    //    string tmp = startWord;
    //    CommaFreeChecker* root = new (task::allocate_root())CommaFreeChecker(wordList, tmp, 0, i, n, k);
    //    //tbb::task::spawn_root_and_wait(*root);
    //    list.push_back(*root);
    //}
    //task::spawn_root_and_wait(list);
    //tick_count t1 = tick_count::now();
    //cout << "Finished!" << endl;
    //cout << "word: " << words.length() << endl;
    ////cout << "wordList: " << *wordList << endl;
    //int length = 0;
    ////for ( int i = 0; i < words.length() - k; i += k ) {
    ////    //cout << words.substr(i, k) << endl;
    ////    ++length;
    ////}
    //cout << "wordList: " << endl;
    //auto tmpList = *wordList;
    //for ( int i = 0; i < tmpList.size(); ++i ) {
    //    cout << tmpList[i] << endl;
    //    //++length;
    //}
    //cout << endl;
    //cout << "Time needed: " << (t1 - t0).seconds() << endl;
    //cout << "Commafree words: " << wordList->size() << endl;

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
