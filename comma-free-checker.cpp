#include "comma-free-checker.h"

CommaFreeChecker::CommaFreeChecker(concurrent_vector<string>* wordList, string word, int index, int raise, int n, int k): tmpList(wordList) {
    this->n = n;
    this->k = k;
    this->raise = raise;
    this->index = index;
    this->word = word;
    tmpIndex = index;
    //this->tmpList = wordList;
    //tmpList = new vector<string>(*wordList);
    //this->holdList = *wordList;
    holdList = new concurrent_vector<string>(*wordList);
}

//CommaFreeChecker::CommaFreeChecker(string* words, vector<string>& wordList, string word, int index, int raise, int n, int k): wordList(wordList), word(word), raise(raise) {
//    this->n = n;
//    this->k = k;
//    this->index = index;
//    this->words = words;
//}

CommaFreeChecker::~CommaFreeChecker() {
    delete holdList;
    //delete tmpList;
}

task* CommaFreeChecker::execute() {
    //cout << "init" << endl;
    //vector<string> tmpList = wordList;
    //int tmpIndex = index;

   /* task_list list;
    int count = 0;
    auto callback = [&](int i) {
        list.push_back(*new (allocate_child())CommaFreeChecker(&words, wordList, word, tmpIndex + 1, i, n, k));
        ++count;
    };
    parallel_for(1, n, callback);

    if ( count > 0 ) {
        set_ref_count(count + 1);
        spawn_and_wait_for_all(list);
    }*/
    //concurrent_vector<string>* tmp = tmpList;
    //cout << "before joinString" << endl;
    code = joinString(*holdList);
    //code = join(holdList);
    //code = *words;
    string code = word;
    //cout << "Raise word" << endl;
    //word[index] += raise;
    code[index] += raise;
    //cout << "Word raised" << endl;
    if ( !checkIfPeriodic(code) && !checkIfCyclical(code) ) {
        //mutex.lock();
        //cout << "Increase size" << endl;

        tmpList->grow_by(1);

        //cout << "Append word" << endl;
        //words->append(code);
        tmpList->push_back(code);
        //wordList.push_back(code);
        //cout << wordList.size() << endl;
        //mutex.unlock();
        //wordList.push_back(code);
    }
    //cout << index << endl;
    if ( tmpIndex == k - 1 ) {
        return NULL;
    }

    //cout << "New children" << endl;
    task_list list;
    int count = 0;
    auto callback = [&](int i) {
        //auto tmp = tmpList;
        list.push_back(*new (allocate_child())CommaFreeChecker(tmpList, code, tmpIndex + 1, i, n, k));
        ++count;
    };
    parallel_for(1, n, callback);
    /*for ( int i = 1; i < n; ++i ) {
        cout << "push_back" << endl;
        list.push_back(*new(allocate_child())CommaFreeChecker(tmpList, code, tmpIndex + 1, i, n, k));
        ++count;
    }*/

    if ( count > 0 ) {
        set_ref_count(count + 1);
        spawn_and_wait_for_all(list);
    }

    return NULL;
}

bool CommaFreeChecker::checkIfPeriodic(string word) {
    //cout << "checkIfPeriod" << endl;
    int MIDDLE = k / 2;
    bool isPeriodic = true;
    //cout << "For for-loop" << endl;
    /*for ( int i = 2; i < MIDDLE + 1; ++i ) {
        string substr = word.substr(0, i);
        int subLength = (int)substr.length();
        for ( int j = 1; j < k / subLength; ++j ) {
            isPeriodic = isPeriodic && substr == word.substr(subLength, i);
            substr = word.substr(subLength, i);
        }
    }*/

    auto callback = [&](int index) {
        string substring = word.substr(0, index);
        int subLength = substring.length();
        for ( int i = 1; i < k / subLength; ++i ) {
            isPeriodic = isPeriodic && substring == word.substr(subLength, index);
            substring = word.substr(subLength, index);
        }
    };
    parallel_for(2, MIDDLE + 1, callback);

    return isPeriodic;
}

bool CommaFreeChecker::checkIfCyclical(string word) {
    //cout << "checkIfCyclical" << endl;
    bool cyclical = false;
    /*for ( int i = 0; i < k; ++i ) {
        if ( contains(word) ) {
            cyclical = true;
            break;
        }
        rotate(word.begin(), word.begin() + 1, word.end());
    }*/
    auto callback = [&](int index) {
        if ( contains(word) ) {
            cyclical = true;
        }
        rotate(word.begin(), word.begin() + 1, word.end());
    };
    parallel_for(0, k, callback);
    return cyclical;
}

void CommaFreeChecker::checkContaining(string word) {

}

bool CommaFreeChecker::contains(string word) {
    //cout << "contains" << endl;
    //return words->find(word) != string::npos;
    return code.find(word) != string::npos;
}

string CommaFreeChecker::joinString(concurrent_vector<string> list) {
    //cout << "joinString" << endl;
    string joinedString = "";
    for ( const auto& item : list ) joinedString += item;
   /* auto callback = [&](int index) {
        joinedString += list[index];
    };
    parallel_for(0, (int)list.size(), callback);*/
    return joinedString;
}

string CommaFreeChecker::join(concurrent_vector<string>* list) {
    //cout << "join" << endl;
    string resultString = "";
    for ( auto it = list->begin(); it != list->end(); ++it ) {
        resultString += *it;
    }
    return resultString;
}



string CommaFreeChecker::shiftWord(string word) {
    //int length = k - 1;
    //char tmp = word[0];
    //auto callback = [&](int i) {
    //    word[i] = word[i + 1];
    //};
    //parallel_for(0, length, callback);

    ////for ( int i = 0; i < length; ++i ) {
    ////    word[i] = word[i + 1];
    ////}
    //word[length] = tmp;
    return word;
}
