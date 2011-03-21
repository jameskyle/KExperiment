#ifndef IMAGEACTIONTEST_H
#define IMAGEACTIONTEST_H

#include <QTest>

#include "Components/Components.h"

namespace kex
{
  class ImageAction;

  class ImageActionTest : public QObject
  {
    Q_OBJECT
  public:
    explicit ImageActionTest();

  private:
    QSet<QString> m_categories;
    ImageAction m_action;

  private slots:
    void initTestCase();
    void cleanupTestCase();
    void constructorTest();
    void cloneTest();
    void nameTest();
    void descriptionTest();
    void labelTest();
    void categoriesTest();
    void toStringTest();
    void componentTypeTest();
    void durationMSecsTest();
    void componentTypeToStringTest();
    void componentTypeFromStringTest();
    void operatorEqualsTest();
    void parentComponentTest();
  };
}

#endif // IMAGEACTIONTEST_H
