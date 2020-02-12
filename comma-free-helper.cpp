#include "comma-free-helper.h"

CommaFreeHelper::CommaFreeHelper(concurrent_vector<string>* wordList, string word, int index, int raise, int n, int k) {
    this->n = n;
    this->k = k;
    this->wordList = wordList;
    this->index = index;
    this->raise = raise;
    this->word = word;
}

// Gebaut von Michael Sieb
task* CommaFreeHelper::execute() {
    word[index] += raise;
    if ( !contains(*wordList, word) ) {
        wordList->push_back(word);
    }

    if ( index == k - 1 ) {
        return NULL;
    }

    task_list list;
    int count = 0;
    auto callback = [&](int i) {
        list.push_back(*new (allocate_child())CommaFreeHelper(wordList, word, index + 1, i, n, k));
        ++count;
    };
    parallel_for(0, n, callback);

    if ( count > 0 ) {
        set_ref_count(count + 1);
        spawn_and_wait_for_all(list);
    }

    return NULL;
}

// Gebaut von Gabriel Meyer
bool CommaFreeHelper::contains(concurrent_vector<string> list, string word) {
    return find(list.begin(), list.end(), word) != list.end();
}
