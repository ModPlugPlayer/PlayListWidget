/*
PlayListItemWidget definitions of PlayListWidget
Copyright (C) 2022 Volkan Orhan

This library is free software; you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation; either version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License along with this library; if not, write to the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
*/

#include "PlayListItemWidget.hpp"
#include "ui_PlayListItemWidget.h"

PlayListItemWidget::PlayListItemWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlayListItemWidget)
{
    ui->setupUi(this);
}

PlayListItemWidget::PlayListItemWidget(QWidget * parent, const PlayListItem & playListItem) :
    QWidget(parent),
    ui(new Ui::PlayListItemWidget)
{
    ui->setupUi(this);
    setItemNumber(playListItem.itemNumber);
    setFormat(playListItem.format);
    setTitle(playListItem.title);
    setFileName(playListItem.fileName);
    setDuration(playListItem.duration);
}

PlayListItemWidget::~PlayListItemWidget()
{
    delete ui;
}

PlayListItem PlayListItemWidget::getData() const
{
    return data;
}

void PlayListItemWidget::setData(const PlayListItem & playListItem)
{
    data = playListItem;
}

size_t PlayListItemWidget::getItemNumber() const
{
    return data.itemNumber;
}

void PlayListItemWidget::setItemNumber(size_t itemNumber)
{
    data.itemNumber = itemNumber;
    ui->itemNumber->setText(QString::number(itemNumber));
}

const QString & PlayListItemWidget::getTitle() const
{
    return data.title;
}

void PlayListItemWidget::setTitle(const QString & title)
{
    data.title = title;
    ui->title->setText(title);
}

const QString & PlayListItemWidget::getFormat() const
{
    return data.title;
}

void PlayListItemWidget::setFormat(const QString & format)
{
    data.format = format;
    ui->format->setText(format);
}

const QString & PlayListItemWidget::getFileName() const
{
    return data.fileName;
}

void PlayListItemWidget::setFileName(const QString & fileName)
{
    data.fileName = fileName;
    ui->fileName->setText(fileName);
}

size_t PlayListItemWidget::getDuration() const
{
    return data.duration;
}

void PlayListItemWidget::setDuration(size_t duration)
{
    data.duration = duration;
    ui->duration->setText(QString::number(duration));
}

