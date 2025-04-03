/*
PlayListItemWidget definitions of PlayListWidget
Copyright (C) 2022 Volkan Orhan

This library is free software; you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation; either version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License along with this library; if not, write to the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
*/

#include "PlayListItemWidget.hpp"
#include "ui_PlayListItemWidget.h"
#include <Util/WindowUtil.hpp>

PlayListItemWidget::PlayListItemWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlayListItemWidget) {
    init();
}

PlayListItemWidget::PlayListItemWidget(QWidget * parent, const PlayListItem & playListItem) :
    QWidget(parent),
    ui(new Ui::PlayListItemWidget) {
    init();
    setData(playListItem);
    setItemNumber(playListItem.itemNumber);
}

PlayListItemWidget::~PlayListItemWidget() {
    disconnectSignals();
    delete ui;
}

PlayListItem PlayListItemWidget::getData() const {
    return data;
}

void PlayListItemWidget::setData(const PlayListItem & playListItem) {
    data = playListItem;
    ui->format->setText(QString::fromStdString(playListItem.songFileInfo.songInfo.songFormat).toUpper());
    ui->titleInfoWidget->setFilePath(playListItem.songFileInfo.filePath);
    ui->duration->setTime(playListItem.songFileInfo.songInfo.songDuration);

    QString title = QString::fromStdString(playListItem.songFileInfo.songInfo.songTitle);
    if(title.trimmed().isEmpty())
        title = QString::fromStdString(playListItem.songFileInfo.filePath.stem().string());
    ui->titleInfoWidget->setTitle(title);
}

boost::uuids::uuid PlayListItemWidget::getId() const {
    return data.id;
}

size_t PlayListItemWidget::getItemNumber() const {
    return data.itemNumber;
}

void PlayListItemWidget::setItemNumber(size_t itemNumber) {
    data.itemNumber = itemNumber;
    ui->statusWidget->setItemNumber(itemNumber);
}

QString PlayListItemWidget::getTitle() const {
    return QString::fromStdString(data.songFileInfo.songInfo.songTitle);
}

QString PlayListItemWidget::getFormat() const {
    return QString::fromStdString(data.songFileInfo.songInfo.songFormat);
}

void PlayListItemWidget::setStatus(PlayingState status) {
    ui->statusWidget->setStatus(status);
    switch(status) {
        case PlayingState::Playing:
            ui->duration->setFontWeight(QFont::Weight::Bold);
            ui->titleInfoWidget->setFontWeight(QFont::Weight::Bold);
            WindowUtil::setFontWeight(ui->format, QFont::Weight::Bold);
            break;
        case PlayingState::Paused:
        case PlayingState::Stopped:
            ui->duration->setFontWeight(QFont::Weight::Normal);
            ui->titleInfoWidget->setFontWeight(QFont::Weight::Normal);
            WindowUtil::setFontWeight(ui->format, QFont::Weight::Normal);
            break;
    }
}

PlayingState PlayListItemWidget::getStatus() {
    return ui->statusWidget->getStatus();
}

void PlayListItemWidget::onPlayClickFromStatusWidget() {
    emit playRequested(data);
}

void PlayListItemWidget::onPauseClickFromStatusWidget() {
    emit pauseRequested(data);
}

void PlayListItemWidget::onResumeClickFromStatusWidget() {
    emit resumeRequested(data);
}

void PlayListItemWidget::init() {
    ui->setupUi(this);
    SongFormatFont = new QFont("BodoniXT", QFont::Thin, -1, false);
    SongFormatFont->setPixelSize(32);
    SongDurationFont = new QFont("Seven Segment", QFont::Normal);
    SongDurationFont->setPixelSize(32);
    ItemNumberFont = new QFont("BodoniXT", QFont::Light, -1, false);
    ItemNumberFont->setPixelSize(32);
    ui->duration->setNumberFont(*SongDurationFont);
    ui->duration->setColonFont(*SongDurationFont);
    ui->format->setFont(*SongFormatFont);
    ui->statusWidget->setItemNumberFont(*ItemNumberFont);
    setMouseTracking(true);
    setAttribute(Qt::WA_Hover);
    connectSignals();
}

void PlayListItemWidget::connectSignals() {
    connect(ui->statusWidget, &PlayListItemStatusWidget::playRequested, this, &PlayListItemWidget::onPlayClickFromStatusWidget);
    connect(ui->statusWidget, &PlayListItemStatusWidget::pauseRequested, this, &PlayListItemWidget::onPauseClickFromStatusWidget);
    connect(ui->statusWidget, &PlayListItemStatusWidget::resumeRequested, this, &PlayListItemWidget::onResumeClickFromStatusWidget);
}

void PlayListItemWidget::disconnectSignals() {
    disconnect(ui->statusWidget, &PlayListItemStatusWidget::playRequested, this, &PlayListItemWidget::onPlayClickFromStatusWidget);
    disconnect(ui->statusWidget, &PlayListItemStatusWidget::pauseRequested, this, &PlayListItemWidget::onPauseClickFromStatusWidget);
    disconnect(ui->statusWidget, &PlayListItemStatusWidget::resumeRequested, this, &PlayListItemWidget::onResumeClickFromStatusWidget);
}

void PlayListItemWidget::enterEvent(QEnterEvent *event) {
    event->accept();
    ui->statusWidget->showOnlyPlayPauseButton();
    //setStyleSheet("background-color: rgba(128, 128, 128, 48);");
}

void PlayListItemWidget::leaveEvent(QEvent *event) {
    event->accept();
    ui->statusWidget->showOnlyItemNumber();
    //setStyleSheet("");
}

const std::filesystem::path & PlayListItemWidget::getFilePath() const {
    return data.songFileInfo.filePath;
}

size_t PlayListItemWidget::getDuration() const {
    return data.songFileInfo.songInfo.songDuration;
}

