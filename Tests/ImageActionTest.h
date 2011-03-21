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
    void categoriesTest();
    void cleanupTestCase();
    void cloneTest();
    void componentTypeFromStringTest();
    void componentTypeTest();
    void componentTypeToStringTest();
    void constructorTest();
    void descriptionTest();
    void durationMSecsTest();
    void initTestCase();
    void labelTest();
    void nameTest();
    void operatorEqualsTest();
    void parentComponentTest();
    void toStringTest();

  };
}

#endif // IMAGEACTIONTEST_H
