#pragma once

#include <QWidget>
#include "PlayListDTOs.hpp"

namespace Ui {
class PlayListItemWidget;
}

class PlayListItemWidget : public QWidget
{
    Q_OBJECT

    public:
        explicit PlayListItemWidget(QWidget *parent = nullptr);
        explicit PlayListItemWidget(QWidget *parent, const PlayListItem &playListItem);
        ~PlayListItemWidget();

        PlayListItem getData() const;
        void setData(const PlayListItem &playListItem);

        size_t getItemNumber() const;
        void setItemNumber(size_t itemNumber);

        const QString & getFileName() const;
        void setFileName(const QString & fileName);

        size_t getDuration() const;
        void setDuration(size_t duration);

        const QString & getTitle() const;
        void setTitle(const QString & title);

        const QString & getFormat() const;
        void setFormat(const QString & format);
    private:
    Ui::PlayListItemWidget *ui;
    PlayListItem data;
};

