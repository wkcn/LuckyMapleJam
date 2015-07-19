#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Defines.h"

namespace Ui {
class MainWindow;
}


enum STATE{
    START,RANDOM,RANDOMRES,RANDOMRESWAIT,WAITVIEW,RESULT
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void paintEvent(QPaintEvent *);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void timerUpDate();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    QPixmap box;
    STATE state;
    string PrintNum(int value,int w);
    int maxNum;
    int truthNum;
    int truthView;
    int aniLen;
    vector<People> peo;
    set<int> haveGot;
    int cup;
    int aniTime;
    int GetNewNum();
    void STRAND();
    QString resultText;
};

#endif // MAINWINDOW_H
