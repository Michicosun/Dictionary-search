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
    pTh.wait();
    ui->words_list->clear();
}

void MainWindow::startReading() {
    if (ui->pattern->text().size() > 0) {
        pFinder.changePattern(ui->pattern->text());
        pFinder.moveToTop();
        pFinder.changeFlag(true);
        pTh.start();
    }
}

void MainWindow::update(QString word) {
    ui->words_list->insertPlainText(word);
}

void MainWindow::on_pattern_textChanged() {
    stopReading();
    startReading();
}

void MainWindow::on_substring_button_clicked() {
    stopReading();
    pFinder.changeMod(0);
    startReading();
}

void MainWindow::on_subsequence_button_clicked() {
    stopReading();
    pFinder.changeMod(1);
    startReading();
}
