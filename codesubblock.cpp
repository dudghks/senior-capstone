#include "codesubblock.h"
#include "codesubblocksettings.h"

CodeSubblock::CodeSubblock(QTextFrame* _frame)
{
    m_settingsButton = new QToolButton();
    m_frame = _frame;
    QBrush background(QColor(200, 200, 200));
    m_format.setBackground(background);

    m_frame->setFrameFormat(m_format);
}

void CodeSubblock::setFrame(QTextFrame* _frame) {
    m_frame = _frame;
}

QTextFrame* CodeSubblock::frame() const {
    return m_frame;
}

void CodeSubblock::setSettingsButton(QToolButton* _settingsButton) {
    m_settingsButton = _settingsButton;
}

QToolButton* CodeSubblock::settingsButton() const {
    return m_settingsButton;
}

void CodeSubblock::openSettingsMenu() {
    CodeSubblockSettings settings(this);
    settings.exec();
}

QTextFrameFormat CodeSubblock::format() const {
    return m_format;
}

