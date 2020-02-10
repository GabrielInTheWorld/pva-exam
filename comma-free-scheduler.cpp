#include "comma-free-scheduler.h"

CommaFreeScheduler::CommaFreeScheduler(int n, int k) {
    this->n = n;
    this->k = k;
}

CommaFreeScheduler::~CommaFreeScheduler() {
    delete wordList;
}

void CommaFreeScheduler::startCommaFreeParallel(int numberCores) {
    cout << "Run task for n: " << n << endl;
    cout << "With k: " << k << endl;
    task_scheduler_init my_task(numberCores);
    int number = (numberCores > 0 ? numberCores : my_task.default_num_threads());
    cout << "Using #" << (numberCores > 0 ? numberCores : my_task.default_num_threads()) << " cores." << endl;
    tick_count c0 = tick_count::now();
    string startWord = initWord();

    task_list list;
    for ( int i = 0; i < n; ++i ) {
        string tmp = startWord;
        CommaFreeParallel* root = new (task::allocate_root())CommaFreeParallel(wordList, tmp, 0, i, n, k);
        list.push_back(*root);
    }
    task::spawn_root_and_wait(list);
    cout << "Number of all words: " << wordList->size() << endl;

    Builder builder;
    auto resultList = builder.buildCommaFreeList(wordList, k);
    tick_count c1 = tick_count::now();
    cout << "Time needed: " << (c1 - c0).seconds() << endl;
    string solutionCode = writer::getDictionary();
    writeSolution(solutionCode, number, (c1 - c0).seconds());
}

string CommaFreeScheduler::initWord() {
    string startWord = "";
    for ( int i = 0; i < k; ++i ) {
        startWord.append("a");
    }
    return startWord;
}

void CommaFreeScheduler::writeSolution(string solutionCode, int numberCores, double seconds) {
    int solutions = 0;
    string stream = "Run task with n: " + to_string(n) + ", k: " + to_string(k) + ", using #cores: " + to_string(numberCores) + " in " + to_string(seconds) + " seconds.\nFound solution: " + solutionCode;
    for ( int i = 0; i < solutionCode.size(); i += k ) {
        string subWord = solutionCode.substr(i, k);
        stream += "\n" + subWord;
        ++solutions;
    }
    stream += "\nFound #" + to_string(solutions) + " code words.";
    writer::writeToFile(stream);
}
