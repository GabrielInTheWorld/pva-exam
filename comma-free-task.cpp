#include "comma-free-task.h"

CommaFreeTask::CommaFreeTask(concurrent_vector<string> wordList, string code, string wordToAppend, int maximumCodeWords, int k) {
    this->wordList = wordList;
    this->code = code;
    this->wordToAppend = wordToAppend;
    this->maximumCodeWords = maximumCodeWords;
    this->k = k;
}

task* CommaFreeTask::execute() {
    
    return NULL;
}

bool CommaFreeTask::checkIfCyclical(string code, string word) {
    bool cyclical = false;
    for ( int i = 0; i < k; ++i ) {
        if ( codeContains(code, word) ) {
            cyclical = true;
            break;
        }
        rotate(word.begin(), word.begin() + 1, word.end());
    }
    return cyclical;
}

bool CommaFreeTask::checkIfPeriod(string word) {
    int MIDDLE = k / 2;
    bool isPeriodic = true;

    if ( k % 2 == 1 ) {
        char letter = word[0];
        for ( int i = 1; i < word.size(); ++i ) {
            if ( word[i] != letter ) {
                isPeriodic = false;
                break;
            }
        }
        return isPeriodic;
    }

    for ( int i = 1; i < MIDDLE + 1; ++i ) {
        string substr = word.substr(0, i);
        int subLength = (int)substr.length();
        for ( int j = 1; j < k / subLength; ++j ) {
            isPeriodic = isPeriodic && substr == word.substr(subLength, i);
            substr = word.substr(subLength, i);
        }
    }
    return isPeriodic;
}

bool CommaFreeTask::codeContains(string code, string word) {
    return code.find(word) != string::npos;
}

bool CommaFreeTask::checkIfAppendingIsAllowed(string code, string word) {
    string result = code + word;
    bool isAllowed = true;
    int codeSize = result.size();
    for ( int i = 1; i < k && codeSize > k; ++i ) {
        string substring = result.substr(codeSize - k - i, k);
        if ( codeContains(code, substring) ) {
            isAllowed = false;
            break;
        }
    }
    return isAllowed;
}
