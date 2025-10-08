#ifndef SETTING_H
#define SETTING_H

#pragma comment(lib, "user32.lib")
#include<QSoundEffect>
#include <qt_windows.h>
#include <QMainWindow>
#include <QPropertyAnimation>
#include<QTimer>
#include <QtSql/QSqlDatabase.h>
#include <QtSql/QSqlQuery.h>
#include <QtMultimedia/QMediaPlayer>
#include<QtMultimedia/QAudioOutput>
#include<QRandomGenerator>
namespace Ui {
class Setting;
}

class Setting : public QMainWindow
{
    Q_OBJECT
signals:
    void subClose();
public:
    float Value=1;
    float Volume=1;
    QMediaPlayer *player=new QMediaPlayer(this);
    QAudioOutput *AO=new QAudioOutput(this);
    void Up2Date();
    bool eventFilter(QObject *obj, QEvent *event);
    void mousePressEvent(QMouseEvent *event);
    explicit Setting(QWidget *parent = nullptr);
    ~Setting();

private slots:
    void on_Close_clicked();

    void on_Volume_valueChanged(int value);


    void on_Volume_2_sliderReleased();

private:
    QSqlDatabase database;
    QSqlQuery *sqlQuery;
    Ui::Setting *ui;
};

#endif // SETTING_H
