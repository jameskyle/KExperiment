#ifndef MEDIAACTIONTEST_H
#define MEDIAACTIONTEST_H

#include <QTest>
#include <QDebug>

#include "Components/Components.h"
#include "Common/Config.h"

namespace kex
{
  class MediaActionTest : public QObject
  {
    Q_OBJECT
  public:
    explicit MediaActionTest();

  private slots:
    void categoriesTest();
    void cleanupTestCase();
    void cloneTest();
    void componentTypeFromStringTest();
    void componentTypeTest();
    void componentTypeToStringTest();
    void constructorTest();
    void delayMSecsTest();
    void descriptionTest();
    void durationMSecsTest();
    void equalityTest();
    void initTestCase();
    void labelTest();
    void mediaObjectTest();
    void nameTest();
    void parentComponentTest();
    void setDelayMSecsTest();
    void setSourceTest();
    void sourceTest();
    void toStringTest();
  };
}


#endif // MEDIAACTIONTEST_H
