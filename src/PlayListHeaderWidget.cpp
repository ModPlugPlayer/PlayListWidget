#include "PlayListHeaderWidget.hpp"
#include "ui_PlayListHeaderWidget.h"

PlayListHeaderWidget::PlayListHeaderWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlayListHeaderWidget)
{
    ui->setupUi(this);
}

PlayListHeaderWidget::~PlayListHeaderWidget()
{
    delete ui;
}
