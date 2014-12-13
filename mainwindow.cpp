#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QApplication>
#include <QtGui>
#include <QTCore/QFile>
#include <QTCore/QTextStream>
#include <QDebug>
#include <time.h>

int totalWordsPassed;
int totalFails;
int maxFiles = 10;
int minFiles = 1;
int timerSeconds;
int totalCharactersPassed = 0;
bool timerIsActive;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->inputText->setAttribute(Qt::WA_MacShowFocusRect, 0);

    MainWindow::initialize();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initialize()
{

    totalWordsPassed    = 0;
    totalFails          = 0;
    timerIsActive       = false;
    timerSeconds        = 60;
    totalCharactersPassed = 0;
    ui->inputText->clear();
    ui->inputText->setEnabled(true);
    ui->resultsWrapper->hide();
    ui->WPM->hide();
    ui->LPM->hide();
    ui->timer->setText("1 : 00");
    if (timer != NULL)
    {
        timer->stop();
        delete timer;
        timer = NULL;
    }
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    MainWindow::loadTextFile();
}

void MainWindow::loadTextFile()
{
    int randomFile = MainWindow::randomNumber();
    qDebug() << randomFile;
    QString fileName = QString(":/texts/") + QString::number(randomFile) + QString(".txt");
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

int MainWindow::randomNumber()
{
    qsrand(time(NULL));
    return qrand() % (maxFiles - minFiles) + minFiles;
}

QStringList MainWindow::getWords()
{
    QString     text  = ui->originalText->toPlainText();
    QStringList words = text.split(" ");
    return words;
}

QString MainWindow::wordToWrite()
{
    return MainWindow::getWords()[0];
}

void MainWindow::removeCurrentWord()
{
    QString word = MainWindow::wordToWrite();
    QString text = ui->originalText->toPlainText();
    ui->originalText->setPlainText(text.remove(0, word.length()+1));
}

void MainWindow::checkIsLastWord()
{
    if (MainWindow::wordToWrite().length() == 0)
    {
        MainWindow::endProgram();
    }
}

void MainWindow::on_inputText_textEdited(const QString &arg)
{
    // Length of characters in input.
    int length = arg.length();
    QChar space = 0x20;

    // Starts timer when input first time changed.
    if (!timerIsActive)
    {
        MainWindow::runTimer();
    }

    // Prevent space as a first character
    if (length == 1 && arg[0] == space)
    {
        ui->inputText->clear();
    }

    if (length > 1) {
        QString wordToWrite = MainWindow::wordToWrite(); // The word that needs to be written.
        QChar lastCharacter = arg[length-1]; // The last character of written(or half-written) word.

        if (lastCharacter == space)
        {
            QString typedWord = arg.mid(0, length-1); // A full word without last character(Space)

            if (typedWord == wordToWrite) {
                ui->inputText->clear();

                MainWindow::removeCurrentWord();
                MainWindow::checkIsLastWord();

                totalCharactersPassed += length;
                totalWordsPassed++;
                return;
            }
        }

        // If user writes the right way
        if (lastCharacter == wordToWrite[length-1])
        {
            // Color the character on originalText
            //qDebug() << "GOOD";
        } else {
            totalFails++;
            //qDebug() << "BAD";
        }
    }
}

void MainWindow::on_refreshButton_clicked()
{
    MainWindow::initialize();
}

void MainWindow::runTimer()
{
    timerIsActive = true;
    timer->start(1000);
}

void MainWindow::update()
{
    if (timerIsActive) {
        --timerSeconds;
        if (timerSeconds > 0)
        {
            QString secondsLeft = QString::number(timerSeconds);
            if (timerSeconds <= 10)
            {
                ui->timer->setText("0 : 0" + secondsLeft);
            }
            ui->timer->setText("0 : " + secondsLeft);
        }
        else
        {
            MainWindow::endProgram();
        }
    }
}

void MainWindow::endProgram()
{
    qDebug() << "END";
    qDebug() << "WINS: " << totalWordsPassed;
    qDebug() << "CHARASTERS: " << totalCharactersPassed;
    ui->resultsWrapper->show();
    ui->WPM->show();
    ui->LPM->show();
    ui->WPM->setText("СЛОВ В МИНУТУ: " + QString::number(totalWordsPassed));
    ui->LPM->setText("СИМВОЛОВ В МИНУТУ: " + QString::number(totalCharactersPassed));
    ui->inputText->setDisabled(true);
    ui->timer->setText("0 : 00");
    timer->stop();
    timerIsActive = false;
}
