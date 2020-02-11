#include "builder.h"

Builder::~Builder() {
    delete context;
}

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
    //return (k % 2 == 0) ? insertWordsEvenK(*wordList) : insertWordsOddK(*wordList);
}

concurrent_vector<bool> Builder::buildPeriodicFreeVector(concurrent_vector<string>* wordList, const int& k) {
    concurrent_vector<bool> wordListIndices(wordList->size(), 1);
    for ( int i = 0; i < (int)wordList->size(); ++i ) {
        wordListIndices[i] = !checkIfPeriod((*wordList)[i]);
    }
    return wordListIndices;
}

//con_set Builder::insertWordsEvenK(const concurrent_vector<string>& wordList) {
//    con_set result;
//    auto callback = [&](int index) {
//        string word = wordList[index];
//        if ( !checkIfPeriodEvenK(word) ) {
//            result.insert(word);
//        }
//    };
//    parallel_for(0, (int)wordList.size(), callback);
//    return result;
//}
//
//con_set Builder::insertWordsOddK(const concurrent_vector<string>& wordList) {
//    con_set result;
//    auto callback = [&](int index) {
//        string word = wordList[index];
//        if ( !checkIfPeriodOddK(word) ) {
//            result.insert(word);
//        }
//    };
//    parallel_for(0, (int)wordList.size(), callback);
//    return result;
//}
//
//bool Builder::checkIfPeriodOddK(const string& word) {
//    bool isPeriodic = true;
//    if ( k == 1 ) {
//        return false;
//    }
//
//    char letter = word[0];
//    for ( int i = 1; i < (int)word.size(); ++i ) {
//        if ( word[i] != letter ) {
//            isPeriodic = false;
//            break;
//        }
//    }
//    return isPeriodic;
//}
//
//bool Builder::checkIfPeriodEvenK(const string& word) {
//    const int MIDDLE = k / 2;
//    bool isPeriodic = true;
//    for ( int i = 1; i < MIDDLE + 1; ++i ) {
//        isPeriodic = true;
//        string substr = word.substr(0, i);
//        int subLength = (int)substr.length();
//        auto callback = [&](int index) {
//            isPeriodic = isPeriodic && substr == word.substr(subLength * index, i);
//        };
//        parallel_for(1, k / subLength, callback);
//        if ( isPeriodic ) {
//            break;
//        }
//    }
//    return isPeriodic;
//}

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
