/*
PlayListItemTitleInfo declarations of PlayListWidget
Copyright (C) 2024 Volkan Orhan

This library is free software; you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation; either version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License along with this library; if not, write to the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
*/

#pragma once

#include <QWidget>
#include <filesystem>

namespace Ui {
class PlayListItemTitleInfo;
}

class PlayListItemTitleInfo : public QWidget
{
    Q_OBJECT

public:
    explicit PlayListItemTitleInfo(QWidget *parent = nullptr);
    ~PlayListItemTitleInfo();

    void setFilePath(const std::filesystem::path & filePath);
    void setTitle(const QString & title);
    void setFontWeight(const QFont::Weight fontWeight);
    void updateTitle();
    void updateFilePath();

private:
    void resizeEvent(QResizeEvent* event) override;
    Ui::PlayListItemTitleInfo *ui;
    QFont *SongTitleFont;
    QFont *SongPathFont;
    std::filesystem::path filePath;
    QString title;
};
