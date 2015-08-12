#ifndef DEFINES_H
#define DEFINES_H

#define _CRT_SECURE_NO_WARNINGS

#include <QMainWindow>
#include <QLabel>
#include <QFileDialog>
#include <QMessageBox>
#include <QTimer>
#include <QPainter>
#include <QApplication>
#include <QDesktopWidget>
#include <QMouseEvent>
#include <QProcess>
#include <QBitmap>
#include <QString>
#include <QSettings>
//#include <Qpalette>

#include <string>
#include <vector>
#include <map>
#include <set>
#include <fstream>
#include <cstdlib>
#include <ctime>
using namespace std;

QDir directoryOf(const QString &subdir);
QString GetFileDir(QString file);

#pragma execution_character_set("utf-8")

struct People{
    string sid;//id的三位数表示形式
    int id;
    string flag;//奖项名称
    string arr;//该奖项的第几个人(1/5)
};

#endif // DEFINES_H
