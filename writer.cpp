#include "writer.h"

string writer::dictionary = "";
//writer* writer::_instance = 0;
//
//writer* writer::getInstance() {
//    if ( !_instance ) {
//        _instance = new writer();
//    }
//    return _instance;
//}
//
//writer::~writer() {}

void writer::writeToFile(string stream) {
    ofstream writeFile("word-list.txt");
    writeFile << stream << "\n";
    writeFile.close();
}

void writer::setDictionary(string dictionary) {
    //if ( this->dictionary.size() < dictionary.size() ) {
        //this->dictionary = dictionary;
    //}
    if ( writer::dictionary.size() < dictionary.size() ) {
        writer::dictionary = dictionary;
    }
}

string writer::getDictionary() {
    return writer::dictionary;
}

//class CGuard {
//public:
//    ~CGuard() {
//        if ( NULL != writer::_instance ) {
//            delete writer::_instance;
//        }
//        writer::_instance = 0;
//    }
//};

//writer::CGuard::~CGuard() {
//    if ( NULL != writer::_instance ) {
//        delete writer::_instance;
//    }
//    writer::_instance = NULL;
//}
