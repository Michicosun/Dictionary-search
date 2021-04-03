#ifndef FINDER_H
#define FINDER_H

#include <QObject>
#include <QString>
#include <QThread>
#include <QDebug>
#include <fstream>
#include <string>

const std::string path = "words.txt";

class Finder : public QObject
{
    Q_OBJECT
public:

    Finder();
    Finder(QString word);

    void changePattern(QString word);

    void changeFlag(bool nxt);

    void moveToTop();

    ~Finder();

public slots:
    void find();

signals:
    void emitWord(QString word);

private:
    bool canFind;
    QString pattern;
    std::ifstream input;
};

#endif // FINDER_H
