#include "dead.h"
#include "ui_dead.h"

Dead::Dead(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Dead)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_TranslucentBackground);  //设置窗口背景透明
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinMaxButtonsHint);  //去掉窗口边框
    setWindowIcon(QIcon(":/BG/BG/myicon.png"));
    ui->Close1->installEventFilter(this);
    ui->AgainB->installEventFilter(this);
}
void Dead::mousePressEvent(QMouseEvent *event)
{

    if (ReleaseCapture()){
        SendMessage(HWND(winId()), WM_SYSCOMMAND, SC_MOVE + HTCAPTION, 0);}
}
Dead::~Dead()
{
    delete ui;
}
void Dead::How(QString a,int mxco,int score){
    ui->HowT->setText(a);
    ui->ScoreL->setText(QString::number(score));
    ui->ComboL->setText(QString::number(mxco));
    ui->Expl->setText(QString::number(score/10));
    if (QSqlDatabase::contains("qt_sql_default_connection"))
    {
        database2 = QSqlDatabase::database("qt_sql_default_connection");
    }
    else
    {
        database2 = QSqlDatabase::addDatabase("QSQLITE");
        database2.setDatabaseName("MyCaculate.db");
        database2.setUserName("QAQMoon");
        database2.setPassword("Mooon2Hans");
    }
    QSqlQuery query(QString(" SELECT * FROM UserInfo;"));
    int Lv,Ex,Co,MS;
    Ex=Lv=Co=MS=0;
    while(query.next()){
        Lv = query.value("Level").toInt();
        Ex = query.value("Exp").toInt();
        MS=query.value("MaxScore").toInt();
        Co=query.value("Counts").toInt();
    }
    qDebug()<<Lv<<Ex<<Co;
    Ex+=(score/10);
    while(Ex>=Lv*200){
        Ex-=Lv*200;
        Lv++;
    }
    Co++;
    if(score>MS){
        MS=score;
    }
    ui->label_8->setText("LV"+QString::number(Lv));
    ui->progressBar->setValue((double)Ex/(Lv*200)*100);
    QSqlQuery query2(QString(" UPDATE UserInfo SET Level = %1,Exp=%2,Counts=%3,MaxScore=%4;").arg(QString::number(Lv),QString::number(Ex),QString::number(Co),QString::number(MS)));
    query2.exec();
    database2.close();
}

bool Dead::eventFilter(QObject *obj, QEvent *event)
{
    switch (event->type()) {
    case QEvent::HoverEnter:
        if(obj==ui->Close1){
            ui->Close1->setStyleSheet("background-color: rgb(255, 183, 184);border-radius:9px;font-size:25px;");
        }
        if(obj==ui->AgainB){
            ui->AgainB->setStyleSheet("color: rgb(59, 59, 59);background-color: rgb(138, 255, 177);border-radius:10px;font-size:25px;");
        }
        break;
    case QEvent::HoverLeave:
        if(obj==ui->Close1){
            ui->Close1->setStyleSheet("background-color: rgb(255, 138, 140);border-radius:9px;font-size:25px;");

        }
        if(obj==ui->AgainB){
            ui->AgainB->setStyleSheet("color: rgb(59, 59, 59);background-color: rgb(215, 255, 220);border-radius:10px;font-size:25px;");
        }
        break;
    case QEvent::MouseButtonPress:
        if(obj==ui->Close1){
            ui->Close1->setStyleSheet("border-color: rgb(255, 138, 140);border-width:2px;border-style:solid;border-radius:9px;font-size:25px;");
        }
        if(obj==ui->AgainB){
            ui->AgainB->setStyleSheet("border-color:  rgb(138, 255, 177);border-width:2px;border-style:solid;border-radius:9px;font-size:25px;");
        }
        break;
    case QEvent::MouseButtonRelease:
        if(obj==ui->Close1){
            ui->Close1->setStyleSheet("background-color: rgb(255, 183, 184);border-radius:9px;font-size:25px;");
        }
        if(obj==ui->AgainB){
            ui->AgainB->setStyleSheet("color: rgb(59, 59, 59);background-color: rgb(138, 255, 177);border-radius:10px;font-size:25px;");
        }
        break;
    default:
        break;
    }
    return QWidget::eventFilter(obj, event);
}
void Dead::on_Close1_clicked()
{
    QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
    animation->setDuration(200);
    animation->setStartValue(1);
    animation->setEndValue(0);
    animation->start();
    connect(animation,SIGNAL(finished()),this,SLOT(hide()));
    emit B2main();
}


void Dead::on_AgainB_clicked()
{
    QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
    animation->setDuration(200);
    animation->setStartValue(1);
    animation->setEndValue(0);
    animation->start();
    emit Again();
    connect(animation,SIGNAL(finished()),this,SLOT(hide()));
}

