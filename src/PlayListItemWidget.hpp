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
#include <APIStructures.hpp>
#include <filesystem>
#include <QtWidgets>

namespace Ui {
class PlayListItemWidget;
}

using namespace ModPlugPlayer;

class PlayListItemWidget : public QWidget
{
    Q_OBJECT

    public:
        explicit PlayListItemWidget(QWidget *parent = nullptr);
        explicit PlayListItemWidget(QWidget *parent, const PlayListItem &playListItem);
        ~PlayListItemWidget();

        PlayListItem getData() const;
        void setData(const PlayListItem &playListItem);

        boost::uuids::uuid getId() const;

        size_t getItemNumber() const;
        void setItemNumber(size_t itemNumber);

        const std::filesystem::path & getFilePath() const;

        size_t getDuration() const;

        QString getTitle() const;

        QString getFormat() const;

        void setStatus(PlayingStatus status);
        PlayingStatus getStatus();

    signals:
        void pauseRequested(ModPlugPlayer::PlayListItem playListItem);
        void resumeRequested(ModPlugPlayer::PlayListItem playListItem);
        void playRequested(ModPlugPlayer::PlayListItem playListItem);

    private slots:
        void onPlayClickFromStatusWidget();
        void onPauseClickFromStatusWidget();
        void onResumeClickFromStatusWidget();

    private:
        Ui::PlayListItemWidget *ui;
        PlayListItem data;
        QFont *SongDurationFont;
        QFont *SongFormatFont;
        QFont *ItemNumberFont;

    protected:
        void enterEvent(QEnterEvent *event);
        void leaveEvent(QEvent *event);
        void init();
        void connectSignals();
        void disconnectSignals();
};

