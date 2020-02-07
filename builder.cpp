#include "builder.h"

concurrent_vector<string> Builder::buildCommaFreeList(concurrent_vector<string>* wordList, int k) {
    this->k = k;

    auto tmp = *wordList;
    for ( int i = 0; i < tmp.size(); ++i ) {
        string word = tmp[i];
        //cout << word << " cyclical? " << checkIfCyclical(word) << endl;
        //cout << word << " period? " << checkIfPeriod(word) << endl;
        string code = joinString(resultList);
        if ( !checkIfCyclical(code, word) && !checkIfPeriod(word) && checkIfAppendingIsAllowed(code, word) ) {
            resultList.push_back(word);
        }
    }

    for ( auto item : resultList ) {
        cout << "item: " << item << endl;
    }

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

bool Builder::checkIfPeriod(string word) {
    int MIDDLE = k / 2;
    bool isPeriodic = true;

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

bool Builder::codeContains(string code, string word) {
    return code.find(word) != string::npos;
}

bool Builder::listContains(string word) {
    return find(resultList.begin(), resultList.end(), word) != resultList.end();
    //return binary_search(resultList.begin(), resultList.end(), word);
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
