#include "Neumorphism.h"
#include <QPainter>
#include <QtDebug>
#include "pixmap_fiter.h"

QList<Neumorphism*> Neumorphism::list=QList<Neumorphism*>();

Neumorphism::Neumorphism(QObject *parent)
    : QGraphicsEffect(parent)
    , strength(0.8)
    , blurRadius(10)
    , distance(3)
    , angle(3.14/8)
{
    list.push_back(this);
}

Neumorphism::~Neumorphism()
{
    list.removeOne(this);
}

QRectF Neumorphism::boundingRectFor(const QRectF &rect) const
{
    return rect.united(rect.translated(0,0).adjusted(-blurRadius-distance, -blurRadius-distance, blurRadius+distance, blurRadius+distance));
}

void Neumorphism::draw(QPainter *painter)
{
    PixmapPadMode mode = PadToEffectiveBoundingRect;
    QPoint pos;
    const QPixmap px = sourcePixmap(Qt::DeviceCoordinates, &pos, mode);
    if (px.isNull())
        return;
    QTransform restoreTransform = painter->worldTransform();
    painter->setWorldTransform(QTransform());
    if (px.isNull())
        return;
    QImage shadow1(px.size(), QImage::Format_ARGB32_Premultiplied);
    shadow1.setDevicePixelRatio(px.devicePixelRatioF());
    shadow1.fill(0);

    QImage shadow2(px.size(), QImage::Format_ARGB32_Premultiplied);
    shadow2.setDevicePixelRatio(px.devicePixelRatioF());
    shadow2.fill(0);

    QPainter shadowPainter(&shadow1);
    shadowPainter.setCompositionMode(QPainter::CompositionMode_Source);
    shadowPainter.drawPixmap(0,0,px);
    shadowPainter.end();

    QImage blurred(shadow1.size(), QImage::Format_ARGB32_Premultiplied);
    blurred.setDevicePixelRatio(px.devicePixelRatioF());
    blurred.fill(0);

    QPainter blurPainter(&blurred);
    qt_blurImage(&blurPainter, shadow1, blurRadius, false, true);
    blurPainter.end();

    shadow1=std::move(blurred);

    // blacken the image...
    shadowPainter.begin(&shadow1);
    shadowPainter.setCompositionMode(QPainter::CompositionMode_SourceIn);
    shadowPainter.fillRect(shadow1.rect(), QColor::fromRgbF(0.0,0.0,0.0,strength));
    shadowPainter.end();
    shadow2=shadow1;
    // blacken the image...
    shadowPainter.begin(&shadow2);
    shadowPainter.setCompositionMode(QPainter::CompositionMode_SourceIn);
    shadowPainter.fillRect(shadow2.rect(),QColor::fromRgbF(1.0,1.0,1.0,strength));
    shadowPainter.end();
    QPoint offset;
    offset.setX(distance*qCos(angle));
    offset.setY(distance*qSin(angle));
    // draw the blurred drop shadow...
    painter->drawImage(pos+offset, shadow1);
    painter->drawImage(pos-offset, shadow2);

    // Draw the actual pixmap...
    painter->drawPixmap(pos, px);
    painter->setWorldTransform(restoreTransform);
}

qreal Neumorphism::getBlurRadius() const
{
    return blurRadius;
}

void Neumorphism::setBlurRadius(const qreal &value)
{
    blurRadius = value;
    update();
}

qreal Neumorphism::getAngle() const
{
    return angle;
}

void Neumorphism::setAngle(const qreal &value)
{
    angle = value;
    update();
}

qreal Neumorphism::getDistance() const
{
    return distance;
}

void Neumorphism::setDistance(const qreal &value)
{
    distance = value;
    update();
}

qreal Neumorphism::getStrength() const
{
    return strength;
}

void Neumorphism::setStrength(const qreal &value)
{
    strength = value;
    update();
}
