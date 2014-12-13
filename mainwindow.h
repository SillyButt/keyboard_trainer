#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

extern int total_words_passed;
extern int total_fails;
extern int timerSeconds;
extern bool timerIsActive;
extern int maxFiles;
extern int minFiles;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = 0);
        ~MainWindow();

        QStringList getWords();
        QString wordToWrite();
        void initialize();
        void disableInput();
        void removeCurrentWord();
        void checkIsLastWord();
        void refresh();
        void runTimer();
        void endProgram();
        int randomNumber();


    private slots:
        void on_inputText_textEdited(const QString &arg1);
        void on_refreshButton_clicked();
        void update();

    private:
            Ui::MainWindow *ui;
            QTimer *timer;
            void loadTextFile();
};



#endif // MAINWINDOW_H
