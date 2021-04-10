#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow), pFinder(), pTh() {
    ui->setupUi(this);
    connect(&pFinder, &Finder::emitWord, this, &MainWindow::update);
    connect(&pTh, &QThread::started, &pFinder, &Finder::find);

    pFinder.setPath(openFile());
    pFinder.moveToThread(&pTh);

    QPalette p1 = palette();
    p1.setBrush(QPalette::ButtonText, Qt::blue);
    ui->substring_button->setPalette(p1);

    QPalette p2 = palette();
    p2.setBrush(QPalette::ButtonText, Qt::black);
    ui->subsequence_button->setPalette(p2);
}

QString MainWindow::openFile() {
    if (!QFile::exists(path)) {
        QString fileName = QFileDialog::getOpenFileName(this,
                                    QString::fromUtf8("Открыть файл"),
                                    QDir::currentPath(),
                                    "All files (*.*)");
        if (QFile::exists(fileName)) return fileName;
        else exit(0);
    } else return path;
}

MainWindow::~MainWindow() {
    stopReading();
    delete ui;
}

void MainWindow::stopReading() {
    pTh.quit();
    pFinder.changeFlag(false);
    pTh.wait();
    QCoreApplication::processEvents();
    ui->words_list->clear();
}

void MainWindow::startReading() {
    if (ui->pattern->text().size() > 0) {
        pFinder.changePattern(ui->pattern->text());
        pFinder.changeFlag(true);
        pTh.start();
    }
}

void MainWindow::update(QString word) {
    if (pFinder.isFinding())
        ui->words_list->insertPlainText(word);
}

void MainWindow::on_pattern_textChanged() {
    stopReading();
    startReading();
}

void MainWindow::on_substring_button_clicked() {
    QPalette p1 = palette();
    p1.setBrush(QPalette::ButtonText, Qt::blue);
    ui->substring_button->setPalette(p1);

    QPalette p2 = palette();
    p2.setBrush(QPalette::ButtonText, Qt::black);
    ui->subsequence_button->setPalette(p2);

    stopReading();
    pFinder.changeMod(0);
    startReading();
}

void MainWindow::on_subsequence_button_clicked() {
    QPalette p1 = palette();
    p1.setBrush(QPalette::ButtonText, Qt::black);
    ui->substring_button->setPalette(p1);

    QPalette p2 = palette();
    p2.setBrush(QPalette::ButtonText, Qt::blue);
    ui->subsequence_button->setPalette(p2);

    stopReading();
    pFinder.changeMod(1);
    startReading();
}
