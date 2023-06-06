#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "blocktextedit.h"
#include <QTextDocument>
#include <QPixmap>
#include <QPageSize>
#include <QSizeF>
#include <QTextCursor>
#include <QPrinter>
#include <QFontComboBox>
#include <QSpinBox>
#include <QPushButton>
#include <QColorDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    // Make sure the app starts on the welcome page
    ui->stackedWidget->setCurrentIndex(0);

    // Set background color
    ui->stackedWidget->setStyleSheet("QWidget#documentPage, QWidget#welcomePage {"
                                     "  background-color: #EAEAEA;"
                                     "}");

    // Place the logo next to the name
    QPixmap logo(":/img/img/logo_temp.png");
    ui->logoLabelPic->setPixmap(logo.scaled(ui->logoLabelPic->width(),
                                            ui->logoLabelPic->height(), Qt::KeepAspectRatio));

    // Define style sheet for the new document block
    ui->templateFrame->setStyleSheet("QFrame {"
                                     "  background-color: #FFFFFF;"
                                     "}"
                                     "QPushButton:hover:!pressed {"
                                     "  background-color: #C5E1FC;"
                                     "  border: 1px solid #67ABF0;"
                                     "}"
                                     "QPushButton:pressed {"
                                     "  background-color: #A2CCF5;"
                                     "  border: 1px solid #4CA0F5;"
                                     "}"
                                     "QPushButton {"
                                     "  background-color: #FFFFFF;"
                                     "  border: 1px solid #FFFFFF;"
                                     "}");

    // Clicking template selection -> document page
    connect(ui->templateOne, &QPushButton::clicked, this, [this]{ui->stackedWidget->setCurrentIndex(1); ui->ribbonDockWidget->setVisible(true);});
    connect(ui->templateTwo, &QPushButton::clicked, this, [this]{ui->stackedWidget->setCurrentIndex(1); ui->ribbonDockWidget->setVisible(true);});
    connect(ui->templateThree, &QPushButton::clicked, this, [this]{ui->stackedWidget->setCurrentIndex(1); ui->ribbonDockWidget->setVisible(true);});
    connect(ui->templateNone, &QPushButton::clicked, this, [this]{ui->stackedWidget->setCurrentIndex(1); ui->ribbonDockWidget->setVisible(true);});

    // Set up document
    ui->textEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    ui->textEdit->setPixelPageSize(QSizeF(8.5, 11), true);
    ui->textEdit->setPixelPageMargins(QMarginsF(1, 1, 1, 1), true);
    ui->textEdit->setPageBreakGap(20);


    /*
     *
     * RIBBON
     *
     */

    // Initially hide the ribbon until in the document page
    ui->ribbonDockWidget->setVisible(false);

    // Hide dock title bar
    ui->ribbonDockWidget->setTitleBarWidget(new QWidget());

    // Add file tab and buttons
    ui->ribbonTabWidget->addTab("File");

    // File: New, Open, Save, Save As
    QToolButton *newDocButton = new QToolButton;
    newDocButton->setText(tr("New"));
    newDocButton->setToolTip(tr("Open new project"));
    newDocButton->setIcon(QIcon(":/icons/new.png"));
    ui->ribbonTabWidget->addButton("File", "File", newDocButton);
    QToolButton *openDocButton = new QToolButton;
    openDocButton->setText(tr("Open"));
    openDocButton->setToolTip(tr("Open existing project"));
    openDocButton->setIcon(QIcon(":/icons/open.png"));
    ui->ribbonTabWidget->addButton("File", "File", openDocButton);
    QToolButton *saveDocButton = new QToolButton;
    saveDocButton->setText(tr("Save"));
    saveDocButton->setToolTip(tr("Save current project"));
    saveDocButton->setIcon(QIcon(":/icons/save.png"));
    ui->ribbonTabWidget->addButton("File", "File", saveDocButton);
    QToolButton *saveDocAsButton = new QToolButton;
    saveDocAsButton->setText(tr("Save As"));
    saveDocAsButton->setToolTip(tr("Save current project as"));
    saveDocAsButton->setIcon(QIcon(":/icons/save_as.png"));
    ui->ribbonTabWidget->addButton("File", "File", saveDocAsButton);

    // Share: Print, Export
    QToolButton *printDocButton = new QToolButton;
    printDocButton->setText(tr("Print"));
    printDocButton->setToolTip(tr("Print current project"));
    printDocButton->setIcon(QIcon(":/icons/print.png"));
    ui->ribbonTabWidget->addButton("File", "Share", printDocButton);
    QToolButton *exportDocButton = new QToolButton;
    exportDocButton->setText(tr("Export"));
    exportDocButton->setToolTip(tr("Open existing project"));
    exportDocButton->setIcon(QIcon(":/icons/export.png"));
    ui->ribbonTabWidget->addButton("File", "Share", exportDocButton);


    // Add Home tab and buttons
    ui->ribbonTabWidget->addTab("Home");

    // Edit: Cut, Copy, Paste, Find, Undo, Redo
    QToolButton *cutButton = new QToolButton;
    cutButton->setToolTip(tr("Cut selection to clipboard\n(Ctrl+X)"));
    cutButton->setText("Cut");
    cutButton->setIcon(QIcon(":/icons/cut.png"));
    cutButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    ui->ribbonTabWidget->addSmallButton("Home", "Edit", cutButton, 0, 0);
    QToolButton *copyButton = new QToolButton;
    copyButton->setToolTip(tr("Copy selection to clipboard\n(Ctrl+C)"));
    copyButton->setText("Copy");
    copyButton->setIcon(QIcon(":/icons/copy.png"));
    copyButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    ui->ribbonTabWidget->addSmallButton("Home", "Edit", copyButton, 1, 0);
    QToolButton *pasteButton = new QToolButton;
    pasteButton->setToolTip(tr("Paste selection to document\n(Ctrl+V)"));
    pasteButton->setText("Paste");
    pasteButton->setIcon(QIcon(":/icons/paste.png"));
    pasteButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    ui->ribbonTabWidget->addSmallButton("Home", "Edit", pasteButton, 0, 1);
    QToolButton *findButton = new QToolButton;
    findButton->setToolTip(tr("Search for text within the document\n(Ctrl+F)"));
    findButton->setText("Find");
    findButton->setIcon(QIcon(":/icons/find.png"));
    findButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    ui->ribbonTabWidget->addSmallButton("Home", "Edit", findButton, 1, 1);
    QToolButton *undoButton = new QToolButton;
    undoButton->setToolTip(tr("Undo recent changes\n(Ctrl+Z"));
    undoButton->setText("Undo");
    undoButton->setIcon(QIcon(":/icons/undo.png"));
    undoButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    ui->ribbonTabWidget->addSmallButton("Home", "Edit", undoButton, 0, 2);
    QToolButton *redoButton = new QToolButton;
    redoButton->setToolTip(tr("Reverse recent undo\nCtrl+Y"));
    redoButton->setText("Redo");
    redoButton->setIcon(QIcon(":/icons/redo.png"));
    redoButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    ui->ribbonTabWidget->addSmallButton("Home", "Edit", redoButton, 1, 2);

    // Font: Font, Font Size, Bold, Italics, Underline, Subscript, Superscript, Color, Highlight
    QFontComboBox *fontBox = new QFontComboBox;
    ui->ribbonTabWidget->addSmallButton("Home", "Font", fontBox, 0, 0);
    QSpinBox *fontSizeBox = new QSpinBox;
    fontSizeBox->setMinimum(1);
    ui->ribbonTabWidget->addSmallButton("Home", "Font", fontSizeBox, 0, 4);
    QToolButton *boldButton = new QToolButton;
    boldButton->setToolTip(tr("Bold\n(Ctrl+B)"));
    boldButton->setIcon(QIcon(":/icons/bold.png"));
    boldButton->setCheckable(true);
    ui->ribbonTabWidget->addSmallButton("Home", "Font", boldButton, 1, 0);
    QToolButton *italicButton = new QToolButton;
    italicButton->setToolTip(tr("Italics\n(Ctrl+I)"));
    italicButton->setIcon(QIcon(":/icons/italic.png"));
    italicButton->setCheckable(true);
    ui->ribbonTabWidget->addSmallButton("Home", "Font", italicButton, 1, 1);
    QToolButton *underlineButton = new QToolButton;
    underlineButton->setToolTip(tr("Underline\n(Ctrl+U)"));
    underlineButton->setIcon(QIcon(":/icons/underline.png"));
    underlineButton->setCheckable(true);
    ui->ribbonTabWidget->addSmallButton("Home", "Font", underlineButton, 1, 2);
    QToolButton *superscriptButton = new QToolButton;
    superscriptButton->setToolTip(tr("Superscript\n(Ctrl+Shift+.)"));
    superscriptButton->setIcon(QIcon(":/icons/superscript.png"));
    superscriptButton->setCheckable(true);
    ui->ribbonTabWidget->addSmallButton("Home", "Font", superscriptButton, 0, 5);
    QToolButton *subscriptButton = new QToolButton;
    subscriptButton->setToolTip(tr("Subscript\n(Ctrl+Shift+,)"));
    subscriptButton->setIcon(QIcon(":/icons/subscript.png"));
    subscriptButton->setCheckable(true);
    ui->ribbonTabWidget->addSmallButton("Home", "Font", subscriptButton, 1, 5);
    QToolButton *textColorButton = new QToolButton;
    textColorButton->setToolTip(tr("Change Text Color"));
    textColorButton->setIcon(QIcon(":/img/img/logo_temp.png"));
    ui->ribbonTabWidget->addSmallButton("Home", "Font", textColorButton, 1, 3);
    QToolButton *textHighlightButton = new QToolButton;
    textHighlightButton->setToolTip(tr("Change Text Highlight"));
    textHighlightButton->setIcon(QIcon(":/img/img/logo_temp.png"));
    ui->ribbonTabWidget->addSmallButton("Home", "Font", textHighlightButton, 1, 4);

    // Add functionality to buttons
    connect(fontBox, &QFontComboBox::currentFontChanged, this, [=](const QFont &f){
        QTextCharFormat format;
        QTextCursor textCursor = ui->textEdit->textCursor();
        format.setFont(f);
        textCursor.mergeCharFormat(format);
        ui->textEdit->mergeCurrentCharFormat(format);
    });
    connect(fontSizeBox, &QSpinBox::valueChanged, this, [=](const int i){
        QTextCharFormat format;
        QTextCursor textCursor = ui->textEdit->textCursor();
        format.setFontPointSize(i);
        textCursor.mergeCharFormat(format);
        ui->textEdit->mergeCurrentCharFormat(format);
    });
    connect(boldButton, &QPushButton::clicked, this, [=]{
        QTextCharFormat format;
        QTextCursor textCursor = ui->textEdit->textCursor();
        format.setFontWeight(boldButton->isChecked() ? QFont::Bold : QFont::Normal);
        textCursor.mergeCharFormat(format);
        ui->textEdit->mergeCurrentCharFormat(format);
    });
    connect(italicButton, &QPushButton::clicked, this, [=]{
        QTextCharFormat format;
        QTextCursor textCursor = ui->textEdit->textCursor();
        format.setFontItalic(italicButton->isChecked());
        textCursor.mergeCharFormat(format);
        ui->textEdit->mergeCurrentCharFormat(format);
    });
    connect(underlineButton, &QPushButton::clicked, this, [=]{
        QTextCharFormat format;
        QTextCursor textCursor = ui->textEdit->textCursor();
        format.setFontUnderline(underlineButton->isChecked());
        textCursor.mergeCharFormat(format);
        ui->textEdit->mergeCurrentCharFormat(format);
    });
    connect(superscriptButton, &QPushButton::clicked, this, [=]{
        QTextCharFormat format;
        QTextCursor textCursor = ui->textEdit->textCursor();
        if(subscriptButton->isChecked()) {
            subscriptButton->setChecked(false);
        }
        format.setVerticalAlignment(superscriptButton->isChecked() ? QTextCharFormat::AlignSuperScript : QTextCharFormat::AlignNormal);
        textCursor.mergeCharFormat(format);
        ui->textEdit->mergeCurrentCharFormat(format);
    });
    connect(subscriptButton, &QPushButton::clicked, this, [=]{
        QTextCharFormat format;
        QTextCursor textCursor = ui->textEdit->textCursor();
        if(superscriptButton->isChecked()) {
            superscriptButton->setChecked(false);
        }
        format.setVerticalAlignment(subscriptButton->isChecked() ? QTextCharFormat::AlignSubScript : QTextCharFormat::AlignNormal);
        textCursor.mergeCharFormat(format);
        ui->textEdit->mergeCurrentCharFormat(format);
    });
    connect(textColorButton, &QPushButton::clicked, this, [=]{
        QTextCharFormat format;
        QTextCursor textCursor = ui->textEdit->textCursor();
        const QColor color = QColorDialog::getColor(textCursor.charFormat().foreground().color(), this,
                                                    "Select Text Color", QColorDialog::ShowAlphaChannel);

        if (color.isValid()) {
            format.setForeground(QBrush(color));
            textCursor.mergeCharFormat(format);
            ui->textEdit->mergeCurrentCharFormat(format);
        }
    });
    connect(textHighlightButton, &QPushButton::clicked, this, [=]{
        QTextCursor textCursor = ui->textEdit->textCursor();
        QTextCharFormat format;
        const QColor color = QColorDialog::getColor(textCursor.charFormat().background().color(), this,
                                                    "Select Text Highlight Color", QColorDialog::ShowAlphaChannel);
        if (color.isValid()) {
            format.setBackground(QBrush(color));
            textCursor.mergeCharFormat(format);
            ui->textEdit->mergeCurrentCharFormat(format);
        }
    });

    // Paragraph: Numbered/Bulleted/Check List, Alignment (left, center, right, justify), Indent Left/Right
    QToolButton *numberedList = new QToolButton;
    numberedList->setToolTip(tr("Numbered List\n(Ctrl+Shift+7"));
    numberedList->setIcon(QIcon(":/icons/numbers.png"));
    ui->ribbonTabWidget->addSmallButton("Home", "Paragraph", numberedList, 0, 0);
    numberedList->setPopupMode(QToolButton::MenuButtonPopup);
    QToolButton *bulletedList = new QToolButton;
    bulletedList->setToolTip(tr("Bulleted List\n(Ctrl+Shift+8)"));
    bulletedList->setIcon(QIcon(":/icons/bullets.png"));
    ui->ribbonTabWidget->addSmallButton("Home", "Paragraph", bulletedList, 0, 1);
    bulletedList->setPopupMode(QToolButton::MenuButtonPopup);
    QToolButton *checkList = new QToolButton;
    checkList->setToolTip(tr("Check List\n(Ctrl+Shift+9)"));
    checkList->setIcon(QIcon(":/icons/checklist.png"));
    ui->ribbonTabWidget->addSmallButton("Home", "Paragraph", checkList, 0, 2);
    QToolButton *alignment = new QToolButton;
    alignment->setToolTip(tr("Text Alignment"));
    alignment->setIcon(QIcon(":/icons/align_left.png"));
    ui->ribbonTabWidget->addSmallButton("Home", "Paragraph", alignment, 1, 0);
    alignment->setPopupMode(QToolButton::MenuButtonPopup);
    checkList->setPopupMode(QToolButton::MenuButtonPopup);
    QToolButton *indentLeft = new QToolButton;
    indentLeft->setToolTip(tr("Indent Line Left\n(Ctrl+[)"));
    indentLeft->setIcon(QIcon(":/icons/not_indent.png"));
    ui->ribbonTabWidget->addSmallButton("Home", "Paragraph", indentLeft, 1, 1);
    QToolButton *indentRight = new QToolButton;
    indentRight->setToolTip(tr("Indent Line Right\n(Ctrl+])"));
    indentRight->setIcon(QIcon(":/icons/indent.png"));
    ui->ribbonTabWidget->addSmallButton("Home", "Paragraph", indentRight, 1, 2);

    // Add Insert tab and buttons
    ui->ribbonTabWidget->addTab("Insert");

    // Document: Blank Page, Page Break, Bookmark, Link
    QToolButton *blankPage = new QToolButton;
    blankPage->setToolTip(tr("Inserts a blank page at the cursor"));
    blankPage->setText("Blank Page");
    blankPage->setIcon(QIcon(":/icons/blank_page.png"));
    blankPage->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    ui->ribbonTabWidget->addSmallButton("Insert", "Document", blankPage, 0, 0);
    QToolButton *pageBreak = new QToolButton;
    pageBreak->setToolTip(tr("Inserts a page break at the cursor"));
    pageBreak->setText("Page Break");
    pageBreak->setIcon(QIcon(":/icons/page_break.png"));
    pageBreak->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    ui->ribbonTabWidget->addSmallButton("Insert", "Document", pageBreak, 1, 0);
    QToolButton *bookmark = new QToolButton;
    bookmark->setToolTip(tr("Inserts a bookmark at the selected text\nUsed for creating outlines"));
    bookmark->setText("Bookmark");
    bookmark->setIcon(QIcon(":/icons/bookmark.png"));
    bookmark->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    ui->ribbonTabWidget->addSmallButton("Insert", "Document", bookmark, 0, 1);
    QToolButton *hyperlink = new QToolButton;
    hyperlink->setToolTip(tr("Inserts a hyperlink at the cursor\nor selected text"));
    hyperlink->setText("Hyperlink");
    hyperlink->setIcon(QIcon(":/icons/hyperlink.png"));
    hyperlink->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    ui->ribbonTabWidget->addSmallButton("Insert", "Document", hyperlink, 1, 1);

    // Blocks: New block (Left, right, up, down:default), Split (selection, lines), Merge (selection)
    QToolButton *newBlock = new QToolButton;
    newBlock->setToolTip(tr("Insert a new block (below by default)"));
    newBlock->setIcon(QIcon(":/img/img/logo_temp.png"));
    newBlock->setText("New Block");
    ui->ribbonTabWidget->addButton("Insert", "Blocks", newBlock);
    newBlock->setPopupMode(QToolButton::MenuButtonPopup);
    QToolButton *splitBlock = new QToolButton;
    splitBlock->setToolTip(tr("Split the current block"));
    splitBlock->setIcon(QIcon(":/img/img/logo_temp.png"));
    splitBlock->setText("Split Block");
    ui->ribbonTabWidget->addButton("Insert", "Blocks", splitBlock);
    splitBlock->setPopupMode(QToolButton::MenuButtonPopup);
    QToolButton *mergeBlock = new QToolButton;
    mergeBlock->setToolTip(tr("Merge multiple blocks"));
    mergeBlock->setIcon(QIcon(":/img/img/logo_temp.png"));
    mergeBlock->setText("Merge Blocks");
    ui->ribbonTabWidget->addButton("Insert", "Blocks", mergeBlock);

    // Subblocks: Table, Equation, Code, Typesetting
    QToolButton *tableBlock = new QToolButton;
    tableBlock->setToolTip(tr("Insert a table subblock"));
    tableBlock->setIcon(QIcon(":/icons/table.png"));
    tableBlock->setText("Table");
    ui->ribbonTabWidget->addButton("Insert", "Subblocks", tableBlock);
    tableBlock->setPopupMode(QToolButton::MenuButtonPopup);
    QToolButton *equationBlock = new QToolButton;
    equationBlock->setToolTip(tr("Insert an equation subblock"));
    equationBlock->setIcon(QIcon(":/icons/equation.png"));
    equationBlock->setText("Equation");
    ui->ribbonTabWidget->addButton("Insert", "Subblocks", equationBlock);
    QToolButton *codeBlock = new QToolButton;
    codeBlock->setToolTip(tr("Insert a code subblock"));
    codeBlock->setIcon(QIcon(":/icons/code.png"));
    codeBlock->setText("Code");
    ui->ribbonTabWidget->addButton("Insert", "Subblocks", codeBlock);
    QToolButton *typesettingBlock = new QToolButton;
    typesettingBlock->setToolTip(tr("Insert a typesetting-enabled subblock"));
    typesettingBlock->setIcon(QIcon(":/img/img/logo_temp.png"));
    typesettingBlock->setText("Typesetting");
    ui->ribbonTabWidget->addButton("Insert", "Subblocks", typesettingBlock);

    connect(codeBlock, &QToolButton::clicked, this, [=]() {
        ui->textEdit->insertCodeBlock();
    });

    // Text: Special characters, image
    QToolButton *specialCharacters = new QToolButton;
    specialCharacters->setToolTip(tr("Insert special characters"));
    specialCharacters->setIcon(QIcon(":/icons/character.png"));
    specialCharacters->setText("Characters");
    ui->ribbonTabWidget->addButton("Insert", "Text", specialCharacters);
    specialCharacters->setPopupMode(QToolButton::MenuButtonPopup);
    QToolButton *insertImage = new QToolButton;
    insertImage->setToolTip(tr("Insert image"));
    insertImage->setIcon(QIcon(":/icons/image.png"));
    insertImage->setText("Image");
    ui->ribbonTabWidget->addButton("Insert", "Text", insertImage);
    insertImage->setPopupMode(QToolButton::MenuButtonPopup);


    // Set initial values for the buttons
    QTextCharFormat f = ui->textEdit->currentCharFormat();
    f.setFontPointSize(10);
    fontSizeBox->setValue(10);
    boldButton->setChecked(f.fontWeight() == QFont::Bold ? true : false);
    italicButton->setChecked(f.fontItalic());
    underlineButton->setChecked(f.fontUnderline());
    subscriptButton->setChecked(f.verticalAlignment() == QTextCharFormat::AlignSubScript ? true : false);
    superscriptButton->setChecked(f.verticalAlignment() == QTextCharFormat::AlignSuperScript ? true : false);

    // Set default font (for when everything in the document gets deleted)
    QFont font = f.font();
    font.setPointSize(10);
    ui->textEdit->document()->setDefaultFont(font);

    // Update buttons based on current text char format
    connect(ui->textEdit, &QTextEdit::currentCharFormatChanged, this, [=](const QTextCharFormat &f){
        fontBox->setCurrentFont(f.font());
        fontSizeBox->setValue(f.fontPointSize());
        boldButton->setChecked(f.fontWeight() == QFont::Bold ? true : false);
        italicButton->setChecked(f.fontItalic());
        underlineButton->setChecked(f.fontUnderline());
        subscriptButton->setChecked(f.verticalAlignment() == QTextCharFormat::AlignSubScript ? true : false);
        superscriptButton->setChecked(f.verticalAlignment() == QTextCharFormat::AlignSuperScript ? true : false);
    });

}

MainWindow::~MainWindow()
{
    delete ui;
}

