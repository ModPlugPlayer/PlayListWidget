#include "MainWindow.hpp"
#include "./ui_MainWindow.h"
#include "PlayListItemWidget.hpp"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->listWidget, &PlayListWidget::fileDropped, this, &MainWindow::onFileDropped);
    connect(ui->listWidget, &PlayListWidget::filesDropped, this, &MainWindow::onFilesDropped);
}

void MainWindow::onFileDropped(QUrl fileUrl, int droppedIndex)
{
    PlayListItem item;
    item.itemNumber = droppedIndex;
    item.fileName = fileUrl.fileName();
    item.title = fileUrl.fileName();
    ui->listWidget->addPlayListItem(item, droppedIndex);
}

void MainWindow::onFilesDropped(QList<QUrl> fileUrls, int droppedIndex)
{
    QList<PlayListItem> items;
    for(QUrl &fileUrl:fileUrls) {
        PlayListItem item;
        item.itemNumber = droppedIndex;
        item.fileName = fileUrl.fileName();
        item.title = fileUrl.fileName();
        items.append(item);
    }
    ui->listWidget->addPlayListItems(items);
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


void MainWindow::on_Remove_clicked()
{
    ui->listWidget->removeSelectedItems();
}

