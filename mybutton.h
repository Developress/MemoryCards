#ifndef MYBUTTON_H
#define MYBUTTON_H

#include <QPushButton>
#include <qtimer.h>



class MyButton : public QPushButton
    {
    Q_OBJECT

public:
    MyButton(QWidget *parent = 0);
    ~MyButton();

public:
    QColor bgColor;
    bool occupied = false;
    bool active = true;
    QColor getBgColor() const;
    void setBgColor(const QColor &value);
    bool isOccupied() const;
    void setOccupied(bool value);
    bool isActive() const;
    void setActive(bool value);

};
#endif // MYBUTTON_H
