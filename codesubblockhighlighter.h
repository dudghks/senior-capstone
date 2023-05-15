#ifndef CODESUBBLOCKHIGHLIGHTER_H
#define CODESUBBLOCKHIGHLIGHTER_H

#include <QSyntaxHighlighter>
#include <QTextCharFormat>
#include <QRegularExpression>
#include "codesubblock.h"

class CodeSubblockHighlighter : QSyntaxHighlighter
{
    Q_OBJECT
public:
    CodeSubblockHighlighter(QTextDocument* _document);
    QList<CodeSubblock> targetBlocks();
    void addTargetBlock(CodeSubblock _newBlock);
    void removeTargetBlock(CodeSubblock _targetBlock);
    void removeTargetBlock(int _index);

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
    QList<CodeSubblock> m_targetBlocks;
};

#endif // CODESUBBLOCKHIGHLIGHTER_H
