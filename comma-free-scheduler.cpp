#include "comma-free-scheduler.h"

CommaFreeScheduler::CommaFreeScheduler(int n, int k) {
    this->n = n;
    this->k = k;
}

CommaFreeScheduler::CommaFreeScheduler(int n, int k, int threadAmount) {
    this->n = n;
    this->k = k;
    task_scheduler_init my_task(threadAmount);
}

CommaFreeScheduler::~CommaFreeScheduler() {
    delete wordList;
}

void CommaFreeScheduler::startCommaFreeParallel() {
    string startWord = initWord();

    task_list list;
    for ( int i = 0; i < n; ++i ) {
        string tmp = startWord;
        CommaFreeParallel* root = new (task::allocate_root())CommaFreeParallel(wordList, tmp, 0, i, n, k);
        list.push_back(*root);
    }

    evaluate(list);
    cout << "wordList.size(): " << wordList->size() << endl;
    Builder builder;
    auto resultList = builder.buildCommaFreeList(wordList, k);
    cout << "ResultList.length: " << resultList.size() << endl;
}

void CommaFreeScheduler::startCommaFreeChecker() {
    /*string startWord = "";
    for ( int i = 0; i < k; ++i ) {
        startWord.append("a");
    }*/
    string startWord = initWord();
    cout << "Start!" << endl;
    
    
    task_list list;

    //concurrent_vector<string>* wordList = new concurrent_vector<string>();
    for ( int i = n - 1; i >= 0; --i ) {
        string tmp = startWord;
        CommaFreeChecker* root = new (task::allocate_root())CommaFreeChecker(wordList, tmp, 0, i, n, k);
        list.push_back(*root);
    }

    evaluate(list);
    //tick_count t0 = tick_count::now();
    //task::spawn_root_and_wait(list);
    //tick_count t1 = tick_count::now();

    //cout << "Finished!" << endl;
    //cout << "wordList: " << endl;
    //auto tmpList = *wordList;
    //for ( int i = 0; i < tmpList.size(); ++i ) {
    //    cout << tmpList[i] << endl;
    //}
    //cout << endl;
    //cout << "Time needed: " << (t1 - t0).seconds() << endl;
    //cout << "Commafree words: " << wordList->size() << endl;
}

string CommaFreeScheduler::initWord() {
    string startWord = "";
    for ( int i = 0; i < k; ++i ) {
        startWord.append("a");
    }
    return startWord;
}

void CommaFreeScheduler::evaluate(task_list& list) {
    tick_count t0 = tick_count::now();
    task::spawn_root_and_wait(list);
    tick_count t1 = tick_count::now();

    cout << "Finished!" << endl;
    cout << "wordList: " << endl;
    auto tmpList = *wordList;
    for ( int i = 0; i < tmpList.size(); ++i ) {
        cout << i << ": " << tmpList[i] << endl;
    }
    cout << endl;
    cout << "Time needed: " << (t1 - t0).seconds() << endl;
    cout << "Commafree words: " << wordList->size() << endl;
}
