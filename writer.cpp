#include "writer.h"

string writer::dictionary = "";

void writer::writeToFile(string stream) {
    ofstream writeFile("word-list.txt");
    writeFile << stream << "\n";
    writeFile.close();
}

void writer::setDictionary(string dictionary) {
    if ( writer::dictionary.size() < dictionary.size() ) {
        writer::dictionary = dictionary;
    }
}

string writer::getDictionary() {
    return writer::dictionary;
}