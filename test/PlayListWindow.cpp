/*
PlayListWindow class definitions for the test purposes of PlayListWidget
Copyright (C) 2022 Volkan Orhan

This library is free software; you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation; either version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License along with this library; if not, write to the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
*/

#include "PlayListWindow.hpp"
#include "./ui_PlayListWindow.h"
#include "PlayListItemWidget.hpp"

PlayListWindow::PlayListWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::PlayListWindow)
{
    ui->setupUi(this);
    connect(ui->listWidget, &PlayListWidget::fileDropped, this, &PlayListWindow::onFileDropped);
    connect(ui->listWidget, &PlayListWidget::filesDropped, this, &PlayListWindow::onFilesDropped);
    ui->listWidget->setDragDropMode(QAbstractItemView::InternalMove);
    windowGeometry = geometry();
    windowGeometry.setX(parent->geometry().x());
    windowGeometry.setY(parent->geometry().y());
    //ui->listWidget.model().rowsMoved.connect(lambda: anyfunction())
}

void PlayListWindow::onFileDropped(QUrl fileUrl, int droppedIndex)
{
    PlayListItem item;
    item.itemNumber = droppedIndex;
    item.filePath = fileUrl.path().toStdString();
    item.title = fileUrl.fileName();
    ui->listWidget->addPlayListItem(item, droppedIndex);
}

void PlayListWindow::onFilesDropped(QList<QUrl> fileUrls, int droppedIndex)
{
    QList<PlayListItem> items;
    for(QUrl &fileUrl:fileUrls) {
        PlayListItem item;
        item.itemNumber = droppedIndex;
        item.filePath = fileUrl.path().toStdString();
        item.title = fileUrl.fileName();
        items.append(item);
    }
    ui->listWidget->addPlayListItems(items, droppedIndex);
}

PlayListWindow::~PlayListWindow()
{
    delete ui;
}

void PlayListWindow::closeEvent(QCloseEvent * event)
{
}

void PlayListWindow::showEvent(QShowEvent * event)
{
    setGeometry(windowGeometry);
}

void PlayListWindow::hideEvent(QHideEvent * event)
{
    windowGeometry = geometry();
    emit hidden();
}

void PlayListWindow::on_Add_clicked()
{
    PlayListItem item;
    item.itemNumber = ui->listWidget->count();
    ui->listWidget->addPlayListItem(item);
    //ui->listWidget->insertItem(ui->listWidget->count(), QString::number(ui->listWidget->count()));


    //ui->listWidget->addItem(QString::number(ui->listWidget->count()));

}

void PlayListWindow::on_Remove_clicked()
{
    ui->listWidget->removeSelectedItems();
}
