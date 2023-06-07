#ifndef CUSTOMTOOLBUTTON_H
#define CUSTOMTOOLBUTTON_H

#include <QToolButton>

class CustomToolButton : public QToolButton
{
    Q_OBJECT
public:
    CustomToolButton(QWidget* parent = nullptr);
    QColor color();
    void setColor(QColor _color);
    QRect colorArea();
    void setColorArea(QRect _colorArea);
    bool border();
    void setBorder(bool _border);
private:
    QColor m_color;
    QRect m_colorArea;
    bool m_border;

protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif // CUSTOMTOOLBUTTON_H
