#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

extern int total_words_passed;
extern int total_fails;

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
        QString currentWord();
        void isAnyWords();
        void removeCurrentWord();
        void refresh();

    private slots:
        void on_inputText_textEdited(const QString &arg1);

        void on_refreshButton_clicked();

private:
        Ui::MainWindow *ui;
        void loadTextFile();
};




#endif // MAINWINDOW_H
