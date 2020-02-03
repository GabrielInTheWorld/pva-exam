#include "comma-free-checker.h"

CommaFreeChecker::CommaFreeChecker(string* words, string word, int index, int raise, int n, int k): words(words), word(word), index(index), raise(raise) {
    this->n = n;
    this->k = k;
}

CommaFreeChecker::~CommaFreeChecker() {}

task* CommaFreeChecker::execute() {
    word[index] += raise;
    if ( !checkIfPeriodic(word) && !checkIfCyclical(word) ) {
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
    bool isPeriodic = true;
    for ( int i = 2; i < MIDDLE + 1; ++i ) {
        string substr = word.substr(0, i);
        int subLength = (int)substr.length();
        for ( int j = 1; j < k / subLength; ++j ) {
            isPeriodic = isPeriodic && substr == word.substr(subLength, i);
            substr = word.substr(subLength, i);
        }
    }
    return isPeriodic;
}

bool CommaFreeChecker::checkIfCyclical(string word) {
    bool cyclical = false;
    for ( int i = 0; i < k; ++i ) {
        if ( contains(word) ) {
            cyclical = true;
            break;
        }
        rotate(word.begin(), word.begin() + 1, word.end());
    }
    return cyclical;
}

void CommaFreeChecker::checkContaining(string word) {

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
