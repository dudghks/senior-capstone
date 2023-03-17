#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPixmap>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap logo(":/img/img/logo_temp.png");
    ui->logoLabelPic->setPixmap(logo.scaled(ui->logoLabelPic->width(),
                                            ui->logoLabelPic->height(), Qt::KeepAspectRatio));

    // Define style sheet for the new document block
    ui->templateFrame->setStyleSheet("QFrame {background-color:#FFFFFF;}"
                                     "QPushButton {background-color:#FFFFFF;}"
                                     "QPushButton:hover {background-color:#1F7CF6;}");

    // Clicking template selection -> document page
    connect(ui->templateOne, &QPushButton::clicked, this, [this]{ui->stackedWidget->setCurrentIndex(1);});
    connect(ui->templateTwo, &QPushButton::clicked, this, [this]{ui->stackedWidget->setCurrentIndex(1);});
    connect(ui->templateThree, &QPushButton::clicked, this, [this]{ui->stackedWidget->setCurrentIndex(1);});
    connect(ui->templateNone, &QPushButton::clicked, this, [this]{ui->stackedWidget->setCurrentIndex(1);});

    // Hide dock title bar
    ui->ribbonDockWidget->setTitleBarWidget(new QWidget());;

    // Add test tab
    ui->ribbonTabWidget->addTab("Project");

    QToolButton *openProjectButton = new QToolButton;
    openProjectButton->setText(tr("Open"));
    openProjectButton->setToolTip(tr("Open existing project"));
    openProjectButton->setIcon(QIcon(":/img/img/logo_temp.png"));
    ui->ribbonTabWidget->addButton("Project", "Project", openProjectButton);
}

MainWindow::~MainWindow()
{
    delete ui;
}

