#include "ControlWindow.hpp"
#include "ui_ControlWindow.h"
#include <PlayList.hpp>

ControlWindow::ControlWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ControlWindow)
{
    ui->setupUi(this);
    this->playListWindow = new PlayListWindow(this, this);
    connect(this->playListWindow, &PlayListWindow::hidden, this, &ControlWindow::onPlayListEditorIsHidden);
    connect(this, &ControlWindow::repeatModeChangeRequested, this, &ControlWindow::onRepeatModeChangeRequested);
    connect(this, qOverload<>(&ControlWindow::playRequested), this, qOverload<>(&ControlWindow::onPlayRequested));
    connect(this, qOverload<>(&ControlWindow::pauseRequested), this, qOverload<>(&ControlWindow::onPauseRequested));
    connect(this, qOverload<>(&ControlWindow::resumeRequested), this, qOverload<>(&ControlWindow::onResumeRequested));
    connect(this, qOverload<>(&ControlWindow::stopRequested), this, qOverload<>(&ControlWindow::onStopRequested));
    connect(this, &ControlWindow::previousRequested, this, &ControlWindow::onPreviousRequested);
    connect(this, &ControlWindow::nextRequested, this, &ControlWindow::onNextRequested);
    ui->playlistButton->click();
}

/*
ControlWindow::ControlWindow(PlayListWindow * playListWindow) :
    QDialog(playListWindow),
    ui(new Ui::ControlWindow)
{
    this->playListWindow = playListWindow;
    ui->setupUi(this);
}*/

ControlWindow::~ControlWindow() {
    delete ui;
}

int ControlWindow::getVolume() const {
    return 0;
}

bool ControlWindow::isAlwaysOnTop() const {
    return false;
}

bool ControlWindow::isTitleBarHidden() const {
    return false;
}

bool ControlWindow::isSnapToViewPort() const {
    return false;
}

bool ControlWindow::isKeptStayingInViewPort() const {
    return false;
}

void ControlWindow::onOpenRequested(const std::filesystem::path filePath) {
    playingMode = PlayingMode::SingleTrack;
}

void ControlWindow::onOpenRequested(const PlayListItem playListItem) {
    playingMode = PlayingMode::PlayList;
    ui->display->setText(playListItem.filePath.filename().c_str());
    emit loaded(playListItem, true);
}

void ControlWindow::onLoaded(const std::filesystem::path filePath, const bool successfull) {

}

void ControlWindow::onLoaded(const PlayListItem playListItem, const bool successfull) {

}

void ControlWindow::onStopRequested() {
    playingStatus = PlayingStatus::Stopped;
    ui->stopButton->setStyleSheet("color: green;");
    ui->pauseButton->setStyleSheet("color: blue;");
    ui->playButton->setStyleSheet("color: blue;");
}

void ControlWindow::onStopRequested(const PlayListItem playListItem) {
    playingStatus = PlayingStatus::Stopped;
    ui->stopButton->setStyleSheet("color: green;");
    ui->pauseButton->setStyleSheet("color: blue;");
    ui->playButton->setStyleSheet("color: blue;");
}

void ControlWindow::onPlayRequested() {
    playingStatus = PlayingStatus::Playing;
    ui->stopButton->setStyleSheet("color: blue;");
    ui->pauseButton->setStyleSheet("color: blue;");
    ui->playButton->setStyleSheet("color: green;");
}

void ControlWindow::onPlayRequested(const PlayListItem playListItem) {
    playingStatus = PlayingStatus::Playing;
    ui->stopButton->setStyleSheet("color: blue;");
    ui->pauseButton->setStyleSheet("color: blue;");
    ui->playButton->setStyleSheet("color: green;");
}

void ControlWindow::onPauseRequested() {
    playingStatus = PlayingStatus::Paused;
    ui->stopButton->setStyleSheet("color: blue;");
    ui->pauseButton->setStyleSheet("color: green;");
    ui->playButton->setStyleSheet("color: blue;");
}

void ControlWindow::onPauseRequested(const PlayListItem playListItem) {
    playingStatus = PlayingStatus::Paused;
    ui->stopButton->setStyleSheet("color: blue;");
    ui->pauseButton->setStyleSheet("color: green;");
    ui->playButton->setStyleSheet("color: blue;");
}

void ControlWindow::onResumeRequested() {
    playingStatus = PlayingStatus::Playing;
    ui->stopButton->setStyleSheet("color: blue;");
    ui->pauseButton->setStyleSheet("color: blue;");
    ui->playButton->setStyleSheet("color: green;");
}

void ControlWindow::onResumeRequested(const PlayListItem playListItem) {
    playingStatus = PlayingStatus::Playing;
    ui->stopButton->setStyleSheet("color: blue;");
    ui->pauseButton->setStyleSheet("color: blue;");
    ui->playButton->setStyleSheet("color: green;");
}

void ControlWindow::onPreviousRequested() {
}

void ControlWindow::onNextRequested() {
}

void ControlWindow::onVolumeChangeRequested(const int volume) {

}

void ControlWindow::onTimeScrubbingRequested(const int position) {

}

void ControlWindow::onRepeatModeChangeRequested(const RepeatMode repeatMode) {
    this->repeatMode = repeatMode;
}

void ControlWindow::onEqStateChangeRequested(const bool activated)
{

}

void ControlWindow::onAGCStateChangeRequested(const bool activated)
{

}

void ControlWindow::onXBassStateChangeRequested(const bool activated)
{

}

void ControlWindow::onSurroundStateChangeRequested(const bool activated)
{

}

void ControlWindow::onReverbStateChangeRequested(const bool activated)
{

}

void ControlWindow::onInterpolationFilterChangeRequested(const InterpolationFilter interpolationFilter)
{

}

void ControlWindow::onAlwaysOnTopStateChangeRequested(bool alwaysOnTop) {

}

void ControlWindow::onTitleBarHidingStateChangeRequested(bool hide) {

}

void ControlWindow::onSnappingToViewPortStateChangeRequested(bool snapToViewPort) {

}

void ControlWindow::onKeepingStayingInViewPortStateChangeRequested(bool keepStayingInViewPort) {

}

void ControlWindow::onSnappingThresholdChangeRequested(int snappingThreshold) {

}

void ControlWindow::on_previousButton_clicked() {
    emit previous();
}

void ControlWindow::on_nextButton_clicked() {
    emit next();
}

void ControlWindow::on_playButton_clicked() {
    emit playingStarted();
}

void ControlWindow::on_pauseButton_clicked() {
    if(playingStatus == PlayingStatus::Playing)
        emit paused();
    else if(playingStatus == PlayingStatus::Paused)
        emit resumed();
}

void ControlWindow::on_stopButton_clicked() {
    emit stopped();
}

void ControlWindow::on_repeatButton_clicked() {
    emit repeatModeChanged(repeatMode++);
}

void ControlWindow::on_playlistButton_clicked() {
    if(playListWindow->isHidden()) {
        ui->playlistButton->setStyleSheet("color: green;");
        playListWindow->show();
    }
    else {
        ui->playlistButton->setStyleSheet("color: blue;");
        playListWindow->hide();
    }
    //ui->actionPlayListEditor->setChecked(turnOn);
    //ui->optionButtons->togglePlayListEditorButton(turnOn);
}

void ControlWindow::onPlayListEditorIsHidden() {
    ui->playlistButton->setStyleSheet("color: blue;");
}

void ControlWindow::on_openButton_clicked() {

}

