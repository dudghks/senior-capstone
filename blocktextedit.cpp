// Multi-page display code adapted from @dimkanovikov on GitHub
// https://github.com/dimkanovikov/PagesTextEdit
// Comments translated using Google Translate with some changes

#include "blocktextedit.h"

#include <QScreen>
#include <QApplication>
#include <QAbstractTextDocumentLayout>
#include <QScrollBar>
#include <QPainter>
#include <QTextFrame>

BlockTextEdit::BlockTextEdit(QWidget *parent) : QTextEdit(parent),
    m_document()
{
    // Prevents the document from automatically changing
    aboutDocumentChanged();
    connect(this, SIGNAL(textChanged()), this, SLOT(aboutDocumentChanged()));

    // Update the document layout when it changes (overrides QTextEdit default reset)
    connect(document()->documentLayout(), SIGNAL(update()), this, SLOT(aboutUpdateDocumentGeometry()));

    // Custom setting of the scroll interval
    connect(verticalScrollBar(), SIGNAL(rangeChanged(int,int)),
        this, SLOT(aboutVerticalScrollRangeChanged(int,int)));
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
    updateVerticalScrollRange();
    paintPagesView();

    QTextEdit::paintEvent(_event);
}


void BlockTextEdit::resizeEvent(QResizeEvent* _event) {
    updateViewportMargins();
    updateVerticalScrollRange();

    QTextEdit::resizeEvent(_event);
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
    const int documentHeight = (pageHeight + m_pageBreakGap) * document()->pageCount();
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
    QPen spacePen(palette().window(), m_pageBreakGap);
    QPen borderPen(palette().dark(), 1);
    QPen testPen(palette().dark(), 5);

    // Find the current height of top page on the screen
    qreal curHeight = pageHeight - (verticalScrollBar()->value() % (int)pageHeight);

    // Find the position of the right border
    const int x = pageWidth + (width() % 2 == 0 ? 2 : 1);

    // Horizontal offset if there is a horizontal scrollbar
    const int horizontalDelta = horizontalScrollBar()->value();

    // Draw the top border
    if (curHeight - pageHeight >= 0) {
        p.setPen(borderPen);
        p.drawLine(0, curHeight - pageHeight + 1, x, curHeight - pageHeight + 1);
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
        p.drawLine(x - horizontalDelta, curHeight-pageHeight, x - horizontalDelta, height());
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
