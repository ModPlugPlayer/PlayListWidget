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
    setTitle(playListItem.title);
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

static void setLabelFontWeight(QLabel *label, const QFont::Weight weight) {
    QFont font = label->font();
    font.setWeight(weight);
    label->setFont(font);
}

void PlayListItemWidget::setStatus(PlayingStatus status) {
    ui->statusWidget->setStatus(status);
    switch(status) {
        case PlayingStatus::Playing:
            setLabelFontWeight(ui->fileName, QFont::Weight::Bold);
            setLabelFontWeight(ui->duration, QFont::Weight::Bold);
            setLabelFontWeight(ui->format, QFont::Weight::Bold);
            setLabelFontWeight(ui->title, QFont::Weight::Bold);
            break;
        case PlayingStatus::Paused:
        case PlayingStatus::Stopped:
            setLabelFontWeight(ui->fileName, QFont::Weight::Normal);
            setLabelFontWeight(ui->duration, QFont::Weight::Normal);
            setLabelFontWeight(ui->format, QFont::Weight::Normal);
            setLabelFontWeight(ui->title, QFont::Weight::Normal);
            break;
    }
}

PlayingStatus PlayListItemWidget::getStatus() {
    return ui->statusWidget->getStatus();
}

void PlayListItemWidget::onPlayClickFromStatusWidget() {
    emit play(data);
}

void PlayListItemWidget::onPauseClickFromStatusWidget() {
    emit pause(data);
}

void PlayListItemWidget::onResumeClickFromStatusWidget() {
    emit resume(data);
}

void PlayListItemWidget::init() {
    ui->setupUi(this);
    setMouseTracking(true);
    setAttribute(Qt::WA_Hover);
    connectSignals();
}

void PlayListItemWidget::connectSignals() {
    QObject::connect(ui->statusWidget, &PlayListItemStatusWidget::play, this, &PlayListItemWidget::onPlayClickFromStatusWidget);
    QObject::connect(ui->statusWidget, &PlayListItemStatusWidget::pause, this, &PlayListItemWidget::onPauseClickFromStatusWidget);
    QObject::connect(ui->statusWidget, &PlayListItemStatusWidget::resume, this, &PlayListItemWidget::onResumeClickFromStatusWidget);
}

void PlayListItemWidget::disconnectSignals() {
    QObject::disconnect(ui->statusWidget, &PlayListItemStatusWidget::play, this, &PlayListItemWidget::onPlayClickFromStatusWidget);
    QObject::disconnect(ui->statusWidget, &PlayListItemStatusWidget::pause, this, &PlayListItemWidget::onPauseClickFromStatusWidget);
    QObject::disconnect(ui->statusWidget, &PlayListItemStatusWidget::resume, this, &PlayListItemWidget::onResumeClickFromStatusWidget);
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
    ui->fileName->setText(filePath.c_str());
}

size_t PlayListItemWidget::getDuration() const {
    return data.duration;
}

void PlayListItemWidget::setDuration(size_t duration) {
    data.duration = duration;
    ui->duration->setText(QString::number(duration));
}

