#include "builder.h"

// Gebaut von Michael Sieb
con_set Builder::buildPeriodicFreeUnorderedSet(concurrent_vector<string>* wordList, const int& k) {
    this->k = k;

    con_set result;
    auto callback = [&](int index) {
        string word = (*wordList)[index];
        if ( !checkIfPeriod(word) ) {
            result.insert(word);
        }
    };
    parallel_for(0, (int)wordList->size(), callback);
    return result;
}

// Gebaut von Gabriel Meyer
bool Builder::checkIfPeriod(const string& word) {
    bool isPeriodic = true;
    concurrent_queue<int> q;
    const int MIDDLE = k / 2 + 1;
    auto findDivider = [&](int index) {
        if ( k % index == 0 ) {
            q.push(index);
        }
    };
    parallel_for(1, MIDDLE, findDivider);

    int i = 0;
    while ( !q.empty() ) {
        if ( q.try_pop(i) ) {
            isPeriodic = true;
            string substr = word.substr(0, i);
            int subLength = (int)substr.length();
            auto callback = [&](int index) {
                isPeriodic = isPeriodic && substr == word.substr(subLength * index, i);
            };
            parallel_for(1, k / subLength, callback);
            if ( isPeriodic ) {
                break;
            }
        }
    }
    return isPeriodic;
}
