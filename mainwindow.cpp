#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "blocktextedit.h"
#include <QTextDocument>
#include <QPixmap>
#include <QPageSize>
#include <QSizeF>
#include <QScrollBar>
#include <QTextCursor>
#include <QPrinter>
#include <QFontComboBox>
#include <QSpinBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap logo(":/img/img/logo_temp.png");
    ui->logoLabelPic->setPixmap(logo.scaled(ui->logoLabelPic->width(),
                                            ui->logoLabelPic->height(), Qt::KeepAspectRatio));

    // Set background color
    ui->stackedWidget->setStyleSheet("QWidget#documentPage, QWidget#welcomePage {"
                                     "  background-color: #EAEAEA;"
                                     "}");

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
    ui->ribbonTabWidget->addSmallButton("Home", "Clipboard", cutButton, 0, 0);
    QToolButton *copyButton = new QToolButton;
    copyButton->setToolTip(tr("Copy selection to clipboard\n(Ctrl+C)"));
    copyButton->setText("Copy");
    copyButton->setIcon(QIcon(":/icons/copy.png"));
    copyButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    ui->ribbonTabWidget->addSmallButton("Home", "Clipboard", copyButton, 1, 0);
    QToolButton *pasteButton = new QToolButton;
    pasteButton->setToolTip(tr("Paste selection to document\n(Ctrl+V)"));
    pasteButton->setText("Paste");
    pasteButton->setIcon(QIcon(":/icons/paste.png"));
    pasteButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    ui->ribbonTabWidget->addSmallButton("Home", "Clipboard", pasteButton, 0, 1);
    QToolButton *findButton = new QToolButton;
    findButton->setToolTip(tr("Search for text within the document\n(Ctrl+F)"));
    findButton->setText("Find");
    findButton->setIcon(QIcon(":/icons/find.png"));
    findButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    ui->ribbonTabWidget->addSmallButton("Home", "Clipboard", findButton, 1, 1);
    QToolButton *undoButton = new QToolButton;
    undoButton->setToolTip(tr("Undo recent changes\n(Ctrl+Z"));
    undoButton->setText("Undo");
    undoButton->setIcon(QIcon(":/icons/undo.png"));
    undoButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    ui->ribbonTabWidget->addSmallButton("Home", "Clipboard", undoButton, 0, 2);
    QToolButton *redoButton = new QToolButton;
    redoButton->setToolTip(tr("Reverse recent undo\nCtrl+Y"));
    redoButton->setText("Redo");
    redoButton->setIcon(QIcon(":/icons/redo.png"));
    redoButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    ui->ribbonTabWidget->addSmallButton("Home", "Clipboard", redoButton, 1, 2);

    // Font: Font, Font Size, Bold, Italics, Underline, Subscript, Superscript, Color, Highlight
    QFontComboBox *fontBox = new QFontComboBox;
    ui->ribbonTabWidget->addSmallButton("Home", "Font", fontBox, 0, 0);
    QSpinBox *fontSizeBox = new QSpinBox;
    ui->ribbonTabWidget->addSmallButton("Home", "Font", fontSizeBox, 0, 4);
    QToolButton *boldButton = new QToolButton;
    boldButton->setToolTip(tr("Bold"));
    boldButton->setIcon(QIcon(":/icons/bold.png"));
    ui->ribbonTabWidget->addSmallButton("Home", "Font", boldButton, 1, 0);
    QToolButton *italicButton = new QToolButton;
    italicButton->setToolTip(tr("Italics"));
    italicButton->setIcon(QIcon(":/icons/italic.png"));
    ui->ribbonTabWidget->addSmallButton("Home", "Font", italicButton, 1, 1);
    QToolButton *underlineButton = new QToolButton;
    underlineButton->setToolTip(tr("Underline"));
    underlineButton->setIcon(QIcon(":/icons/underline.png"));
    ui->ribbonTabWidget->addSmallButton("Home", "Font", underlineButton, 1, 2);
    QToolButton *superscriptButton = new QToolButton;
    superscriptButton->setToolTip(tr("Superscript"));
    superscriptButton->setIcon(QIcon(":/icons/superscript.png"));
    ui->ribbonTabWidget->addSmallButton("Home", "Font", superscriptButton, 0, 5);
    QToolButton *subscriptButton = new QToolButton;
    subscriptButton->setToolTip(tr("Subscript"));
    subscriptButton->setIcon(QIcon(":/icons/subscript.png"));
    ui->ribbonTabWidget->addSmallButton("Home", "Font", subscriptButton, 1, 5);
    QToolButton *textColorButton = new QToolButton;
    textColorButton->setToolTip(tr("Change Text Color"));
    textColorButton->setIcon(QIcon(":/img/img/logo_temp.png"));
    ui->ribbonTabWidget->addSmallButton("Home", "Font", textColorButton, 1, 3);
    textColorButton->setPopupMode(QToolButton::MenuButtonPopup);
    QToolButton *textHighlightButton = new QToolButton;
    textHighlightButton->setToolTip(tr("Change Text Highlight"));
    textHighlightButton->setIcon(QIcon(":/img/img/logo_temp.png"));
    ui->ribbonTabWidget->addSmallButton("Home", "Font", textHighlightButton, 1, 4);
    textHighlightButton->setPopupMode(QToolButton::MenuButtonPopup);


    // Change the border of the QTextEdit
    ui->textEdit->setStyleSheet("QTextEdit {"
                                "   border: 1px solid #C0C0C0;"
                                "   background: #FFFFFF"
                                "}");


    // Create Text Document for the editor
    // Establish page size
    QTextDocument *textDocument = new QTextDocument;
    ui->textEdit->setDocument(textDocument);
    QPrinter printer;
    printer.setPageSize(QPageSize(QPageSize::Letter));
    textDocument->setPageSize(printer.pageRect(QPrinter::DevicePixel).size());
    qreal dpi = printer.resolution();
    ui->textEdit->setFixedSize(textDocument->pageSize().toSize());
    textDocument->setDocumentMargin(dpi); // Establish margin

    // Sync QTextEdit Scroll bar with the one on the side of the screen
    /// \todo: make this a scroll area
    connect(ui->textEdit->verticalScrollBar(), &QScrollBar::rangeChanged, this, [=](int min, int max) {ui->textVerticalScrollBar->setRange(min, max);
                                                                                  ui->textVerticalScrollBar->setValue(ui->textEdit->verticalScrollBar()->value());
                                                                                });
    connect(ui->textVerticalScrollBar, &QScrollBar::valueChanged, this, [=](int value) {ui->textEdit->verticalScrollBar()->setValue(value);
                                                                                  ui->textVerticalScrollBar->setPageStep(ui->textEdit->verticalScrollBar()->pageStep());
                                                                                  ui->textVerticalScrollBar->setSingleStep(ui->textEdit->verticalScrollBar()->singleStep());
                                                                                 });
    connect(ui->textVerticalScrollBar, SIGNAL(valueChanged(int)), ui->textEdit->verticalScrollBar(), SLOT(setValue(int)));


}

MainWindow::~MainWindow()
{
    delete ui;
}

