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
    cout << "Run task for n: " << n << endl;
    cout << "With k: " << k << endl;
    task_scheduler_init my_task(numberCores);
    //int number = (numberCores > 0 ? numberCores : my_task.default_num_threads());
    cout << "Using #" << numberCores << " cores." << endl;
    tick_count c0 = tick_count::now();
    string startWord = initWord();
    createWordList(startWord);

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
    string solutionCode = writer::getDictionary();
    writeSolution(solutionCode, numberCores, (c1 - c0).seconds());
}

void CommaFreeScheduler::startCommaFreeVector() {
    cout << "Run task for n: " << n << endl;
    cout << "With k: " << k << endl;
    task_scheduler_init my_task(numberCores);
    //int number = (numberCores > 0 ? numberCores : my_task.default_num_threads());
    cout << "Using #" << numberCores << " cores." << endl;
    tick_count c0 = tick_count::now();
    string startWord = initWord();
    createWordList(startWord);

    auto wordListIndices = builder.buildPeriodicFreeVector(wordList, k);

    task_list roots;
    for ( int i = 0; i < (int)wordListIndices.size(); ++i ) {
        if ( wordListIndices[i] ) {
            CommaFreeVectorTask* root = new(task::allocate_root(*context))CommaFreeVectorTask(wordList, wordListIndices, concurrent_vector<unsigned int>(), i, wordListIndices.size()/k, k, 0, context, NULL);
            roots.push_back(*root);
        }
    }
    task::spawn_root_and_wait(roots);

    tick_count c1 = tick_count::now();
    cout << "Time needed: " << (c1 - c0).seconds() << endl;
    string solutionCode = writer::getDictionary();
    writeSolution(solutionCode, numberCores, (c1 - c0).seconds());
}

string CommaFreeScheduler::initWord() {
    string startWord = "";
    for ( int i = 0; i < k; ++i ) {
        startWord.append("a");
    }
    return startWord;
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
