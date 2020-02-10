#include "comma-free-task.h"

CommaFreeTask::CommaFreeTask(con_set wordList, string code, string wordToAppend, int maximumCodeWords, int k, int solutions, bool* isFinished) {
    this->wordList = wordList;
    this->code = code;
    this->wordToAppend = wordToAppend;
    this->maximumCodeWords = maximumCodeWords;
    this->k = k;
    this->solutions = solutions;
    this->isFinished = isFinished;
}

task* CommaFreeTask::execute() {
    if ( *isFinished ) {
        return NULL;
    }
    if ( !checkIfCyclical(code, wordToAppend) && checkIfAppendingIsAllowed(code, wordToAppend) ) {
        string nextCode = code + wordToAppend;
        wordList = filterCyclicalWords(wordList, wordToAppend);
        ++solutions;
        //writer::getInstance()->setDictionary(nextCode);
        writer::setDictionary(nextCode);
        
        if ( solutions == maximumCodeWords ) {
            cout << "Solution found with " << solutions << " CodeWords: " << nextCode << endl;
            *isFinished = true;
            return NULL;
        }

        task_list children;
        int count = 0;
        auto callback = [&](int index) {
            string nextWordToAppend = *next(wordList.begin(), index);
            CommaFreeTask* child = new(allocate_child())CommaFreeTask(wordList, nextCode, nextWordToAppend, maximumCodeWords, k, solutions, isFinished);
            children.push_back(*child);
            ++count;
        };
        parallel_for(0, (int)wordList.size(), callback);

        if ( count > 0 ) {
            set_ref_count(count + 1);
            spawn_and_wait_for_all(children);
        }

    }
    
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

con_set CommaFreeTask::filterCyclicalWords(con_set list, string word) {
    for ( int i = 0; i < k; ++i ) {
        rotate(word.begin(), word.begin() + 1, word.end());
        list.unsafe_erase(word);
    }
    /*auto callback = [&](int index) {
        string tmp = word;
        rotate(tmp.begin(), tmp.begin() + 1, tmp.end());
        list.erase(tmp);
    };
    parallel_for(0, k, callback);*/
    return list;
}
