#ifndef FINDER_H
#define FINDER_H

#include <QObject>
#include <QString>
#include <QThread>
#include <QDebug>
#include <fstream>
#include <string>
#include <cctype>
#include <algorithm>
#include <QFileDialog>

const std::string path = "./words1.txt";

class Finder : public QObject
{
    Q_OBJECT
public:

    Finder();
    Finder(QString word);

    void changePattern(QString word);

    void changeFlag(bool nxt);

    void moveToTop();

    void changeMod(int x);

    bool isFinding();

    ~Finder();

public slots:
    void find();

signals:
    void emitWord(QString word);

private:
    bool canFind;
    QString pattern;
    std::ifstream input;
    int findingType;
};

#endif // FINDER_H
