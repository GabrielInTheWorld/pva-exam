#include "comma-free-seq.h"

CommaFreeSeq::CommaFreeSeq() {
    cout << "Run" << endl;
    initWordList();
    start();
}

// Gebaut von Gabriel Meyer
bool CommaFreeSeq::codeContains(string code, string word) {
    return code.find(word) != string::npos;
}

// Gebaut von Michael Sieb
bool CommaFreeSeq::checkIfAppendingIsAllowed(string code, string word) {
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

// Gebaut von Gabriel Meyer
bool CommaFreeSeq::checkIfPeriodic(string word) {
    bool isPeriodic = true;
    queue<int> q;
    const int MIDDLE = k / 2 + 1;
    for ( int i = 1; i < MIDDLE; ++i ) {
        if ( k % i == 0 ) {
            q.push(i);
        }
    }

    while ( !q.empty() ) {
        int length = q.front();

        isPeriodic = true;
        string substr = word.substr(0, length);
        int subLength = (int)substr.length();
        for ( int i = 0; i < k / subLength; ++i ) {
            isPeriodic = isPeriodic && substr == word.substr(subLength * i, length);
        }
        if ( isPeriodic ) {
            break;
        }
        q.pop();
    }
    return isPeriodic;
}

// Gebaut von Michael Sieb
bool CommaFreeSeq::checkIfCyclical(string code, string word) {
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

// Gebaut von Gabriel Meyer
bool CommaFreeSeq::checkIfCommaFree(string word) {
    return word.size() == k && !checkIfPeriodic(word) && !checkIfCyclical(commaFreeCode, word) && checkIfAppendingIsAllowed(commaFreeCode, word);
}

// Gebaut von Michael Sieb
void CommaFreeSeq::initWordList() {
    string word;
    ifstream readFile("word-list.txt");
    while ( readFile >> word ) {
        cout << "Word: " << word << endl;
        wordList.push_back(word);
        commaFreeCode += word;
    }
}

// Gebaut von Gabriel Meyer
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
            commaFreeCode += word;
        }
    }
    cout << "End of input" << endl;
    writeFile.close();
}