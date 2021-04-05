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

    void setInput(std::ifstream&& newIn);

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
