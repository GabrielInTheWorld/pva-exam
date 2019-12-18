#include "comma-free-seq.h"

CommaFreeSeq::CommaFreeSeq() {
    start();
}

bool CommaFreeSeq::checkIfCommaFree(string word) {
    return word.size() == 4 && !checkIfPeriodic(word) && !checkIfPermutation(word);
}

bool CommaFreeSeq::checkIfPeriodic(string word) {
    return word.substr(0, 1) != word.substr(2, 3);
}

bool CommaFreeSeq::checkIfPermutation(string word) {
    for ( int i = 0; i < wordList.size(); ++i ) {
        if ( arePermutation(word, wordList[i]) ) {
            return true;
        }
    }
    return false;
}

bool CommaFreeSeq::arePermutation(string word, string comparison) {
    int count[4] = { 0 };

    // Check, if there are the same number of letters.
    for ( int i = 0; i < 4; ++i ) {
        count[word[i]]++;
        count[word[i]]--;
    }

    for ( int i = 0; i < 4; ++i ) {
        if ( count[i] ) {
            return false;
        }
    }
    return true;
}

void CommaFreeSeq::initWordList() {
    char word[4];
    ifstream readFile("word-list.txt");
    while ( readFile >> word ) {
        cout << "Word: " << word << endl;
        wordList.push_back(word);
    }
}

void CommaFreeSeq::start() {
    cout << "Press 'x' to cancel" << endl;
    ofstream writeFile("word-list.txt");
    while (true) {
        char word[4];
        cin >> word;
        if ( word == "x" ) {
            break;
        }
        if ( checkIfCommaFree(word) ) {
            writeFile << word << "\n";
        }
    }
    cout << "End of input" << endl;
    writeFile.close();
}