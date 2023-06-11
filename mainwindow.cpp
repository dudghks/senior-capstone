#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "blocktextedit.h"
#include "customtoolbutton.h"

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
#include <QPainter>
#include <QTextList>
#include <QAction>
#include <QTextDocumentFragment>
#include <QRegularExpression>
#include <QShortcut>
#include <QClipboard>
#include <QMimeData>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("NoteBlock");
    setWindowIcon(QIcon(":/img/img/logo_temp.png"));

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
    connect(ui->templateOne, &QPushButton::clicked, this, [this]{ui->stackedWidget->setCurrentIndex(1); ui->ribbonDockWidget->setVisible(true); setWindowTitle("NoteBlock - New Document");});
    connect(ui->templateTwo, &QPushButton::clicked, this, [this]{ui->stackedWidget->setCurrentIndex(1); ui->ribbonDockWidget->setVisible(true); setWindowTitle("NoteBlock - New Document");});
    connect(ui->templateThree, &QPushButton::clicked, this, [this]{ui->stackedWidget->setCurrentIndex(1); ui->ribbonDockWidget->setVisible(true); setWindowTitle("NoteBlock - New Document");});
    connect(ui->templateNone, &QPushButton::clicked, this, [this]{ui->stackedWidget->setCurrentIndex(1); ui->ribbonDockWidget->setVisible(true); setWindowTitle("NoteBlock - New Document");});

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
    QAction* newDocAction = new QAction;
    newDocAction->setText(tr("New"));
    newDocAction->setToolTip(tr("Open new project"));
    newDocAction->setIcon(QIcon(":/icons/new.png"));
    newDocButton->setDefaultAction(newDocAction);
    ui->ribbonTabWidget->addButton("File", "File", newDocButton);
    QToolButton *openDocButton = new QToolButton;
    QAction* openDocAction = new QAction;
    openDocAction->setText(tr("Open"));
    openDocAction->setToolTip(tr("Open existing project"));
    openDocAction->setIcon(QIcon(":/icons/open.png"));
    openDocButton->setDefaultAction(openDocAction);
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
    cutButton->setEnabled(false);
    QToolButton *copyButton = new QToolButton;
    copyButton->setToolTip(tr("Copy selection to clipboard\n(Ctrl+C)"));
    copyButton->setText("Copy");
    copyButton->setIcon(QIcon(":/icons/copy.png"));
    copyButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    copyButton->setEnabled(false);
    ui->ribbonTabWidget->addSmallButton("Home", "Edit", copyButton, 1, 0);
    QToolButton *pasteButton = new QToolButton;
    QClipboard *clipboard = QApplication::clipboard();
    pasteButton->setToolTip(tr("Paste selection to document\n(Ctrl+V)"));
    pasteButton->setText("Paste");
    pasteButton->setIcon(QIcon(":/icons/paste.png"));
    pasteButton->setEnabled(clipboard->mimeData()->hasText());
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
    undoButton->setEnabled(false);
    ui->ribbonTabWidget->addSmallButton("Home", "Edit", undoButton, 0, 2);
    QToolButton *redoButton = new QToolButton;
    redoButton->setToolTip(tr("Reverse recent undo\nCtrl+Y"));
    redoButton->setText("Redo");
    redoButton->setIcon(QIcon(":/icons/redo.png"));
    redoButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    redoButton->setEnabled(false);
    ui->ribbonTabWidget->addSmallButton("Home", "Edit", redoButton, 1, 2);

    // Tracks if these actions are available or not. enables and disables buttons accordingly
    connect(ui->textEdit, &QTextEdit::copyAvailable, cutButton, &QWidget::setEnabled);
    connect(ui->textEdit, &QTextEdit::copyAvailable, copyButton, &QWidget::setEnabled);
    connect(clipboard, &QClipboard::dataChanged, this, [=]() {
        pasteButton->setEnabled(clipboard->mimeData()->hasText());
    });
    connect(ui->textEdit, &QTextEdit::undoAvailable, undoButton, &QWidget::setEnabled); // for some reason this is always available
    connect(ui->textEdit, &QTextEdit::redoAvailable, redoButton, &QWidget::setEnabled);

    // Button functionality
    connect(cutButton, &QToolButton::clicked, ui->textEdit, &QTextEdit::cut);
    connect(copyButton, &QToolButton::clicked, ui->textEdit, &QTextEdit::copy);
    connect(pasteButton, &QToolButton::clicked, ui->textEdit, &QTextEdit::paste);
    connect(undoButton, &QToolButton::clicked, ui->textEdit, &QTextEdit::undo);
    connect(redoButton, &QToolButton::clicked, ui->textEdit, &QTextEdit::redo);

    // Font: Font, Font Size, Bold, Italics, Underline, Subscript, Superscript, Color, Highlight
    QFontComboBox *fontBox = new QFontComboBox;
    ui->ribbonTabWidget->addSmallButton("Home", "Font", fontBox, 0, 0);
    QComboBox *fontSizeBox = new QComboBox;
    QShortcut *increaseFontSizeShortcut = new QShortcut(QKeySequence(Qt::CTRL | Qt::SHIFT | Qt::Key_Period), ui->documentPage);
    QShortcut *decreaseFontSizeShortcut = new QShortcut(QKeySequence(Qt::CTRL | Qt::SHIFT | Qt::Key_Comma), ui->documentPage);
    ui->ribbonTabWidget->addSmallButton("Home", "Font", fontSizeBox, 0, 4);
    fontSizeBox->setEditable(true);
    fontSizeBox->setInsertPolicy(QComboBox::NoInsert);
    const QList<int> standardSizes = QFontDatabase::standardSizes();
    for (int i : standardSizes) {
        fontSizeBox->addItem(QString::number(i));
    }
    fontSizeBox->setCurrentIndex(standardSizes.indexOf(QApplication::font().pointSize()));
    QToolButton *boldButton = new QToolButton;
    QAction *boldAction = new QAction;
    boldAction->setToolTip(tr("Bold\n(Ctrl+B)"));
    boldAction->setIcon(QIcon(":/icons/bold.png"));
    boldAction->setCheckable(true);
    boldAction->setShortcut(QKeySequence::Bold);
    boldButton->setDefaultAction(boldAction);
    ui->ribbonTabWidget->addSmallButton("Home", "Font", boldButton, 1, 0);
    QToolButton *italicButton = new QToolButton;
    QAction *italicAction = new QAction;
    italicAction->setToolTip(tr("Italics\n(Ctrl+I)"));
    italicAction->setIcon(QIcon(":/icons/italic.png"));
    italicAction->setCheckable(true);
    italicAction->setShortcut(QKeySequence::Italic);
    italicButton->setDefaultAction(italicAction);
    ui->ribbonTabWidget->addSmallButton("Home", "Font", italicButton, 1, 1);
    QToolButton *underlineButton = new QToolButton;
    QAction *underlineAction = new QAction;
    underlineAction->setToolTip(tr("Underline\n(Ctrl+U)"));
    underlineAction->setIcon(QIcon(":/icons/underline.png"));
    underlineAction->setCheckable(true);
    underlineAction->setShortcut(QKeySequence::Underline);
    underlineButton->setDefaultAction(underlineAction);
    ui->ribbonTabWidget->addSmallButton("Home", "Font", underlineButton, 1, 2);
    QToolButton *superscriptButton = new QToolButton;
    QAction *superscriptAction = new QAction;
    superscriptAction->setToolTip(tr("Superscript\n(Ctrl+Shift+.)"));
    superscriptAction->setIcon(QIcon(":/icons/superscript.png"));
    superscriptAction->setCheckable(true);
    superscriptAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_Period));
    superscriptButton->setDefaultAction(superscriptAction);
    ui->ribbonTabWidget->addSmallButton("Home", "Font", superscriptButton, 0, 5);
    QToolButton *subscriptButton = new QToolButton;
    QAction *subscriptAction = new QAction;
    subscriptAction->setToolTip(tr("Subscript\n(Ctrl+Shift+,)"));
    subscriptAction->setIcon(QIcon(":/icons/subscript.png"));
    subscriptAction->setCheckable(true);
    subscriptAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_Comma));
    subscriptButton->setDefaultAction(subscriptAction);
    ui->ribbonTabWidget->addSmallButton("Home", "Font", subscriptButton, 1, 5);
    CustomToolButton *textColorButton = new CustomToolButton;
    textColorButton->setColor(QColor(0, 0, 0));
    textColorButton->setBorder(false);
    textColorButton->setColorArea(QRect(10, 24, 18, 3));
    textColorButton->setToolTip(tr("Change Text Color"));
    textColorButton->setIcon(QIcon(":/icons/A.png"));
    ui->ribbonTabWidget->addSmallButton("Home", "Font", textColorButton, 1, 3);
    CustomToolButton *textHighlightButton = new CustomToolButton;
    textHighlightButton->setColor(QColor(0, 0, 0, 0));
    textHighlightButton->setBorder(true);
    textHighlightButton->setColorArea(QRect(8, 2, 22, 23));
    textHighlightButton->setToolTip(tr("Change Text Highlight"));
    textHighlightButton->setIcon(QIcon(":/icons/A.png"));
    ui->ribbonTabWidget->addSmallButton("Home", "Font", textHighlightButton, 1, 4);

    // Add functionality to buttons
    connect(fontBox, &QFontComboBox::textActivated, this, [=](const QString &text){
        QTextCharFormat format;
        format.setFont(QFont(text));
        ui->textEdit->mergeCurrentCharFormat(format);
        ui->textEdit->setFocus();
    });
    connect(fontSizeBox, &QComboBox::textActivated, this, [=](const QString &text){
        qreal pointSize = text.toFloat();
        if(pointSize > 0) {
            QTextCharFormat format;
            format.setFontPointSize(pointSize);
            ui->textEdit->mergeCurrentCharFormat(format);
            ui->textEdit->setFocus();
        }
    });
    connect(increaseFontSizeShortcut, &QShortcut::activated, this, [=] {
        qDebug() << "Font Size Increased";
        qreal pointSize = fontSizeBox->currentText().toFloat() + 1;
        fontSizeBox->setEditText(QString::number(pointSize));
        QTextCharFormat format;
        format.setFontPointSize(pointSize);
        ui->textEdit->mergeCurrentCharFormat(format);
        ui->textEdit->setFocus();
    });
    connect(decreaseFontSizeShortcut, &QShortcut::activated, this, [=] {
        qDebug() << "Font Size Decreased";
        qreal pointSize = fontSizeBox->currentText().toFloat() - 1;
        if(pointSize < 1) {
            pointSize = 1;
        }
        fontSizeBox->setEditText(QString::number(pointSize));
        QTextCharFormat format;
        format.setFontPointSize(pointSize);
        ui->textEdit->mergeCurrentCharFormat(format);
        ui->textEdit->setFocus();
    });
    connect(boldAction, &QAction::triggered, this, [=]{
        QTextCharFormat format;
        format.setFontWeight(boldButton->isChecked() ? QFont::Bold : QFont::Normal);
        ui->textEdit->mergeCurrentCharFormat(format);
        ui->textEdit->setFocus();
    });
    connect(italicAction, &QAction::triggered, this, [=]{
        QTextCharFormat format;
        format.setFontItalic(italicButton->isChecked());
        ui->textEdit->mergeCurrentCharFormat(format);
        ui->textEdit->setFocus();
    });
    connect(underlineAction, &QAction::triggered, this, [=]{
        QTextCharFormat format;
        format.setFontUnderline(underlineButton->isChecked());
        ui->textEdit->mergeCurrentCharFormat(format);
        ui->textEdit->setFocus();
    });
    connect(superscriptAction, &QAction::triggered, this, [=]{
        QTextCharFormat format;
        if(subscriptButton->isChecked()) {
            subscriptButton->setChecked(false);
        }
        format.setVerticalAlignment(superscriptButton->isChecked() ? QTextCharFormat::AlignSuperScript : QTextCharFormat::AlignNormal);
        ui->textEdit->mergeCurrentCharFormat(format);
        ui->textEdit->setFocus();
    });
    connect(subscriptAction, &QAction::triggered, this, [=]{
        QTextCharFormat format;
        if(superscriptButton->isChecked()) {
            superscriptButton->setChecked(false);
        }
        format.setVerticalAlignment(subscriptButton->isChecked() ? QTextCharFormat::AlignSubScript : QTextCharFormat::AlignNormal);
        ui->textEdit->mergeCurrentCharFormat(format);
        ui->textEdit->setFocus();
    });
    connect(textColorButton, &QToolButton::clicked, this, [=]{
        QTextCharFormat format;
        QTextCursor textCursor = ui->textEdit->textCursor();
        const QColor color = QColorDialog::getColor(textCursor.charFormat().foreground().color(), this,
                                                    "Select Text Color", QColorDialog::ShowAlphaChannel);

        if (color.isValid()) {
            format.setForeground(QBrush(color));
            ui->textEdit->mergeCurrentCharFormat(format);
            textColorButton->setColor(color);
        }
        ui->textEdit->setFocus();
    });
    connect(textHighlightButton, &QToolButton::clicked, this, [=]{
        QTextCursor textCursor = ui->textEdit->textCursor();
        QTextCharFormat format;
        const QColor color = QColorDialog::getColor(textCursor.charFormat().background().color(), this,
                                                    "Select Text Highlight Color", QColorDialog::ShowAlphaChannel);
        if (color.isValid()) {
            format.setBackground(QBrush(color));
            ui->textEdit->mergeCurrentCharFormat(format);
            textHighlightButton->setColor(color);
        }
        ui->textEdit->setFocus();
    });

    // Paragraph: Numbered/Bulleted/Check List, Alignment (left, center, right, justify), Indent Left/Right
    QToolButton *numberedListButton = new QToolButton;
    QAction *numberedListAction = new QAction;
    numberedListAction->setToolTip(tr("Numbered List\n(Ctrl+Shift+7)"));
    numberedListAction->setIcon(QIcon(":/icons/numbers.png"));
    numberedListAction->setShortcut(QKeySequence(Qt::CTRL | Qt::SHIFT | Qt::Key_7));
    numberedListAction->setCheckable(true);
    numberedListButton->setPopupMode(QToolButton::MenuButtonPopup);
    numberedListButton->setDefaultAction(numberedListAction);
    ui->ribbonTabWidget->addSmallButton("Home", "Paragraph", numberedListButton, 0, 0);
    QToolButton *bulletedListButton = new QToolButton;
    QAction *bulletedListAction = new QAction;
    bulletedListAction->setToolTip(tr("Bulleted List\n(Ctrl+Shift+8)"));
    bulletedListAction->setIcon(QIcon(":/icons/bullets.png"));
    bulletedListAction->setShortcut(QKeySequence(Qt::CTRL | Qt::SHIFT | Qt::Key_8));
    bulletedListAction->setCheckable(true);
    bulletedListButton->setPopupMode(QToolButton::MenuButtonPopup);
    bulletedListButton->setDefaultAction(bulletedListAction);
    ui->ribbonTabWidget->addSmallButton("Home", "Paragraph", bulletedListButton, 0, 1);
    QToolButton *checkListButton = new QToolButton;
    QAction *checkListAction = new QAction;
    checkListAction->setToolTip(tr("Check List\n(Ctrl+Shift+9)"));
    checkListAction->setIcon(QIcon(":/icons/checklist.png"));
    checkListAction->setShortcut(QKeySequence(Qt::CTRL | Qt::SHIFT | Qt::Key_9));
    checkListAction->setCheckable(true);
    checkListButton->setPopupMode(QToolButton::MenuButtonPopup);
    checkListButton->setDefaultAction(checkListAction);
    ui->ribbonTabWidget->addSmallButton("Home", "Paragraph", checkListButton, 0, 2);
    QToolButton *alignment = new QToolButton;
    alignment->setToolTip(tr("Text Alignment"));
    alignment->setIcon(QIcon(":/icons/align_left.png"));
    ui->ribbonTabWidget->addSmallButton("Home", "Paragraph", alignment, 1, 0);
    alignment->setPopupMode(QToolButton::MenuButtonPopup);
    QToolButton *indentLeftButton = new QToolButton;
    QAction *indentLeftAction = new QAction;
    indentLeftAction->setToolTip(tr("Indent Line Left\n(Ctrl+[)"));
    indentLeftAction->setIcon(QIcon(":/icons/not_indent.png"));
    indentLeftAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_BracketLeft));
    indentLeftButton->setDefaultAction(indentLeftAction);
    ui->ribbonTabWidget->addSmallButton("Home", "Paragraph", indentLeftButton, 1, 1);
    QToolButton *indentRightButton = new QToolButton;
    QAction *indentRightAction = new QAction;
    indentRightAction->setToolTip(tr("Indent Line Right\n(Ctrl+])"));
    indentRightAction->setIcon(QIcon(":/icons/indent.png"));
    indentRightAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_BracketRight));
    indentRightButton->setDefaultAction(indentRightAction);
    ui->ribbonTabWidget->addSmallButton("Home", "Paragraph", indentRightButton, 1, 2);

    // Add button functionality
    connect(numberedListAction, &QAction::triggered, this, [=]{
        // todo: add continue past list
        QTextCursor textCursor = ui->textEdit->textCursor();
        textCursor.beginEditBlock();
        QTextBlockFormat format = textCursor.blockFormat();
        QTextListFormat listFormat;

        if(!numberedListButton->isChecked()) {
            format.setObjectIndex(0);
            textCursor.setBlockFormat(format);
            textCursor.endEditBlock();
            return;
        }

        if(textCursor.currentList()) {
            listFormat = textCursor.currentList()->format();
        } else {
            listFormat.setIndent(format.indent() + 1);
            format.setIndent(0);
            textCursor.setBlockFormat(format);
        }
        listFormat.setStyle(QTextListFormat::ListDecimal);
        textCursor.createList(listFormat);
        textCursor.endEditBlock();
        ui->textEdit->setFocus();
    });
    connect(indentLeftAction, &QAction::triggered, this, [=]{
        QTextCursor textCursor = ui->textEdit->textCursor();
        QTextBlockFormat format = textCursor.blockFormat();
        format.setIndent(format.indent() > 0 ? format.indent() - 1 : 0);
        textCursor.setBlockFormat(format);
        ui->textEdit->setFocus();
    });
    connect(indentRightAction, &QAction::triggered, this, [=]{
        QTextCursor textCursor = ui->textEdit->textCursor();
        QTextBlockFormat format = textCursor.blockFormat();
        format.setIndent(format.indent() + 1);
        textCursor.setBlockFormat(format);
        ui->textEdit->setFocus();
    });


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
        ui->textEdit->setFocus();
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

    // Set ribbon to home tab
    ui->ribbonTabWidget->setCurrentIndex(1);

    // Set default font (for when everything in the document gets deleted)
    QFont font = ui->textEdit->currentCharFormat().font();
    font.setPointSize(9);
    ui->textEdit->document()->setDefaultFont(font);

    // Update buttons based on current text char format
    connect(ui->textEdit, &QTextEdit::currentCharFormatChanged, this, [=](const QTextCharFormat &f){
        QTextCursor textCursor = ui->textEdit->textCursor();

        // If text has selection, check for formatting
        // (if there is formatted + nonformatted, button is unchecked, other is checked)
        // for example: plaintext**boldtext** (button is unchecked). **boldtext** (button is checekd)
        if(textCursor.hasSelection()) {
            // Convert selection to HTML to search for formatting
            QString selection = textCursor.selection().toHtml();

            // <span style=[all text, excludes >]>[all text, excludes <]</span>
            // Note: in html, < is &lt; and > is &gt; so no worries of user writing < or >
            static QRegularExpression formattingTags(R"(<span style=[^>]+>[^<]+</span>)");

            // Store all style tags in a string list
            QRegularExpressionMatchIterator iterator = formattingTags.globalMatch(selection);
            QStringList formattedText;

            // Store length of different text formats
            int boldTextLength = 0;
            int italicTextLength = 0;
            int underlineTextLength = 0;
            int superscriptTextLength = 0;
            int subscriptTextLength = 0;
            int plainTextLength = textCursor.selection().toPlainText().length();

            // Find amount of formatted text
            while(iterator.hasNext()) {
                QString match = iterator.next().captured(0);
                formattedText.append(match);

                // Get plain text
                QString innerText = match.mid(match.indexOf(">") + 1, match.lastIndexOf("<") -
                                              match.indexOf(">") - 1);

                // <span style="[text]">
                QString tagInfo = match.first(match.indexOf(">"));

                if(tagInfo.contains("font-weight")) {
                    boldTextLength += innerText.length();
                }
                if(tagInfo.contains("font-style")) {
                    italicTextLength += innerText.length();
                }
                if(tagInfo.contains("text-decoration")) {
                    underlineTextLength += innerText.length();
                }
                if(tagInfo.contains("super")) {
                    superscriptTextLength += innerText.length();
                }
                if(tagInfo.contains("sub")) {
                    subscriptTextLength += innerText.length();
                }
                qDebug() << "Match vs inner text:" << match << "   " << innerText;
            }

            // True if all text is the given format, otherwise false
            boldButton->setChecked(boldTextLength == plainTextLength);
            italicButton->setChecked(italicTextLength == plainTextLength);
            underlineButton->setChecked(underlineTextLength == plainTextLength);
            superscriptButton->setChecked(superscriptTextLength == plainTextLength);
            subscriptButton->setChecked(subscriptTextLength == plainTextLength);
        } else {
            // Check if formats are currently applied if there is no selection
            boldButton->setChecked(f.fontWeight() == QFont::Bold);
            italicButton->setChecked(f.fontItalic());
            underlineButton->setChecked(f.fontUnderline());
            subscriptButton->setChecked(f.verticalAlignment() == QTextCharFormat::AlignSubScript);
            superscriptButton->setChecked(f.verticalAlignment() == QTextCharFormat::AlignSuperScript);
        }

        // Update font info and colors info
        fontBox->setCurrentFont(f.font());
        fontSizeBox->setEditText(QString::number(f.font().pointSize()));
        textColorButton->setColor(f.foreground().color());
        if(f.background().style() == Qt::NoBrush) {
            textHighlightButton->setColor(QColor(0, 0, 0, 0));
        } else {
            textHighlightButton->setColor(f.background().color());
        }
    });

    // Update paragraph formatting information
    connect(ui->textEdit, &QTextEdit::cursorPositionChanged, this, [=]() {
        QTextCursor textCursor = ui->textEdit->textCursor();
        numberedListButton->setChecked(textCursor.currentList());
    });
    connect(ui->textEdit->document(), &QTextDocument::contentsChanged, this, [=]() {
        QTextCursor textCursor = ui->textEdit->textCursor();
        numberedListButton->setChecked(textCursor.currentList());
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

