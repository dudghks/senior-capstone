#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTextDocument>
#include <QPixmap>
#include <QPageSize>
#include <QSizeF>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap logo(":/img/img/logo_temp.png");
    ui->logoLabelPic->setPixmap(logo.scaled(ui->logoLabelPic->width(),
                                            ui->logoLabelPic->height(), Qt::KeepAspectRatio));

    // Define style sheet for the new document block
    ui->templateFrame->setStyleSheet("QFrame {"
                                     "  background-color:#FFFFFF;"
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

    // Add test tab
    ui->ribbonTabWidget->addTab("Project");

    QToolButton *openProjectButton = new QToolButton;
    openProjectButton->setText(tr("Open"));
    openProjectButton->setToolTip(tr("Open existing project"));
    openProjectButton->setIcon(QIcon(":/img/img/logo_temp.png"));
    ui->ribbonTabWidget->addButton("Project", "Project", openProjectButton);

    // Change the border of the QTextEdit and establish margins
    ui->textEdit->setStyleSheet("QTextEdit {"
                                "   border: 1px solid #C0C0C0;"
                                "   padding: 100px;"
                                "   background: #FFFFFF"
                                "}");
    // Create Text Document for the editor
    QPageSize pageSize(QPageSize::Letter); // Establish page size
    QSizeF pageSizeF = pageSize.size(QPageSize::Point);
    QTextDocument *textDocument = new QTextDocument;
    textDocument->setPageSize(pageSizeF);
    ui->textEdit->setDocument(textDocument);
}

MainWindow::~MainWindow()
{
    delete ui;
}

