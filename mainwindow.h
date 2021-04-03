#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QThread>
#include <QMainWindow>
#include "finder.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void stopReading();

private slots:

    void on_pattern_textChanged();
    void update(QString word);

private:
    Ui::MainWindow *ui;
    Finder pFinder;
    QThread pTh;
};
#endif // MAINWINDOW_H
