#ifndef DEAD_H
#define DEAD_H
#pragma comment(lib, "user32.lib")
#include <qt_windows.h>
#include <QtSql/QSqlDatabase.h>
#include <QtSql/QSqlQuery.h>
#include <QMainWindow>
#include <QPropertyAnimation>
namespace Ui {
class Dead;
}

class Dead : public QMainWindow
{
    Q_OBJECT

public:
    void How(QString a,int mxco,int score);
    bool eventFilter(QObject *obj, QEvent *event);
    explicit Dead(QWidget *parent = nullptr);
    ~Dead();
signals:
    void Again();
    void B2main();
private slots:
    void on_Close1_clicked();
    void mousePressEvent(QMouseEvent *event);
    void on_AgainB_clicked();

private:
    QSqlDatabase database2;
    Ui::Dead *ui;
};


#endif // DEAD_H
