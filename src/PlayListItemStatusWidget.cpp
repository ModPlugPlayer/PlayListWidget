/*
PlayListHeaderStatusWidget definitions of PlayListWidget
Copyright (C) 2022 Volkan Orhan

This library is free software; you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation; either version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License along with this library; if not, write to the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
*/

#include "PlayListItemStatusWidget.hpp"
#include "ui_PlayListItemStatusWidget.h"

void PlayListItemStatusWidget::setItemNumber(size_t itemNumber)
{
    ui->itemNumberLabel->setText(QString::number(itemNumber));
}

void PlayListItemStatusWidget::showOnlyItemNumber()
{
    ui->playPauseButton->hide();
    ui->itemNumberLabel->show();
}

void PlayListItemStatusWidget::showOnlyPlayPauseButton()
{
    ui->itemNumberLabel->hide();
    ui->playPauseButton->show();
}

void PlayListItemStatusWidget::setStatus(PlayingStatus status)
{
    this->status = status;
    switch(status) {
    case PlayingStatus::Paused:
        //ui->playPauseButton->setIcon(iconPause->getActiveIcon());
        break;
    case PlayingStatus::Playing:
    case PlayingStatus::Stopped:
        //ui->playPauseButton->setIcon(iconPlay->getActiveIcon());
        break;
    }
}

PlayingStatus PlayListItemStatusWidget::getStatus()
{
    return status;
}

PlayListItemStatusWidget::PlayListItemStatusWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlayListItemStatusWidget)
{
    ui->setupUi(this);
    showOnlyItemNumber();
    QObject::connect(ui->playPauseButton, &QPushButton::clicked, this, &PlayListItemStatusWidget::onClick);
}

PlayListItemStatusWidget::~PlayListItemStatusWidget()
{
    delete ui;
}

void PlayListItemStatusWidget::onClick()
{
    switch(status) {
    case PlayingStatus::Playing:
        emit pause();
        break;
    case PlayingStatus::Paused:
        emit resume();
        break;
    case PlayingStatus::Stopped:
        emit play();
        break;
    }
}
