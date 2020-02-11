#include "comma-free-vector-task.h"

CommaFreeVectorTask::CommaFreeVectorTask(const con_vec* wordList, const concurrent_vector<bool> wordListIndices, concurrent_vector<unsigned int> indices, unsigned int nextIndex, const int& maximumCodeWords, const int& k, int solutions, task_group_context* group, CommaFreeVectorTask* parent): wordList(wordList), wordListIndices(wordListIndices), maximumCodeWords(maximumCodeWords), k(k), group(group), parent(parent) {
    this->indices = indices;
    this->nextIndex = nextIndex;
    this->solutions = solutions;
    this->word = (*wordList)[nextIndex];
}

task* CommaFreeVectorTask::execute() {
    if ( group->is_group_execution_cancelled() ) {
        return NULL;
    }
    bool canBeAppended = true;
    bool isCyclical = false;
    auto checkCyclical = [&]() {
        isCyclical = checkIfCyclical(dereferencingCode(), word);
    };
    auto checkAppending = [&]() {
        canBeAppended = checkIfAppendingIsAllowed(dereferencingCode(), word);
    };
    parallel_invoke(checkAppending, checkCyclical);
    if ( canBeAppended && !isCyclical ) {
        auto filterWords = [&]() {
            ++solutions;
            writer::setDictionary(dereferencingCode() + getWord());
        };
        parallel_invoke([&]() {filterCyclicalWords(&wordListIndices, getWord()); }, filterWords);

        if ( solutions == maximumCodeWords ) {
            cout << "Solution found with " << solutions << " CodeWords: " << (dereferencingCode() + getWord()) << endl;
            group->cancel_group_execution();
            return NULL;
        }

        task_list children;
        int count = 0;
        auto callback = [&](int index) {
            if ( wordListIndices[index] ) {
                CommaFreeVectorTask* child = new(allocate_child())CommaFreeVectorTask(wordList, wordListIndices, indices, index, maximumCodeWords, k, solutions, group, this);
                children.push_back(*child);
                ++count;
            }
        };
        parallel_for(0, (int)wordListIndices.size(), callback);

        if ( count > 0 ) {
            set_ref_count(count + 1);
            spawn_and_wait_for_all(children);
        }
    }
    return NULL;
}

CommaFreeVectorTask* CommaFreeVectorTask::getParent() {
    cout << "getParent" << endl;
    return parent;
}

string CommaFreeVectorTask::getWord() {
    cout << "getWord" << endl;
    //return (*wordList)[nextIndex];
    return word;
}

bool CommaFreeVectorTask::checkIfCyclical(const string code, string word) {
    cout << "checkIfCyclical" << endl;
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

bool CommaFreeVectorTask::codeContains(const string code, const string word) {
    cout << "codeContains" << endl;
    return code.find(word) != string::npos;
}

bool CommaFreeVectorTask::checkIfAppendingIsAllowed(const string code, const string word) {
    cout << "checkIfAppendingIsAllowed" << endl;
    string result = code + word;
    bool isAllowed = true;
    int codeSize = result.size();
    if ( codeSize <= k ) {
        return true;
    }
    for ( int i = 1; i < k; ++i ) {
        string substring = result.substr(codeSize - k - i, k);
        if ( codeContains(code, substring) ) {
            isAllowed = false;
            break;
        }
    }
    return isAllowed;
}

void CommaFreeVectorTask::filterCyclicalWords(concurrent_vector<bool>* list, const string word) {
    cout << "filterCyclicalWords" << endl;
    auto callback = [&](int index) {
        string tmp = word;
        rotateLeft(tmp, index);
        auto it = find(wordList->begin(), wordList->end(), tmp);
        if ( it != wordList->end() ) {
            (*list)[distance(wordList->begin(), it)] = 0;
        }
    };
    parallel_for(0, k, callback);
}

void CommaFreeVectorTask::rotateLeft(string& word, int range) {
    cout << "rotate" << endl;
    reverse(word.begin(), word.begin() + range);
    reverse(word.begin() + range, word.end());
    reverse(word.begin(), word.end());
}

string& CommaFreeVectorTask::dereferencingCode() {
    cout << "dereferencing" << endl;
    string result = "";
    for ( auto i = parent; i != NULL; i = parent->getParent() ) result += i->getWord();
    return result;
}
