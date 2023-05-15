#include "colorlineedit.h"

ColorLineEdit::ColorLineEdit(QWidget *parent) : QLineEdit(parent)
{
    bW = 0;
    m_color = "#171717";
}

ColorLineEdit::~ColorLineEdit()
{
    delete animation;
}

QColor ColorLineEdit::color() const
{
    return m_color;
}

void ColorLineEdit::setColor(const QColor &color)
{
    m_color = color;
    setStyleSheet(QString("QLineEdit { background-color: %1; border: %2px solid; border-color: %3; }").arg(m_color.name(), QString::number(bW), b_color.name()));
}

void ColorLineEdit::setColorAnim(const QColor &col)
{
    animation->setDuration(200);
    animation->setStartValue(QColor(color()));
    animation->setEndValue(col);
    animation->start();
}

void ColorLineEdit::setBColor(const QColor &color)
{
    b_color = color;
}

void ColorLineEdit::setBW(const int &px)
{
    bW = px;
}

void ColorLineEdit::errorMode()
{
    bW = 1;
    b_color = "#ff0303";
    setColor(color());
}

void ColorLineEdit::enterEvent(QEvent *)
{   
    if (!this->hasFocus())
    {
        setColorAnim("#2C3D82");
    }
}

void ColorLineEdit::leaveEvent(QEvent *)
{
    if (!this->hasFocus())
    {
        setColorAnim("#171717");
    }
}

void ColorLineEdit::focusOutEvent(QFocusEvent *e)
{
    if (b_color == "#ff0303" && bW == 1)
    {
        b_color = "#000";
        bW = 0;
    }

    QLineEdit::focusOutEvent(e);
    setColorAnim("#171717");
}

void ColorLineEdit::focusInEvent(QFocusEvent *e)
{
    if (b_color == "#ff0303" && bW == 1)
    {
        b_color = "#000";
        bW = 0;
    }

    QLineEdit::focusInEvent(e);
    setColorAnim("#fff");
}
