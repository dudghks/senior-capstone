#ifndef EQUATIONSUBBLOCK_H
#define EQUATIONSUBBLOCK_H

#include <QTextFrame>
#include <QToolButton>
class EquationSubBlock : public QTextFrame
{
    Q_OBJECT

public:
    EquationSubBlock(QTextDocument* doc);

private:
    QToolButton* m_editButton;

};

#endif // EQUATIONSUBBLOCK_H