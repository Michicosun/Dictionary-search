#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow), pFinder(), pTh() {
    ui->setupUi(this);
    connect(&pFinder, &Finder::emitWord, this, &MainWindow::update);
    connect(&pTh, &QThread::started, &pFinder, &Finder::find);
    pFinder.moveToThread(&pTh);
}

MainWindow::~MainWindow() {
    stopReading();
    delete ui;
}

void MainWindow::stopReading() {
    pTh.quit();
    pFinder.changeFlag(false);
    ui->words_list->clear();
}

void MainWindow::update(QString word) {
    ui->words_list->insertPlainText(word);
}

void MainWindow::on_pattern_textChanged() {
    stopReading();
    if (ui->pattern->toPlainText().size() > 0) {
        pFinder.changePattern(ui->pattern->toPlainText());
        pFinder.moveToTop();
        pFinder.changeFlag(true);
        pTh.start();
    }
}
