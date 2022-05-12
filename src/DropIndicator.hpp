/*
DropIndicator definitions of PlayListWidget
Copyright (C) 2022 Volkan Orhan

This library is free software; you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation; either version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License along with this library; if not, write to the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
*/

#pragma once
#include <QPointF>
#include <QRectF>
#include <QPaintDevice>
#include <QPainter>
#include <QColor>

class DropIndicator
{
public:
    DropIndicator();
    DropIndicator(qreal thickness, qreal radius, qreal color);
    void paint(QPainter &painter);
    qreal getThickness() const;
    void setThickness(qreal thickness);

    qreal getRadius() const;
    void setRadius(qreal diameter);

    const QColor & getColor() const;
    void setColor(const QColor & color);

    bool isActive() const;
    void setActive(bool active);

    QPointF getBeginningPoint() const;
    void setBeginningPoint(QPointF beginningPoint);

    qreal getWidth() const;
    void setWidth(qreal newWidth);

private:
    qreal thickness;
    qreal radius;
    QColor color;
    bool active;
    qreal width;
    QPointF beginningPoint;
    QPointF circleCenter;
    void update();
};
