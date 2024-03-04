/*
* @Author: Qianhua Liu
* @Date: 2024-03-03
* @Description: 
* @Note: Copyright (c) 2024, Qianhua Liu Inc., All rights reserved
*/
#include <QtWidgets/QApplication>
#include <QtCore/QDebug>

#include "gui/MainWindow.h"

int main(int argc, char* argv[]) {
    // QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);
    localminmax::gui::MainWindow w;
    // w.setWindowFlag(Qt::FramelessWindowHint);
    // w.setAttribute(Qt::WA_TranslucentBackground);
    w.show();
    return app.exec();
}