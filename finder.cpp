#include "finder.h"

Finder::Finder() : canFind(false), pattern(""), findingType(0) {}

Finder::Finder(QString word) : canFind(false), pattern(word), findingType(0) {}

void Finder::changePattern(QString word) {
    swap(word, pattern);
    pattern = pattern.toLower();
}

void Finder::changeFlag(bool nxt) {
    canFind = nxt;
}

void Finder::changeMod(int x) {
    findingType = x;
}

bool Finder::isFinding() {
    return canFind;
}

void Finder::setPath(QString path) {
    file.setFileName(path);
}

Finder::~Finder() {
    if (file.isOpen()) file.close();
}

bool checkSequences(const QString& text, const QString& pat) {
    int l = 0, r = 0;
    while (l < text.size() && r < pat.size()) {
        while (l < text.size() && text[l] != pat[r]) ++l;
        if (l < text.size() && text[l] == pat[r]) {
            ++r;
            ++l;
        }
    }
    return r == pat.size();
}

bool checkStrings(const QString& text, const QString& pat) {
    return text.contains(pat);
}

void Finder::find() {
    file.open(QIODevice::ReadOnly);
    QTextStream input(&file);

    QString word;
    while (canFind && !input.atEnd()) {
        input >> word;
        if (findingType == 1) {
            if (checkSequences(word.toLower(), pattern)) {
                emit emitWord(word + "\n");
                QThread::msleep(10);
            }
        } else {
            if (checkStrings(word.toLower(), pattern)) {
                emit emitWord(word + "\n");
                QThread::msleep(10);
            }
        }
    }
    file.close();
}

