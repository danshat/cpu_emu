#include "commandswindow.h"
#include "ui_commandswindow.h"

CommandsWindow::CommandsWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CommandsWindow)
{
    ui->setupUi(this);
}

CommandsWindow::~CommandsWindow()
{
    delete ui;
}

void CommandsWindow::on_pushButton_6_clicked()
{
    this->close();
}

