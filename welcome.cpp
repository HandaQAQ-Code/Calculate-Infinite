#include "welcome.h"
#include "ui_welcome.h"

Welcome::Welcome(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Welcome)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_TranslucentBackground);  //设置窗口背景透明
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinMaxButtonsHint);  //去掉窗口边框
    setWindowIcon(QIcon(":/BG/BG/myicon.png"));
    ui->Goo->installEventFilter(this);
    ui->Goo->setStyleSheet("border-image: url(:/BG/BG/Sure.png);");
    ui->Close->installEventFilter(this);
}
bool Welcome::eventFilter(QObject *obj, QEvent *event)
{
    switch (event->type()) {
    case QEvent::HoverEnter:
        if(obj==ui->Close){
            ui->Close->setStyleSheet("background-color: rgb(255, 183, 184);border-radius:9px;");

        }
        break;
        ui->Goo->setStyleSheet("border-image: url(:/BG/BG/SureH.png);");
        break;
    case QEvent::HoverLeave:
        if(obj==ui->Close){
            ui->Close->setStyleSheet("background-color: rgb(255, 138, 140);border-radius:9px;");

        }
        ui->Goo->setStyleSheet("border-image: url(:/BG/BG/Sure.png);");
        break;
    case QEvent::MouseButtonPress:
        if(obj==ui->Goo){
            ui->Goo->setStyleSheet("border-image: url(:/BG/BG/Pressed.png);");
        }
        break;
    case QEvent::MouseButtonRelease:
        if(obj==ui->Goo){
            ui->Goo->setStyleSheet("border-image: url(:/BG/BG/Sure.png);");}
        break;
    default:
        break;
    }
    return QWidget::eventFilter(obj, event);
}

Welcome::~Welcome()
{
    delete ui;
}

void Welcome::on_Close_clicked()
{
    QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
    animation->setDuration(200);
    animation->setStartValue(1);
    animation->setEndValue(0);
    animation->start();
    connect(animation, SIGNAL(finished()), this, SLOT(close()));
}

void Welcome::mousePressEvent(QMouseEvent *event)
{

    if (ReleaseCapture()){
        SendMessage(HWND(winId()), WM_SYSCOMMAND, SC_MOVE + HTCAPTION, 0);}
}
void Welcome::on_Header_clicked()
{
    if(index1==3){
        ui->Header->setStyleSheet("border-image: url(:/BG/BG/boss_4.jpg);");
        index1=4;
        qDebug()<<index1;
    }
    else if(index1==4){
        ui->Header->setStyleSheet("border-image: url(:/BG/BG/boss_5.jpg);");
        index1=5;
    }
    else if(index1==5){
        ui->Header->setStyleSheet("border-image: url(:/BG/BG/boss_6.jpg);");
        index1=6;
    }
    else if(index1==6){
        ui->Header->setStyleSheet("border-image: url(:/BG/BG/boss_1.jpg);");
        index1=1;
    }
    else if(index1==1){
        ui->Header->setStyleSheet("border-image: url(:/BG/BG/boss_2.jpg);");
        index1=2;
    }
    else if(index1==2){
        ui->Header->setStyleSheet("border-image: url(:/BG/BG/boss_3.jpg);");
        index1=3;
    }
}

void Welcome::on_Goo_clicked()
{
    if(ui->lineEdit->text().isEmpty()){
        QMessageBox MyBox(QMessageBox::Warning,"Warning","You Havn't Enter Your Name",QMessageBox::Ok);
        MyBox.exec();
    }
    else{
        database = QSqlDatabase::addDatabase("QSQLITE");
        database.setDatabaseName("MyCaculate.db");
        database.setUserName("QAQMoon");
        database.setPassword("Mooon2Hans");
        if (database.open())
        {
            qDebug() << "Database opened successfully！";
        }
        else
        {
            QMessageBox MyBox(QMessageBox::Critical,"Warning","Critical Failure",QMessageBox::Ok);
            MyBox.exec();
            this->close();
            qApp->quit();
        }
        QSqlQuery query;
        query.exec(QString("CREATE TABLE 'UserInfo' ('Name'	TEXT,'Header'  INTEGER,'Level'	INTEGER,'Exp' INTEGER,'Counts' INTEGER,'MaxScore' INTEGER)"));
        QSqlQuery query2;
        query2.exec(QString("INSERT INTO UserInfo VALUES('%1','%2','1','0','0','0')").arg(ui->lineEdit->text(),QString::number(index1)));
        emit Go();
        QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
        animation->setDuration(200);
        animation->setStartValue(1);
        animation->setEndValue(0);
        animation->start();
        connect(animation, SIGNAL(finished()), this, SLOT(close()));
    }
}

