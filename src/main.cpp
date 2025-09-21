#include "system.h"
#include "mainwindow.h"
#include <QThread>
#include <iostream>
#include <QApplication>
#include "cpu.h"

void connectSignals(MainWindow *w, System *system, QThread *logicThr) {
    QObject::connect(system->memory, &Memory::updateMemoryUI, w, &MainWindow::updateMemoryListbox);
    QObject::connect(w, &MainWindow::loadDefaultProgram, system, &System::loadDefaultProgram);
    QObject::connect(w, &MainWindow::cpuReset, system->cpu, &CPU::cpuReset);
    QObject::connect(w, &MainWindow::memReset, system->memory, &Memory::memReset);
    QObject::connect(system, &System::sendUpdateRegisterUI, w, &MainWindow::updateRegisters);
    QObject::connect(system->cpu, &CPU::updateRegisters, w, &MainWindow::updateRegisters);
    QObject::connect(system, &System::decodeLabel, w, &MainWindow::decodeLabel);
    QObject::connect(system, &System::halt, w, &MainWindow::halt);
    QObject::connect(w, &MainWindow::oneTick, system, &System::run);
    QObject::connect(logicThr, &QThread::started, system, &System::started);
    QObject::connect(system, &System::updateMemoryUI, w, &MainWindow::updateMemoryListbox);
}

int main(int argc, char *argv[])
{
    System *system = new System();
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    QThread *logicThr = new QThread;
    system->moveToThread(logicThr);
    //QObject::connect(logicThr, &QThread::started, system, &System::run);
    connectSignals(&w, system, logicThr);
    logicThr->start();



    int result = a.exec();
    logicThr->quit();
    return result;
}
