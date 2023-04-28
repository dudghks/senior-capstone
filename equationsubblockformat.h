#ifndef EQUATIONSUBBLOCKFORMAT_H
#define EQUATIONSUBBLOCKFORMAT_H

#include <QTextFrameFormat>
#include <QStyleOptionGraphicsItem>
#include <QToolButton>

class EquationSubBlockFormat : public QTextFrameFormat
{
public:
    EquationSubBlockFormat();
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* parent = nullptr);

private:
    QToolButton* m_editButton;
};

#endif // EQUATIONSUBBLOCKFORMAT_H
