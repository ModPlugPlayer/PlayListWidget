#pragma once

#include <QDialog>
#include "PlayListWindow.hpp"
#include <Player.hpp>

namespace Ui {
class ControlWindow;
}

using namespace ModPlugPlayer;

class ControlWindow : public QDialog, public ModPlugPlayer::Player
{
    Q_OBJECT

public:
    explicit ControlWindow(QWidget *parent = nullptr);
    //explicit ControlWindow(PlayListWindow *playListWindow = nullptr);
    ~ControlWindow();
    int getVolume() const;
    bool isAlwaysOnTop() const;
    bool isTitleBarHidden() const;
    bool isSnapToViewPort() const;
    bool isKeptStayingInViewPort() const;

signals:
    void stop();
    void play();
    void pause();
    void resume();
    void previous();
    void next();
    void changeVolume(int volume);
    void changeRepeat(ModPlugPlayer::RepeatState repeat);
    void setAlwaysOnTop(bool alwaysOnTop);
    bool getAlwaysOnTop() const;
    void hideTitleBar(bool hide);
    bool snapToViewPort(bool toBeSnappedToViewPort) const;
    void keepStayingInViewPort(bool toBeKeptStayingInViewPort);

public slots:
    void onStop();
    void onPlay();
    void onPause();
    void onResume();
    void onPrevious();
    void onNext();
    void onChangeVolume(int volume);
    void onChangeRepeat(ModPlugPlayer::RepeatState repeat);
    void onSetAlwaysOnTop(bool alwaysOnTop);
    void onHideTitleBar(bool hide);
    void onSetSnapToViewPort(bool snapToViewPort);
    void onSetKeepStayingInViewPort(bool keepStayingInViewPort);
    void onSetSnappingThreshold(int snappingThreshold);

private slots:
    void on_previousButton_clicked();
    void on_nextButton_clicked();
    void on_playButton_clicked();
    void on_pauseButton_clicked();
    void on_resumeButton_clicked();
    void on_stopButton_clicked();
    void on_repeatButton_clicked();
    void on_playlistButton_toggled(bool checked);
    void onPlayListEditorIsHidden();

private:
    Ui::ControlWindow *ui;
    PlayListWindow * playListWindow;
    RepeatState repeatState = RepeatState::None;
    void toggleRepeat();
};

