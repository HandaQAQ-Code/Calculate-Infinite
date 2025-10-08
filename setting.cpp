#include "setting.h"
#include "ui_setting.h"

#include <QSettings>

Setting::Setting(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Setting)
{

    ui->setupUi(this);
    setAttribute(Qt::WA_TranslucentBackground);  //设置窗口背景透明
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinMaxButtonsHint);  //去掉窗口边框
    setWindowIcon(QIcon(":/BG/BG/myicon.png"));
    ui->Close->installEventFilter(this);
    QSettings *configIniRead = new QSettings("Config.ini", QSettings::IniFormat);
    Value = configIniRead->value("BVolume").toInt();
    ui->Volume->setValue(Value);
    Volume=(double)configIniRead->value("EVolume").toInt() /100;
    ui->Volume_2->setValue(Volume*100);
    delete configIniRead;
    AO->setVolume(Value);
    player->setAudioOutput(AO);
    player->setSource(QUrl("qrc:/Music/Ms/MainUI.mp3"));
    player->play();
}
void Setting::Up2Date(){
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
    QString name="";
    int index1,Level1,Exp1,count1=0;
    QSqlQuery query(QString(" SELECT * FROM UserInfo;"));
    while(query.next()){
        name = query.value("Name").toString();
        index1 = query.value("Header").toInt();
        Level1 = query.value("Level").toInt();
        Exp1 = query.value("Exp").toInt();
        count1=query.value("Counts").toInt();
    }
    ui->Namee->setText(name);
    if(index1==3){
        ui->Header->setStyleSheet("border-image: url(:/BG/BG/boss_3.jpg);");
    }
    else if(index1==4){
        ui->Header->setStyleSheet("border-image: url(:/BG/BG/boss_4.jpg);");
    }
    else if(index1==5){
        ui->Header->setStyleSheet("border-image: url(:/BG/BG/boss_5.jpg);");
    }
    else if(index1==6){
        ui->Header->setStyleSheet("border-image: url(:/BG/BG/boss_6.jpg);");
    }
    else if(index1==1){
        ui->Header->setStyleSheet("border-image: url(:/BG/BG/boss_1.jpg);");
    }
    else if(index1==2){
        ui->Header->setStyleSheet("border-image: url(:/BG/BG/boss_2.jpg);");
    }
    ui->Level->setText("LV "+QString::number(Level1));
    ui->Exp->setText("Next level " +QString::number(Level1*200-Exp1)+"EXP");
    ui->progressBar->setValue(Exp1*100/(Level1*200)*100);
    ui->Level_2->setText("Played "+QString::number(count1)+" Times");
}
void Setting::mousePressEvent(QMouseEvent *event)
{

    if (ReleaseCapture()){
        SendMessage(HWND(winId()), WM_SYSCOMMAND, SC_MOVE + HTCAPTION, 0);}
}
Setting::~Setting()
{
    delete ui;
}
bool Setting::eventFilter(QObject *obj, QEvent *event)
{
    switch (event->type()) {
    case QEvent::HoverEnter:
        if(obj==ui->Close){
            ui->Close->setStyleSheet("background-color: rgb(255, 183, 184);border-radius:9px;");

        }
        break;
    case QEvent::HoverLeave:
        if(obj==ui->Close){
            ui->Close->setStyleSheet("background-color: rgb(255, 138, 140);border-radius:9px;");

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
void Setting::on_Close_clicked()
{
    emit subClose();
    QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
    animation->setDuration(200);
    animation->setStartValue(1);
    animation->setEndValue(0);
    animation->start();
    connect(animation, SIGNAL(finished()), this, SLOT(hide()));
}


void Setting::on_Volume_valueChanged(int value)
{

    QSettings *configIniWrite = new QSettings("Config.ini", QSettings::IniFormat);
    configIniWrite->setValue("BVolume", value);
    delete configIniWrite;
    Value=(double)value/100;
    AO->setVolume(Value);
}


void Setting::on_Volume_2_sliderReleased()
{
    int value = ui->Volume_2->value();
    QSettings *configIniWrite = new QSettings("Config.ini", QSettings::IniFormat);
    configIniWrite->setValue("EVolume", value);
        delete configIniWrite;
    Volume=(double)value/100;
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

