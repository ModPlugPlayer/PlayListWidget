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
    int getVolume() const override;
    bool isAlwaysOnTop() const override;
    bool isTitleBarHidden() const override;
    bool isSnapToViewPort() const override;
    bool isKeptStayingInViewPort() const override;

signals:
    void stop() override;
    void stop(const ModPlugPlayer::PlayListItem playListItem) override;
    void play() override;
    void play(const ModPlugPlayer::PlayListItem playListItem) override;
    void pause() override;
    void pause(const ModPlugPlayer::PlayListItem playListItem) override;
    void resume() override;
    void resume(const ModPlugPlayer::PlayListItem playListItem) override;
    void previous() override;
    void next() override;
    void changeVolume(const int volume) override;
    void changeRepeat(const ModPlugPlayer::RepeatState repeat) override;
    void setAlwaysOnTop(const bool alwaysOnTop) override;
    void hideTitleBar(const bool hide) override;
    void snapToViewPort(const bool toBeSnappedToViewPort) override;
    void keepStayingInViewPort(const bool toBeKeptStayingInViewPort) override;
    void open(const std::filesystem::path filePath) override;
    void open(const ModPlugPlayer::PlayListItem playListItem) override;
    void scrubTime(const int position) override;

public slots:
    void onOpen(const std::filesystem::path filePath) override;
    void onOpen(const ModPlugPlayer::PlayListItem playListItem) override;
    void onStop() override;
    void onStop(const ModPlugPlayer::PlayListItem playListItem) override;
    void onPlay() override;
    void onPlay(const ModPlugPlayer::PlayListItem playListItem) override;
    void onPause() override;
    void onPause(const ModPlugPlayer::PlayListItem playListItem) override;
    void onResume() override;
    void onResume(const ModPlugPlayer::PlayListItem playListItem) override;
    void onPrevious() override;
    void onNext() override;
    void onChangeVolume(const int volume) override;
    void onScrubTime(const int position) override;
    void onChangeRepeat(const ModPlugPlayer::RepeatState repeat) override;
    void onSetAlwaysOnTop(const bool alwaysOnTop) override;
    void onHideTitleBar(const bool hide) override;
    void onSetSnapToViewPort(const bool snapToViewPort) override;
    void onSetKeepStayingInViewPort(const bool keepStayingInViewPort) override;
    void onSetSnappingThreshold(const int snappingThreshold) override;

private slots:
    void on_previousButton_clicked();
    void on_nextButton_clicked();
    void on_playButton_clicked();
    void on_pauseButton_clicked();
    void on_stopButton_clicked();
    void on_repeatButton_clicked();
    void on_playlistButton_clicked();
    void onPlayListEditorIsHidden();

    void on_openButton_clicked();

private:
    Ui::ControlWindow *ui;
    PlayListWindow * playListWindow;
    RepeatState repeatState = RepeatState::None;
    PlayingStatus playingStatus = PlayingStatus::Stopped;
    void toggleRepeat();
    PlayingMode playingMode = PlayingMode::SingleTrack;
};

