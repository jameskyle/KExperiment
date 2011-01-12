#ifndef COMPONENTGRAPHICSITEM_H
#define COMPONENTGRAPHICSITEM_H

#include <QObject>
#include <QGraphicsItem>

namespace kex
{
  class ComponentGraphicsItem : public QObject, public QGraphicsItem
  {
      Q_OBJECT
  public:
    explicit ComponentGraphicsItem(QObject *parent = 0);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);

  protected:
    void timerEvent(QTimerEvent *event);

  };
}

#endif // COMPONENTGRAPHICSITEM_H
