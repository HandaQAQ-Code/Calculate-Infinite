#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#pragma comment(lib, "user32.lib")
#include <qt_windows.h>
#include <QMainWindow>
#include <QPropertyAnimation>
#include<QTimer>
#include <QtSql/QSqlDatabase.h>
#include <QtSql/QSqlQuery.h>
#include "welcome.h"
#include "infinitemode.h"
#include "setting.h"
#include"dead.h"
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    void mousePressEvent(QMouseEvent *event);
    bool eventFilter(QObject *obj, QEvent *event);
    void ShowA();
    void OnFinished(QNetworkReply *reply);
    ~MainWindow();
public slots:


private slots:
    void linkDatabase();

    void on_Ads_clicked();

    void on_Infinite_clicked();

    void on_Close_clicked();

    void on_Setting_clicked();

    void on_Story_clicked();

    void on_Online_clicked();

private:
    int maxS=0;
    QSqlDatabase database;
    QSqlQuery *sqlQuery;
    QNetworkAccessManager *YIY;
    InfiniteMode *in=new InfiniteMode();
    Welcome *Wel=new Welcome();
    Setting *Set=new Setting();
    Ui::MainWindow *ui;
    Dead *dea =new Dead();
};
#endif // MAINWINDOW_H
