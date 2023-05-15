#include "codesubblocksettings.h"
#include "codesubblock.h"

#include <QLabel>
#include <QPushButton>
#include <QComboBox>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QDialogButtonBox>
#include <QColorDialog>
#include <QSpinBox>
#include <QMetaEnum>

CodeSubblockSettings::CodeSubblockSettings(CodeSubblock* target, QWidget* parent) : QDialog(parent)
{
    verticalLayout = new QVBoxLayout;
    formLayout = new QFormLayout;
    backgroundColorLabel = new QLabel("Background Color");
    backgroundColorButton = new QPushButton;
    borderColorLabel = new QLabel("Border Color");
    borderColorButton = new QPushButton;
    borderStyleLabel = new QLabel("Border Style");
    borderStyleBox = new QComboBox;
    borderWidthLabel = new QLabel("Border Width");
    borderWidthBox = new QSpinBox;
    buttonBox = new QDialogButtonBox;

    m_oldFormat = target->format();
    m_newFormat = target->format();
    m_target = target;

    QStringList borderStyles = {"None", "Dotted", "Dashed", "Solid", "Double", "Dot Dash", "Dot Dot Dash", "Groove", "Ridge", "Inset", "Outset"};
    borderStyleBox->addItems(borderStyles);

    borderColorButton->setPalette(m_target->format().borderBrush().color());
    borderColorButton->setFlat(true);
    borderColorButton->setAutoFillBackground(true);
    backgroundColorButton->setPalette(m_target->format().background().color());
    backgroundColorButton->setFlat(true);
    backgroundColorButton->setAutoFillBackground(true);
    borderWidthBox->setValue(m_target->format().border());
    borderStyleBox->setCurrentIndex(borderStyleToInt(m_target->format().borderStyle()));


    setLayout(verticalLayout);
    formLayout->setLabelAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
    verticalLayout->addLayout(formLayout);
    formLayout->addRow(backgroundColorLabel, backgroundColorButton);
    formLayout->addRow(borderColorLabel, borderColorButton);
    formLayout->addRow(borderStyleLabel, borderStyleBox);
    formLayout->addRow(borderWidthLabel, borderWidthBox);

    buttonBox->setOrientation(Qt::Horizontal);
    buttonBox->setStandardButtons(QDialogButtonBox::Apply|QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
    verticalLayout->addWidget(buttonBox);

    setWindowTitle(tr("Code Subblock Settings"));
    setFixedSize(300, 300);


    connect(backgroundColorButton, &QPushButton::clicked, this, &CodeSubblockSettings::changeFormatBackgroundColor);
    connect(borderStyleBox, &QComboBox::currentIndexChanged, this, &CodeSubblockSettings::changeFormatBorderStyle);
    connect(borderColorButton, &QPushButton::clicked, this, &CodeSubblockSettings::changeFormatBorderColor);
    connect(borderWidthBox, &QSpinBox::valueChanged, this, &CodeSubblockSettings::changeFormatBorderWidth);
}

int CodeSubblockSettings::borderStyleToInt(QTextFrameFormat::BorderStyle _input) {
    switch(_input) {
        case QTextFrameFormat::BorderStyle_None:
            return 0;
            break;
        case QTextFrameFormat::BorderStyle_Dotted:
            return 1;
            break;
        case QTextFrameFormat::BorderStyle_Dashed:
            return 2;
            break;
        case QTextFrameFormat::BorderStyle_Solid:
            return 3;
            break;
        case QTextFrameFormat::BorderStyle_Double:
            return 4;
            break;
        case QTextFrameFormat::BorderStyle_DotDash:
            return 5;
            break;
        case QTextFrameFormat::BorderStyle_DotDotDash:
            return 6;
            break;
        case QTextFrameFormat::BorderStyle_Groove:
            return 7;
            break;
        case QTextFrameFormat::BorderStyle_Ridge:
            return 8;
            break;
        case QTextFrameFormat::BorderStyle_Inset:
            return 9;
            break;
        case QTextFrameFormat::BorderStyle_Outset:
            return 10;
            break;
        default:
            return 0;
    }
}

void CodeSubblockSettings::changeFormatBorderStyle(int _newFormat) {
    QTextFrameFormat::BorderStyle newStyle = QTextFrameFormat::BorderStyle_None;
    switch(_newFormat) {
    case 0:
        newStyle = QTextFrameFormat::BorderStyle_None;
        break;
    case 1:
        newStyle = QTextFrameFormat::BorderStyle_Dotted;
        break;
    case 2:
        newStyle = QTextFrameFormat::BorderStyle_Dashed;
        break;
    case 3:
        newStyle = QTextFrameFormat::BorderStyle_Solid;
        break;
    case 4:
        newStyle = QTextFrameFormat::BorderStyle_Double;
        break;
    case 5:
        newStyle = QTextFrameFormat::BorderStyle_DotDash;
        break;
    case 6:
        newStyle = QTextFrameFormat::BorderStyle_DotDotDash;
        break;
    case 7:
        newStyle = QTextFrameFormat::BorderStyle_Groove;
        break;
    case 8:
        newStyle = QTextFrameFormat::BorderStyle_Ridge;
        break;
    case 9:
        newStyle = QTextFrameFormat::BorderStyle_Inset;
        break;
    case 10:
        newStyle = QTextFrameFormat::BorderStyle_Outset;
        break;
    }

    m_newFormat.setBorderStyle(newStyle);
    m_target->frame()->setFrameFormat(m_newFormat);

}

void CodeSubblockSettings::changeFormatBorderWidth(int _newWidth) {
    m_newFormat.setBorder(_newWidth);
    m_target->frame()->setFrameFormat(m_newFormat);
}

void CodeSubblockSettings::changeFormatBorderColor() {
    const QColor color = QColorDialog::getColor(m_target->frame()->frameFormat().borderBrush().color(), this, "Select Border Color");

    if (color.isValid()) {
        QBrush newBrush = m_target->frame()->frameFormat().borderBrush();
        newBrush.setColor(color);
        m_newFormat.setBorderBrush(newBrush);
        m_target->frame()->setFrameFormat(m_newFormat);
        borderColorButton->setPalette(color);
        borderColorButton->update();
    }
}

void CodeSubblockSettings::changeFormatBackgroundColor() {
    const QColor color = QColorDialog::getColor(m_target->frame()->frameFormat().borderBrush().color(), this, "Select Background Color");

    if (color.isValid()) {
        QBrush newBrush = m_target->frame()->frameFormat().background();
        newBrush.setColor(color);
        m_newFormat.setBackground(newBrush);
        m_target->frame()->setFrameFormat(m_newFormat);
        backgroundColorButton->setPalette(color);
        backgroundColorButton->update();
    }
}
