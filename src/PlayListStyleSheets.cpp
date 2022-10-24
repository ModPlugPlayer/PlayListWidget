#include "PlayListStyleSheets.hpp"

const QString PlayListStyleSheets::scrollBar = R"(
    QScrollBar:vertical {
        border: 0px;
        background: transparent;
        width: 8px;
        margin: 0px 0 0px 0;
    }
    QScrollBar::handle:vertical {
        background: #88888888;
        min-height: 20px;
        /*border-radius: 4px;*/
    }
    QScrollBar::add-line:vertical {
        border: 0px;
        background: none;
        height: 0px;
    }
    QScrollBar::sub-line:vertical {
        border: 0px;
        background: none;
        height: 0px;
    }
    QScrollBar::up-arrow:vertical, QScrollBar::down-arrow:vertical {
        border: 0px solid grey;
        width: 0px;
        height: 0px;
        background: transparent;
    }
    QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {
        background: none;
    }
)";
