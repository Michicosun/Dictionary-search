#include "finder.h"

Finder::Finder() : canFind(false), pattern(""), input(path), findingType(0) {
    if (!input) {
        QString fileName = QFileDialog::getOpenFileName(0,
                                    QString::fromUtf8("Открыть файл"),
                                    QDir::currentPath(),
                                    "All files (*.*)");
        input = std::ifstream(fileName.toStdString());
        if (!input) exit(0);
    }
}

Finder::Finder(QString word) : canFind(false), pattern(word), input(path), findingType(0) {
    if (!input) {
        QString fileName = QFileDialog::getOpenFileName(0,
                                    QString::fromUtf8("Открыть файл"),
                                    QDir::currentPath(),
                                    "All files (*.*)");
        input = std::ifstream(fileName.toStdString());
        if (!input) exit(0);
    }
}

void Finder::changePattern(QString word) {
    swap(word, pattern);
    pattern = pattern.toLower();
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

bool Finder::isFinding() {
    return canFind;
}

Finder::~Finder() {
    input.close();
}

using std::string;

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
    string word;
    while (canFind && input >> word) {
        if (findingType == 1) {
            if (checkSequences(QString::fromStdString(word).toLower(), pattern)) {
                emit emitWord(QString::fromStdString(word) + "\n");
            }
        } else {
            if (checkStrings(QString::fromStdString(word).toLower(), pattern)) {
                emit emitWord(QString::fromStdString(word) + "\n");
            }
        }
        QThread::msleep(10);
    }
}

