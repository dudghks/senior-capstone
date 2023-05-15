#include "codesubblockhighlighter.h"

CodeSubblockHighlighter::CodeSubblockHighlighter(QTextDocument* _document) :
    QSyntaxHighlighter(_document)
{

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
