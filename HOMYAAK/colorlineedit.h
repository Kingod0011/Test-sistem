#ifndef COLORLINEEDIT_H
#define COLORLINEEDIT_H

#include <QLineEdit>
#include <QPropertyAnimation>

class ColorLineEdit : public QLineEdit
{
    Q_OBJECT
    Q_PROPERTY(QColor color READ color WRITE setColor)

public:
    explicit ColorLineEdit(QWidget *parent = nullptr);
    virtual ~ColorLineEdit();

    virtual QColor color() const;
    virtual void setColor(const QColor &color);
    void setColorAnim(const QColor &col);
    void setBColor(const QColor &color);
    void setBW(const int &px);
    void errorMode();

protected:
    virtual void enterEvent(QEvent *);
    virtual void leaveEvent(QEvent *);
    virtual void focusOutEvent(QFocusEvent *);
    virtual void focusInEvent(QFocusEvent *);

private:
    QColor m_color;
    int bW;
    QColor b_color;
    QPropertyAnimation *animation = new QPropertyAnimation(this, "color");
};

#endif // COLORLINEEDIT_H
