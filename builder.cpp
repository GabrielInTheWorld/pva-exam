#include "builder.h"

concurrent_vector<string> Builder::buildCommaFreeList(concurrent_vector<string>* wordList, int k) {
    this->k = k;

    auto tmp = *wordList;
    set<string> setCodeWords;
    for ( int i = 0; i < tmp.size(); ++i ) {
        string word = tmp[i];
        if ( k % 2 == 0 ? !checkIfPeriodEvenK(word) : !checkIfPeriodOddK(word) ) {
            setCodeWords.insert(word);
        }
    }

    int solutions = 0;
    int maximumCodeWords = setCodeWords.size() / k;
    cout << "Maximum code words: " << maximumCodeWords << endl;
    string code = "";
    bool isFinished = false;
    task_list roots;
    for ( int i = 0; i < setCodeWords.size(); ++i ) {
        string firstWord = *next(setCodeWords.begin(), i);
        CommaFreeTask* root = new(task::allocate_root())CommaFreeTask(setCodeWords, code, firstWord, maximumCodeWords, k, solutions, &isFinished);
        roots.push_back(*root);
    }
    task::spawn_root_and_wait(roots);

    return resultList;
}

bool Builder::checkIfCyclical(string code, string word) {
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

bool Builder::checkIfPeriodOddK(string word) {
    bool isPeriodic = true;
    if ( k == 1 ) {
        return false;
    }
    
    char letter = word[0];
    for ( int i = 1; i < word.size(); ++i ) {
        if ( word[i] != letter ) {
            isPeriodic = false;
            break;
        }
    }
    return isPeriodic;
}

bool Builder::checkIfPeriodEvenK(string word) {
    const int MIDDLE = k / 2;
    bool isPeriodic = true;
    for ( int i = 1; i < MIDDLE + 1; ++i ) {
        isPeriodic = true;
        string substr = word.substr(0, i);
        int subLength = (int)substr.length();
        for ( int j = 1; j < k / subLength; ++j ) {
            isPeriodic = isPeriodic && substr == word.substr(subLength * j, i);
            substr = word.substr(subLength * j, i);
        }
        if ( isPeriodic ) {
            break;
        }
    }
    return isPeriodic;
}

bool Builder::codeContains(string code, string word) {
    return code.find(word) != string::npos;
}

bool Builder::listContains(string word) {
    return find(resultList.begin(), resultList.end(), word) != resultList.end();
}

bool Builder::checkIfAppendingIsAllowed(string code, string word) {
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

string Builder::joinString(concurrent_vector<string> list) {
    string joinedString = "";
    for ( const auto& item : list ) joinedString += item;
    return joinedString;
}
