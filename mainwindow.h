#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "mybutton.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void setColors();
private slots:
    void on_btnStart_clicked();
    void onBlockClicked();
    void setDefaultStyle();
    void clearColors();

private:
    MyButton* prev =  nullptr, *currentButton, ***button;
    QString defaultStyle = "border-radius: 10px;background-color: rgb(225, 225, 225);";
    int size, pairCounter;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
