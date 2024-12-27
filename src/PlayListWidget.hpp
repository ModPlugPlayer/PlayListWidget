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
#include <Interfaces/PlayList.hpp>
#include <PlayListDTOs.hpp>
#include "DropIndicator.hpp"
#include "PlayListItemWidget.hpp"
#include <QMap>
#include <boost/uuid/uuid.hpp>
#include <mutex>
#include <EventFilters.hpp>

class PlayListWidget : public QListWidget, public ModPlugPlayer::Interfaces::PlayList {
    Q_OBJECT
     public:
        explicit PlayListWidget(QWidget *parent = nullptr);
        ~PlayListWidget();
        void addPlayListItem(const PlayListItem & playListItem, int rowIndex = -1);
        //void addPlayListItems(const std::vector<PlayListItem> & playListItems, int rowIndex = -1);
        void removeSelectedItems();
        PlayListItem getCurrentItem() override;
        void updateItemNumbers();

     signals:
        void fileDropped(const QUrl &fileUrl, int droppedIndex);
        void filesDropped(const QList<QUrl> &fileUrls, int droppedIndex);

        void metaDataRequested(const ModPlugPlayer::PlayListItem playListItem) override;
        void loadRequested(const ModPlugPlayer::PlayListItem playListItem) override;
        void playRequested(const ModPlugPlayer::PlayListItem playListItem) override;
        void pauseRequested(const ModPlugPlayer::PlayListItem playListItem) override;
        void resumeRequested(const ModPlugPlayer::PlayListItem playListItem) override;
        void stopRequested(const ModPlugPlayer::PlayListItem playListItem) override;
        void repeatRequested(const ModPlugPlayer::RepeatMode repeatMode) override;
        void clearPlayListRequested() override;
        void horizontalScrollBarVisibilityChanged(bool isVisible) override;
        void verticalScrollBarVisibilityChanged(bool isVisible) override;

    public slots:
        void onMetaDataObtained(const ModPlugPlayer::PlayListItem playListItem) override;
        void onLoaded(const ModPlugPlayer::PlayListItem playListItem, bool successfull) override;
        void onPlayingStarted(const ModPlugPlayer::PlayListItem playListItem) override;
        void onPaused(const ModPlugPlayer::PlayListItem playListItem) override;
        void onResumed(const ModPlugPlayer::PlayListItem playListItem) override;
        void onStopped(const ModPlugPlayer::PlayListItem playListItem) override;
        void onNextRequested() override;
        void onPreviousRequested() override;
        void onClearPlayListRequested() override;
        void onRepeatModeChanged(const ModPlugPlayer::RepeatMode repeatMode) override;

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
        bool isValidDrop(const QPointF &dropPosition);
        void connectPlayListItemSignals(PlayListItemWidget &playListItemWidget);
        void disconnectPlayListItemSignals(PlayListItemWidget &playListItemWidget);
        PlayListItemWidget *currentItem = nullptr;
        std::mutex listItemsLock;
        QMap<boost::uuids::uuid, PlayListItemWidget *> playListMap;
        PlayListItems playList;
        RepeatMode repeatMode = RepeatMode::NoRepeat;
        EventFilters::ScrollBarVisibilityEventFilter *verticalScrollBarVisibilityEventFilter = nullptr;
        EventFilters::ScrollBarVisibilityEventFilter *horizontalScrollBarVisibilityEventFilter = nullptr;
};
