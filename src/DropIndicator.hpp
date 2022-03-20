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
