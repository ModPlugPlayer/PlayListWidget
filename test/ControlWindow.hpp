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
    void play() override;
    void pause() override;
    void resume() override;
    void previous() override;
    void next() override;
    void changeVolume(int volume) override;
    void changeRepeat(ModPlugPlayer::RepeatState repeat) override;
    void setAlwaysOnTop(bool alwaysOnTop) override;
    void hideTitleBar(bool hide) override;
    void snapToViewPort(bool toBeSnappedToViewPort) override;
    void keepStayingInViewPort(bool toBeKeptStayingInViewPort) override;
    void open(std::filesystem::path filePath) override;
    void scrubTime(int position) override;

public slots:
    void onOpen(std::filesystem::path filePath) override;
    void onOpen(PlayListItem playListItem) override;
    void onStop() override;
    void onPlay() override;
    void onPause() override;
    void onResume() override;
    void onPrevious() override;
    void onNext() override;
    void onChangeVolume(int volume) override;
    void onScrubTime(int position) override;
    void onChangeRepeat(ModPlugPlayer::RepeatState repeat) override;
    void onSetAlwaysOnTop(bool alwaysOnTop) override;
    void onHideTitleBar(bool hide) override;
    void onSetSnapToViewPort(bool snapToViewPort) override;
    void onSetKeepStayingInViewPort(bool keepStayingInViewPort) override;
    void onSetSnappingThreshold(int snappingThreshold) override;

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
    PlayingMode playingMode = PlayingMode::SingleTrack;
};

