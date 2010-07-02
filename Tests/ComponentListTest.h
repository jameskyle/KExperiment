#ifndef COMPONENTLISTTEST_H
#define COMPONENTLISTTEST_H

#include <QTest>
#include <QDebug>

#include <Components/Components.h>

namespace kex
{
  class ComponentListTest : public QObject
  {
    Q_OBJECT
  public:
    ComponentListTest();
    
  private slots:
    void initTestCase();

    // iterator methods
    void incrementIteratorTest();
    void decrementIteratorTest();
    void randomAccessIteratorTest();
    
    // STL
    void frontTest();
    void backTest();
    void sizeTest();
    void emptyTest();
    void push_backTest();
    void push_frontTest();
    void beginTest();
    void endTest();
    void clearTest();
    void removeTest();
    void cleanupTestCase();
    
    void getLists(ComponentList *cList, 
                  QList<ComponentList::Node::Pointer> *nList);

  };
};
#endif
