#ifndef COLORPUSHBUTTON_H
#define COLORPUSHBUTTON_H

#include <QPropertyAnimation>
#include <QPushButton>

class ColorPushButton : public QPushButton
{
    Q_OBJECT
    Q_PROPERTY(QColor color READ color WRITE setColor)

public:
    explicit ColorPushButton(QWidget *parent = nullptr);
    virtual ~ColorPushButton();

    virtual QColor color() const;
    virtual void setColor(const QColor &color);
    virtual void setColorAnim(const QColor &col);
    void setColorSettings(QColor mCol, QColor entCol, QColor leavCol, QColor pressCol, QColor relCol);

protected:
    virtual void enterEvent(QEvent *);
    virtual void leaveEvent(QEvent *);
    virtual void mousePressEvent(QMouseEvent *);
    virtual void mouseReleaseEvent(QMouseEvent *);

private:
    QColor m_color;
    QColor enterColor;
    QColor leaveColor;
    QColor pressColor;
    QColor releaseColor;
    QPropertyAnimation *animation = new QPropertyAnimation(this, "color");
};

#endif // COLORPUSHBUTTON_H
