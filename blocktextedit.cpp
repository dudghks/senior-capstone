// Multi-page display code adapted from @dimkanovikov on GitHub
// https://github.com/dimkanovikov/PagesTextEdit
// ^ Comments translated using Google Translate with some changes

#include "blocktextedit.h"
#include "subblockuserdata.h"
#include "codesubblocksettings.h"

#include <QScreen>
#include <QApplication>
#include <QAbstractTextDocumentLayout>
#include <QScrollBar>
#include <QPainter>
#include <QTextFrame>
#include <QToolButton>
#include <QLayout>
#include <QPushButton>
#include <QRegularExpression>
#include <QRegularExpressionMatchIterator>

BlockTextEdit::BlockTextEdit(QWidget *parent) : QTextEdit(parent),
    m_document(), m_codeHighlighter(this->document())
{
    // Prevents the document from automatically changing
    aboutDocumentChanged();
    connect(this, SIGNAL(textChanged()), this, SLOT(aboutDocumentChanged()));

    // Update the document layout when it changes (overrides QTextEdit default reset)
    connect(document()->documentLayout(), SIGNAL(update()), this, SLOT(aboutUpdateDocumentGeometry()));

    // Custom setting of the scroll interval
    connect(verticalScrollBar(), SIGNAL(rangeChanged(int,int)),
        this, SLOT(aboutVerticalScrollRangeChanged(int,int)));

    connect(m_document, &QTextDocument::contentsChange, this, &BlockTextEdit::handleContentsChange);
}


qreal BlockTextEdit::inchesToPixels(qreal inches, bool _x) {
    // Convert inches to pixel using physical screen size
    QScreen *screen = QApplication::primaryScreen();
    return inches * (_x ? screen->physicalDotsPerInchX() : screen->physicalDotsPerInchY());
}


void BlockTextEdit::setPixelPageSize(QSizeF _pageSize, bool _inches) {
    if(_inches) {
        _pageSize = QSizeF(inchesToPixels(_pageSize.width()), inchesToPixels(_pageSize.height(), false));
    }
    m_pixelPageSize = _pageSize;

    // Repaint after change
    repaint();
}


void BlockTextEdit::setPixelPageMargins(QMarginsF _pageMargins, bool _inches) {
    if(_inches) {
        _pageMargins = QMarginsF(inchesToPixels(_pageMargins.left()), inchesToPixels(_pageMargins.top(), false),
                                 inchesToPixels(_pageMargins.right()), inchesToPixels(_pageMargins.bottom(), false));
    }
    m_pixelPageMargins = _pageMargins;

    // Repaint after change
    repaint();
}

void BlockTextEdit::setPageBreakGap(qreal _pageBreakGap, bool _inches) {
    if(_inches) {
        _pageBreakGap = inchesToPixels(_pageBreakGap, false);
    }
    m_pageBreakGap = _pageBreakGap;

    // Repaint after change
    repaint();
}

void BlockTextEdit::paintEvent(QPaintEvent* _event) {
    // Make sure the scroll bar range is correct before painting to user
    updateVerticalScrollRange();

    // Paints page break lines
    paintPagesView();

    QTextEdit::paintEvent(_event);
}


void BlockTextEdit::resizeEvent(QResizeEvent* _event) {
    // Updates viewport and scroll bar range when the window is resized
    updateViewportMargins();
    updateVerticalScrollRange();

    QTextEdit::resizeEvent(_event);
}

void BlockTextEdit::keyPressEvent(QKeyEvent* _event) {
    if(textCursor().hasSelection()) {
        QString deletedText(textCursor().selectedText());
        static QRegularExpression frameBoundaryExp("\\p{nChar}");
        QRegularExpressionMatchIterator it = frameBoundaryExp.globalMatch(deletedText);
        QStringList testCatches;
        while(it.hasNext()) {
            QRegularExpressionMatch match = it.next();
            QString word = match.captured(0);
            if(word == "\uFDD0" || word == "\uFDD1") {
                testCatches.append(word);
            }
        }
        qDebug() << deletedText;
        qDebug() << testCatches;
    }

    QTextEdit::keyPressEvent(_event);
    if(textCursor().block() == textCursor().currentFrame()->begin().currentBlock()) {
        if(_event->key()) {

        }
    }
}

void BlockTextEdit::updateViewportMargins() {
    // Declare Margins
    QMargins viewportMargins;

    // Get page width and height
    int pageWidth = m_pixelPageSize.width();
    int pageHeight = m_pixelPageSize.height() + m_pageBreakGap;

    // Calculate padding for the viewport
    const int DEFAULT_TOP_MARGIN = 0;
    const int DEFAULT_BOTTOM_MARGIN = 0;
    int leftMargin = 0;
    int rightMargin = 0;

    // If the editor's width is greater than the width of the document, add side padding
    if (width() > pageWidth) {
        const int BORDERS_WIDTH = 4;

        // Account for vertical scroll bar width if visible
        const int VERTICAL_SCROLLBAR_WIDTH =
                verticalScrollBar()->isVisible() ? verticalScrollBar()->width() : 0;
        // The padding width of one side is half the editor width minus the page, scroll bar, and borders
        leftMargin = rightMargin =
                (width() - pageWidth - VERTICAL_SCROLLBAR_WIDTH - BORDERS_WIDTH) / 2;
    }

    // Top margin remains constant
    int topMargin = DEFAULT_TOP_MARGIN;

    // Calculate bottom margin
    int bottomMargin = DEFAULT_BOTTOM_MARGIN;

    int documentHeight = pageHeight * document()->pageCount();
    // Check if document is taller than editor
    if ((height() - documentHeight) > (DEFAULT_TOP_MARGIN + DEFAULT_BOTTOM_MARGIN)) {
        const int BORDERS_HEIGHT = 2;

        // Account for horizontal scroll bar height if visible
        const int HORIZONTAL_SCROLLBAR_HEIGHT =
                horizontalScrollBar()->isVisible() ? horizontalScrollBar()->height() : 0;
        // Calculate the amount of padding needed on the bottom
        bottomMargin = height() - documentHeight - HORIZONTAL_SCROLLBAR_HEIGHT - DEFAULT_TOP_MARGIN - BORDERS_HEIGHT;
    }

    // Define the viewport margins
    viewportMargins = QMargins(leftMargin, topMargin, rightMargin, bottomMargin);

    setViewportMargins(viewportMargins);

    // Update document geometry
    aboutUpdateDocumentGeometry();
}

void BlockTextEdit::updateVerticalScrollRange() {
    const int pageHeight = m_pixelPageSize.height();
    const int documentHeight = (pageHeight + m_pageBreakGap) * document()->pageCount() -  1;
    const int maximumValue = documentHeight - viewport()->height();
    if (verticalScrollBar()->maximum() != maximumValue) {
        verticalScrollBar()->setMaximum(maximumValue);
    }
}

void BlockTextEdit::paintPagesView() {

    // Draw page break lines
    qreal pageWidth = m_pixelPageSize.width();
    qreal pageHeight = m_pixelPageSize.height() + m_pageBreakGap;

    QPainter p(viewport());
    QPen spacePen(QColor(234, 234, 234), m_pageBreakGap);
    QPen borderPen(palette().dark(), 1);

    // Find the current height of top page on the screen
    qreal curHeight = pageHeight - (verticalScrollBar()->value() % (int)pageHeight);

    // Find the position of the right border
    const int x = pageWidth + (width() % 2 == 0 ? 2 : 1);

    // Horizontal offset if there is a horizontal scrollbar
    const int horizontalDelta = horizontalScrollBar()->value();

    // Draw the top border
    if (curHeight - pageHeight >= 0) {
        p.setPen(borderPen);
        p.drawLine(0, curHeight - pageHeight, x, curHeight - pageHeight);
    }

    // Draw page breaks and borders for each page visible
    while (curHeight <= height()) {

        // Draw Page Break
        p.setPen(spacePen);
        p.drawLine(0, curHeight - (int)(m_pageBreakGap / 2), width(), curHeight - (int)(m_pageBreakGap / 2));

        // Draw Page Borders
        p.setPen(borderPen);
        // Bottom of the page
        p.drawLine(0, curHeight - (m_pageBreakGap), x, curHeight - (m_pageBreakGap));
        // Top of the next page
        p.drawLine(0, curHeight, x, curHeight);
        // Left border
        p.drawLine(0 - horizontalDelta, curHeight - pageHeight, 0 - horizontalDelta, curHeight - (m_pageBreakGap));
        // Right border
        p.drawLine(x - horizontalDelta, curHeight - pageHeight, x - horizontalDelta, curHeight - (m_pageBreakGap));

        // Move to next page
        curHeight += pageHeight;
    }

    // Draw the side borders of the last page when it doesn't fit the screen
    if (curHeight >= height()) {
        p.setPen(borderPen);
        // Left border
        p.drawLine(0 - horizontalDelta, curHeight-pageHeight, 0 - horizontalDelta, height());
        // Right border
        p.drawLine(x - horizontalDelta + 1, curHeight-pageHeight, x - horizontalDelta + 1, height());
    }
}

void BlockTextEdit::aboutVerticalScrollRangeChanged(int _minimum, int _maximum) {
    Q_UNUSED(_minimum)
    updateViewportMargins();
    int scrollValue = verticalScrollBar()->value();

    // If the current scroll position is greater than the maximum value,
    // so textedit updated the interval itself, apply our own correction function
    if (scrollValue > _maximum) {
        updateVerticalScrollRange();
    }
}

void BlockTextEdit::aboutDocumentChanged() {
    if (m_document != document()) {
        m_document = document();
    }

}

void BlockTextEdit::aboutUpdateDocumentGeometry()
{
    // Determine the document size
    QSizeF documentSize(width() - verticalScrollBar()->width(), -1);
    int pageWidth = m_pixelPageSize.width();
    int pageHeight = m_pixelPageSize.height() + m_pageBreakGap;
    documentSize = QSizeF(pageWidth, pageHeight);

    // Update document size
    if (document()->pageSize() != documentSize) {
        document()->setPageSize(documentSize);
    }

    // Clear document margins, uses root frame margins instead
    if (document()->documentMargin() != 0) {
        document()->setDocumentMargin(0);
    }

    QMarginsF rootFrameMargins = m_pixelPageMargins;
    QTextFrameFormat rootFrameFormat = document()->rootFrame()->frameFormat();
    if (rootFrameFormat.leftMargin() != rootFrameMargins.left()
        || rootFrameFormat.topMargin() != rootFrameMargins.top()
        || rootFrameFormat.rightMargin() != rootFrameMargins.right()
        || rootFrameFormat.bottomMargin() != rootFrameMargins.bottom()) {
        rootFrameFormat.setLeftMargin(rootFrameMargins.left());
        rootFrameFormat.setTopMargin(rootFrameMargins.top());
        rootFrameFormat.setRightMargin(rootFrameMargins.right());
        rootFrameFormat.setBottomMargin(rootFrameMargins.bottom());
        document()->rootFrame()->setFrameFormat(rootFrameFormat);
    }
}

void BlockTextEdit::handleContentsChange(int position, int charsRemoved, int charsAdded) {
    Q_UNUSED(charsRemoved)
    for(int i = 0; i < m_codeSubblocks.length(); i++) {
        if(textCursor().currentFrame() == m_codeSubblocks.at(i).m_frame && textCursor().block().userData() != &m_codeSubblocks.at(i).m_data) {
            SubblockUserData* subblockData = new SubblockUserData(m_codeSubblocks.at(i).m_data);
            textCursor().block().setUserData(subblockData);
        }
    }

    if (charsAdded > 0) {
        QString insertedText = m_document->toPlainText().mid(position, charsAdded);
        if (insertedText.contains('\n')) {
            m_codeHighlighter.manualRehighlightBlock(textCursor().block());
        }
    }
};

void BlockTextEdit::insertCodeBlock(QWidget* _centralwidget) {
    CodeSubblock sblock;

    // Set up subblock format
    QTextFrameFormat format;
    format.setBorder(1);
    format.setBorderStyle(QTextFrameFormat::BorderStyle_Solid);
    format.setBackground(QBrush(QColor(230, 230, 230)));

    // Insert new frame
    textCursor().insertFrame(format);
    QTextFrame* newFrame = textCursor().currentFrame();
    textCursor().block().setUserData(new SubblockUserData(1));
    textCursor().insertText("\uFDD0");
    textCursor().block();
    textCursor().block().setVisible(false);
    textCursor().insertBlock();
    textCursor().insertBlock();
    textCursor().insertText("\uFDD1");
    textCursor().block().setVisible(false);
    textCursor().setPosition(textCursor().block().position() - 1);
    update();

    // Insert settings button
    QPushButton* settingsButton = new QPushButton();
    _centralwidget->layout()->addWidget(settingsButton);
    settingsButton->setParent(this);


    // Update struct
    sblock.m_frame = newFrame;
    sblock.m_settingsButton = settingsButton;
    sblock.m_data.setSubblockType(1);
    sblock.m_data.setOtherData(0);

    // Add to list of buttons
    m_codeSubblocks.append(sblock);

    // Set initial button positions

    // Get the bounding rectangle of the frame
    QRectF frameRect = document()->documentLayout()->frameBoundingRect(sblock.m_frame);

    // Convert the frame-bounding rectangle coordinate system to the one of the central widget
    QPointF frameRectTopRight = viewport()->mapTo(this, frameRect.topLeft());
    frameRectTopRight.setY(frameRectTopRight.y() - verticalScrollBar()->value());
    frameRectTopRight.setX(frameRectTopRight.x() + frameRect.width());

    // Move the button
    QRectF border = QRectF(frameRectTopRight, QSizeF(20, 20));
    sblock.m_settingsButton->setGeometry(border.toRect());
    border.moveRight(border.right() + 25);
    sblock.m_settingsButton->repaint();

    // Keep the button on top of the frame. Adjust for position, as long as frame is on screen.
    connect(verticalScrollBar(), &QScrollBar::valueChanged, this, [this, sblock]() {
        // Get the bounding rectangle of the frame
        QRectF frameRect = document()->documentLayout()->frameBoundingRect(sblock.m_frame);

        // Convert the frame-bounding rectangle coordinate system to the one of the central widget
        QPointF frameRectTopRight = viewport()->mapTo(this, frameRect.topLeft());
        frameRectTopRight.setY(frameRectTopRight.y() - verticalScrollBar()->value());
        frameRectTopRight.setX(frameRectTopRight.x() + frameRect.width());

        // If the top of the frame is partially off screen, move button downwards, lowest point is the bottom of the frame
        if(frameRectTopRight.y() <= 0 && frameRectTopRight.y() >= -frameRect.height() + sblock.m_settingsButton->height()) {
            frameRectTopRight.setY(0);
        } else if(frameRectTopRight.y() <= 0 && frameRectTopRight.y() >= -frameRect.height()) {
            frameRectTopRight.setY(frameRectTopRight.y() + frameRect.height() - sblock.m_settingsButton->height());
        }

        // Move the button
        QRectF border = QRectF(frameRectTopRight, QSizeF(20, 20));
        sblock.m_settingsButton->setGeometry(border.toRect());
        border.moveRight(border.right() + 25);
        sblock.m_settingsButton->repaint();
    });

    // Buttons only visible when frame is selected
    connect(this, &QTextEdit::cursorPositionChanged, this, [this, sblock]() {
        if(textCursor().currentFrame() == sblock.m_frame) {
            sblock.m_settingsButton->setVisible(true);
        } else {
            sblock.m_settingsButton->setVisible(false);
        }
    });

    // Open settings menu
    connect(sblock.m_settingsButton, &QPushButton::clicked, this, [sblock]() mutable {
        CodeSubblockSettings settings(sblock.m_frame);
        settings.exec();
    });
}
