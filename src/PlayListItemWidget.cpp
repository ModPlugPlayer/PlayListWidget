#include "PlayListItemWidget.hpp"
#include "ui_PlayListItemWidget.h"

PlayListItemWidget::PlayListItemWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlayListItemWidget)
{
    ui->setupUi(this);
}

PlayListItemWidget::PlayListItemWidget(QWidget * parent, const PlayListItem & playListItem) :
    QWidget(parent),
    ui(new Ui::PlayListItemWidget)
{
    ui->setupUi(this);
    setItemNumber(playListItem.itemNumber);
    setFormat(playListItem.format);
    setTitle(playListItem.title);
    setFileName(playListItem.fileName);
    setDuration(playListItem.duration);
}

PlayListItemWidget::~PlayListItemWidget()
{
    delete ui;
}

PlayListItem PlayListItemWidget::getData() const
{
    return data;
}

void PlayListItemWidget::setData(const PlayListItem & playListItem)
{
    data = playListItem;
}

size_t PlayListItemWidget::getItemNumber() const
{
    return data.itemNumber;
}

void PlayListItemWidget::setItemNumber(size_t itemNumber)
{
    data.itemNumber = itemNumber;
    ui->itemNumber->setText(QString::number(itemNumber));
}

const QString & PlayListItemWidget::getTitle() const
{
    return data.title;
}

void PlayListItemWidget::setTitle(const QString & title)
{
    data.title = title;
    ui->title->setText(title);
}

const QString & PlayListItemWidget::getFormat() const
{
    return data.title;
}

void PlayListItemWidget::setFormat(const QString & format)
{
    data.format = format;
    ui->format->setText(format);
}

const QString & PlayListItemWidget::getFileName() const
{
    return data.fileName;
}

void PlayListItemWidget::setFileName(const QString & fileName)
{
    data.fileName = fileName;
    ui->fileName->setText(fileName);
}

size_t PlayListItemWidget::getDuration() const
{
    return data.duration;
}

void PlayListItemWidget::setDuration(size_t duration)
{
    data.duration = duration;
    ui->duration->setText(QString::number(duration));
}

