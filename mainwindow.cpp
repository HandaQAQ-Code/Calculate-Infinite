#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
    animation->setDuration(200);
    animation->setStartValue(0);
    animation->setEndValue(1);
    animation->start();
    ui->Close->installEventFilter(this);
    ui->Infinite->installEventFilter(this);
    ui->Setting->installEventFilter(this);
    ui->Story->installEventFilter(this);
    ui->Online->installEventFilter(this);
    setAttribute(Qt::WA_TranslucentBackground);  //设置窗口背景透明
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinMaxButtonsHint);  //去掉窗口边框
    setWindowIcon(QIcon(":/BG/BG/myicon.png"));
    linkDatabase();
    YIY = new QNetworkAccessManager(this);
    connect(YIY,&QNetworkAccessManager::finished,this,&MainWindow::OnFinished);
    QUrl url("https://api.vvhan.com/api/dailyEnglish?type=sj");
    // 使用 get 请求方式
    YIY->get(QNetworkRequest(url));
    connect(in,SIGNAL(AgainMM()),this,SLOT(on_Infinite_clicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::OnFinished(QNetworkReply *reply)

{  // 状态码：响应成功为 200
    int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    if(reply->error() != QNetworkReply::NoError || statusCode != 200)
    {

    }
    else
    {
        QStringList a;
        QByteArray byteArray = reply->readAll();
        if(byteArray.isEmpty()){

        }
        else{
        int p,q;
        p=1;
        for(int i=0;i<byteArray.size();i++){
            if(byteArray[i]=='\n'){
                q=i;
                QString string = QString::fromUtf8(byteArray.mid(p,q),q-p);
                a.append(string);
                p=q;
            }
        }
        QString Ju =a[4];
        QStringList a2;
        a2=Ju.split("\"");
        ui->Yiyan->setText(a2[3]);
        }
    }
    // 必须释放内存，否则会造成内存泄露
    reply->deleteLater();

}
void MainWindow::mousePressEvent(QMouseEvent *event)
{

    if (ReleaseCapture()){
        SendMessage(HWND(winId()), WM_SYSCOMMAND, SC_MOVE + HTCAPTION, 0);}
}
bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    switch (event->type()) {
    case QEvent::HoverEnter:
        if(obj==ui->Close){
            ui->Close->setStyleSheet("background-color: rgb(255, 183, 184);border-radius:9px;");
        }
        if(obj==ui->Infinite){
            QPropertyAnimation *animation = new QPropertyAnimation(ui->Infinite, "geometry");
            animation->setDuration(200);
            animation->setStartValue(QRect(510,230,181,187));
            animation->setEndValue(QRect(510-5,230-5,181+10,187+10));
            animation->setEasingCurve(QEasingCurve::OutBack);
            animation->start();}
        if(obj==ui->Setting){
            QPropertyAnimation *animation = new QPropertyAnimation(ui->Setting, "geometry");
            animation->setDuration(500);
            animation->setStartValue(QRect(510,460,181,185));
            animation->setEndValue(QRect(510-5,460-5,181+10,185+10));
            animation->setEasingCurve(QEasingCurve::OutBounce);
            animation->start();}
        if(obj==ui->Online){
            QPropertyAnimation *animation = new QPropertyAnimation(ui->Online, "geometry");
            animation->setDuration(500);
            animation->setStartValue(QRect(280,460,181,185));
            animation->setEndValue(QRect(280-5,460-5,181+10,185+10));
            animation->setEasingCurve(QEasingCurve::OutBounce);
            animation->start();}
        if(obj==ui->Story){
            QPropertyAnimation *animation = new QPropertyAnimation(ui->Story, "geometry");
            animation->setDuration(500);
            animation->setStartValue(QRect(280,230,181,201));
            animation->setEndValue(QRect(280-5,230-5,181+10,201+10));
            animation->setEasingCurve(QEasingCurve::OutBounce);
            animation->start();}

        break;
    case QEvent::HoverLeave:
        if(obj==ui->Close){
            ui->Close->setStyleSheet("background-color: rgb(255, 138, 140);border-radius:9px;");
        }
        if(obj==ui->Infinite){
            QPropertyAnimation *animation = new QPropertyAnimation(ui->Infinite, "geometry");
            animation->setDuration(200);
            animation->setEndValue(QRect(510,230,181,187));
            animation->setStartValue(QRect(510-5,230-5,181+10,187+10));
            animation->setEasingCurve(QEasingCurve::OutBack);
            animation->start();}
        if(obj==ui->Setting){
            QPropertyAnimation *animation = new QPropertyAnimation(ui->Setting, "geometry");
            animation->setDuration(500);
            animation->setEndValue(QRect(510,460,181,185));
            animation->setStartValue(QRect(510-5,460-5,181+10,185+10));
            animation->setEasingCurve(QEasingCurve::OutBounce);
            animation->start();}
        if(obj==ui->Online){
            QPropertyAnimation *animation = new QPropertyAnimation(ui->Online, "geometry");
            animation->setDuration(500);
            animation->setEndValue(QRect(280,460,181,185));
            animation->setStartValue(QRect(280-5,460-5,181+10,185+10));
            animation->setEasingCurve(QEasingCurve::OutBounce);
            animation->start();}
        if(obj==ui->Story){
            QPropertyAnimation *animation = new QPropertyAnimation(ui->Story, "geometry");
            animation->setDuration(500);
            animation->setEndValue(QRect(280,230,181,201));
            animation->setStartValue(QRect(280-5,230-5,181+10,201+10));
            animation->setEasingCurve(QEasingCurve::OutBounce);
            animation->start();}
        break;
    case QEvent::MouseButtonPress:
        if(obj==ui->Infinite){
            QPropertyAnimation *animation = new QPropertyAnimation(ui->Infinite, "geometry");
            animation->setDuration(200);
            animation->setStartValue(QRect(510,230,181,187));
            animation->setEndValue(QRect(510+10,230+10,181-20,187-20));
            animation->setEasingCurve(QEasingCurve::OutBack);
            animation->start();}
        if(obj==ui->Setting){
            QPropertyAnimation *animation = new QPropertyAnimation(ui->Setting, "geometry");
            animation->setDuration(500);
            animation->setStartValue(QRect(510,460,181,185));
            animation->setEndValue(QRect(510+10,460+10,181-20,185-20));
            animation->setEasingCurve(QEasingCurve::OutBounce);
            animation->start();}
        if(obj==ui->Online){
            QPropertyAnimation *animation = new QPropertyAnimation(ui->Online, "geometry");
            animation->setDuration(500);
            animation->setStartValue(QRect(280,460,181,185));
            animation->setEndValue(QRect(280+10,460+10,181-20,185-20));
            animation->setEasingCurve(QEasingCurve::OutBounce);
            animation->start();}
        if(obj==ui->Story){
            QPropertyAnimation *animation = new QPropertyAnimation(ui->Story, "geometry");
            animation->setDuration(500);
            animation->setStartValue(QRect(280,230,181,201));
            animation->setEndValue(QRect(280+10,230+10,181-20,201-20));
            animation->setEasingCurve(QEasingCurve::OutBounce);
            animation->start();}

        break;
    case QEvent::MouseButtonRelease:
        if(obj==ui->Infinite){
            QPropertyAnimation *animation = new QPropertyAnimation(ui->Infinite, "geometry");
            animation->setDuration(500);
            animation->setEndValue(QRect(510,230,181,187));
            animation->setStartValue(QRect(510+10,230+10,181-20,187-20));
            animation->setEasingCurve(QEasingCurve::OutBounce);
            animation->start();}
        if(obj==ui->Setting){
            QPropertyAnimation *animation = new QPropertyAnimation(ui->Setting, "geometry");
            animation->setDuration(500);
            animation->setEndValue(QRect(510,460,181,185));
            animation->setStartValue(QRect(510+10,460+10,181-20,185-20));
            animation->setEasingCurve(QEasingCurve::OutBounce);
            animation->start();}
        if(obj==ui->Online){
            QPropertyAnimation *animation = new QPropertyAnimation(ui->Online, "geometry");
            animation->setDuration(500);
            animation->setEndValue(QRect(280,460,181,185));
            animation->setStartValue(QRect(280+10,460+10,181-20,185-20));
            animation->setEasingCurve(QEasingCurve::OutBounce);
            animation->start();}
        if(obj==ui->Story){
            QPropertyAnimation *animation = new QPropertyAnimation(ui->Story, "geometry");
            animation->setDuration(500);
            animation->setEndValue(QRect(280,230,181,201));
            animation->setStartValue(QRect(280+10,230+10,181-20,201-20));
            animation->setEasingCurve(QEasingCurve::OutBounce);
            animation->start();}

        break;
    default:
        break;
    }
    return QWidget::eventFilter(obj, event);
}

void MainWindow::on_Ads_clicked()
{
    QPropertyAnimation *animation = new QPropertyAnimation(ui->Ads, "geometry");
    animation->setDuration(500);
    animation->setEndValue(QRect(280,-430,411,421));
    animation->setStartValue(QRect(280,220,411,421));
    animation->setEasingCurve(QEasingCurve::InOutBack);
    animation->start();
}


void MainWindow::on_Infinite_clicked()
{
    linkDatabase();
    in->show();
    in->SetVolume(Set->Volume);
    in->Don=3;
    in->Mac=maxS;
    in->ContDown();
    connect(in,&InfiniteMode::subClose,this,&MainWindow::ShowA);//关联子窗体关闭信号与父窗体显示事件
    QPropertyAnimation *animation = new QPropertyAnimation(in, "windowOpacity");
    animation->setDuration(200);
    animation->setStartValue(0.5);
    animation->setEndValue(1);
    animation->start();
    connect(animation,SIGNAL(finished()),this,SLOT(hide()));
}

void MainWindow::ShowA(){
    QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
    animation->setDuration(200);
    animation->setStartValue(0);
    animation->setEndValue(1);
    animation->start();
    this->show();
}
void MainWindow::on_Close_clicked()
{
    QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
    animation->setDuration(200);
    animation->setStartValue(1);
    animation->setEndValue(0);
    animation->start();
    connect(animation, SIGNAL(finished()), this, SLOT(close()));
}

void MainWindow::linkDatabase()
{
    if (QSqlDatabase::contains("qt_sql_default_connection"))
    {
        database = QSqlDatabase::database("qt_sql_default_connection");
    }
    else
    {
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
            qDebug() << "无法打开数据库：" ;
        }
    }
    QSqlQuery query;
    bool isTableExist = query.exec(QString("select * from UserInfo where Name"));
    if(!isTableExist){
        Wel->show();
        connect(Wel,&Welcome::Go,this,&MainWindow::ShowA);//关联子窗体关闭信号与父窗体显示事件
        QPropertyAnimation *animation = new QPropertyAnimation(in, "windowOpacity");
        animation->setDuration(200);
        animation->setStartValue(0.5);
        animation->setEndValue(1);
        animation->start();
        connect(animation,SIGNAL(finished()),this,SLOT(hide()));
    } else{
        QSqlQuery query(QString(" SELECT * FROM UserInfo;"));
        while(query.next()){
            maxS=query.value("MaxScore").toInt();
        }
    }
}


void MainWindow::on_Setting_clicked()
{

    Set->show();
    Set->Up2Date();
    connect(Set,&Setting::subClose,this,&MainWindow::ShowA);//关联子窗体关闭信号与父窗体显示事件
    QPropertyAnimation *animation = new QPropertyAnimation(Set, "windowOpacity");
    animation->setDuration(200);
    animation->setStartValue(0.5);
    animation->setEndValue(1);
    animation->start();
    connect(animation,SIGNAL(finished()),this,SLOT(hide()));
}


void MainWindow::on_Story_clicked()
{
    QPropertyAnimation *animation = new QPropertyAnimation(ui->Ads, "geometry");
    animation->setDuration(500);
    animation->setStartValue(QRect(280,-430,411,421));
    animation->setEndValue(QRect(280,220,411,421));
    animation->setEasingCurve(QEasingCurve::OutBack);
    animation->start();
}


void MainWindow::on_Online_clicked()
{

    QPropertyAnimation *animation = new QPropertyAnimation(ui->Ads, "geometry");
    animation->setDuration(500);
    animation->setStartValue(QRect(280,-430,411,421));
    animation->setEndValue(QRect(280,220,411,421));
    animation->setEasingCurve(QEasingCurve::OutBack);
    animation->start();
}

