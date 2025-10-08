#ifndef WELCOME_H
#define WELCOME_H
#pragma comment(lib, "user32.lib")1
#include <qt_windows.h>
#include <QPropertyAnimation>
#include <QMainWindow>
#include <QtSql/QSqlDatabase.h>
#include <QtSql/QSqlQuery.h>
#include <QMessageBox>
#include<QPainter>
#include<QPixmap>
#include<QPainterPath>
#include<QFileDialog>
#include <QApplication>
namespace Ui {
class Welcome;
}

class Welcome : public QMainWindow
{
    Q_OBJECT

public:

    void mousePressEvent(QMouseEvent *event);
    explicit Welcome(QWidget *parent = nullptr);
    QPixmap getRoundRectPixmap(QPixmap srcPixMap, const QSize & size, int radius);
    ~Welcome();
     bool eventFilter(QObject *obj, QEvent *event);

private slots:
    void on_Close_clicked();

    void on_Header_clicked();
    void on_Goo_clicked();

signals:
    void Go();
private:
    QSqlDatabase database;
    QSqlQuery *sqlQuery;
    int index1 =3;
    Ui::Welcome *ui;
};

#endif // WELCOME_H
