#include "infinitemode.h"
#include "ui_infinitemode.h"
#include <QTimerEvent>
InfiniteMode::InfiniteMode(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::InfiniteMode)
{
    ui->setupUi(this);
    QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
    animation->setDuration(200);
    animation->setStartValue(0);
    animation->setEndValue(1);
    animation->start();
    setAttribute(Qt::WA_TranslucentBackground);  //设置窗口背景透明
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinMaxButtonsHint);  //去掉窗口边框
    setWindowIcon(QIcon(":/BG/BG/myicon.png"));
    //设置只能输入数字
    ui->Close1->installEventFilter(this);
    timer=new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(Count()));
}

InfiniteMode::~InfiniteMode()
{
    delete ui;
}
void InfiniteMode::mousePressEvent(QMouseEvent *event)
{

    if (ReleaseCapture()){
        SendMessage(HWND(winId()), WM_SYSCOMMAND, SC_MOVE + HTCAPTION, 0);}
}
void InfiniteMode::Count(){

    if(time>0) {//跳转主界面的任务代码写在TimerTask的run()方法中
        time-=set;
        score += 1;
        if(score>=7000 &&score<=7050){
            set=2;
            ui->Score->setText("Up Lv"+QString::number(1));
        }
        else if(score>=10000 &&score<=10050){
            set=3;
            ui->Score->setText("Up Lv"+QString::number(2));
        }
        else if(score>=20000 &&score<=20050){
            set=4;
            ui->Score->setText("Up Lv"+QString::number(3));
        }
        else {
            ui->Score->setText(QString::number(score));
        }
        ui->progressBar->setValue(time);
    }
    else{
        disconnect(timer, SIGNAL(timeout()), this, SLOT(Count()));
        Dead1("HP Run out",MaxCo,score);
    }
}
void InfiniteMode::FixCount(){
    if(FixTime>0) {//跳转主界面的任务代码写在TimerTask的run()方法中
        FixTime-=1;
        ui->progressBar_4->setValue((double)FixTime/FixTimeT*100);
    }
    else{
        Dead1("Machine Error",MaxCo,score);
    }
}
void InfiniteMode::ContDown(){
    ui->Close1->setEnabled(false);
    QPropertyAnimation *animation = new QPropertyAnimation(ui->N1, "geometry");
    animation->setDuration(100);
    animation->setEndValue(QRect(240,280,121,121));
    animation->setStartValue(QRect(240+410,280,121,121));
    animation->setEasingCurve(QEasingCurve::OutBack);
    animation->start();
    QPropertyAnimation *animationq = new QPropertyAnimation(ui->label_3, "geometry");
    animationq->setDuration(100);
    animationq->setEndValue(QRect(370,290,71,91));
    animationq->setStartValue(QRect(370+410,290,71,91));
    animationq->setEasingCurve(QEasingCurve::OutBack);
    animationq->start();
    QPropertyAnimation *animation2 = new QPropertyAnimation(ui->N2, "geometry");
    animation2->setDuration(100);
    animation2->setEndValue(QRect(440,280,121,121));
    animation2->setStartValue(QRect(440+410,280,121,121));
    animation2->setEasingCurve(QEasingCurve::OutBack);
    animation2->start();
    QPropertyAnimation *animation3 = new QPropertyAnimation(ui->label_4, "geometry");
    animation3->setDuration(100);
    animation3->setEndValue(QRect(580,290,71,91));
    animation3->setStartValue(QRect(580+410,290,71,91));
    animation3->setEasingCurve(QEasingCurve::OutBack);
    animation3->start();
    QPropertyAnimation *animation4 = new QPropertyAnimation(ui->lineEdit, "geometry");
    animation4->setDuration(100);
    animation4->setEndValue(QRect(650,280,121,121));
    animation4->setStartValue(QRect(650+410,280,121,121));
    animation4->setEasingCurve(QEasingCurve::OutBack);
    animation4->start();
    if(condi==0){
        condi=1;
        ui->progressBar->setValue(100);
        ui->CNT->setVisible(true);
        QSoundEffect *effect=new QSoundEffect;
        effect->setSource(QUrl("qrc:/Music/Ms/CtDown.wav"));
        effect->setLoopCount(1);
        effect->setVolume(Volume);
        effect->play();
        ContTimer=new QTimer(this);
        ContTimer->start(1000);
        Don=3;
        ui->CNT->setText(QString::number(3));
        connect(ContTimer,SIGNAL(timeout()),SLOT(ContDownSub()));
    }
}
void InfiniteMode::ContDownSub(){
    Don--;
    if(Don==0){
        ui->CNT->setText("🧐");
        QSoundEffect *effect=new QSoundEffect;
        effect->setSource(QUrl("qrc:/Music/Ms/D.wav"));
        effect->setLoopCount(1);
        effect->setVolume(Volume);
        effect->play();
    }
    if(Don>0){ui->CNT->setText(QString::number(Don));}
    if(Don<0){
        ui->Close1->setEnabled(true);
        ui->CNT->setVisible(false);
        ContTimer->stop();
        StartGame(Mac);
    }
}
void InfiniteMode::StartGame(int a){
    this->grabKeyboard();
    En=true;
    Answer="";
    score=0;
    Combo1=0;
    time = 100;
    UP=10;
    In =true;
    RestoP=100;
    MaxCo=0;
    set=1;
    T=0;
    ui->Score_2->setText(QString::number(a));
    ui->No1->setText("√");
    ui->No2->setText("√");
    ui->No3->setText("√");
    ui->No4->setText("√");
    ui->C1->setChecked(true);
    ui->C2->setChecked(true);
    ui->C3->setChecked(true);
    ui->C4->setChecked(true);
    ui->Score->setText(QString::number(score));
    ui->Combo->setText(QString::number(Combo1));
    ui->progressBar->setValue(100);
    //this 为parent类, 表示当前窗口
    // SLOT填入一个槽函数
    timer=new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(Count()));
    timer->start(100);
    N1R = QRandomGenerator::global()->bounded(UP);
    N2R = QRandomGenerator::global()->bounded(UP);
    QString N11 = QString::number(N1R);
    QString N22 = QString::number(N2R);
    ui->N1->setText(N11);
    ui->N2->setText(N22);
    RestoP = 0;

    timer2=new QTimer(this);
    timer3=new QTimer(this);
    IncresTimer=new QTimer(this);
    StopTimer=new QTimer(this);
    HunFixTimer=new QTimer(this);

    timer2->start(200);
    timer3->start(1000);
    //随机技能
    FixE();
    HunE();
    IncresTimer->start(20000);
    connect(IncresTimer,SIGNAL(timeout()),SLOT(Incre()));
    StopTimer->start(15000);
    connect(StopTimer,SIGNAL(timeout()),SLOT(Stop()));
    HunFixTimer->start(40000);
    connect(HunFixTimer,SIGNAL(timeout()),SLOT(Randon()));
}
void InfiniteMode::Visible(){
    ui->lineEdit->setStyleSheet("border-image: url(:/BG/BG/NumA.png);");
}
void InfiniteMode::SetVolume(float a){
    Volume=a;
}
void InfiniteMode::Randon(){
    QSoundEffect *effect=new QSoundEffect;
    effect->setSource(QUrl("qrc:/Music/Ms/Effect.wav"));
    effect->setLoopCount(1); //循环次数
    effect->setVolume(Volume); //音量 0~1之间
    effect->play();
    if(QRandomGenerator::global()->bounded(0,2)==1){
        Fix();
        HunE();
    }
    else{
        HunS();
        FixE();
    }
}
void InfiniteMode::keyPressEvent( QKeyEvent *key )
{   if(En2){
        if(key->key() ==Qt::Key_F){
            ui->ToP->setStyleSheet("border-image: url(:/BG/BG/NoP.png);");
        }
    }
    if(!key->isAutoRepeat()){
        QSoundEffect *effect=new QSoundEffect;
        switch(QRandomGenerator::global()->bounded(0,5)){
        case 1:
            effect->setSource(QUrl("qrc:/Music/Ms/Click.wav"));
            break;
        case 2:
            effect->setSource(QUrl("qrc:/Music/Ms/Click2.wav"));
            break;
        case 3:
            effect->setSource(QUrl("qrc:/Music/Ms/Click3.wav"));
            break;
        case 4:
            effect->setSource(QUrl("qrc:/Music/Ms/Click4.wav"));
            break;
        case 0:
            effect->setSource(QUrl("qrc:/Music/Ms/Click0.wav"));
            break;
        default:
            effect->setSource(QUrl("qrc:/Music/Ms/Click.wav"));
            break;
        }
        effect->setLoopCount(1); //循环次数
        effect->setVolume(Volume); //音量 0~1之间
        effect->play();
    }
    if(key->key() == Qt::Key_Space && !key->isAutoRepeat())
    {
        if(RestoP>0){
            RestoP -= 10;
        }
    }

    if(key->key() ==Qt::Key_D  && !key->isAutoRepeat()){
        En=false;
        QPropertyAnimation *animation = new QPropertyAnimation(ui->N1, "geometry");
        animation->setDuration(500);
        animation->setStartValue(QRect(240,280,121,121));
        animation->setEndValue(QRect(240+410,280,121,121));
        animation->setEasingCurve(QEasingCurve::OutBack);
        animation->start();
        QPropertyAnimation *animationq = new QPropertyAnimation(ui->label_3, "geometry");
        animationq->setDuration(500);
        animationq->setStartValue(QRect(370,290,71,91));
        animationq->setEndValue(QRect(370+410,290,91,91));
        animationq->setEasingCurve(QEasingCurve::OutBack);
        animationq->start();
        QPropertyAnimation *animation2 = new QPropertyAnimation(ui->N2, "geometry");
        animation2->setDuration(500);
        animation2->setStartValue(QRect(440,280,121,121));
        animation2->setEndValue(QRect(440+410,280,121,121));
        animation2->setEasingCurve(QEasingCurve::OutBack);
        animation2->start();
        QPropertyAnimation *animation3 = new QPropertyAnimation(ui->label_4, "geometry");
        animation3->setDuration(500);
        animation3->setStartValue(QRect(580,290,71,91));
        animation3->setEndValue(QRect(580+410,290,71,91));
        animation3->setEasingCurve(QEasingCurve::OutBack);
        animation3->start();
        QPropertyAnimation *animation4 = new QPropertyAnimation(ui->lineEdit, "geometry");
        animation4->setDuration(500);
        animation4->setStartValue(QRect(650,280,121,121));
        animation4->setEndValue(QRect(650+410,280,121,121));
        animation4->setEasingCurve(QEasingCurve::OutBack);
        animation4->start();
    }

    if(En){
        if(key->key() == Qt::Key_Return ||  key->key() == Qt::Key_Enter && !key->isAutoRepeat())
        {
            if (ui->lineEdit->text() == "") {
                //Emprt

            } else {
                if (ui->lineEdit->text().toInt() - (N1R + N2R) == 0) {
                    ui->lineEdit->setStyleSheet("border-image: url(:/BG/BG/Yes.png);");
                    score = score + 10 + Combo1/10;
                    if (time<100){
                        time+=25;
                        if(time>=100){time=100;}
                        ui->progressBar->setValue(time);
                    }
                    Combo1++;
                    if (Combo1 > MaxCo){
                        MaxCo = Combo1;
                    }
                    ui->Combo->setText(QString::number(Combo1));
                    //Right!!


                } else {
                    ui->lineEdit->setStyleSheet("border-image: url(:/BG/BG/NoC.png);");
                    Combo1=0;
                    ui->Combo->setText(QString::number(Combo1));
                    //Wrong!!
                }
                ui->lineEdit->setText("");
                ui->Score->setText(QString::number(score));
                N1R =  QRandomGenerator::global()->bounded(UP);
                N2R =  QRandomGenerator::global()->bounded(UP);
                QString N11 = QString::number(N1R);
                QString N22 = QString::number(N2R);
                ui->N1->setText(N11);
                ui->N2->setText(N22);
            }
            QPropertyAnimation *animation = new QPropertyAnimation(ui->lineEdit, "geometry");
            animation->setDuration(500);
            animation->setStartValue(QRect(650,280,121,121));
            animation->setKeyValueAt(0.5,QRect(650-10,280-10,121+20,121+20));
            animation->setEndValue(QRect(650,280,121,121));
            animation->setEasingCurve(QEasingCurve::OutCirc);
            animation->start();
            connect(animation,SIGNAL(finished()),this,SLOT(Visible()));
            Input="";
            ui->lineEdit->setText("");
        }
        else if(key->key() == Qt::Key_C)
        {
            Input="";
            ui->lineEdit->setText("");
        }
        else if(key->key() == Qt::Key_Backspace)
        {
            if (Input.length() > 1) {
                Input=Input.removeLast();
                ui->lineEdit->setText(Input);
            }
            else if(ui->lineEdit->text().length() == 1){
                Input="";
                ui->lineEdit->setText("");
            }
        }
        else if(key->key() ==Qt::Key_0){
            if(Input.length()<3){
                Input.append("0");
                ui->lineEdit->setText(Input);
            }
        }
        else if(key->key() ==Qt::Key_1){
            if(Input.length()<3){
                Input.append("1");
                ui->lineEdit->setText(Input);
            }
        }
        else if(key->key() ==Qt::Key_2){
            if(Input.length()<3){
                Input.append("2");
                ui->lineEdit->setText(Input);
            }
        }

        else if(key->key() ==Qt::Key_3){
            if(Input.length()<3){
                Input.append("3");
                ui->lineEdit->setText(Input);
            }
        }

        else if(key->key() ==Qt::Key_4){
            if(Input.length()<3){
                Input.append("4");
                ui->lineEdit->setText(Input);
            }
        }

        else if(key->key() ==Qt::Key_5){
            if(Input.length()<3){
                Input.append("5");
                ui->lineEdit->setText(Input);
            }
        }

        else if(key->key() ==Qt::Key_6){
            if(Input.length()<3){
                Input.append("6");
                ui->lineEdit->setText(Input);
            }
        }

        else if(key->key() ==Qt::Key_7){
            if(Input.length()<3){
                Input.append("7");
                ui->lineEdit->setText(Input);
            }
        }
        else if(key->key() ==Qt::Key_8){
            if(Input.length()<3){
                Input.append("8");
                ui->lineEdit->setText(Input);
            }
        }
        else if(key->key() ==Qt::Key_9){
            if(Input.length()<3){
                Input.append("9");
                ui->lineEdit->setText(Input);
            }
        }

    }
    if(!En){
        if(key->key()==Qt::Key_Q && !key->isAutoRepeat() && Fixx){
            ui->C1->setChecked(!ui->C1->isChecked());
            if(ui->C1->isChecked()){
                FSU+=V1;
            }
            else if(FSU-V1>=0){
                FSU-=V1;
            }
            if(VF==FSU){
                T--;
                if(T>=0){
                    ui->C1->setChecked(false);
                    ui->C2->setChecked(false);
                    ui->C3->setChecked(false);
                    ui->C4->setChecked(false);
                    FSU=0;
                    FixSub();
                }
            }
        }
        else if(key->key()==Qt::Key_W && !key->isAutoRepeat() && Fixx){
            ui->C2->setChecked(!ui->C2->isChecked());
            if(ui->C2->isChecked()){
                FSU+=V2;
            }
            else if(FSU-V2>=0){
                FSU-=V2;
            }
            if(VF==FSU){
                T--;
                if(T>=0){
                    ui->C1->setChecked(false);
                    ui->C2->setChecked(false);
                    ui->C3->setChecked(false);
                    ui->C4->setChecked(false);
                    FSU=0;
                    FixSub();
                }
            }
        }
        else if(key->key()==Qt::Key_E && !key->isAutoRepeat()&& Fixx){
            ui->C3->setChecked(!ui->C3->isChecked());
            if(ui->C3->isChecked()){
                FSU+=V3;
            }
            else if(FSU-V3>=0){
                FSU-=V3;
            }
            if(VF==FSU){
                T--;
                if(T>=0){
                    ui->C1->setChecked(false);
                    ui->C2->setChecked(false);
                    ui->C3->setChecked(false);
                    ui->C4->setChecked(false);
                    FSU=0;
                    FixSub();
                }
            }
        }
        else if(key->key()==Qt::Key_R && !key->isAutoRepeat()&& Fixx){
            ui->C4->setChecked(!ui->C4->isChecked());
            if(ui->C4->isChecked()){
                FSU+=V4;
            }
            else if(FSU-V4>=0){
                FSU-=V4;
            }
            if(VF==FSU){
                T--;
                if(T>=0){
                    ui->C1->setChecked(false);
                    ui->C2->setChecked(false);
                    ui->C3->setChecked(false);
                    ui->C4->setChecked(false);
                    FSU=0;
                    FixSub();
                }
            }
        }
    }
}
//数字变大
void InfiniteMode::Incre(){
    QSoundEffect *effect=new QSoundEffect;
    effect->setSource(QUrl("qrc:/Music/Ms/Effect.wav"));
    effect->setLoopCount(1); //循环次数
    effect->setVolume(Volume); //音量 0~1之间
    effect->play();
    QPropertyAnimation *animation = new QPropertyAnimation(ui->IncreT, "geometry");
    animation->setDuration(500);
    animation->setStartValue(QRect(810+270,100,161,101));
    animation->setEndValue(QRect(810,100,161,101));
    animation->setEasingCurve(QEasingCurve::OutCirc);
    animation->start();
    IncresETimer=new QTimer(this);


    IncresETimer->start(QRandomGenerator::global()->bounded(5000,19000));
    IncresETimer->setSingleShot(true);
    connect(IncresETimer,SIGNAL(timeout()),this,SLOT(IncreE()));
    UP=100;
}
void InfiniteMode::IncreE(){
    QPropertyAnimation *animation = new QPropertyAnimation(ui->IncreT, "geometry");
    animation->setDuration(500);
    animation->setEndValue(QRect(810+270,100,161,101));
    animation->setStartValue(QRect(810,100,161,101));
    animation->setEasingCurve(QEasingCurve::OutCirc);
    animation->start();
    UP=10;
}
//捆绑
void InfiniteMode::Stop(){
    QSoundEffect *effect=new QSoundEffect;
    effect->setSource(QUrl("qrc:/Music/Ms/Effect.wav"));
    effect->setLoopCount(1); //循环次数
    effect->setVolume(Volume); //音量 0~1之间
    effect->play();
    En=false;
    En2=true;
    ui->progressBar_3->setValue(0);
    QPropertyAnimation *animation = new QPropertyAnimation(ui->ToP, "geometry");
    animation->setDuration(500);
    animation->setStartValue(QRect(490,-130,171,61));
    animation->setEndValue(QRect(490,320,171,61));
    animation->setEasingCurve(QEasingCurve::OutBack);
    animation->start();
    QPropertyAnimation *animationq = new QPropertyAnimation(ui->TOPB, "geometry");
    animationq->setDuration(500);
    animationq->setStartValue(QRect(310,-540,371,497));
    animationq->setEndValue(QRect(310,80,391,521));
    animationq->setEasingCurve(QEasingCurve::OutBack);
    animationq->start();
    QPropertyAnimation *animation2 = new QPropertyAnimation(ui->TopLa, "geometry");
    animation2->setDuration(500);
    animation2->setStartValue(QRect(350,-120,321,51));
    animation2->setEndValue(QRect(350,240,231,51));
    animation2->setEasingCurve(QEasingCurve::OutBack);
    animation2->start();
    QPropertyAnimation *animation3 = new QPropertyAnimation(ui->progressBar_3, "geometry");
    animation3->setDuration(500);
    animation3->setStartValue(QRect(320,-530,371,497));
    animation3->setEndValue(QRect(320,92,371,497));
    animation3->setEasingCurve(QEasingCurve::OutBack);
    animation3->start();
}
void InfiniteMode::EndStop(){
    En=true;
    ui->progressBar_3->setValue(0);
    QPropertyAnimation *animation = new QPropertyAnimation(ui->ToP, "geometry");
    animation->setDuration(500);
    animation->setEndValue(QRect(490,-130,171,61));
    animation->setStartValue(QRect(490,320,171,61));
    animation->setEasingCurve(QEasingCurve::InOutBack);
    animation->start();
    QPropertyAnimation *animationq = new QPropertyAnimation(ui->TOPB, "geometry");
    animationq->setDuration(500);
    animationq->setEndValue(QRect(310,-540,371,497));
    animationq->setStartValue(QRect(310,80,391,521));
    animationq->setEasingCurve(QEasingCurve::InOutBack);
    animationq->start();
    QPropertyAnimation *animation2 = new QPropertyAnimation(ui->TopLa, "geometry");
    animation2->setDuration(500);
    animation2->setEndValue(QRect(350,-120,321,51));
    animation2->setStartValue(QRect(350,240,231,51));
    animation2->setEasingCurve(QEasingCurve::InOutBack);
    animation2->start();
    QPropertyAnimation *animation3 = new QPropertyAnimation(ui->progressBar_3, "geometry");
    animation3->setDuration(500);
    animation3->setEndValue(QRect(320,-530,371,497));
    animation3->setStartValue(QRect(320,92,371,497));
    animation3->setEasingCurve(QEasingCurve::InOutBack);
    animation3->start();
    En2=false;

}
//混沌
void InfiniteMode::HunS(){
    QSoundEffect *effect=new QSoundEffect;
    effect->setSource(QUrl("qrc:/Music/Ms/Effect.wav"));
    effect->setLoopCount(1); //循环次数
    effect->setVolume(Volume); //音量 0~1之间
    effect->play();
    QPropertyAnimation *animation = new QPropertyAnimation(ui->HunT, "geometry");
    animation->setDuration(500);
    animation->setStartValue(QRect(530,730,251,151));
    animation->setEndValue(QRect(530,450,251,151));
    animation->setEasingCurve(QEasingCurve::OutBack);
    animation->start();
    QPropertyAnimation *animation2 = new QPropertyAnimation(ui->Hund, "geometry");
    animation2->setDuration(500);
    animation2->setEndValue(QRect(260,500,121,41));
    animation2->setStartValue(QRect(260,770,121,41));
    animation2->setEasingCurve(QEasingCurve::OutBack);
    animation2->start();
    QPropertyAnimation *animation1 = new QPropertyAnimation(ui->progressBar_2, "geometry");
    animation1->setDuration(500);
    animation1->setEndValue(QRect(260,540,501,31));
    animation1->setStartValue(QRect(260,870,501,31));
    animation1->setEasingCurve(QEasingCurve::OutBack);
    animation1->start();
    connect(timer2, SIGNAL(timeout()), this, SLOT(Hun()));
    HunETimer=new QTimer(this);
    HunETimer->setSingleShot(true);
    HunETimer->start(QRandomGenerator::global()->bounded(20000,30000));
    connect(HunETimer,SIGNAL(timeout()),this,SLOT(HunE()));
}
void InfiniteMode::HunE(){
    QPropertyAnimation *animation = new QPropertyAnimation(ui->HunT, "geometry");
    animation->setDuration(500);
    animation->setEndValue(QRect(530,730,251,151));
    animation->setStartValue(QRect(530,450,251,151));
    animation->setEasingCurve(QEasingCurve::InOutBack);
    animation->start();
    QPropertyAnimation *animation2 = new QPropertyAnimation(ui->Hund, "geometry");
    animation2->setDuration(500);
    animation2->setStartValue(QRect(260,500,121,41));
    animation2->setEndValue(QRect(260,770,121,41));
    animation2->setEasingCurve(QEasingCurve::InOutBack);
    animation2->start();
    QPropertyAnimation *animation1 = new QPropertyAnimation(ui->progressBar_2, "geometry");
    animation1->setDuration(500);
    animation1->setStartValue(QRect(260,540,501,31));
    animation1->setEndValue(QRect(260,870,501,31));
    animation1->setEasingCurve(QEasingCurve::InOutBack);
    animation1->start();
    disconnect(timer2, SIGNAL(timeout()), this, SLOT(Hun()));
}
void InfiniteMode::Hun()
{
    if (RestoP <100) {
        RestoP += 8;
        ui->progressBar_2->setValue(RestoP);
    } else {
        disconnect(timer2, SIGNAL(timeout()), this, SLOT(Hun()));
        disconnect(HunETimer,SIGNAL(timeout()),this,SLOT(HunE()));
        disconnect(timer, SIGNAL(timeout()), this, SLOT(Count()));
        Dead1("Chaos value too high",MaxCo,score);
    }
}
//机械故障
void InfiniteMode::Fix(){
    QSoundEffect *effect=new QSoundEffect;
    effect->setSource(QUrl("qrc:/Music/Ms/Effect.wav"));
    effect->setLoopCount(1); //循环次数
    effect->setVolume(Volume); //音量 0~1之间
    effect->play();
    Fixx=true;
    ui->C1->setChecked(false);
    ui->C2->setChecked(false);
    ui->C3->setChecked(false);
    ui->C4->setChecked(false);
    FixTimeT=QRandomGenerator::global()->bounded(20,30);
    FixTime=FixTimeT;
    T=FixTimeT/10;
    FSU=0;
    ui->progressBar_4->setValue(100);
    ui->Progre->setText("Complete damage");
    connect(timer3, SIGNAL(timeout()), this, SLOT(FixCount()));
    QPropertyAnimation *animation2 = new QPropertyAnimation(ui->Progre, "geometry");
    animation2->setDuration(500);
    animation2->setEndValue(QRect(260,500,400,41));
    animation2->setStartValue(QRect(260,770,400,41));
    animation2->setEasingCurve(QEasingCurve::OutBack);
    animation2->start();
    QPropertyAnimation *animation1 = new QPropertyAnimation(ui->progressBar_4, "geometry");
    animation1->setDuration(500);
    animation1->setEndValue(QRect(260,540,501,31));
    animation1->setStartValue(QRect(260,870,501,31));
    animation1->setEasingCurve(QEasingCurve::OutBack);
    animation1->start();
    QPropertyAnimation *animation3 = new QPropertyAnimation(ui->ERRORT, "geometry");
    animation3->setDuration(500);
    animation3->setEndValue(QRect(240,80,361,211));
    animation3->setStartValue(QRect(240,80-200,400,41));
    animation3->setEasingCurve(QEasingCurve::OutBack);
    animation3->start();
    QPropertyAnimation *animation4 = new QPropertyAnimation(ui->ERRORT1, "geometry");
    animation4->setDuration(500);
    animation4->setEndValue(QRect(250,50,441,31));
    animation4->setStartValue(QRect(250,50-200,441,31));
    animation4->setEasingCurve(QEasingCurve::OutBack);
    animation4->start();
    FixSub();
}
void InfiniteMode::FixSub(){
    if(T<=0){
        FixE();
        return ;
    }
    VF=0;
    FSU=0;
    V1=QRandomGenerator::global()->bounded(1,10);
    V2=QRandomGenerator::global()->bounded(1,10);
    while(V2==V1){V2=QRandomGenerator::global()->bounded(1,10);}
    V3=QRandomGenerator::global()->bounded(1,10);
    while(V3==V1 ||V3==V2){V3=QRandomGenerator::global()->bounded(1,10);}
    V4=QRandomGenerator::global()->bounded(1,10);
    while(V4==V1 ||V4==V2 || V4==V3){V4=QRandomGenerator::global()->bounded(1,10);}
    if(QRandomGenerator::global()->bounded(0,2)==1){
        VF+=V1;
    }
    if(QRandomGenerator::global()->bounded(0,2)==1){
        VF+=V2;
    }
    if(QRandomGenerator::global()->bounded(0,2)==1){
        VF+=V3;
    }
    if(QRandomGenerator::global()->bounded(0,2)==1){
        VF+=V4;
    }
    if(VF==0){
        VF+=V1;
    }
    ui->No1->setText(QString::number(V1)+"V");
    ui->No2->setText(QString::number(V2)+"V");
    ui->No3->setText(QString::number(V3)+"V");
    ui->No4->setText(QString::number(V4)+"V");
    ui->ERRORT1->setText("Adjust the voltage to "+QString::number(VF)+"V ("+QString::number(T)+")");
}
void InfiniteMode::FixE(){
    Fixx=false;
    ui->No1->setText("√");
    ui->No2->setText("√");
    ui->No3->setText("√");
    ui->No4->setText("√");
    ui->C1->setChecked(true);
    ui->C2->setChecked(true);
    ui->C3->setChecked(true);
    ui->C4->setChecked(true);
    ui->C1->setEnabled(false);
    ui->C2->setEnabled(false);
    ui->C3->setEnabled(false);
    ui->C4->setEnabled(false);
    disconnect(timer3, SIGNAL(timeout()), this, SLOT(FixCount()));
    QPropertyAnimation *animation2 = new QPropertyAnimation(ui->Progre, "geometry");
    animation2->setDuration(500);
    animation2->setStartValue(QRect(260,500,400,41));
    animation2->setEndValue(QRect(260,770,400,41));
    animation2->setEasingCurve(QEasingCurve::OutBack);
    animation2->start();
    QPropertyAnimation *animation1 = new QPropertyAnimation(ui->progressBar_4, "geometry");
    animation1->setDuration(500);
    animation1->setStartValue(QRect(260,540,501,31));
    animation1->setEndValue(QRect(260,870,501,31));
    animation1->setEasingCurve(QEasingCurve::OutBack);
    animation1->start();
    QPropertyAnimation *animation3 = new QPropertyAnimation(ui->ERRORT, "geometry");
    animation3->setDuration(500);
    animation3->setStartValue(QRect(240,80,361,211));
    animation3->setEndValue(QRect(240,80-200,400,41));
    animation3->setEasingCurve(QEasingCurve::OutBack);
    animation3->start();
    QPropertyAnimation *animation4 = new QPropertyAnimation(ui->ERRORT1, "geometry");
    animation4->setDuration(500);
    animation4->setStartValue(QRect(250,50,441,31));
    animation4->setEndValue(QRect(250,50-200,441,31));
    animation4->setEasingCurve(QEasingCurve::OutBack);
    animation4->start();
}

void InfiniteMode::keyReleaseEvent( QKeyEvent * event)
{
    if(En2){
        if (event->key() == Qt::Key_F && !event->isAutoRepeat())
        {
            ui->progressBar_3->setValue(ui->progressBar_3->value()+7);
            ui->ToP->setStyleSheet("border-image: url(:/BG/BG/No.png);");
            if(ui->progressBar_3->value()>=96){
                ui->progressBar_3->setValue(0);
                EndStop();
                En2=false;
            }
        }
    }
    if(event->key() ==Qt::Key_D  && !event->isAutoRepeat()){
        QPropertyAnimation *animation = new QPropertyAnimation(ui->N1, "geometry");
        animation->setDuration(500);
        animation->setEndValue(QRect(240,280,121,121));
        animation->setStartValue(QRect(240+410,280,121,121));
        animation->setEasingCurve(QEasingCurve::OutBack);
        animation->start();
        QPropertyAnimation *animationq = new QPropertyAnimation(ui->label_3, "geometry");
        animationq->setDuration(500);
        animationq->setEndValue(QRect(370,290,71,91));
        animationq->setStartValue(QRect(370+410,290,71,91));
        animationq->setEasingCurve(QEasingCurve::OutBack);
        animationq->start();
        QPropertyAnimation *animation2 = new QPropertyAnimation(ui->N2, "geometry");
        animation2->setDuration(500);
        animation2->setEndValue(QRect(440,280,121,121));
        animation2->setStartValue(QRect(440+410,280,121,121));
        animation2->setEasingCurve(QEasingCurve::OutBack);
        animation2->start();
        QPropertyAnimation *animation3 = new QPropertyAnimation(ui->label_4, "geometry");
        animation3->setDuration(500);
        animation3->setEndValue(QRect(580,290,71,91));
        animation3->setStartValue(QRect(580+410,290,71,91));
        animation3->setEasingCurve(QEasingCurve::OutBack);
        animation3->start();
        QPropertyAnimation *animation4 = new QPropertyAnimation(ui->lineEdit, "geometry");
        animation4->setDuration(500);
        animation4->setEndValue(QRect(650,280,121,121));
        animation4->setStartValue(QRect(650+410,280,121,121));
        animation4->setEasingCurve(QEasingCurve::OutBack);
        animation4->start();
        En=true;
    }
}
bool InfiniteMode::eventFilter(QObject *obj, QEvent *event)
{
    switch (event->type()) {
    case QEvent::HoverEnter:
        if(obj==ui->Close1){
            ui->Close1->setStyleSheet("background-color: rgb(255, 183, 184);border-radius:9px;");
        }
        break;
    case QEvent::HoverLeave:
        if(obj==ui->Close1){
            ui->Close1->setStyleSheet("background-color: rgb(255, 138, 140);border-radius:9px;");
        }
        break;
    case QEvent::MouseButtonPress:


        break;
    case QEvent::MouseButtonRelease:

        break;
    default:
        break;
    }
    return QWidget::eventFilter(obj, event);
}
void InfiniteMode::on_Close1_clicked()
{
    condi=0;
    EndAll();
    emit subClose();
}
//统一开关
void InfiniteMode::EndAll(){
    this->releaseKeyboard();
    En=false;
    ContTimer->stop();
    timer->stop();
    timer2->stop();
    timer3->stop();
    StopTimer->stop();
    HunFixTimer->stop();
    IncresTimer->stop();

    QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
    animation->setDuration(200);
    animation->setStartValue(1);
    animation->setEndValue(0);
    animation->start();
    connect(animation,SIGNAL(finished()),this,SLOT(hide()));
}
void InfiniteMode::AgainM(){
    emit AgainMM();
}
void InfiniteMode::Dead1(QString a,int mxco,int score2){
    if(condi==1){
        condi=0;
        EndAll();
        connect(dea,SIGNAL(Again()),this,SLOT(AgainM()));
        connect(dea,SIGNAL(B2main()),this,SLOT(on_Close1_clicked()));
        dea->show();
        dea->How(a,mxco,score2);
        QPropertyAnimation *animation = new QPropertyAnimation(dea, "windowOpacity");
        animation->setDuration(200);
        animation->setStartValue(0.5);
        animation->setEndValue(1);
        animation->start();
        connect(animation,SIGNAL(finished()),this,SLOT(hide()));}

}

