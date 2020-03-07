#include "mybutton.h"

MyButton::MyButton(QWidget *parent)
    : QPushButton(parent)
{

}

MyButton::~MyButton()
{

}

bool MyButton::isActive() const
{
    return active;
}

void MyButton::setActive(bool value)
{
    active = value;
}

bool MyButton::isOccupied() const
{
    return occupied;
}

void MyButton::setOccupied(bool value)
{
    occupied = value;
}

QColor MyButton::getBgColor() const
{
    return bgColor;
}

void MyButton::setBgColor(const QColor &value)
{
    bgColor = value;
}

