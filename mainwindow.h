#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

extern int totalWordsPassed;
extern int totalFails;
extern int timerSeconds;
extern bool timerIsActive;
extern int maxFiles;
extern int minFiles;
extern int totalCharactersPassed;
extern int mode;

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
        void initialize_practice_mode();
        void initialize_training_mode();
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
        void on_button_practice_clicked();
        void on_button_training_clicked();
        void update();

private:
            Ui::MainWindow *ui;
            QTimer *timer;
            void loadTextFile(bool practiceMode);
};



#endif // MAINWINDOW_H
