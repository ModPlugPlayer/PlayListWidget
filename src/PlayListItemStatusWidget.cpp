/*
PlayListHeaderStatusWidget definitions of PlayListWidget
Copyright (C) 2022 Volkan Orhan

This library is free software; you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation; either version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License along with this library; if not, write to the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
*/

#include "PlayListItemStatusWidget.hpp"
#include "ui_PlayListItemStatusWidget.h"
#include <SVGIcon.hpp>
#include <ResourceUtil.hpp>


void PlayListItemStatusWidget::setItemNumber(size_t itemNumber) {
    ui->itemNumberLabel->setText(QString::number(itemNumber));
}

void PlayListItemStatusWidget::showOnlyItemNumber() {
    ui->playPauseButton->hide();
    ui->itemNumberLabel->show();
}

void PlayListItemStatusWidget::showOnlyPlayPauseButton() {
    ui->itemNumberLabel->hide();
    ui->playPauseButton->show();
}

void PlayListItemStatusWidget::setStatus(PlayingStatus status) {
    this->status = status;
    switch(status) {
    case PlayingStatus::Paused:
        ui->playPauseButton->setIcon(iconPause->getActiveIcon());
        break;
    case PlayingStatus::Playing:
        ui->playPauseButton->setIcon(iconPause->getInactiveIcon());
        break;
    case PlayingStatus::Stopped:
        ui->playPauseButton->setIcon(iconPlay->getInactiveIcon());
        break;
    }
}

void PlayListItemStatusWidget::setItemNumberFont(QFont &font) {
    ui->itemNumberLabel->setFont(font);
}

PlayingStatus PlayListItemStatusWidget::getStatus() {
    return status;
}

PlayListItemStatusWidget::PlayListItemStatusWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlayListItemStatusWidget) {
    ui->setupUi(this);
    showOnlyItemNumber();
    QObject::connect(ui->playPauseButton, &QPushButton::clicked, this, &PlayListItemStatusWidget::onClick);
    iconPlay = new SVGIcon(ResourceUtil::getResourceContent(":/Graphics/Vectoral/play.svg"), "#00ff00");
    iconPause = new SVGIcon(ResourceUtil::getResourceContent(":/Graphics/Vectoral/pause.svg"), "#00ff00");
    iconStop = new SVGIcon(ResourceUtil::getResourceContent(":/Graphics/Vectoral/stop.svg"), "#00ff00");
    iconRewind = new SVGIcon(ResourceUtil::getResourceContent(":/Graphics/Vectoral/rewind.svg"), "#00ff00");
    iconFastForward = new SVGIcon(ResourceUtil::getResourceContent(":/Graphics/Vectoral/fastforward.svg"), "#00ff00");
    iconPrevious = new SVGIcon(ResourceUtil::getResourceContent(":/Graphics/Vectoral/previous.svg"), "#00ff00");
    iconNext = new SVGIcon(ResourceUtil::getResourceContent(":/Graphics/Vectoral/next.svg"), "#00ff00");

    icons.push_back(iconPlay);
    icons.push_back(iconPause);
    icons.push_back(iconStop);
    icons.push_back(iconRewind);
    icons.push_back(iconFastForward);
    icons.push_back(iconPrevious);
    icons.push_back(iconNext);
}

PlayListItemStatusWidget::~PlayListItemStatusWidget() {
    iconPlay->deleteLater();
    iconPause->deleteLater();
    iconStop->deleteLater();
    iconRewind->deleteLater();
    iconFastForward->deleteLater();
    iconPrevious->deleteLater();
    iconNext->deleteLater();
    delete ui;
}

void PlayListItemStatusWidget::onClick() {
    switch(status) {
    case PlayingStatus::Playing:
        emit pauseRequested();
        break;
    case PlayingStatus::Paused:
        emit resumeRequested();
        break;
    case PlayingStatus::Stopped:
        emit playRequested();
        break;
    }
}

void PlayListItemStatusWidget::refreshStyleSheet() {
    /*
    QString style = QString("background-color:%1; color:%2;").arg(backgroundColor.hex().c_str(), textColor.hex().c_str());
    for(QPushButton * button : buttons) {
        button->setStyleSheet(style);
    }*/
}
