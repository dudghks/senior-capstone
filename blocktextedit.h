// Multi-page display code adapted from @dimkanovikov on GitHub
// https://github.com/dimkanovikov/PagesTextEdit
// Comments translated using Google Translate with some changes

#ifndef BLOCKTEXTEDIT_H
#define BLOCKTEXTEDIT_H

#include <QSizeF>
#include <QMarginsF>
#include <QTextEdit>
#include <QPushButton>

#include "codesubblockhighlighter.h"
#include "subblockuserdata.h"

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
    /**
     * @brief Inserts a code subblock
     */
    void insertCodeBlock();

    void undo();
    void redo();

protected:
    /**
     * @brief Overridden for correct document and page layout drawing
     */
    void paintEvent(QPaintEvent* _event) override;

    /**
     * @brief Overridden for correct viewport size updates
     */
    void resizeEvent(QResizeEvent* _event) override;

    void keyPressEvent(QKeyEvent* _event) override;

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

    /**
     * @brief Syntax Highlighter for Code Subblocks
     */
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

    /**
     * @brief Used to preserve highlighting after a newline is inserted
     * @note Can be deleted after I rewrite subblock handling (if it works)
     */
    void handleContentsChange(int position, int charsRemoved, int charsAdded);
};

#endif // BLOCKTEXTEDIT_H
