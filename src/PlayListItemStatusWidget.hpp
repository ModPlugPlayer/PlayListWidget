/*
PlayListHeaderStatusWidget declarations of PlayListWidget
Copyright (C) 2022 Volkan Orhan

This library is free software; you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation; either version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License along with this library; if not, write to the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
*/

#pragma once

#include <QWidget>
#include <SVGIcon.hpp>
#include <QPushButton>
#include <APIStructures.hpp>
#include <LEDColorProperties.hpp>

namespace Ui {
class PlayListItemStatusWidget;
}

using namespace ModPlugPlayer;

class PlayListItemStatusWidget : public QWidget,  public LEDColorProperties {
    Q_OBJECT
    public:
        void setItemNumber(size_t itemNumber);
        void setStatus(PlayingState state);
        void setItemNumberFont(QFont &font);
        PlayingState getStatus();
        explicit PlayListItemStatusWidget(QWidget *parent = nullptr);
        void showOnlyItemNumber();
        void showOnlyPlayPauseButton();
        ~PlayListItemStatusWidget();
signals:
        void playRequested();
        void pauseRequested();
        void resumeRequested();
private slots:
        void onClick();
private:
        Ui::PlayListItemStatusWidget *ui;
        PlayingState status = PlayingState::Stopped;
protected:
        SVGIcon *iconPlay, *iconPause, *iconStop,
                *iconRewind, *iconFastForward, *iconPrevious, *iconNext;
        std::vector<SVGIcon *> icons;

        RGB activeButtonLightColor, inactiveButtonLightColor;
        void refreshStyleSheet() override;
};

