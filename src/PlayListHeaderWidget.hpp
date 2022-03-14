#pragma once

#include <QWidget>

namespace Ui {
class PlayListHeaderWidget;
}

class PlayListHeaderWidget : public QWidget
{
    Q_OBJECT

        public:
                 explicit PlayListHeaderWidget(QWidget *parent = nullptr);
    ~PlayListHeaderWidget();

private:
    Ui::PlayListHeaderWidget *ui;
};

