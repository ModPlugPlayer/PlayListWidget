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

    //Request Signals
signals:
    void openRequested(const std::filesystem::path filePath) override;
    void openRequested(const PlayListItem playListItem) override;
    void stopRequested() override;
    void stopRequested(const PlayListItem playListItem) override;
    void playRequested() override;
    void playRequested(const PlayListItem playListItem) override;
    void pauseRequested() override;
    void pauseRequested(const PlayListItem playListItem) override;
    void resumeRequested() override;
    void resumeRequested(const PlayListItem playListItem) override;
    void previousRequested() override;
    void nextRequested() override;
    void volumeChangeRequested(const int volume) override;
    void timeScrubbingRequested(const int position) override;
    void repeatModeChangeRequested(const ModPlugPlayer::RepeatMode repeatMode) override;
    void agcStateChangeRequested(const bool activated) override;
    void xBassStateChangeRequested(const bool activated) override;
    void surroundStateChangeRequested(const bool activated) override;
    void reverbStateChangeRequested(const bool activated) override;
    void interpolationFilterChangeRequested(const ModPlugPlayer::InterpolationFilter interpolationFilter) override;
    void eqStateChangeRequested(const bool activated) override;
    void alwaysOnTopStateChangeRequested(const bool alwaysOnTop) override;
    void titleBarHidingStateChangeRequested(const bool hide) override;
    void snappingToViewPortStateChangeRequested(const bool toBeSnappedToViewPort) override;
    void keepingStayingInViewPortStateChangeRequested(const bool toBeKeptStayingInViewPort) override;

    //Response Signals
    void loaded(const std::filesystem::path filePath, bool successfull) override;
    void loaded(const PlayListItem playListItem, bool successfull) override;
    void stopped() override;
    void stopped(const PlayListItem playListItem) override;
    void playingStarted() override;
    void playingStarted(const PlayListItem playListItem) override;
    void paused() override;
    void paused(const PlayListItem playListItem) override;
    void resumed() override;
    void resumed(const PlayListItem playListItem) override;
    void previous() override;
    void next() override;
    void volumeChanged(const int volume) override;
    void timeScrubbed(const int position) override;
    void repeatModeChanged(const ModPlugPlayer::RepeatMode repeat) override;
    void eqStateChanged(const bool activated) override;
    void agcStateChanged(const bool activated) override;
    void xBassStateChanged(const bool activated) override;
    void surroundStateChanged(const bool activated) override;
    void reverbStateChanged(const bool activated) override;
    void interpolationFilterChanged(const ModPlugPlayer::InterpolationFilter interpolationFilter) override;
    void alwaysOnTopStateChanged(const bool alwaysOnTop) override;
    void titleBarHidingStateChanged(const bool hide) override;
    void snappingToViewPortStateChanged(const bool snapToViewPort) override;
    void keepingStayingInViewPortStateChanged(const bool toBeKeptStayingInViewPort) override;

public slots:
    // Request Signal Handlers
    void onOpenRequested(const std::filesystem::path filePath) override;
    void onOpenRequested(const PlayListItem playListItem) override;
    void onLoaded(const std::filesystem::path filePath, const bool successfull) override;
    void onLoaded(const PlayListItem playListItem, const bool successfull) override;
    void onStopRequested() override;
    void onStopRequested(const PlayListItem playListItem) override;
    void onPlayRequested() override;
    void onPlayRequested(const PlayListItem playListItem) override;
    void onPauseRequested() override;
    void onPauseRequested(const PlayListItem playListItem) override;
    void onResumeRequested() override;
    void onResumeRequested(const PlayListItem playListItem) override;
    void onVolumeChangeRequested(const int volume) override;
    void onTimeScrubbingRequested(const int position) override;
    void onAlwaysOnTopStateChangeRequested(const bool alwaysOnTop) override;
    void onTitleBarHidingStateChangeRequested(const bool hide) override;
    void onSnappingToViewPortStateChangeRequested(const bool snapToViewPort) override;
    void onSnappingThresholdChangeRequested(const int snappingThreshold) override;
    void onKeepingStayingInViewPortStateChangeRequested(const bool keepStayingInViewPort) override;
    void onPreviousRequested() override;
    void onNextRequested() override;
    void onRepeatModeChangeRequested(const ModPlugPlayer::RepeatMode repeatMode) override;
    void onEqStateChangeRequested(const bool activated) override;
    void onAGCStateChangeRequested(const bool activated) override;
    void onXBassStateChangeRequested(const bool activated) override;
    void onSurroundStateChangeRequested(const bool activated) override;
    void onReverbStateChangeRequested(const bool activated) override;
    void onInterpolationFilterChangeRequested(const ModPlugPlayer::InterpolationFilter interpolationFilter) override;

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
    RepeatMode repeatMode = RepeatMode::NoRepeat;
    PlayingStatus playingStatus = PlayingStatus::Stopped;
    PlayingMode playingMode = PlayingMode::SingleTrack;
};

