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

    // Initially hide the ribbon until in the document page
    ui->ribbonDockWidget->setVisible(false);

    // Hide dock title bar
    ui->ribbonDockWidget->setTitleBarWidget(new QWidget());;

    // Add file tab and buttons
    ui->ribbonTabWidget->addTab("File");

    // New, Open, Save, Save As buttons
    QToolButton *newDocButton = new QToolButton;
    newDocButton->setText(tr("New"));
    newDocButton->setToolTip(tr("Open new project"));
    newDocButton->setIcon(QIcon(":/img/img/logo_temp.png"));
    ui->ribbonTabWidget->addButton("File", "Files", newDocButton);
    QToolButton *openDocButton = new QToolButton;
    openDocButton->setText(tr("Open"));
    openDocButton->setToolTip(tr("Open existing project"));
    openDocButton->setIcon(QIcon(":/img/img/logo_temp.png"));
    ui->ribbonTabWidget->addButton("File", "Files", openDocButton);
    QToolButton *saveDocButton = new QToolButton;
    saveDocButton->setText(tr("Save"));
    saveDocButton->setToolTip(tr("Save current project"));
    saveDocButton->setIcon(QIcon(":/img/img/logo_temp.png"));
    ui->ribbonTabWidget->addButton("File", "Files", saveDocButton);
    QToolButton *saveDocAsButton = new QToolButton;
    saveDocAsButton->setText(tr("Save As"));
    saveDocAsButton->setToolTip(tr("Save current project as"));
    saveDocAsButton->setIcon(QIcon(":/img/img/logo_temp.png"));
    ui->ribbonTabWidget->addButton("File", "Files", saveDocAsButton);

    // Print, export buttons
    QToolButton *printDocButton = new QToolButton;
    printDocButton->setText(tr("Print"));
    printDocButton->setToolTip(tr("Print current project"));
    printDocButton->setIcon(QIcon(":/img/img/logo_temp.png"));
    ui->ribbonTabWidget->addButton("File", "Share", printDocButton);
    QToolButton *exportDocButton = new QToolButton;
    exportDocButton->setText(tr("Export"));
    exportDocButton->setToolTip(tr("Open existing project"));
    exportDocButton->setIcon(QIcon(":/img/img/logo_temp.png"));
    ui->ribbonTabWidget->addButton("File", "Share", exportDocButton);

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

}

MainWindow::~MainWindow()
{
    delete ui;
}

