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

ControlWindow::~ControlWindow()
{
    delete ui;
}

int ControlWindow::getVolume() const
{
    return 0;
}

bool ControlWindow::isAlwaysOnTop() const
{
    return false;
}

bool ControlWindow::isTitleBarHidden() const
{
    return false;
}

bool ControlWindow::isSnapToViewPort() const
{
    return false;
}

bool ControlWindow::isKeptStayingInViewPort() const
{
    return false;
}

void ControlWindow::onOpen(std::filesystem::path filePath)
{
    playingMode = PlayingMode::SingleTrack;
}

void ControlWindow::onOpen(PlayListItem playListItem)
{
    playingMode = PlayingMode::PlayList;
    ui->display->setText(playListItem.filePath.filename().c_str());
    emit open(playListItem);
}

void ControlWindow::onStop()
{
    emit stop();
}

void ControlWindow::onPlay()
{
    emit play();
}

void ControlWindow::onPause()
{
    emit pause();
}

void ControlWindow::onResume()
{
    emit resume();
}

void ControlWindow::onPrevious()
{
    emit previous();
}

void ControlWindow::onNext()
{
    emit next();
}

void ControlWindow::onChangeVolume(int volume)
{

}

void ControlWindow::onScrubTime(int position)
{

}

void ControlWindow::onChangeRepeat(RepeatState repeat)
{

}

void ControlWindow::onSetAlwaysOnTop(bool alwaysOnTop)
{

}

void ControlWindow::onHideTitleBar(bool hide)
{

}

void ControlWindow::onSetSnapToViewPort(bool snapToViewPort)
{

}

void ControlWindow::onSetKeepStayingInViewPort(bool keepStayingInViewPort)
{

}

void ControlWindow::onSetSnappingThreshold(int snappingThreshold)
{

}

void ControlWindow::on_previousButton_clicked()
{
    emit previous();
}

void ControlWindow::on_nextButton_clicked()
{
    emit next();
}

void ControlWindow::on_playButton_clicked()
{
    emit play();
}

void ControlWindow::on_pauseButton_clicked()
{
    emit pause();
}

void ControlWindow::on_resumeButton_clicked()
{
    emit resume();
}

void ControlWindow::on_stopButton_clicked()
{
    emit stop();
}

void ControlWindow::on_repeatButton_clicked()
{
    toggleRepeat();
    if(repeatState == RepeatState::None)
        ui->repeatButton->setText("Repeat\nNone");
    if(repeatState == RepeatState::SingleTrack)
        ui->repeatButton->setText("Repeat\nSong");
    if(repeatState == RepeatState::PlayList)
        ui->repeatButton->setText("Repeat\nPlaylist");
}

void ControlWindow::on_playlistButton_toggled(bool turnOn)
{
    if(turnOn) {
        playListWindow->show();
    }
    else {
        playListWindow->hide();
    }
    //ui->actionPlayListEditor->setChecked(turnOn);
    //ui->optionButtons->togglePlayListEditorButton(turnOn);
}

void ControlWindow::onPlayListEditorIsHidden()
{
    ui->playlistButton->setChecked(false);
}

void ControlWindow::toggleRepeat()
{
    if(repeatState == RepeatState::None)
        repeatState = RepeatState::SingleTrack;
    else
        if(repeatState == RepeatState::SingleTrack)
            repeatState = RepeatState::PlayList;
    else
        if(repeatState == RepeatState::PlayList)
            repeatState = RepeatState::None;

    emit changeRepeat(repeatState);
}
