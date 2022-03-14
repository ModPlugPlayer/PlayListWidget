#include "MainWindow.hpp"
#include "./ui_MainWindow.h"
#include "PlayListItemWidget.hpp"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->listWidget, &PlayListWidget::fileDropped, this, &MainWindow::onFileDropped);
}

void MainWindow::onFileDropped(QUrl fileUrl, int droppedIndex)
{
    PlayListItem item;
    item.itemNumber = droppedIndex;
    item.fileName = fileUrl.fileName();
    item.title = fileUrl.fileName();
    ui->listWidget->addPlayListItem(item, droppedIndex);
}

void MainWindow::onFilesDropped(QList<QUrl> filesUrl, int droppedIndex)
{

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_Add_clicked()
{
    PlayListItem item;
    item.itemNumber = ui->listWidget->count();
    ui->listWidget->addPlayListItem(item);
    //ui->listWidget->insertItem(ui->listWidget->count(), QString::number(ui->listWidget->count()));


    //ui->listWidget->addItem(QString::number(ui->listWidget->count()));

}

