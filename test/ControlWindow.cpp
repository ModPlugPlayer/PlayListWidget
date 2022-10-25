#include "ControlWindow.hpp"
#include "ui_ControlWindow.h"
#include <PlayList.hpp>

ControlWindow::ControlWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ControlWindow)
{
    ui->setupUi(this);
    this->playListWindow = new PlayListWindow(this, this);
    QObject::connect(this->playListWindow, &PlayListWindow::hidden, this, &ControlWindow::onPlayListEditorIsHidden);
    QObject::connect(this, &ControlWindow::changeRepeat, this, &ControlWindow::onChangeRepeat);
    QObject::connect(this, qOverload<>(&ControlWindow::play), this, qOverload<>(&ControlWindow::onPlay));
    QObject::connect(this, qOverload<>(&ControlWindow::pause), this, qOverload<>(&ControlWindow::onPause));
    QObject::connect(this, qOverload<>(&ControlWindow::resume), this, qOverload<>(&ControlWindow::onResume));
    QObject::connect(this, qOverload<>(&ControlWindow::stop), this, qOverload<>(&ControlWindow::onStop));
    QObject::connect(this, &ControlWindow::previous, this, &ControlWindow::onPrevious);
    QObject::connect(this, &ControlWindow::next, this, &ControlWindow::onNext);
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

void ControlWindow::onOpen(std::filesystem::path filePath) {
    playingMode = PlayingMode::SingleTrack;
}

void ControlWindow::onOpen(PlayListItem playListItem) {
    playingMode = PlayingMode::PlayList;
    ui->display->setText(playListItem.filePath.filename().c_str());
    emit open(playListItem);
}

void ControlWindow::onStop() {
    playingStatus = PlayingStatus::Stopped;
    ui->stopButton->setStyleSheet("color: green;");
    ui->pauseButton->setStyleSheet("color: blue;");
    ui->playButton->setStyleSheet("color: blue;");
}

void ControlWindow::onStop(const PlayListItem playListItem) {
    playingStatus = PlayingStatus::Stopped;
    ui->stopButton->setStyleSheet("color: green;");
    ui->pauseButton->setStyleSheet("color: blue;");
    ui->playButton->setStyleSheet("color: blue;");
}

void ControlWindow::onPlay() {
    playingStatus = PlayingStatus::Playing;
    ui->stopButton->setStyleSheet("color: blue;");
    ui->pauseButton->setStyleSheet("color: blue;");
    ui->playButton->setStyleSheet("color: green;");
}

void ControlWindow::onPlay(const PlayListItem playListItem) {
    playingStatus = PlayingStatus::Playing;
    ui->stopButton->setStyleSheet("color: blue;");
    ui->pauseButton->setStyleSheet("color: blue;");
    ui->playButton->setStyleSheet("color: green;");
}

void ControlWindow::onPause() {
    playingStatus = PlayingStatus::Paused;
    ui->stopButton->setStyleSheet("color: blue;");
    ui->pauseButton->setStyleSheet("color: green;");
    ui->playButton->setStyleSheet("color: blue;");
}

void ControlWindow::onPause(const PlayListItem playListItem) {
    playingStatus = PlayingStatus::Paused;
    ui->stopButton->setStyleSheet("color: blue;");
    ui->pauseButton->setStyleSheet("color: green;");
    ui->playButton->setStyleSheet("color: blue;");
}

void ControlWindow::onResume() {
    playingStatus = PlayingStatus::Playing;
    ui->stopButton->setStyleSheet("color: blue;");
    ui->pauseButton->setStyleSheet("color: blue;");
    ui->playButton->setStyleSheet("color: green;");
}

void ControlWindow::onResume(const PlayListItem playListItem) {
    playingStatus = PlayingStatus::Playing;
    ui->stopButton->setStyleSheet("color: blue;");
    ui->pauseButton->setStyleSheet("color: blue;");
    ui->playButton->setStyleSheet("color: green;");
}

void ControlWindow::onPrevious() {
}

void ControlWindow::onNext() {
}

void ControlWindow::onChangeVolume(int volume) {

}

void ControlWindow::onScrubTime(int position) {

}

void ControlWindow::onChangeRepeat(RepeatState repeat) {
    repeatState = repeat;
}

void ControlWindow::onSetAlwaysOnTop(bool alwaysOnTop) {

}

void ControlWindow::onHideTitleBar(bool hide) {

}

void ControlWindow::onSetSnapToViewPort(bool snapToViewPort) {

}

void ControlWindow::onSetKeepStayingInViewPort(bool keepStayingInViewPort)
{

}

void ControlWindow::onSetSnappingThreshold(int snappingThreshold)
{

}

void ControlWindow::on_previousButton_clicked() {
    emit previous();
}

void ControlWindow::on_nextButton_clicked() {
    emit next();
}

void ControlWindow::on_playButton_clicked() {
    emit play();
}

void ControlWindow::on_pauseButton_clicked() {
    if(playingStatus == PlayingStatus::Playing)
        emit pause();
    else if(playingStatus == PlayingStatus::Paused)
        emit resume();
}

void ControlWindow::on_stopButton_clicked() {
    emit stop();
}

void ControlWindow::on_repeatButton_clicked() {
    toggleRepeat();
    if(repeatState == RepeatState::None)
        ui->repeatButton->setText("Repeat\nNone");
    if(repeatState == RepeatState::SingleTrack)
        ui->repeatButton->setText("Repeat\nSong");
    if(repeatState == RepeatState::PlayList)
        ui->repeatButton->setText("Repeat\nPlaylist");
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

void ControlWindow::toggleRepeat() {
    RepeatState repeat = RepeatState::None;

    if(repeatState == RepeatState::None)
        repeat = RepeatState::SingleTrack;
    else
        if(repeatState == RepeatState::SingleTrack)
            repeat = RepeatState::PlayList;
    else
        if(repeatState == RepeatState::PlayList)
            repeat = RepeatState::None;

    emit changeRepeat(repeat);
}

void ControlWindow::on_openButton_clicked() {

}

