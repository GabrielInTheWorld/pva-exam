// pva-exam.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cstdlib>
#include <tbb/task_scheduler_init.h>

#include "comma-free-seq.h"
#include "comma-free-scheduler.h"

using namespace std;
using namespace tbb;

int readArgument(int arg, int defaults) {
    if ( arg > 0 && arg <= 10 ) {
        return arg;
    } else {
        return defaults;
    }
}

int main(int argc, char** argv) {
    /*for ( int i = 0; i < argc; ++i ) {
        cout << "argv[" << i << "]: " << atoi(argv[i]) << endl;
    }*/
    int numberCores = task_scheduler_init::automatic;
    int n = 2;
    int k = 6;

    if ( argc < 3 ) {
        cout << "Warning: You have to enter arguments for n k #cores" << endl;
    } else {
        if ( argc == 4 ) {
            cout << "Entered: " << argv[3] << " cores to be used." << endl;
            numberCores = atoi(argv[3]);
        }

        //n = readArgument(atoi(argv[1]), 2);
        //k = readArgument(atoi(argv[2]), 6);
        n = atoi(argv[1]);
        k = atoi(argv[2]);
    }

    //int n = 2;
    //int k = 5;
    //int numberCores = 8;
    CommaFreeScheduler scheduler(n, k);
    scheduler.startCommaFreeParallel(numberCores);
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
