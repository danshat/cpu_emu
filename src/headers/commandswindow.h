#ifndef COMMANDSWINDOW_H
#define COMMANDSWINDOW_H

#include <QWidget>

namespace Ui {
class CommandsWindow;
}

class CommandsWindow : public QWidget
{
    Q_OBJECT

public:
    explicit CommandsWindow(QWidget *parent = nullptr);
    ~CommandsWindow();

private slots:
    void on_pushButton_6_clicked();

private:
    Ui::CommandsWindow *ui;
};

#endif // COMMANDSWINDOW_H
