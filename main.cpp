#include "system.h"
#include "mainwindow.h"
#include <QThread>
#include <iostream>
#include <QApplication>

int main(int argc, char *argv[])
{
    System *system = new System();
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    QThread *logicThr = new QThread;
    system->moveToThread(logicThr);
    //QObject::connect(logicThr, &QThread::started, system, &System::run);
    QObject::connect(system->memory, &Memory::updateMemoryUI, &w, &MainWindow::updateMemoryListbox);
    QObject::connect(&w, &MainWindow::loadDefaultProgram, system, &System::loadDefaultProgram);
    QObject::connect(system, &System::sendUpdateRegisterUI, &w, &MainWindow::updateRegisters);
    QObject::connect(system, &System::decodeLabel, &w, &MainWindow::decodeLabel);
    QObject::connect(&w, &MainWindow::oneTick, system, &System::run);
    logicThr->start();



    int result = a.exec();
    logicThr->quit();
    return result;
}
