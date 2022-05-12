#include "ControlWindow.hpp"
#include "ui_ControlWindow.h"
#include <PlayList.hpp>

ControlWindow::ControlWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ControlWindow)
{
    ui->setupUi(this);
}

ControlWindow::ControlWindow(PlayListWindow * playListWindow) :
    QDialog(playListWindow),
    ui(new Ui::ControlWindow)
{
    this->playListWindow = playListWindow;
    ui->setupUi(this);
}

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

void ControlWindow::onStop()
{

}

void ControlWindow::onPlay()
{

}

void ControlWindow::onPause()
{

}

void ControlWindow::onResume()
{

}

void ControlWindow::onPrevious()
{

}

void ControlWindow::onNext()
{

}

void ControlWindow::onChangeVolume(int volume)
{

}

void ControlWindow::onChangeRepeat(ModPlugPlayer::Repeat repeat)
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
    previous();
}


void ControlWindow::on_playButton_clicked()
{

}


void ControlWindow::on_pauseButton_clicked()
{

}


void ControlWindow::on_resumeButton_clicked()
{

}


void ControlWindow::on_stopButton_clicked()
{

}


void ControlWindow::on_repeatButton_toggled(bool checked)
{

}


void ControlWindow::on_playlistButton_toggled(bool checked)
{

}


void ControlWindow::on_nextButton_clicked()
{

}

