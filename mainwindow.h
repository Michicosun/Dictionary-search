#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QThread>
#include <QMainWindow>
#include <QFile>
#include "finder.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

const QString path = "./words.txt";

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void stopReading();

    void startReading();

    QString openFile();

private slots:

    void on_pattern_textChanged();

    void update(QString word);

    void on_substring_button_clicked();

    void on_subsequence_button_clicked();

private:
    Ui::MainWindow *ui;
    Finder pFinder;
    QThread pTh;
};
#endif // MAINWINDOW_H
