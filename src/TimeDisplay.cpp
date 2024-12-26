/*
TimeDisplay class definitions of ModPlug Player
Copyright (C) 2024 Volkan Orhan

This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this program. If not, see <https://www.gnu.org/licenses/>.
*/

#include "TimeDisplay.hpp"
#include "ui_TimeDisplay.h"
#include <Util/WindowUtil.hpp>

TimeDisplay::TimeDisplay(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TimeDisplay)
{
    ui->setupUi(this);

    #ifdef Q_OS_MACOS
        //Makes this component seem under the transparent titlebar correctly
        setAttribute(Qt::WA_ContentsMarginsRespectsSafeArea, false);
    #endif
}

void TimeDisplay::setTime(int seconds)
{
    sec = seconds%60;
    min = seconds/60;
    ui->secondDigit1->setText(QString::number(sec/10));
    ui->secondDigit2->setText(QString::number(sec%10));
    ui->minuteDigit1->setText(QString::number(min/10));
    ui->minuteDigit2->setText(QString::number(min%10));
}

void TimeDisplay::setNumberFont(QFont &font) {
    ui->secondDigit1->setFont(font);
    ui->secondDigit2->setFont(font);
    ui->minuteDigit1->setFont(font);
    ui->minuteDigit2->setFont(font);}

void TimeDisplay::setColonFont(QFont &font) {
    ui->colon->setFont(font);
}

void TimeDisplay::setFontWeight(QFont::Weight weight) {
    WindowUtil::setFontWeight(ui->secondDigit1, weight);
    WindowUtil::setFontWeight(ui->secondDigit2, weight);
    WindowUtil::setFontWeight(ui->colon, weight);
    WindowUtil::setFontWeight(ui->minuteDigit1, weight);
    WindowUtil::setFontWeight(ui->minuteDigit2, weight);
}

TimeDisplay::~TimeDisplay()
{
    delete ui;
}
