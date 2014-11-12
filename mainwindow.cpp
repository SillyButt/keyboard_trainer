#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QApplication>
#include <QtGui>
#include <QTCore/QFile>
#include <QTCore/QTextStream>
#include <QDebug>


int total_words_passed;
int total_fails;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->inputText->setAttribute(Qt::WA_MacShowFocusRect, 0);
    loadTextFile();

    total_words_passed = 0;
    total_fails = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadTextFile()
{
    QString fileName = ":/text.txt";
    QFile inputFile(fileName);
    if (!inputFile.exists())
    {
        qWarning() << "No such file: " << fileName;
        return;
    }
    inputFile.open(QIODevice::ReadOnly);

    QTextStream in(&inputFile);
    QString line = in.readAll();
    inputFile.close();

    ui->originalText->setPlainText(line);
}

QStringList MainWindow::getWords()
{
    QString text = ui->originalText->toPlainText();
    QStringList words = text.split(" ");
    return words;
}

QString MainWindow::currentWord()
{
    return MainWindow::getWords()[0];
}

void MainWindow::isAnyWords()
{
    QStringList elements = MainWindow::getWords();
    int words = elements.length();
    int letters = elements[0].length();

    if ((words == 1) && (letters == 0))
    {
        ui->inputText->setDisabled(true);
    }
}

void MainWindow::removeCurrentWord()
{
    QString word = MainWindow::currentWord();
    QString text = ui->originalText->toPlainText();
    ui->originalText->setPlainText(text.remove(0, word.length()+1));
    MainWindow::isAnyWords();
}

void MainWindow::on_inputText_textEdited(const QString &arg)
{
    QString currentWord = MainWindow::currentWord();
    int length = arg.length();
    if (arg[length-1] == 0x20) // Space
    {
        QString typedWord = arg.mid(0, length-1);
        if (typedWord == currentWord) {
            MainWindow::removeCurrentWord();
            ui->inputText->clear();
            total_words_passed++;
            return;
        }
    }
    if (arg[length-1] == currentWord[length-1])
    {
        // Color the character on originalText
        qDebug() << "GOOD";
    } else {
        total_fails++;
         qDebug() << "BAD";
    }
}

void MainWindow::on_refreshButton_clicked()
{
    total_words_passed = 0;
    total_fails = 0;
    MainWindow::loadTextFile();
    ui->inputText->clear();
    ui->inputText->setEnabled(true);
}
