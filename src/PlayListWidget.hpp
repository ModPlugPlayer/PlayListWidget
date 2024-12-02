/*
PlayListWidget declarations of PlayListWidget
Copyright (C) 2022 Volkan Orhan

This library is free software; you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation; either version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License along with this library; if not, write to the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
*/

#pragma once
#include <QListWidget>
#include <QDragEnterEvent>
#include <QDragLeaveEvent>
#include <QDropEvent>
#include <QDragMoveEvent>
#include <QUrl>
#include <PlayList.hpp>
#include <PlayListDTOs.hpp>
#include "DropIndicator.hpp"
#include "PlayList.hpp"
#include "PlayListItemWidget.hpp"
#include <QMap>
#include <boost/uuid/uuid.hpp>
#include <mutex>

class PlayListWidget : public QListWidget, public PlayList {
    Q_OBJECT
     public:
        explicit PlayListWidget(QWidget *parent = nullptr);
        void addPlayListItem(const PlayListItem & playListItem, int rowIndex = -1);
        void addPlayListItems(const QList<PlayListItem> & playListItems, int rowIndex = -1);
        void removeSelectedItems();
        PlayListItem getCurrentItem() override;

     signals:
        void fileDropped(const QUrl &fileUrl, int droppedIndex);
        void filesDropped(const QList<QUrl> &fileUrls, int droppedIndex);

        void requestMetaData(const ModPlugPlayer::PlayListItem playListItem) override;
        void open(const ModPlugPlayer::PlayListItem playListItem) override;
        void play(const ModPlugPlayer::PlayListItem playListItem) override;
        void pause(const ModPlugPlayer::PlayListItem playListItem) override;
        void resume(const ModPlugPlayer::PlayListItem playListItem) override;
        void stop(const ModPlugPlayer::PlayListItem playListItem) override;
        void repeat(const ModPlugPlayer::RepeatMode repeatMode) override;

    public slots:
        void onMetaData(const ModPlugPlayer::PlayListItem playListItem) override;
        void onOpen(const ModPlugPlayer::PlayListItem playListItem) override;
        void onPlay(const ModPlugPlayer::PlayListItem playListItem) override;
        void onPause(const ModPlugPlayer::PlayListItem playListItem) override;
        void onResume(const ModPlugPlayer::PlayListItem playListItem) override;
        void onStop(const ModPlugPlayer::PlayListItem playListItem) override;
        void onNextSong() override;
        void onPreviousSong() override;
        void onClear() override;
        void onRepeat(const ModPlugPlayer::RepeatMode repeatMode) override;

    private slots:
        void onItemDoubleClicked(QListWidgetItem *item);

    protected:
        void dragEnterEvent(QDragEnterEvent *event) override;
        void dragLeaveEvent(QDragLeaveEvent *event) override;
        void dropEvent(QDropEvent *e) override;
        void dragMoveEvent(QDragMoveEvent *e) override;
        void paintEvent(QPaintEvent *event) override;
        void scrollToItemIfNeeded(QListWidgetItem *listWidgetItem);
        DropIndicator dropIndicator;
        QPointF getDropIndicatorPosition(const QPointF &mousePosition);
        int getDroppingItemDestinationIndex(const QPointF &mousePosition);
        static bool isDropIndicatorOnTopOrBottom(const QRect &itemRectangle, const QPointF &mousePosition);
        /**
         * @brief updateItemNumbers Updates item number of each playlist item.
         * If listItemsLock is not locked outside of this method, this method locks it until this method finishes to make the operation atomic.
         */
        void updateItemNumbers();
        bool isValidDrop(const QPointF &dropPosition);
        void connectPlayListItemSignals(PlayListItemWidget &playListItemWidget);
        void disconnectPlayListItemSignals(PlayListItemWidget &playListItemWidget);
        PlayListItemWidget *currentItem = nullptr;
        std::mutex listItemsLock;
        QMap<boost::uuids::uuid, PlayListItemWidget *> playListMap;
        PlayListItems playList;
        RepeatMode repeatMode = RepeatMode::None;
};
