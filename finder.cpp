#include "finder.h"

Finder::Finder() : canFind(false), pattern(""), input(path) {
    if (!input) qDebug() << "ERROR File not opened";
}

Finder::Finder(QString word) : canFind(false), pattern(word), input(path) {
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

Finder::~Finder() {
    input.close();
}

using std::string;

bool check(const string& text, const string& pat) {
    size_t l = 0, r = 0;
    while (l < text.size() && r < pat.size()) {
        while (l < text.size() && text[l] != pat[r]) ++l;
        if (l < text.size() && text[l] == pat[r]) ++r;
    }
    return r == pat.size();
}

#include<iostream>

void Finder::find() {
    string word;
    while (canFind && input >> word) {
        if (check(word, pattern.toStdString())) {
            emit emitWord(QString::fromStdString(word) + "\n");
        }
        QThread::msleep(10);
    }
}

