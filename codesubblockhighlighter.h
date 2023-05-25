#ifndef CODESUBBLOCKHIGHLIGHTER_H
#define CODESUBBLOCKHIGHLIGHTER_H

#include <QSyntaxHighlighter>
#include <QTextCharFormat>
#include <QRegularExpression>

class CodeSubblockHighlighter : QSyntaxHighlighter
{
    Q_OBJECT
public:
    CodeSubblockHighlighter(QTextDocument* _document = nullptr);
    void manualRehighlightBlock(const QTextBlock& block);
protected:
    void highlightBlock(const QString &text) override;

private:
    struct HighlightingRule
    {
        QRegularExpression m_pattern;
        QTextCharFormat m_format;
    };
    QList<HighlightingRule> m_highlightingRules;

    QRegularExpression m_commentStartExpression;
    QRegularExpression m_commentEndExpression;

    QTextCharFormat m_keywordFormat;
    QTextCharFormat m_classFormat;
    QTextCharFormat m_singleLineCommentFormat;
    QTextCharFormat m_multiLineCommentFormat;
    QTextCharFormat m_quotationFormat;
    QTextCharFormat m_functionFormat;
};

#endif // CODESUBBLOCKHIGHLIGHTER_H
