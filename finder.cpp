#include "finder.h"

Finder::Finder() : canFind(false), pattern(""), input(path), findingType(0) {
    if (!input) qDebug() << "ERROR File not opened";
}

Finder::Finder(QString word) : canFind(false), pattern(word), input(path), findingType(0) {
    if (!input) qDebug() << "ERROR File not opened";
}

void Finder::changePattern(QString word) {
    swap(word, pattern);
}

void Finder::changeFlag(bool nxt) {
    canFind = nxt;
}

void Finder::moveToTop() {
    input.clear();
    input.seekg(0, std::ios::beg);
}

void Finder::changeMod(int x) {
    findingType = x;
}

Finder::~Finder() {
    input.close();
}

using std::string;

bool checkSequences(const string& text, const string& pat) {
    size_t l = 0, r = 0;
    while (l < text.size() && r < pat.size()) {
        while (l < text.size() && text[l] != pat[r]) ++l;
        if (l < text.size() && text[l] == pat[r]) {
            ++r;
            ++l;
        }
    }
    return r == pat.size();
}

bool checkStrings(QString text, QString pat) {
    return text.contains(pat);
}

void Finder::find() {
    string word;
    while (canFind && input >> word) {
        if (findingType == 1) {
            if (checkSequences(word, pattern.toStdString())) {
                emit emitWord(QString::fromStdString(word) + "\n");
            }
        } else {
            if (checkStrings(QString::fromStdString(word), pattern)) {
                emit emitWord(QString::fromStdString(word) + "\n");
            }
        }
        QThread::msleep(10);
    }
}

