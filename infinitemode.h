#ifndef INFINITEMODE_H
#define INFINITEMODE_H
#pragma comment(lib, "user32.lib")
#include<QSoundEffect>
#include <qt_windows.h>
#include <QMainWindow>
#include<QPropertyAnimation>
#include<QIntValidator>
#include<QRandomGenerator>
#include <qtimer.h>
#include<QKeyEvent>
#include"dead.h"
namespace Ui {
class InfiniteMode;
}

class InfiniteMode : public QMainWindow
{
    Q_OBJECT

public:
    int Mac=0;
    int Don=3;
    explicit InfiniteMode(QWidget *parent = nullptr);
    int Combo;
    int Score;
    float Volume=1;
    int MCo;
    bool En;
    bool En2=false;
    int MSc;
    ~InfiniteMode();
public slots:
    void ContDown();
    void ContDownSub();
    void StartGame(int a);
    void SetVolume(float a);
    void EndAll();
signals:
    void subClose();
    void AgainMM();
private slots:
    void Randon();
    void AgainM();
    void Visible();
    void Count();
    void FixCount();
    void FixSub();
    void on_Close1_clicked();
    void Hun();
    void HunS();
    void HunE();
    void Incre();
    void IncreE();
    void Stop();
    void EndStop();
    void Fix();
    void FixE();
    void Dead1(QString a,int mxco,int score2);
    void keyPressEvent( QKeyEvent *key );
    void keyReleaseEvent( QKeyEvent * event);
    void mousePressEvent(QMouseEvent *event);
private:
    int condi=0;
    QString Answer="";
    int count;
    int score=0;
    int Combo1=0;
    int N1R;
    int N2R;
    int time = 100;
    int FSU=0;
    int V1,V2,V3,V4,VF,T;
    int FixTimeT=100;
    int FixTime=100;
    int UP=10;
    bool In =true;
    bool Fixx=false;
    int RestoP=100;
    int MaxCo=0;
    int set=2;
    QString Input;
    QTimer *timer  ;
    QTimer *timer2  ;
    QTimer *timer3  ;
    QTimer *StopTimer ;
    QTimer *HunFixTimer ;
    QTimer *IncresTimer ;
    QTimer *IncresETimer ;
    QTimer *HunETimer ;
    QTimer *ContTimer ;
    bool eventFilter(QObject *obj, QEvent *event);
    Ui::InfiniteMode *ui;
    Dead *dea =new Dead();
};

#endif // INFINITEMODE_H
