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
    setId(playListItem.id);
    setItemNumber(playListItem.itemNumber);
    setFormat(playListItem.format);
    QString title = playListItem.title;
    if(title.trimmed().isEmpty())
        title = QString::fromStdString(playListItem.filePath.stem().string());
    setTitle(title);
    setFilePath(playListItem.filePath);
    setDuration(playListItem.duration);
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
}

boost::uuids::uuid PlayListItemWidget::getId() const {
    return data.id;
}

void PlayListItemWidget::setId(const boost::uuids::uuid &id) {
    data.id = id;
}

size_t PlayListItemWidget::getItemNumber() const {
    return data.itemNumber;
}

void PlayListItemWidget::setItemNumber(size_t itemNumber) {
    data.itemNumber = itemNumber;
    ui->statusWidget->setItemNumber(itemNumber);
}

const QString & PlayListItemWidget::getTitle() const {
    return data.title;
}

void PlayListItemWidget::setTitle(const QString & title) {
    data.title = title;
    ui->title->setText(title);
}

const QString & PlayListItemWidget::getFormat() const {
    return data.title;
}

void PlayListItemWidget::setFormat(const QString & format) {
    data.format = format;
    ui->format->setText(format);
}

void PlayListItemWidget::setStatus(PlayingStatus status) {
    ui->statusWidget->setStatus(status);
    switch(status) {
        case PlayingStatus::Playing:
            WindowUtil::setFontWeight(ui->fileName, QFont::Weight::Bold);
            ui->duration->setFontWeight(QFont::Weight::Bold);
            WindowUtil::setFontWeight(ui->format, QFont::Weight::Bold);
            WindowUtil::setFontWeight(ui->title, QFont::Weight::Bold);
            break;
        case PlayingStatus::Paused:
        case PlayingStatus::Stopped:
            WindowUtil::setFontWeight(ui->fileName, QFont::Weight::Normal);
            ui->duration->setFontWeight(QFont::Weight::Normal);
            WindowUtil::setFontWeight(ui->format, QFont::Weight::Normal);
            WindowUtil::setFontWeight(ui->title, QFont::Weight::Normal);
            break;
    }
}

PlayingStatus PlayListItemWidget::getStatus() {
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
    SongTitleFont = new QFont("Inter", QFont::Normal, -1, false);
    SongTitleFont->setPixelSize(15);
    SongPathFont = new QFont("Inter", QFont::Normal, -1, false);
    SongPathFont->setPixelSize(10);
    ui->duration->setNumberFont(*SongDurationFont);
    ui->duration->setColonFont(*SongDurationFont);
    ui->format->setFont(*SongFormatFont);
    ui->statusWidget->setItemNumberFont(*ItemNumberFont);
    ui->title->setFont(*SongTitleFont);
    ui->fileName->setFont(*SongPathFont);
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
    return data.filePath;
}

void PlayListItemWidget::setFilePath(const std::filesystem::path & filePath) {
    data.filePath = filePath;
    ui->fileName->setText(QString(filePath.c_str()));
}

size_t PlayListItemWidget::getDuration() const {
    return data.duration;
}

void PlayListItemWidget::setDuration(size_t duration) {
    data.duration = duration;
    ui->duration->setTime(duration);
}

