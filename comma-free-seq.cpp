#include "comma-free-seq.h"

CommaFreeSeq::CommaFreeSeq() {
    cout << "Run" << endl;
    initWordList();
    start();
}

bool CommaFreeSeq::checkIfCommaFree(string word) {
    return word.size() == 4 && !checkIfPeriodic(word) && !checkIfPermutation(word);
}

bool CommaFreeSeq::checkIfPeriodic(string word) {
    return word[0] == word[2] && word[1] == word[3];
}

bool CommaFreeSeq::checkIfPermutation(string word) {
    for ( int i = 0; i < wordList.size(); ++i ) {
        if ( isPermutation(word, wordList[i]) ) {
            cout << word << " is permutation of " << wordList[i] << endl;
            return true;
        }
    }
    return false;
}

bool CommaFreeSeq::isPermutation(string word, string comparison) {
    sort(word.begin(), word.end());
    sort(comparison.begin(), comparison.end());

    for ( int i = 0; i < word.length(); ++i ) {
        if ( word[i] != comparison[i] ) {
            return false;
        }
    }

    return true;
}

void CommaFreeSeq::initWordList() {
    string word;
    ifstream readFile("word-list.txt");
    while ( readFile >> word ) {
        cout << "Word: " << word << endl;
        wordList.push_back(word);
    }
}

void CommaFreeSeq::start() {
    cout << "Press 'x' to cancel" << endl;
    ofstream writeFile("word-list.txt");
    bool isRunning = true;
    while (isRunning) {
        string word;
        cin >> word;
        if ( word == "x" ) {
            isRunning = false;
            break;
        }
        cout << word << " is comma-free? " << checkIfCommaFree(word) << endl;
        if ( checkIfCommaFree(word) ) {
            writeFile << word << "\n";
            wordList.push_back(word);
        }
    }
    cout << "End of input" << endl;
    writeFile.close();
}