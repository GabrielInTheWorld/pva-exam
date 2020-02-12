#include "writer.h"

string writer::dictionary = "";
concurrent_unordered_multiset<string> writer::solutionSet;

void writer::writeToFile(string stream) {
    ofstream writeFile("word-list.txt");
    writeFile << stream << "\n";
    writeFile.close();
}

void writer::setDictionary(string dictionary) {
    solutionSet.insert(dictionary);
}

string writer::getDictionary() {
    for ( string word : solutionSet ) {
        if ( word.size() > dictionary.size() ) {
            dictionary = word;
        }
    }
    return writer::dictionary;
}