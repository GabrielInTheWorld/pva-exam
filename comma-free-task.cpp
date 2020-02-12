#include "comma-free-task.h"

CommaFreeTask::CommaFreeTask(con_set wordList, string code, string wordToAppend, const int& maximumCodeWords, const int& k, int solutions, task_group_context* group): maximumCodeWords(maximumCodeWords) {
    this->wordList = wordList;
    this->code = code;
    this->wordToAppend = wordToAppend;
    this->k = k;
    this->solutions = solutions;
    this->group = group;
}

task* CommaFreeTask::execute() {
    if ( group->is_group_execution_cancelled() ) {
        return NULL;
    }
    bool canBeAppended = true;
    bool isCyclical = false;
    auto checkCyclical = [&]() {
        isCyclical = checkIfCyclical(code, wordToAppend);
    };
    auto checkAppending = [&]() {
        canBeAppended = checkIfAppendingIsAllowed(code, wordToAppend);
    };
    parallel_invoke(checkAppending, checkCyclical);
    if (canBeAppended && !isCyclical) {
        code += wordToAppend;
        auto writeCode = [&]() {
            ++solutions;
            writer::setDictionary(code);
        };
        parallel_invoke([&]() {filterCyclicalWords(wordList, wordToAppend); }, writeCode);

        if ( solutions == maximumCodeWords && !group->is_group_execution_cancelled() ) {
            locker.lock();
            cout << "Solution found with " << solutions << " CodeWords: " << code << endl;
            group->cancel_group_execution();
            locker.unlock();
            return NULL;
        }

        task_list children;
        int count = 0;
        auto callback = [&](int index) {
            string nextWordToAppend = *next(wordList.begin(), index);
            CommaFreeTask* child = new(allocate_child())CommaFreeTask(wordList, code, nextWordToAppend, maximumCodeWords, k, solutions, group);
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

bool CommaFreeTask::codeContains(const string& code, const string& word) {
    return code.find(word) != string::npos;
}

bool CommaFreeTask::checkIfCyclical(const string& code, string word) {
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

bool CommaFreeTask::checkIfAppendingIsAllowed(const string& code, string word) {
    string result = code + word;
    bool isAllowed = true;
    int codeSize = result.size();
    if ( codeSize <= k ) {
        return true;
    }
    for ( int i = 1; i < k && codeSize > k; ++i ) {
        string substring = result.substr(codeSize - k - i, k);
        if ( codeContains(code, substring) ) {
            isAllowed = false;
            break;
        }
    }
    return isAllowed;
}

void CommaFreeTask::filterCyclicalWords(con_set& list, string word) {
    for ( int i = 0; i < k; ++i ) {
        rotate(word.begin(), word.begin() + 1, word.end());
        list.unsafe_erase(word);
    }
}
