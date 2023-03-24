#ifndef BLOCKTEXTEDIT_H
#define BLOCKTEXTEDIT_H

#include <QTextEdit>

class BlockTextEdit : public QTextEdit
{
    Q_OBJECT
public:
    BlockTextEdit(QWidget *parent = nullptr);
    void customSetViewportMargins(int left, int top, int right, int bottom);
    void customSetViewportMargins(const QMargins & margins);
    void setScrollBarToEdge();
};

#endif // BLOCKTEXTEDIT_H
