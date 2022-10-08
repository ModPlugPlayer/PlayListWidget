/*
PlayListWindow class declarations for the test purposes of PlayListWidget
Copyright (C) 2022 Volkan Orhan

This library is free software; you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation; either version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License along with this library; if not, write to the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
*/

#pragma once

#include <QMainWindow>
#include <QUrl>
#include <QList>
#include <Player.hpp>

QT_BEGIN_NAMESPACE
    namespace Ui { class PlayListWindow; }
QT_END_NAMESPACE

using namespace ModPlugPlayer;

class PlayListWindow : public QMainWindow {
    Q_OBJECT

    public:
     PlayListWindow(QWidget *parent, Player *playerWindow);
    ~PlayListWindow();
    signals:
        void hidden();
    public slots:
        void onFileDropped(QUrl fileUrl, int droppedIndex);
        void onFilesDropped(QList<QUrl> fileUrls, int droppedIndex);
        void onNext();
        void onPrevious();
        void onStop();
        void onPlay();
        void onPause();

    private slots:
        void on_Add_clicked();
        void on_Remove_clicked();

    private:
    Ui::PlayListWindow *ui;
    void closeEvent(QCloseEvent *event);
    void showEvent(QShowEvent *event);
    void hideEvent(QHideEvent *event);
    QRect windowGeometry;
    Player *playerWindow;

};
