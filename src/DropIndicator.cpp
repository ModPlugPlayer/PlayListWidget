#include "DropIndicator.hpp"
#include <QPainter>

DropIndicator::DropIndicator()
{
    thickness = 1.7;
    radius = 4;
    color = Qt::green;
    active = false;
    update();
}

DropIndicator::DropIndicator(qreal thickness, qreal diameter, qreal color)
{
    this->thickness = thickness;
    this->radius = diameter;
    this->color = color;
    active = false;
    update();

}

void DropIndicator::paint(QPainter &painter)
{
    painter.setPen(QPen(color, thickness));
    painter.drawEllipse(circleCenter, radius, radius);
    painter.drawLine(beginningPoint.x()+radius*2+thickness, beginningPoint.y(), beginningPoint.x() + width, beginningPoint.y());
}


qreal DropIndicator::getThickness() const
{
    return thickness;
}

void DropIndicator::setThickness(qreal thickness)
{
    this->thickness = thickness;
    update();
}

qreal DropIndicator::getRadius() const
{
    return radius;
}

void DropIndicator::setRadius(qreal radius)
{
    this->radius = radius;
    update();
}

const QColor & DropIndicator::getColor() const
{
    return color;
}

void DropIndicator::setColor(const QColor & color)
{
    this->color = color;
}

bool DropIndicator::isActive() const
{
    return active;
}

void DropIndicator::setActive(bool active)
{
    this->active = active;
}

QPointF DropIndicator::getBeginningPoint() const
{
    return beginningPoint;
}

void DropIndicator::setBeginningPoint(QPointF beginningPoint)
{
    this->beginningPoint = beginningPoint;
    update();
}

qreal DropIndicator::getWidth() const
{
    return width;
}

void DropIndicator::setWidth(qreal width)
{
    this->width = width;
}

void DropIndicator::update()
{
    circleCenter.setX(beginningPoint.x() + radius + thickness);
    circleCenter.setY(beginningPoint.y());
}
