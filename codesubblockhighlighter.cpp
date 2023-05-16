#include "codesubblockhighlighter.h"
#include "subblockuserdata.h"

CodeSubblockHighlighter::CodeSubblockHighlighter(QTextDocument* _document) :
    QSyntaxHighlighter(_document)
{

    //
    // Taken from Qt Syntax Highlighter Example
    //
    HighlightingRule rule;

    m_keywordFormat.setForeground(Qt::darkBlue);
    m_keywordFormat.setFontWeight(QFont::Bold);
    const QString keywordPatterns[] = {
        QStringLiteral("\\bchar\\b"), QStringLiteral("\\bclass\\b"), QStringLiteral("\\bconst\\b"),
        QStringLiteral("\\bdouble\\b"), QStringLiteral("\\benum\\b"), QStringLiteral("\\bexplicit\\b"),
        QStringLiteral("\\bfriend\\b"), QStringLiteral("\\binline\\b"), QStringLiteral("\\bint\\b"),
        QStringLiteral("\\blong\\b"), QStringLiteral("\\bnamespace\\b"), QStringLiteral("\\boperator\\b"),
        QStringLiteral("\\bprivate\\b"), QStringLiteral("\\bprotected\\b"), QStringLiteral("\\bpublic\\b"),
        QStringLiteral("\\bshort\\b"), QStringLiteral("\\bsignals\\b"), QStringLiteral("\\bsigned\\b"),
        QStringLiteral("\\bslots\\b"), QStringLiteral("\\bstatic\\b"), QStringLiteral("\\bstruct\\b"),
        QStringLiteral("\\btemplate\\b"), QStringLiteral("\\btypedef\\b"), QStringLiteral("\\btypename\\b"),
        QStringLiteral("\\bunion\\b"), QStringLiteral("\\bunsigned\\b"), QStringLiteral("\\bvirtual\\b"),
        QStringLiteral("\\bvoid\\b"), QStringLiteral("\\bvolatile\\b"), QStringLiteral("\\bbool\\b")
    };
    for (const QString &pattern : keywordPatterns) {
        rule.m_pattern = QRegularExpression(pattern);
        rule.m_format = m_keywordFormat;
        m_highlightingRules.append(rule);
//! [0] //! [1]
    }
//! [1]

//! [2]
    m_classFormat.setFontWeight(QFont::Bold);
    m_classFormat.setForeground(Qt::darkMagenta);
    rule.m_pattern = QRegularExpression(QStringLiteral("\\bQ[A-Za-z]+\\b"));
    rule.m_format = m_classFormat;
    m_highlightingRules.append(rule);
//! [2]

//! [3]
    m_singleLineCommentFormat.setForeground(Qt::red);
    rule.m_pattern = QRegularExpression(R"(//[^\n]*)");
    rule.m_format = m_singleLineCommentFormat;
    m_highlightingRules.append(rule);
    m_multiLineCommentFormat.setForeground(Qt::red);
//! [3]

//! [4]
    m_quotationFormat.setForeground(Qt::darkGreen);
    rule.m_pattern = QRegularExpression(QStringLiteral("\".*\""));
    rule.m_format = m_quotationFormat;
    m_highlightingRules.append(rule);
//! [4]

//! [5]
    m_functionFormat.setFontItalic(true);
    m_functionFormat.setForeground(Qt::blue);
    rule.m_pattern = QRegularExpression(QStringLiteral("\\b[A-Za-z0-9_]+(?=\\()"));
    rule.m_format = m_functionFormat;
    m_highlightingRules.append(rule);
//! [5]

//! [6]
    m_commentStartExpression = QRegularExpression(QStringLiteral("/\\*"));
    m_commentEndExpression = QRegularExpression(QStringLiteral("\\*/"));
}

QList<CodeSubblock> CodeSubblockHighlighter::targetBlocks() {
    return m_targetBlocks;
}

void CodeSubblockHighlighter::addTargetBlock(CodeSubblock _newBlock) {
    m_targetBlocks.append(_newBlock);
}

//void CodeSubblockHighlighter::removeTargetBlock(CodeSubblock _targetBlock) {

//}
//
//void CodeSubblockHighlighter::removeTargetBlock(int _index) {

//}

void CodeSubblockHighlighter::highlightBlock(const QString &text) {
    SubblockUserData* data = static_cast<SubblockUserData*>(currentBlock().userData());
    if(data) {
        if(data->subblockType() == 1) {
        //! Code from Qt Syntax Highlighter example. Reimplement as needed

            // setHighlighterRules(data->otherData());
            for (const HighlightingRule &rule : std::as_const(m_highlightingRules)) {
                QRegularExpressionMatchIterator matchIterator = rule.m_pattern.globalMatch(text);
                while (matchIterator.hasNext()) {
                    QRegularExpressionMatch match = matchIterator.next();
                    setFormat(match.capturedStart(), match.capturedLength(), rule.m_format);
                }
            }
        //! [7] //! [8]
            setCurrentBlockState(0);
        //! [8]

        //! [9]
            int startIndex = 0;
            if (previousBlockState() != 1)
                startIndex = text.indexOf(m_commentStartExpression);

        //! [9] //! [10]
            while (startIndex >= 0) {
        //! [10] //! [11]
                QRegularExpressionMatch match = m_commentEndExpression.match(text, startIndex);
                int endIndex = match.capturedStart();
                int commentLength = 0;
                if (endIndex == -1) {
                    setCurrentBlockState(1);
                    commentLength = text.length() - startIndex;
                } else {
                    commentLength = endIndex - startIndex
                                    + match.capturedLength();
                }
                setFormat(startIndex, commentLength, m_multiLineCommentFormat);
                startIndex = text.indexOf(m_commentStartExpression, startIndex + commentLength);
            }
        }
    }
}
