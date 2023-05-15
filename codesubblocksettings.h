#ifndef CODESUBBLOCKSETTINGS_H
#define CODESUBBLOCKSETTINGS_H

#include "codesubblock.h"
#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QComboBox>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QDialogButtonBox>
#include <QColorDialog>
#include <QSpinBox>

class CodeSubblockSettings : public QDialog
{
public:
    CodeSubblockSettings(CodeSubblock* target = nullptr, QWidget* parent = nullptr);

private:
    QTextFrameFormat m_oldFormat;
    QTextFrameFormat m_newFormat;
    CodeSubblock* m_target;

    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout;
    QLabel *backgroundColorLabel;
    QPushButton *backgroundColorButton;
    QLabel *borderColorLabel;
    QPushButton *borderColorButton;
    QLabel *borderStyleLabel;
    QComboBox *borderStyleBox;
    QLabel *borderWidthLabel;
    QSpinBox *borderWidthBox;
    QDialogButtonBox *buttonBox;
    int borderStyleToInt(QTextFrameFormat::BorderStyle _input);

private slots:
    void changeFormatBorderStyle(int _newFormat);
    void changeFormatBorderWidth(int _newWidth);
    void changeFormatBorderColor();
    void changeFormatBackgroundColor();
};

#endif // CODESUBBLOCKSETTINGS_H
