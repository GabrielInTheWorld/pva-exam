#include "comma-free-scheduler.h"

CommaFreeScheduler::CommaFreeScheduler(int n, int k, int numberCores) {
    this->n = n;
    this->k = k;
    this->numberCores = (numberCores > 0 ? numberCores : task_scheduler_init::default_num_threads());
    this->context = new tbb::task_group_context();
}

CommaFreeScheduler::~CommaFreeScheduler() {
    delete wordList;
}

void CommaFreeScheduler::startCommaFreeParallel() {
    task_scheduler_init my_task(numberCores);
    tick_count c0 = initParallelWork();

    auto setCodeWords = builder.buildPeriodicFreeUnorderedSet(wordList, k);

    task_list roots;
    for ( int i = 0; i < (int)setCodeWords.size(); ++i ) {
        string firstWord = *next(setCodeWords.begin(), i);
        CommaFreeTask* root = new(task::allocate_root(*context))CommaFreeTask(setCodeWords, "", firstWord, setCodeWords.size()/k, k, 0, context);
        roots.push_back(*root);
    }
    task::spawn_root_and_wait(roots);

    tick_count c1 = tick_count::now();
    cout << "Time needed: " << (c1 - c0).seconds() << endl;
    writeSolution(writer::getDictionary(), numberCores, (c1 - c0).seconds());
}

string CommaFreeScheduler::initWord() {
    string startWord = "";
    auto callback = [&](auto _) {
        startWord.append("a");
    };
    parallel_for(0, k, callback);
    return startWord;
}

tick_count CommaFreeScheduler::initParallelWork() {
    cout << "Run task for n: " << n << endl;
    cout << "With k: " << k << endl;
    cout << "Using #" << numberCores << " cores." << endl;
    tick_count c0 = tick_count::now();
    createWordList(initWord());
    return c0;
}

void CommaFreeScheduler::createWordList(string startWord) {
    task_list list;
    for ( int i = 0; i < n; ++i ) {
        string tmp = startWord;
        CommaFreeParallel* root = new (task::allocate_root())CommaFreeParallel(wordList, tmp, 0, i, n, k);
        list.push_back(*root);
    }
    task::spawn_root_and_wait(list);
    cout << "Number of all words: " << wordList->size() << endl;
}

void CommaFreeScheduler::writeSolution(string solutionCode, int numberCores, double seconds) {
    int solutions = 0;
    string stream = "Run task with n: " + to_string(n) + ", k: " + to_string(k) + ", using #cores: " + to_string(numberCores) + " in " + to_string(seconds) + " seconds.\nFound solution: " + solutionCode;
    for ( int i = 0; i < (int)solutionCode.size(); i += k ) {
        string subWord = solutionCode.substr(i, k);
        stream += "\n" + subWord;
        ++solutions;
    }
    stream += "\nFound #" + to_string(solutions) + " code words.";
    writer::writeToFile(stream);
}
