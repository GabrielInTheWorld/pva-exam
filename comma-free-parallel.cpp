#include "comma-free-parallel.h"

CommaFreeParallel::CommaFreeParallel(concurrent_vector<string>* wordList, string word, int index, int raise, int n, int k) {
    this->n = n;
    this->k = k;
    this->wordList = wordList;
    this->index = index;
    this->raise = raise;
    this->word = word;
}

task* CommaFreeParallel::execute() {
    word[index] += raise;
    if ( !contains(*wordList, word) ) {
        wordList->push_back(word);
    }

    if ( index == k - 1 ) {
        return NULL;
    }

    task_list list;
    int count = 0;
    auto callback = [&](int i) {
        list.push_back(*new (allocate_child())CommaFreeParallel(wordList, word, index + 1, i, n, k));
        ++count;
    };
    parallel_for(0, n, callback);

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
   /* for ( int i = 0; i < k; ++i ) {
        if ( contains(NULL, word) ) {
            cyclical = true;
            break;
        }
    }*/
    return cyclical;
}

bool CommaFreeParallel::contains(concurrent_vector<string> list, string word) {
    return find(list.begin(), list.end(), word) != list.end();
}

bool CommaFreeParallel::checkIfPeriodic() {
    return false;
}

void CommaFreeParallel::addWord() {
}
