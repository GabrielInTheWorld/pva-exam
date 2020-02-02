#include "comma-free-checker.h"

CommaFreeChecker::CommaFreeChecker(string* words, string& word, int index, int raise, int n, int k): words(words), word(word), index(index), raise(raise) {
    this->n = n;
    this->k = k;
}

CommaFreeChecker::~CommaFreeChecker() {}

task* CommaFreeChecker::execute() {
    word[index] += raise;
    if ( !contains(word) && !checkIfPeriodic(word) ) {
        words->append(word);
    }
    if ( index == k - 1 ) {
        return NULL;
    }

    task_list list;
    int count = 0;
    auto callback = [&](int i) {
        list.push_back(*new (allocate_child())CommaFreeChecker(words, word, index + 1, i, n, k));
        ++count;
    };
    parallel_for(0, n, callback);

    //for ( int i = 0; i < n; ++i ) {
    //    list.push_back(*new (allocate_child())CommaFreeChecker(words, word, index + 1, i, n, k));
    //    ++count;
    //}
    if ( count > 0 ) {
        set_ref_count(count + 1);
        spawn_and_wait_for_all(list);
    }

    return NULL;
}

bool CommaFreeChecker::checkIfPeriodic(string word) {
    int MIDDLE = k / 2;
    return word.substr(0, MIDDLE) == word.substr(MIDDLE);
}

bool CommaFreeChecker::contains(string word) {
    return words->find(word) != string::npos;
}

string CommaFreeChecker::shiftWord(string word) {
    int length = k - 1;
    char tmp = word[0];
    auto callback = [&](int i) {
        word[i] = word[i + 1];
    };
    parallel_for(0, length, callback);

    //for ( int i = 0; i < length; ++i ) {
    //    word[i] = word[i + 1];
    //}
    word[length] = tmp;
    return word;
}
