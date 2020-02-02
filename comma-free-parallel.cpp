#include "comma-free-parallel.h"

CommaFreeParallel::CommaFreeParallel(int n, int k) {
    this->n = n;
    this->k = k;
}

void CommaFreeParallel::start() {
    for ( int i = 0; i < pow(n, k); ++i ) {

    }

}

bool CommaFreeParallel::checkIfCommaFree() {
    return false;
}

bool CommaFreeParallel::checkIfCyclical(string word) {
    bool cyclical = false;
    for ( int i = 0; i < k; ++i ) {
        word = shiftWord(word);
        if ( isCyclical(word) ) {
            cyclical = true;
            break;
        }
    }
    return cyclical;
}

bool CommaFreeParallel::isCyclical(string word) {
    return words.find(word) != string::npos;
}

bool CommaFreeParallel::checkIfPeriodic() {
    return false;
}

string CommaFreeParallel::shiftWord(string word) {
    int length = k - 1;
    word[length] = word[0];
    for ( int i = 0; i < length; ++i ) {
        word[i] = word[i + 1];
    }
    return word;
}

void CommaFreeParallel::addWord() {
}

void CommaFreeParallel::addToWordList() {
}
