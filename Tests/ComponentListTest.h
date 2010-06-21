#ifndef COMPONENTLISTTEST_H
#define COMPONENTLISTTEST_H

#include <QTest>
#include <QDebug>

#include "Components/Components.h"

namespace kex
{
  class ComponentListTest : public QObject
  {
    Q_OBJECT
  public:
    ComponentListTest();
    
  private:
    QList<ComponentList::Node::Pointer> componentNodes();
    
    QList<ComponentList::Node::Pointer> createTestActionNodes();
    QList<ComponentList::Node::Pointer> createTestEventNodes();
    QList<ComponentList::Node::Pointer> createTestTrialNodes();
    QList<ComponentList::Node::Pointer> createTestExperimentNodes();
    
    int _numExamples;
    int _numActions;
    
  private slots:
    void initTestCase();

    // iterator methods
    void beginTest();
    void endTest();
    void cleanupTestCase();
    void iteratorTest();
    
    void findTest();
    void removeTest();
    void clearTest();
    void operatorTest();

    void findByNameTest();
    
    void insertTest();
    void cloneTest();
    void nextPreviousNodeTest();
    
    void insertAfterTest();
    void insertBeforeTest();
    
  void appendTest();
    void prependTest();
    
    // here
    void sortComponentListTest();

  };
};

#endif
