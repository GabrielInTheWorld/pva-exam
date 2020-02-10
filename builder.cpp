#include "builder.h"

Builder::~Builder() {
    delete context;
}

concurrent_vector<string> Builder::buildCommaFreeList(concurrent_vector<string>* wordList, int k) {
    this->k = k;

    auto tmp = *wordList;
    con_set setCodeWords = k % 2 == 0 ? insertWordsEvenK(tmp) : insertWordsOddK(tmp);

    int solutions = 0;
    int maximumCodeWords = setCodeWords.size() / k;
    cout << "Maximum code words: " << maximumCodeWords << endl;
    string code = "";
    bool isFinished = false;
    context = new task_group_context();
    task_list roots;
    for ( int i = 0; i < (int)setCodeWords.size(); ++i ) {
        string firstWord = *next(setCodeWords.begin(), i);
        CommaFreeTask* root = new(task::allocate_root(*context))CommaFreeTask(setCodeWords, code, firstWord, maximumCodeWords, k, solutions, &isFinished, context);
        roots.push_back(*root);
        //group.run(roots);
    }
    task::spawn_root_and_wait(roots);
    //group.run_and_wait(roots);
    return resultList;
}

con_set Builder::insertWordsEvenK(concurrent_vector<string> wordList) {
    con_set result;
    concurrent_vector<string> tmp;
    auto callback = [&](int index) {
        string word = wordList[index];
        if ( !checkIfPeriodEvenK(word) ) {
            result.insert(word);
        }
    };
    parallel_for(0, (int)wordList.size(), callback);
    return result;
}

con_set Builder::insertWordsOddK(concurrent_vector<string> wordList) {
    con_set result;
    auto callback = [&](int index) {
        string word = wordList[index];
        if ( !checkIfPeriodOddK(word) ) {
            result.insert(word);
        }
    };
    parallel_for(0, (int)wordList.size(), callback);
    return result;
}

bool Builder::checkIfPeriodOddK(string word) {
    bool isPeriodic = true;
    if ( k == 1 ) {
        return false;
    }
    
    char letter = word[0];
    for ( int i = 1; i < (int)word.size(); ++i ) {
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
        /*for ( int j = 1; j < k / subLength; ++j ) {
            isPeriodic = isPeriodic && substr == word.substr(subLength * j, i);
            substr = word.substr(subLength * j, i);
        }*/
        auto callback = [&](int index) {
            isPeriodic = isPeriodic && substr == word.substr(subLength * index, i);
        };
        parallel_for(1, k / subLength, callback);
        if ( isPeriodic ) {
            break;
        }
    }
    return isPeriodic;
}
