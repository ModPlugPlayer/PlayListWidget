/*
MainWindow class definitions for the test purposes of PlayListWidget
Copyright (C) 2022 Volkan Orhan

This library is free software; you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation; either version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License along with this library; if not, write to the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
*/

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
    ui->listWidget->addPlayListItems(items, droppedIndex);
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

