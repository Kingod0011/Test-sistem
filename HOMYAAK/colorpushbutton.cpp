#include "colorpushbutton.h"

ColorPushButton::ColorPushButton(QWidget *parent) : QPushButton(parent)
{
    m_color = "#000";
    pressColor = "#000";
    releaseColor = "#fff";
    enterColor = QColor("#fff");
    leaveColor = QColor("#000");
}

ColorPushButton::~ColorPushButton()
{
    delete animation;
}

QColor ColorPushButton::color() const
{
    return m_color;
}

void ColorPushButton::setColor(const QColor &color)
{
    m_color = color;
    setStyleSheet(QString("QPushButton { background-color: %1 }").arg(m_color.name()));
}

void ColorPushButton::setColorAnim(const QColor &col)
{
    animation->setDuration(200);
    animation->setStartValue(QColor(color()));
    animation->setEndValue(col);
    animation->start();
}

void ColorPushButton::setColorSettings(QColor mCol = "#000", QColor entCol = "#fff", QColor leavCol = "#000", QColor pressCol = "#000", QColor relCol = "#fff")
{
    m_color = mCol;
    enterColor = entCol;
    leaveColor = leavCol;
    pressColor = pressCol;
    releaseColor = relCol;
}

void ColorPushButton::enterEvent(QEvent *)
{
    setStyleSheet("QPushButton { color: #fff }");
    animation->setDuration(200);
    animation->setStartValue(QColor(color()));
    animation->setEndValue(enterColor);
    animation->start();
}

void ColorPushButton::leaveEvent(QEvent *)
{
    animation->setDuration(200);
    animation->setStartValue(QColor(color()));
    animation->setEndValue(leaveColor);
    animation->start();
}

void ColorPushButton::mousePressEvent(QMouseEvent *e)
{
    QPushButton::mousePressEvent(e);
    animation->setDuration(100);
    animation->setStartValue(QColor(color()));
    animation->setEndValue(pressColor);
    animation->start();
    //setStyleSheet("QPushButton {color: #000}");
}

void ColorPushButton::mouseReleaseEvent(QMouseEvent *e)
{
    QPushButton::mouseReleaseEvent(e);
    animation->setDuration(100);
    animation->setStartValue(QColor(color()));
    animation->setEndValue(releaseColor);
    animation->start();
}
