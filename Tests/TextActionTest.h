#ifndef TEXTACTIONTEST_H
#define TEXTACTIONTEST_H

#include <QTest>

#include "Components/Components.h"

namespace kex
{
  class TextActionTest : public QObject
  {
    Q_OBJECT
  public:
    explicit TextActionTest();

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
    void nameTest();
    void parentComponentTest();
    void setDelayMSecsTest();
    void setSourceTest();
    void sourceTest();
    void textTest();
    void toStringTest();
  };
}

#endif // TEXTACTIONTEST_H
