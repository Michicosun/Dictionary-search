#ifndef FINDER_H
#define FINDER_H

#include <QObject>
#include <QString>
#include <QThread>
#include <QDebug>
#include <QFileDialog>
#include <QTextStream>

class Finder : public QObject
{
    Q_OBJECT
public:

    Finder();
    Finder(QString word);

    void changePattern(QString word);

    void changeFlag(bool nxt);

    void changeMod(int x);

    bool isFinding();

    void setPath(QString path);

    ~Finder();

public slots:
    void find();

signals:
    void emitWord(QString word);

private:
    bool canFind;
    QString pattern;
    int findingType;
    QFile file;
};

#endif // FINDER_H
