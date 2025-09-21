#include "mainwindow.h"
#include "Memory.h"
#include "commandswindow.h"
#include "cpu.h"
#include "ui_mainwindow.h"
#include <iostream>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

void MainWindow::halt() {
    ui->pushButton_2->setEnabled(false);
    ui->pushButton_4->setEnabled(false);
}

void MainWindow::updateRegisters(CPU *cpu) {
    int cycle = cpu->tick % 4;
    switch (cycle) {
        case 0:
            ui->label_10->setText("Увеличение (IC)");
        break;
        case 1:
            ui->label_10->setText("Выборка (IF)");
        break;
        case 2:
            ui->label_10->setText("Раскодирование (ID)");
        break;
        case 3:
            ui->label_10->setText("Выполнение (EX)");
        break;
    }
    ui->lcdNumber->display((double)cpu->stackPointer.to_ulong());
    ui->lcdNumber_3->display((double)cpu->aluOp1Reg.to_ulong());
    ui->lcdNumber_4->display((double)cpu->aluOp2Reg.to_ulong());
    ui->lcdNumber_2->display((double)cpu->instructionRegister.to_ulong());
    ui->lcdNumber_5->display((int)cpu->tick);
    ui->listWidget->clearSelection();
    ui->listWidget->selectionModel()->setCurrentIndex(ui->listWidget->model()->index((double)cpu->stackPointer.to_ulong(),0), QItemSelectionModel::SelectionFlag::Select);
}

void MainWindow::decodeLabel(QString text) {
    ui->label_8->setText(text);
}

void MainWindow::updateMemoryListbox(Memory *mem) {
    ui->listWidget->clear();
    std::bitset<4224> memoryBlock = mem->ramStorage;
    QList<QString> cells = QList<QString>();
    for (std::size_t i = 0; i < memoryBlock.size(); i += 33) {
        QString new_item;
        for (std::size_t j = 0; j < 33; j++) {
            new_item.append(std::to_string(memoryBlock[i+j]));
        }
        std::reverse(new_item.begin(), new_item.end());
        cells.append(QString::fromStdString(std::to_string(i/33)) + ": " + new_item);
    }
    ui->listWidget->insertItems(0, cells);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    emit loadDefaultProgram();
}


void MainWindow::on_pushButton_3_clicked()
{
    CommandsWindow *w = new CommandsWindow;
    w->show();
}


void MainWindow::on_pushButton_2_clicked()
{
    emit oneTick();
}


void MainWindow::on_pushButton_4_clicked()
{
    for (int i=0; i<4; i++) emit oneTick();
}


void MainWindow::on_pushButton_5_clicked()
{
    ui->pushButton_2->setEnabled(true);
    ui->pushButton_4->setEnabled(true);
    emit memReset();
    emit cpuReset();
}

