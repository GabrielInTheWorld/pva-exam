#include "writer.h"

string writer::dictionary = "";
concurrent_vector<string> writer::solutionList;

void writer::writeToFile(string stream) {
    ofstream writeFile("word-list.txt");
    writeFile << stream << "\n";
    writeFile.close();
}

void writer::setDictionary(string dictionary) {
    solutionList.push_back(dictionary);
}

string writer::getDictionary() {
    for ( string word : solutionList ) {
        if ( word.size() > dictionary.size() ) {
            dictionary = word;
        }
    }
    return writer::dictionary;
}