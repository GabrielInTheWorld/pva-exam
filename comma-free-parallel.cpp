#include "comma-free-parallel.h"

CommaFreeParallel::CommaFreeParallel(concurrent_vector<string>* wordList, string word, int index, int raise, int n, int k) {
    this->n = n;
    this->k = k;
    this->wordList = wordList;
    this->index = index;
    this->raise = raise;
    this->word = word;
}

//void CommaFreeParallel::start() {
//    for ( int i = 0; i < pow(n, k); ++i ) {
//
//    }
//
//}

task* CommaFreeParallel::execute() {
    word[index] += raise;
    cout << "word: " << word << endl;
    //wordList->grow_by(2);
    wordList->push_back(word);

    if ( index == k - 1 ) {
        return NULL;
    }

    task_list list;
    int count = 0;
    auto callback = [&](int i) {
        list.push_back(*new (allocate_child())CommaFreeParallel(wordList, word, index + 1, i, n, k));
        ++count;
    };
    parallel_for(1, n, callback);

    if ( count > 0 ) {
        set_ref_count(count + 1);
        spawn_and_wait_for_all(list);
    }

    return NULL;
}

bool CommaFreeParallel::checkIfCommaFree() {
    return false;
}

bool CommaFreeParallel::checkIfCyclical(string word) {
    bool cyclical = false;
    for ( int i = 0; i < k; ++i ) {
        //word = shiftWord(word);
        if ( contains(word) ) {
            cyclical = true;
            break;
        }
    }
    return cyclical;
}

bool CommaFreeParallel::contains(string word) {
    //return words.find(word) != string::npos;
    return false;
}

bool CommaFreeParallel::checkIfPeriodic() {
    return false;
}

//string CommaFreeParallel::shiftWord(string word) {
//    int length = k - 1;
//    word[length] = word[0];
//    for ( int i = 0; i < length; ++i ) {
//        word[i] = word[i + 1];
//    }
//    return word;
//}

void CommaFreeParallel::addWord() {
}

//void CommaFreeParallel::addToWordList() {
//}
