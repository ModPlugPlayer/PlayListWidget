/*
PlayListItemWidget declarations of PlayListWidget
Copyright (C) 2022 Volkan Orhan

This library is free software; you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation; either version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License along with this library; if not, write to the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
*/

#pragma once
#include <QWidget>
#include "PlayListDTOs.hpp"

namespace Ui {
class PlayListItemWidget;
}

class PlayListItemWidget : public QWidget
{
    Q_OBJECT

    public:
        explicit PlayListItemWidget(QWidget *parent = nullptr);
        explicit PlayListItemWidget(QWidget *parent, const PlayListItem &playListItem);
        ~PlayListItemWidget();

        PlayListItem getData() const;
        void setData(const PlayListItem &playListItem);

        size_t getItemNumber() const;
        void setItemNumber(size_t itemNumber);

        const QString & getFileName() const;
        void setFileName(const QString & fileName);

        size_t getDuration() const;
        void setDuration(size_t duration);

        const QString & getTitle() const;
        void setTitle(const QString & title);

        const QString & getFormat() const;
        void setFormat(const QString & format);
    private:
    Ui::PlayListItemWidget *ui;
    PlayListItem data;
};

