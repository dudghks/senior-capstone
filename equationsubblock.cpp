#include "equationsubblock.h"

#include <QTextEdit>
#include <QTextBlock>
#include <QAbstractTextDocumentLayout>
EquationSubBlock::EquationSubBlock(QTextDocument *document) : QTextFrame(document) {
    m_editButton = new QToolButton();

}

QTextDocument* EquationSubBlock::document() {
    QTextFrame* rootFrame = this->parentFrame();
    // Find the Root frame of the document
    while(rootFrame->parentFrame() != 0) {
        rootFrame = rootFrame->parentFrame();
    }
    // Return the QTextDocument (parent of the root frame)
    return qobject_cast<QTextDocument*>(rootFrame->parent());
}

QRectF EquationSubBlock::boundingRect() {
    // Get the bounding rectangle of the frame
    QRectF frameRect = EquationSubBlock::document()->documentLayout()->frameBoundingRect(this);

    // Find the text editor associated with the document
    QTextEdit* textEditor = qobject_cast<QTextEdit*>(document()->parent());

    // Convert the frame-bounding rectangle coordinate system to the one of the text editor
    QPointF frameRectTopLeft = textEditor->viewport()->mapTo(textEditor, frameRect.topLeft());
    return QRectF(frameRectTopLeft, frameRect.size());
}
