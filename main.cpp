#include "mainwindow.h"
#include<QFontDatabase>
#include <QApplication>
#include<QTranslator>
void setDefaultFont(QApplication *app){
    int loadedFontId = QFontDatabase::addApplicationFont(":/Font/font/chinese2.ttf");
    QStringList loadedFontFamilies = QFontDatabase::applicationFontFamilies(loadedFontId);
    for(int i =0 ; i < loadedFontFamilies.size() ; i++){
        QString sansCNFamily = loadedFontFamilies.at(i);
        if(i == 0 ){
            QFont defaultFont = (app)->font();
            //设置字体大小格式为pixel，字体占用固定像素。相同像素的大小屏，不会发生字体遮挡现象
            defaultFont.setFamily(sansCNFamily);
            (app)->setFont(defaultFont);
        }


    }
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    setDefaultFont(&a);
    MainWindow w;
    w.show();
    return a.exec();
}
