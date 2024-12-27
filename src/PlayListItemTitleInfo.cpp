/*
PlayListItemTitleInfo definitions of PlayListWidget
Copyright (C) 2024 Volkan Orhan

This library is free software; you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation; either version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License along with this library; if not, write to the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
*/

#include "PlayListItemTitleInfo.hpp"
#include "ui_PlayListItemTitleInfo.h"
#include <Util/WindowUtil.hpp>

PlayListItemTitleInfo::PlayListItemTitleInfo(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PlayListItemTitleInfo) {
    ui->setupUi(this);
    SongTitleFont = new QFont("Inter", QFont::Normal, -1, false);
    SongTitleFont->setPixelSize(15);
    SongPathFont = new QFont("Inter", QFont::Normal, -1, false);
    SongPathFont->setPixelSize(10);
    ui->title->setFont(*SongTitleFont);
    ui->fileName->setFont(*SongPathFont);
}

PlayListItemTitleInfo::~PlayListItemTitleInfo() {
    delete ui;
}

void PlayListItemTitleInfo::setFilePath(const std::filesystem::path &filePath) {
    ui->fileName->setText(QString(filePath.c_str()));
    ui->fileName->setMinimumWidth(0);
}

void PlayListItemTitleInfo::setTitle(const QString &title) {
    ui->title->setText(title);
    ui->title->setMinimumWidth(0);
}

void PlayListItemTitleInfo::setFontWeight(const QFont::Weight fontWeight) {
    WindowUtil::setFontWeight(ui->fileName, fontWeight);
    WindowUtil::setFontWeight(ui->title, fontWeight);

}
