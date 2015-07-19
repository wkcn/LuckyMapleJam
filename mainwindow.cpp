#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //读取配置
    QString iniFilePath = GetFileDir("Data\\config.ini");
    //qDebug("%s",iniFilePath.toStdString().c_str());
    QSettings iniSetting(iniFilePath,QSettings::IniFormat);
    iniSetting.setIniCodec("UTF-8");

    QString title = iniSetting.value("LuckyMapleJam/Title","LuckyMapleJam").toString();
    int width = iniSetting.value("LuckyMapleJam/Width","1024").toInt();
    int height = iniSetting.value("LuckyMapleJam/Height","768").toInt();
    aniLen = iniSetting.value("LuckyMapleJam/AnimationTime","18").toInt();

    QString logo = iniSetting.value("LuckyMapleJam/Logo","logo.png").toString();
    int logoX = iniSetting.value("LuckyMapleJam/LogoX","0").toInt();
    int logoY = iniSetting.value("LuckyMapleJam/LogoY","0").toInt();

    QString background = iniSetting.value("LuckyMapleJam/Background","back.png").toString();
    int bgX = iniSetting.value("LuckyMapleJam/BackgroundX","0").toInt();
    int bgY = iniSetting.value("LuckyMapleJam/BackgroundY","0").toInt();

    QString resetText = iniSetting.value("LuckyMapleJam/ResetText","Reset").toString();
    int resetX = iniSetting.value("LuckyMapleJam/ResetX","0").toInt();
    int resetY = iniSetting.value("LuckyMapleJam/ResetY","740").toInt();
    bool haveReset = iniSetting.value("LuckyMapleJam/HaveReset","1").toBool();

    int clickX = iniSetting.value("LuckyMapleJam/ClickX","380").toInt();
    int clickY = iniSetting.value("LuckyMapleJam/ClickY","630").toInt();

    maxNum = iniSetting.value("LuckyMapleJam/PeopleSize","200").toInt();
    QString prizes = iniSetting.value("LuckyMapleJam/Prizes","").toString();
    resultText = iniSetting.value("LuckyMapleJam/ResultText","").toString();

    this->setWindowTitle(title);
    this->resize(width,height);
    this->setMinimumSize(width,height);
    this->setMaximumSize(width,height);

    ui->logoPic->setPixmap(QPixmap(GetFileDir("Data\\Pic\\" + logo)));
    ui->logoPic->move(logoX,logoY);
    ui->backgroundPic->setPixmap(QPixmap(GetFileDir("Data\\Pic\\" + background)));
    ui->backgroundPic->move(bgX,bgY);
    ui->pushButton_2->setText(resetText);
    ui->pushButton_2->move(resetX,resetY);
    ui->pushButton->move(clickX,clickY);
    if (!haveReset)ui->pushButton_2->hide();

    //qDebug("%s--%d--",prizes.toStdString().c_str(),maxNum);
    QStringList pList = prizes.split("]");
    for(auto &str:pList){
        //qDebug("%s==",str.toStdString().c_str());
        QStringList ls = str.split("[");
        if (ls.size() != 2)continue;
        string temp = ls[0].toStdString();
        int ti = ls[1].toInt();
        People p;
        for(int i=1;i<=ti;i++){
            p.id = 0;
            p.flag = temp;
            p.sid = "000";
            char temp[256];
            sprintf(temp,"(%d/%d)",i,ti);
            p.arr = temp;
            peo.push_back(p);
        }
    }


    state = START;
    truthNum = 0;
    box = QPixmap(GetFileDir("box.png"));


    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(timerUpDate()));
    timer->start(25);//FPS 40

    cup = 0;
    aniTime = 0;
    truthView = 0;
    srand(time(0));
}
void MainWindow::timerUpDate(){
    this->update();
    if(state == RANDOMRESWAIT){
        aniTime ++;
        if(aniTime >= 1 * aniLen){
            truthView = 1;
        }
        if(aniTime >= (1+2) * aniLen){
            truthView = 2;
        }
        if(aniTime >= (1+2+2) * aniLen){
            truthView = 3;
            if(cup+1 < peo.size()){
                state = RANDOMRES;
                ui->pushButton->setText("下一个");
            }else{
                state = WAITVIEW;
                ui->pushButton->setText("显示结果");
            }

        }
    }
}
string MainWindow::PrintNum(int value,int w){
    //w指显示的位数
    char str[64];
    int v = value;
    //sprintf(str, "%.3d", v);
    switch (w){
    case 0:
        sprintf(str, "%.3d", rand() % maxNum + 1); break;
    case 1:
        sprintf(str, "%.1d%.2d", v/100,rand() % 100); break;
    case 2:
        sprintf(str, "%.2d%.1d", v / 10, rand() % 10); break;
    default:
        sprintf(str, "%.3d",v);
    }
    return str;
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::paintEvent(QPaintEvent *){

    QPainter painter;

    painter.begin(this);
    //state = RESULT;
    if (state == START){
        painter.drawText(320,0,500,200,Qt::AlignBottom,"抽奖环节");
    }else if (state == RANDOM || state == RANDOMRESWAIT || state == RANDOMRES || state == WAITVIEW){
        People p = peo[cup];
        char text[256];
        sprintf(text,"%s%s",p.flag.c_str(),p.arr.c_str());
        painter.drawText(300,0,500,200,Qt::AlignBottom,text);
        painter.drawPixmap(335,250,320,120,box);
        string str = PrintNum(truthNum,truthView);
        painter.drawText(410,250,320,120,Qt::AlignBottom,str.c_str());
    }else if(state == RESULT){
        painter.drawText(320,0,500,200,Qt::AlignBottom,"中奖名单");
        string name;
        int total = int(peo.size());
        int xgap = 140;
        int ygap = 60;
        int ox = 170;
        int y = 0;
        int x = ox;
        QFont font  = painter.font();
        for(int i=total - 1;i>=0;i--){
            People p = peo[i];
            if(name != p.flag){
                name = p.flag;
                x = ox;
                y+=ygap+18;
                font.setPointSize(40);
                painter.setFont(font);
                painter.drawText(x,y,500,200,Qt::AlignBottom,name.c_str());
                y+=ygap;
            }
            font.setPointSize(35);
            painter.setFont(font);
            painter.drawText(45+x,y,500,200,Qt::AlignBottom,p.sid.c_str());
            x += xgap;
        }
        font.setPointSize(28);
        painter.setFont(font);
        painter.drawText(120,y+100,1000,200,Qt::AlignBottom,resultText);
    }

    painter.end();
}

int MainWindow::GetNewNum(){
    while(true){
        bool can = true;
        int i = rand() % maxNum + 1;
        /*
        for(auto p:peo){
            if(p.id == i){
                can = false;
                break;
            }
        }*/
        if(haveGot.count(i) > 0)
            can = false;

        if(can){
            haveGot.insert(i);
            return i;
        }
    }
}
void MainWindow::STRAND(){
    truthNum = GetNewNum();
    peo[cup].sid = PrintNum(truthNum,3);
    peo[cup].id = truthNum;
    state = RANDOMRESWAIT;
    aniTime = 0;
    truthView = 0;
    ui->pushButton->setText("");
}

void MainWindow::on_pushButton_clicked(){
    if(state == START){
        state = RANDOM;
        ui->pushButton->setText("停");
    }else if(state == RANDOM){
        STRAND();
    }else if(state == RANDOMRESWAIT){

    }else if(state == RANDOMRES){
        //下一个
        if(cup+1 < peo.size())cup ++;
        STRAND();
    }else if(state == WAITVIEW){
        state = RESULT;
        ui->pushButton->hide();
        ui->pushButton_2->hide();
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    peo[cup].id = 0;
    STRAND();
}
