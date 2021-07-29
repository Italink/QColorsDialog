#ifndef NEUMORPHISM_H
#define NEUMORPHISM_H

#include <QObject>
#include <QGraphicsEffect>
QT_BEGIN_NAMESPACE
class QGraphicsItem;
class QPainter;
class QPixmap;
class QGraphicsEffectSource;
class QPainter;
QT_END_NAMESPACE

class  Neumorphism: public QGraphicsEffect
{
public:
    Neumorphism(QObject *parent = nullptr);
    ~Neumorphism();
    QRectF boundingRectFor(const QRectF &rect) const override;

    qreal getStrength() const;
    void setStrength(const qreal &value);

    qreal getDistance() const;
    void setDistance(const qreal &value);

    qreal getAngle() const;
    void setAngle(const qreal &value);

    qreal getBlurRadius() const;
    void setBlurRadius(const qreal &value);

    static QList<Neumorphism *> list;

protected:
    void draw(QPainter *painter) override;
private:
    qreal strength;
    qreal blurRadius;
    qreal distance;
    qreal angle;
};

#endif // SHADOW_H
