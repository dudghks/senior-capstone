#include "blocktextedit.h"
#include <QScrollBar>

BlockTextEdit::BlockTextEdit(QWidget *parent) : QTextEdit(parent)
{

}

void BlockTextEdit::customSetViewportMargins(int left, int top, int right, int bottom) {
    setViewportMargins(left, top, right, bottom);
}

void BlockTextEdit::customSetViewportMargins(const QMargins & margins) {
    setViewportMargins(margins);
}

void BlockTextEdit::setScrollBarToEdge()
{
    QScrollBar *scrollBar = verticalScrollBar();
    QWidget *centralWidget = qobject_cast<QWidget*>(parent());
    if (centralWidget)
    {
        QPoint topLeft = mapTo(centralWidget, QPoint(0, 0));
        int x = centralWidget->width() - scrollBar->width() - topLeft.x();
        int y = scrollBar->y() - topLeft.y();
        scrollBar->move(x, y);
    }
}
