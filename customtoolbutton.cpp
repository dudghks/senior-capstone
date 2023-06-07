#include "customtoolbutton.h"
#include <QPainter>

CustomToolButton::CustomToolButton(QWidget* parent) : QToolButton(parent),
    m_color(0, 0, 0)
{

}

QColor CustomToolButton::color() {
    return m_color;
}

void CustomToolButton::setColor(QColor _color) {
    m_color = _color;
    repaint();
}

QRect CustomToolButton::colorArea() {
    return m_colorArea;
}

void CustomToolButton::setColorArea(QRect _colorArea) {
    m_colorArea = _colorArea;
    repaint();
}

bool CustomToolButton::border() {
    return m_border;
}

void CustomToolButton::setBorder(bool _border) {
    m_border = _border;
    repaint();
}

void CustomToolButton::paintEvent(QPaintEvent *event) {
    QPainter p(this);
    QBrush brush(m_color);

    p.setBrush(brush);
    p.drawRect(m_colorArea);

    if(!m_border) {
        QPen pen(Qt::transparent);
        p.setPen(pen);
    }
    QToolButton::paintEvent(event);
}
