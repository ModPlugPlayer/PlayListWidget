#pragma once
#include <QString>

struct PlayListItem {
    size_t itemNumber = 0;
    QString format;
    QString title;
    QString fileName;
    size_t duration = 0;
};
