// Multi-page display code adapted from @dimkanovikov on GitHub
// https://github.com/dimkanovikov/PagesTextEdit
// Comments translated using Google Translate with some changes

#ifndef BLOCKTEXTEDIT_H
#define BLOCKTEXTEDIT_H

#include <QSizeF>
#include <QMarginsF>
#include <QTextEdit>
#include "codesubblock.h"
#include "codesubblockhighlighter.h"
class BlockTextEdit : public QTextEdit
{
    Q_OBJECT
public:
    BlockTextEdit(QWidget *parent = nullptr);

    /**
     * @brief Convert inch value to pixels using screen information
     */
    static qreal inchesToPixels(qreal inches, bool _x = true);

    /**
     * @brief Access method for Document Page Size (Pixels)
     */
    void setPixelPageSize(QSizeF _pageSize, bool _inches = false);

    /**
     * @brief Access method for Document Page Margins (Pixels)
     */
    void setPixelPageMargins(QMarginsF _pageMargins, bool _inches = false);

    /**
     * @brief Access method for Document Page Gaps (Pixels)
     */
    void setPageBreakGap(qreal _pageBreakGap, bool _inches = false);

public slots:
    void insertCodeBlock(QWidget* _centralwidget);

protected:
    /**
     * @brief Overridden for correct document and page layout drawing
     */
    void paintEvent(QPaintEvent* _event);

    /**
     * @brief Overridden for correct viewport size updates
     */
    void resizeEvent(QResizeEvent* _event);

private:
    /**
     * @brief Update viewport margins
     */
    void updateViewportMargins();

    /**
     * @brief Update vertical scrolling interval
     */
    void updateVerticalScrollRange();

    /**
     * @brief Draw the document page layout
     */
    void paintPagesView();

    /**
     * @brief Link to the current document
     */
    QTextDocument* m_document;

    /**
     * @brief Document Page Size (Pixels)
     */
    QSizeF m_pixelPageSize;

    /**
     * @brief Document Page Margins (Pixels)
     */
    QMarginsF m_pixelPageMargins;

    /**
     * @brief Document Page Break Gap
     */
    qreal m_pageBreakGap;

    CodeSubblockHighlighter m_codeHighlighter;

private slots:
    /**
     * @brief The vertical scrolling interval has changed
     */
    void aboutVerticalScrollRangeChanged(int _minimum, int _maximum);

    /**
     * @brief Document change check
     */
    void aboutDocumentChanged();

    /**
     * @brief Update the document geometry
     * @details The standard implementation of QTextEdit is such that it always resets the set document size
     *          leading to undesired consequences.
     */
    void aboutUpdateDocumentGeometry();
};

#endif // BLOCKTEXTEDIT_H
